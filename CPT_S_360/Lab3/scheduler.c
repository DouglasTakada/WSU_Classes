#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>

// Headers as needed

typedef enum {false, true} bool;        // Allows boolean types in C

/* Defines a job struct */
typedef struct Process {
    uint32_t A;                         // A: Arrival time of the process
    uint32_t B;                         // B: Upper Bound of CPU burst times of the given random integer list
    uint32_t C;                         // C: Total CPU time required
    uint32_t M;                         // M: Multiplier of CPU burst time
    uint32_t processID;                 // The process ID given upon input read

    uint8_t status;                     // 0 is unstarted, 1 is ready, 2 is running, 3 is blocked, 4 is terminated

    int32_t finishingTime;              // The cycle when the the process finishes (initially -1)
    uint32_t currentCPUTimeRun;         // The amount of time the process has already run (time in running state)
    uint32_t currentIOBlockedTime;      // The amount of time the process has been IO blocked (time in blocked state)
    uint32_t currentWaitingTime;        // The amount of time spent waiting to be run (time in ready state)

    uint32_t IOBurst;                   // The amount of time until the process finishes being blocked
    uint32_t CPUBurst;                  // The CPU availability of the process (has to be > 1 to move to running)

    int32_t quantum;                    // Used for schedulers that utilise pre-emption

    bool isFirstTimeRunning;            // Used to check when to calculate the CPU burst when it hits running mode

    struct Process* nextInBlockedList;  // A pointer to the next process available in the blocked list
    struct Process* nextInReadyQueue;   // A pointer to the next process available in the ready queue
    struct Process* nextInReadySuspendedQueue; // A pointer to the next process available in the ready suspended queue
} _process;


uint32_t CURRENT_CYCLE = 0;             // The current cycle that each process is on
uint32_t TOTAL_CREATED_PROCESSES = 0;   // The total number of processes constructed
uint32_t TOTAL_STARTED_PROCESSES = 0;   // The total number of processes that have started being simulated
uint32_t TOTAL_FINISHED_PROCESSES = 0;  // The total number of processes that have finished running
uint32_t TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED = 0; // The total cycles in the blocked state

const char* RANDOM_NUMBER_FILE_NAME= "random-numbers";
const uint32_t SEED_VALUE = 200;  // Seed value for reading from file

// Additional variables as needed

char file_input[200];
_process *blocked_head;
_process *ready_head;
_process *suspend_head;

_process *run_cur;

/**
 * Reads a random non-negative integer X from a file with a given line named random-numbers (in the current directory)
 */
uint32_t getRandNumFromFile(uint32_t line, FILE* random_num_file_ptr){
    uint32_t end, loop;
    char str[512];

    rewind(random_num_file_ptr); // reset to be beginning
    for(end = loop = 0;loop<line;++loop){
        if(0==fgets(str, sizeof(str), random_num_file_ptr)){ //include '\n'
            end = 1;  //can't input (EOF)
            break;
        }
    }
    if(!end) {
        return (uint32_t) atoi(str);
    }

    // fail-safe return
    return (uint32_t) 1804289383;
}



/**
 * Reads a random non-negative integer X from a file named random-numbers.
 * Returns the CPU Burst: : 1 + (random-number-from-file % upper_bound)
 */
uint32_t randomOS(uint32_t upper_bound, uint32_t process_indx, FILE* random_num_file_ptr)
{
    char str[20];
    
    uint32_t unsigned_rand_int = (uint32_t) getRandNumFromFile(SEED_VALUE+process_indx, random_num_file_ptr);
    uint32_t returnValue = 1 + (unsigned_rand_int % upper_bound);

    return returnValue;
} 


/********************* SOME PRINTING HELPERS *********************/


/**
 * Prints to standard output the original input
 * process_list is the original processes inputted (in array form)
 */
void printStart(_process process_list[])
{
    printf("The original input was: %i", TOTAL_CREATED_PROCESSES);

    uint32_t i = 0;
    for (; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        printf(" ( %i %i %i %i)", process_list[i].A, process_list[i].B,
               process_list[i].C, process_list[i].M);
    }
    printf("\n");
}

/**
 * Prints to standard output the final output
 * finished_process_list is the terminated processes (in array form) in the order they each finished in.
 */
void printFinal(_process finished_process_list[])
{
    printf("The (sorted) input is: %i", TOTAL_CREATED_PROCESSES);

    uint32_t i = 0;
    for (; i < TOTAL_FINISHED_PROCESSES; ++i)
    {
        printf(" ( %i %i %i %i)", finished_process_list[i].A, finished_process_list[i].B,
               finished_process_list[i].C, finished_process_list[i].M);
    }
    printf("\n");
} // End of the print final function

/**
 * Prints out specifics for each process.
 * @param process_list The original processes inputted, in array form
 */
void printProcessSpecifics(_process process_list[])
{
    uint32_t i = 0;
    printf("\n");
    for (; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        printf("Process %i:\n", process_list[i].processID);
        printf("\t(A,B,C,M) = (%i,%i,%i,%i)\n", process_list[i].A, process_list[i].B,
               process_list[i].C, process_list[i].M);
        printf("\tFinishing time: %i\n", process_list[i].finishingTime);
        printf("\tTurnaround time: %i\n", process_list[i].finishingTime - process_list[i].A);
        printf("\tI/O time: %i\n", process_list[i].currentIOBlockedTime);
        printf("\tWaiting time: %i\n", process_list[i].currentWaitingTime);
        printf("\n");
    }
} // End of the print process specifics function

/**
 * Prints out the summary data
 * process_list The original processes inputted, in array form
 */
void printSummaryData(_process process_list[])
{
    uint32_t i = 0;
    double total_amount_of_time_utilizing_cpu = 0.0;
    double total_amount_of_time_io_blocked = 0.0;
    double total_amount_of_time_spent_waiting = 0.0;
    double total_turnaround_time = 0.0;
    uint32_t final_finishing_time = CURRENT_CYCLE - 1;
    for (; i < TOTAL_CREATED_PROCESSES; ++i)
    {
        total_amount_of_time_utilizing_cpu += process_list[i].currentCPUTimeRun;
        total_amount_of_time_io_blocked += process_list[i].currentIOBlockedTime;
        total_amount_of_time_spent_waiting += process_list[i].currentWaitingTime;
        total_turnaround_time += (process_list[i].finishingTime - process_list[i].A);
    }

    // Calculates the CPU utilisation
    double cpu_util = total_amount_of_time_utilizing_cpu / final_finishing_time;

    // Calculates the IO utilisation
    double io_util = (double) TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED / final_finishing_time;

    // Calculates the throughput (Number of processes over the final finishing time times 100)
    double throughput =  100 * ((double) TOTAL_CREATED_PROCESSES/ final_finishing_time);

    // Calculates the average turnaround time
    double avg_turnaround_time = total_turnaround_time / TOTAL_CREATED_PROCESSES;

    // Calculates the average waiting time
    double avg_waiting_time = total_amount_of_time_spent_waiting / TOTAL_CREATED_PROCESSES;

    printf("Summary Data:\n");
    printf("\tFinishing time: %i\n", CURRENT_CYCLE - 1);
    printf("\tCPU Utilisation: %6f\n", cpu_util);
    printf("\tI/O Utilisation: %6f\n", io_util);
    printf("\tThroughput: %6f processes per hundred cycles\n", throughput);
    printf("\tAverage turnaround time: %6f\n", avg_turnaround_time);
    printf("\tAverage waiting time: %6f\n", avg_waiting_time);
} // End of the print summary data function

//Finds the number of processes in the input based on parenthesis
uint32_t find_proc(void)
{
    char *ptr;
    ptr = file_input;
    if(isdigit(*ptr)){
        return atoi(ptr);
    }

}

//modifies input from makefile to open input file and read and return input
void get_file_in(char** argv)
{
    char path[100];
    
    //Format file path to open file
    getcwd(path,100);
    strcat(path,"/");
    strcat(path,*(argv + 1));

    FILE *fp;
    fp = fopen(path,"r");
    if(fp == NULL)
    {
        perror("Could not find file");
        exit(1);
    } else
    {
        char chunk[200];
        strcpy(file_input,fgets(chunk, 200, fp));
    }
    fclose(fp);
}

//Updates the list with all the given input from the file using strtok_r
void fill_list(_process *list, uint32_t *size){

    char *str;
    str = file_input;

    //Grab first token and check if it is the PID
    char *inner_tok;
    char *outer_tok;
    char *outer_ptr;
    char *inner_ptr;
    outer_tok = strtok_r(str," ",&outer_ptr);

    //Grab the process ID number and assign it to all the processes.
    if(isdigit(*outer_tok)){
        for (int i = 0; i < *size;i++){
            list[i].processID = i;
        }
    }
    //Using strtok_r to find inner and outer parameters.
    //Now search for tokens with '(' and ')' and ' ' within parenthesis
        
    for (int i = 0; i < *size;i++){
        while(*(outer_ptr) == ' '){
            *(outer_ptr++);
        }
        outer_tok = strtok_r(NULL,"()",&outer_ptr);//gets to the beinning of first process grabs everything between ()

        //Now there should only be 4 elements within the parenthesis

        inner_tok = strtok_r(outer_tok," ", &inner_ptr); //Grabs first number
        if(isdigit(*inner_tok)){ //Makes sure it is a number before converting
            list[i].A = atoi(inner_tok);
        } else{
            perror("Cannot convert items within parenthesis into numbers");
            exit(1);
        }
        //Now do the same thing for the other three values

        inner_tok = strtok_r(NULL," ", &inner_ptr); 
        if(isdigit(*inner_tok)){
            list[i].B = atoi(inner_tok);
        } else{
            perror("Cannot convert items within parenthesis into numbers");
            exit(1);
        }

        inner_tok = strtok_r(NULL," ", &inner_ptr); 
        if(isdigit(*inner_tok)){
            list[i].C = atoi(inner_tok);
        } else{
            perror("Cannot convert items within parenthesis into numbers");
            exit(1);
        }

        inner_tok = strtok_r(NULL,")", &inner_ptr); // last delimiter won't be a space
        if(isdigit(*inner_tok)){
            list[i].M = atoi(inner_tok);
        } else{
            perror("Cannot convert items within parenthesis into numbers");
            exit(1);
        }
        
    }
}

//Initalize Process List
void init_list(_process *list){
    for(uint32_t i = 0; i < TOTAL_CREATED_PROCESSES; i++){

        list[i].A = 0;
        list[i].B = 0;
        list[i].C = 0;
        list[i].M = 0;

        list[i].processID = 0;

        list[i].status = 0;

        list[i].finishingTime = -1;
        list[i].currentCPUTimeRun = 0;
        list[i].currentIOBlockedTime = 0;
        list[i].currentWaitingTime = 0;

        list[i].IOBurst = 0;
        list[i].CPUBurst = 0;

        list[i].quantum = 0;

        list[i].isFirstTimeRunning = false;

        list[i].nextInBlockedList = NULL;
        list[i].nextInReadyQueue = NULL;
        list[i].nextInReadySuspendedQueue = NULL;
    }
}

//If there is a process that is not the status terminated return false, otherwise true
bool is_term(_process *list){
    for(int i = 0; i < TOTAL_CREATED_PROCESSES;i++){
        if(list[i].status != 4){
            return false;
        }
    }
    return true;
}

//To check if a process is already running, or if it is already blocked
bool is_status(_process *list, int status_val){
    for(int i = 0; i < TOTAL_CREATED_PROCESSES;i++){
        if(list->status == status_val){
            return false;
        }
    }
    return true;
}

// adds given node to the suspended queue
void add_to_suspended_queue(_process *new_node){
    if(suspend_head == NULL){
            suspend_head = new_node;
        } else{
            new_node->nextInReadySuspendedQueue = suspend_head;
            suspend_head = new_node;
        }
}

// adds given node to the ready queue
void add_to_ready_queue(_process *new_node){
    if(ready_head == NULL){
        ready_head = new_node;
    } else{
        new_node->nextInReadyQueue = ready_head;
        ready_head = new_node;
    }
}

// adds given node to the blocked list
void add_to_blocked_list(_process *new_node){
    if(blocked_head == NULL){
        blocked_head = new_node;
    } else{
        new_node->nextInBlockedList = blocked_head;
        blocked_head = new_node;
    }
}

//Removes the node for the list based on if it is at the end, front or in the middle
void rm_from_blocked_list(){

    _process *cur = blocked_head;
    _process *prev = NULL;
    while(cur != NULL){
        if(cur->IOBurst == 0){
            cur->status = 1;// updating status
            add_to_ready_queue(cur);
            if(prev != NULL){//deleting node out of blocked list since it is now ready
                if(cur->nextInBlockedList == NULL){
                    prev->nextInBlockedList = NULL;//at the end of the list just remove the last node
                    cur = NULL;
                } else if(cur->nextInBlockedList != NULL){//In the middle of the list
                    prev->nextInBlockedList = cur->nextInBlockedList;
                    cur->nextInBlockedList = NULL;
                    cur = prev->nextInBlockedList;
                }
            } else if (prev == NULL){//Removing at the beginning of the list
                if(cur->nextInBlockedList == NULL){
                    blocked_head = NULL;
                    cur = NULL;
                } else if(cur->nextInBlockedList != NULL){
                    blocked_head = cur->nextInBlockedList;
                    cur->nextInBlockedList = NULL;
                    cur = blocked_head;
                }
                
            } else{
                printf("Something went wrong in rm_from_blocked_list");
            }
            

        }else{// If the node should not be removed, move onto the next node
            prev = cur;
            cur = cur->nextInBlockedList;
        }
    }
}

//Removes the last node from the queue and assign it as the running process and update queue
void rm_from_ready_queue(){//Removes last node from queue and saves it to the run_cur ptr
    
    if(ready_head !=NULL){
        _process *cur = ready_head;
        if(cur->nextInReadyQueue != NULL){
            while(cur->nextInReadyQueue->nextInReadyQueue != NULL){
                cur = cur->nextInReadyQueue;
            }
            run_cur = cur->nextInReadyQueue;
            cur->nextInReadyQueue = NULL;

        }else {
            run_cur = cur;
            ready_head = NULL;
        }
        run_cur->status = 2;
    }
}

//Removes the last node from the queue and assign it as the running process and update queue
void rm_from_suspend_queue(){
    if(suspend_head !=NULL){
        _process *cur = suspend_head;
        if(cur->nextInReadySuspendedQueue != NULL){
            while(cur->nextInReadySuspendedQueue->nextInReadySuspendedQueue != NULL){
                cur = cur->nextInReadySuspendedQueue;
            }
            run_cur = cur->nextInReadySuspendedQueue;
            cur->nextInReadySuspendedQueue = NULL;

        }else {
            run_cur = cur;
            suspend_head = NULL;
        }
        run_cur->status = 2;
    }
}

//Returns false if it should be added to the ready queue. Otherwise return true for suspend process
bool add_to_ready_or_suspend(_process *new_node){
    _process *cur = ready_head;
    while(cur!= NULL){
        if(new_node->C > cur->C){
            return true;
        }
        cur = cur->nextInReadyQueue;
    }
    return false;
}

//If these don't work as intended, I think there is a easy workaround.
void update_IO_burst(void){
    _process *cur = blocked_head;
    if(cur != NULL){
        TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED++;
    }
    while(cur != NULL){
        cur->IOBurst--;
        cur->currentIOBlockedTime++;
        cur = cur->nextInBlockedList;
    }
}

//Updates the CPU burst value for current running process and other variables for correct calcualtions in the end
void update_CPU_burst(){
    if(run_cur != NULL){
        run_cur->quantum--;
        run_cur->CPUBurst--;
        if(run_cur->C != 0)
            run_cur->C--;
        run_cur->currentCPUTimeRun++;
    }
}

//Updates the wait value for each process in the ready queue and the suspended queue
void update_wait(void){
    _process *cur = ready_head;
    while(cur != NULL){
        cur->currentWaitingTime++;
        cur = cur->nextInBlockedList;
    }
    cur = suspend_head;
    while(cur != NULL){
        cur->currentWaitingTime++;
        cur = cur->nextInReadySuspendedQueue;
    }
}

//calculate burst times for given process when called
void calculate_burst_times(FILE* f){
    uint32_t tmp  = randomOS(run_cur->B,run_cur->processID,f);
    if(tmp > run_cur->C)
        run_cur->CPUBurst = run_cur->C;
    else{
        run_cur->CPUBurst = tmp;
    }
   run_cur->IOBurst = tmp * run_cur->M;
}

//Function that prints out each process state for ease of debugging
void print_trace(_process *list, int *time){
    printf("Before cycle\t%d:\t",*time);
    for(int i =0; i < TOTAL_CREATED_PROCESSES; i++){
        if(list[i].status == 0){
            printf("unstarted \t");
        } else if (list[i].status ==1){
            printf("ready \t");
        }else if (list[i].status ==2){
            printf("running \t");
        }else if (list[i].status ==3){
            printf("blocked \t");
        }else if (list[i].status ==4){
            printf("terminated \t");
        }
    }
    printf("\n");
}

//Helper function for the sort_on_finished function to swap processes
void swap(_process* xptr,_process* yptr){
    _process tmp  = *xptr;
    *xptr = *yptr;
    *yptr = tmp;
}

//Sorts the list based on finished values in ascending order for correct print output
void sort_on_finished(_process *list){
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t min_idx = 0;
    for(; i < TOTAL_CREATED_PROCESSES; i++){
        min_idx = i; 
        for (j = i + 1; j < TOTAL_CREATED_PROCESSES; j++) 
            if (list[j].finishingTime < list[min_idx].finishingTime) 
                min_idx = j;
        swap(&list[min_idx], &list[i]); 
    }
}

//Resets list of input parameters that are needed to get correct calcualtions for next process algorithms 
void reset_list(_process *list){
    for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
        list[i].status = 0;

        list[i].finishingTime = -1;
        list[i].currentCPUTimeRun = 0;
        list[i].currentIOBlockedTime = 0;
        list[i].currentWaitingTime = 0;

        list[i].IOBurst = 0;
        list[i].CPUBurst = 0;

        list[i].quantum = 2;

        list[i].isFirstTimeRunning = false;

        list[i].nextInBlockedList = NULL;
        list[i].nextInReadyQueue = NULL;
        list[i].nextInReadySuspendedQueue = NULL;
    }
}

//Resets global variables that are needed to get correct calcualtions for next process algorithms 
void reset_globals(){
    CURRENT_CYCLE = 0;
    TOTAL_STARTED_PROCESSES = 0;
    TOTAL_FINISHED_PROCESSES = 0;
    TOTAL_NUMBER_OF_CYCLES_SPENT_BLOCKED = 0;

    blocked_head = NULL;
    ready_head = NULL;
    suspend_head = NULL;
    run_cur = NULL;
}

//Runs First Come First Serve algorthim on the given input processes
void FCFS(_process *list, FILE* f){
    printf("######################### START OF FIRST COME FIRST SERVE #########################\n");
    printStart(list);

    uint32_t arr[TOTAL_CREATED_PROCESSES];
    for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
        arr[i] = list[i].C;
    }

    uint32_t current_time = 0;

    while(!is_term(list)){//while not all processes have terminated, keep running program
        //print_trace(list, &current_time);
        rm_from_blocked_list();
        if(run_cur == NULL){// If there is no process running then grab one from the queue
            rm_from_ready_queue();
        }
        
        for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
            if(list[i].A == current_time){// Process Arrives, set status to ready
                list[i].status = 1;
                add_to_ready_queue(&list[i]);
            }
        }
        if(run_cur != NULL && run_cur->C != 0 && run_cur->CPUBurst == 0 && run_cur->IOBurst != 0){
                add_to_blocked_list(run_cur);
                run_cur->status = 3;
                run_cur = NULL;
        }

        //check each node in blocked list to see if the I/O counter == 0, if it is remove it from this list and add it to ready queue
        rm_from_blocked_list();
        if(run_cur == NULL){// If there is no process running then grab one from the queue
            rm_from_ready_queue();
        }
        
        if (run_cur != NULL && run_cur->C == 0 && run_cur->CPUBurst == 0) {// If process is finished, label it terminated
            run_cur->finishingTime = current_time;
            run_cur->status = 4;
            run_cur = NULL;
            TOTAL_FINISHED_PROCESSES++;
            rm_from_ready_queue();
        }

        

        if(run_cur != NULL){

            if(run_cur->isFirstTimeRunning == false){
                run_cur->isFirstTimeRunning = true;
                TOTAL_STARTED_PROCESSES++;
            }
            if (run_cur->C != 0 && run_cur->CPUBurst == 0 && run_cur->IOBurst == 0){
                calculate_burst_times(f);    
            }
            
        }
        
        update_CPU_burst();
        update_IO_burst();
        update_wait();
        current_time++;
    }
    CURRENT_CYCLE = current_time;
    for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
        list[i].C = arr[i];
    }
    sort_on_finished(list);
    printFinal(list);
    printf("\nThe scheduling algorithm used was First Come First Serve\n");
    printProcessSpecifics(list);
    printSummaryData(list);
    printf("######################### END OF FIRST COME FIRST SERVE #########################\n");
}

//Runs Round Robin algorthim on the given input processes
void RR(_process *list, FILE* f){
    printf("######################### START OF ROUND ROBIN #########################\n");
    printStart(list);

    uint32_t arr[TOTAL_CREATED_PROCESSES];
    for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
        arr[i] = list[i].C;
    }

    uint32_t current_time = 0;
    while(!is_term(list)){//while not all processes have terminated, keep running program
        //print_trace(list, &current_time);
        rm_from_blocked_list();
        if(run_cur == NULL){// If there is no process running then grab one from the queue
            rm_from_ready_queue();
        }
        
        for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
            if(list[i].A == current_time){// Process Arrives, set status to ready
                list[i].status = 1;
                add_to_ready_queue(&list[i]);
            }
        }

        if(run_cur != NULL && run_cur->C != 0 && run_cur->CPUBurst == 0 && run_cur->IOBurst != 0){
                add_to_blocked_list(run_cur);
                run_cur->status = 3;
                run_cur = NULL;
        }

        if(run_cur != NULL && run_cur->C != 0 && run_cur->CPUBurst != 0 && run_cur->quantum ==0){
                add_to_blocked_list(run_cur);
                run_cur->status = 3;
                run_cur = NULL;
                run_cur->quantum = 2;//Reset quantum
        }

        //check each node in blocked list to see if the I/O counter == 0, if it is remove it from this list and add it to ready queue
        rm_from_blocked_list();
        if(run_cur == NULL){// If there is no process running then grab one from the queue
            rm_from_ready_queue();
        }
        
        if (run_cur != NULL && run_cur->C == 0 && run_cur->CPUBurst == 0) {// If process is finished, label it terminated
            run_cur->finishingTime = current_time;
            run_cur->status = 4;
            run_cur = NULL;
            TOTAL_FINISHED_PROCESSES++;
            rm_from_ready_queue();
        }

        

        if(run_cur != NULL){

            if(run_cur->isFirstTimeRunning == false){
                run_cur->isFirstTimeRunning = true;
                TOTAL_STARTED_PROCESSES++;
            }
            if (run_cur->C != 0 && run_cur->CPUBurst == 0 && run_cur->IOBurst == 0){
                calculate_burst_times(f);    
            }
            
        }
        
        update_CPU_burst();
        update_IO_burst();
        update_wait();
        current_time++;
    }


    CURRENT_CYCLE = current_time;
    for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
        list[i].C = arr[i];
    }
    sort_on_finished(list);
    printFinal(list);
    printf("\nThe scheduling algorithm used was Round Robin\n");
    printProcessSpecifics(list);
    printSummaryData(list);
    printf("######################### END OF ROUND ROBIN #########################\n");
}

//Runs Shortest Job First algorthim on the given input processes
void SJF(_process *list, FILE* f){
    printf("######################### START OF SHORTEST JOB FIRST #########################\n");
    printStart(list);

    uint32_t arr[TOTAL_CREATED_PROCESSES];
    for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
        arr[i] = list[i].C;
    }

    uint32_t current_time = 0;

    while(!is_term(list)){//while not all processes have terminated, keep running program
        //print_trace(list, &current_time);
        rm_from_blocked_list();
        if(run_cur == NULL){// If there is no process running then grab one from the queue
            rm_from_ready_queue();
        }
        
        for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
            if(list[i].A == current_time){// Process Arrives, set status to ready
                list[i].status = 1;
                if(add_to_ready_or_suspend(&list[i])){
                    add_to_suspended_queue(&list[i]);
                }else{
                    add_to_ready_queue(&list[i]);
                }
            }
        }
        if(run_cur != NULL && run_cur->C != 0 && run_cur->CPUBurst == 0 && run_cur->IOBurst != 0){
                add_to_blocked_list(run_cur);
                run_cur->status = 3;
                run_cur = NULL;
        }

        //check each node in blocked list to see if the I/O counter == 0, if it is remove it from this list and add it to ready queue
        rm_from_blocked_list();
        if(run_cur == NULL){// If there is no process running then grab one from the queue
            rm_from_ready_queue();
            if(run_cur == NULL){
                rm_from_suspend_queue();
            }
        }
        
        if (run_cur != NULL && run_cur->C == 0 && run_cur->CPUBurst == 0) {// If process is finished, label it terminated
            run_cur->finishingTime = current_time;
            run_cur->status = 4;
            run_cur = NULL;
            TOTAL_FINISHED_PROCESSES++;
            rm_from_ready_queue();
            if(run_cur == NULL){
                rm_from_suspend_queue();
            }
        }

        

        if(run_cur != NULL){

            if(run_cur->isFirstTimeRunning == false){
                run_cur->isFirstTimeRunning = true;
                TOTAL_STARTED_PROCESSES++;
            }
            if (run_cur->C != 0 && run_cur->CPUBurst == 0 && run_cur->IOBurst == 0){
                calculate_burst_times(f);    
            }
            
        }
        
        update_CPU_burst();
        update_IO_burst();
        update_wait();
        current_time++;
    }
    CURRENT_CYCLE = current_time;
    for(int i = 0; i < TOTAL_CREATED_PROCESSES; i++){
        list[i].C = arr[i];
    }
    sort_on_finished(list);

    printFinal(list);
    printf("\nThe scheduling algorithm used was Shortest Job First\n");
    printProcessSpecifics(list);
    printSummaryData(list);
    printf("######################### END OF SHORTEST JOB FIRST #########################\n");
}

/**
 * The magic starts from here
 */
int main(int argc, char *argv[])
{
    //For the sale of debuggin, I need a jank input
    //argv[1] = "sample_io/input/input-3";

    get_file_in(argv); // Read from the file and save command

    uint32_t total_num_of_process = find_proc(); // number of processes to create
    _process process_list[total_num_of_process]; // Creates a container for all processes
    TOTAL_CREATED_PROCESSES = total_num_of_process;
    init_list(process_list); // initialize process list
    // Other variables



    // Write code for your shiny scheduler
    fill_list(process_list, &total_num_of_process);
    //Now time to code the shiny scheduler
    FILE *fp;
    fp = fopen("random-numbers","r");
    if(fp != NULL){
        FCFS(process_list,fp);

        reset_list(process_list);
        reset_globals();

        RR(process_list,fp);

        reset_list(process_list);
        reset_globals();

        SJF(process_list,fp);

    } else{
        perror("Cannot open random-numbers file.");
        exit(1);
    }
    
    fclose(fp);
    return 0;
} 