#include <iostream>

//takes array of babies and size of array
void Sort_two_types (std::string arr[], int n){
    //Create exactly two pointers
    std::string *start = &arr[0];
    std::string *end= &arr[n-1];

    //while the two pointers have not overlapped check conditions
    while(start < end){
        
        //If there is a purple hair baby at the pointer at front of list and
        //there is a brown hair baby at the end of the list, swap them
        if(*(start) == "Purple" && *(end) == "Brown"){
            //swap
            std::swap(*(start),*(end));
            start++;end--;
        }

        //If there is a brown baby at the front of the list leave it alone and move onto next baby to the right of it
        if(*(start) == "Brown"){
            start++;
        }

        //If there is a purple baby at the end of the list leave it alone and move onto the next baby to the left of it
        if(*(end) == "Purple"){
            end--;
        }
    }
}

//takes array of babies and size of array
void Sort_three_types (std::string arr[], int n){

    //creates exactly three pointers
    std::string *start = &arr[0];
    std::string *middle= &arr[1];
    std::string *end= &arr[n-1];

    //while the middle pointer has not overlapped with the end pointer continue
    while(middle < end){

        //The swapping conditions are all "if else if" because if a baby has already been swapped,
        //A babby will be in its proper place so there is no need to swap until the index of each
        //pointer is updated.

        //If there is a purple hair baby at the pointer in the beginning of the list 
        //and not a purple hair baby at the pointer to the middle of the list then swap them
        if(*(start) == "Purple" && *(middle) != "Purple"){
            //swap
            std::swap(*(start),*(middle));

        //If there is a purple hair baby at the pointer in the end of the list 
        //and not a purple hair baby at the pointer to the middle of the list then swap them
        } else if(*(end) == "Purple" && *(middle) != "Purple"){
            //swap
            std::swap(*(end),*(middle));
        }

        //If there is a brown hair baby at the pointer in the middle of the list 
        //and not a brown hair baby at the pointer to the start of the list then swap them
        if(*(middle) == "Brown" && *(start) != "Brown"){
            //swap
            std::swap(*(middle),*(start));

        //If there is a brown hair baby at the pointer at the end of the list 
        //and not a brown hair baby at the pointer to the start of the list then swap them
        } else if(*(end) == "Brown" && *(start) != "Brown"){
            //swap
            std::swap(*(end),*(start));
        }

        //If there is a black hair baby at the pointer in the start of the list 
        //and not a black hair baby at the pointer to the end of the list then swap them
        if(*(start) == "Black" && *(end) != "Black"){
            //swap
            std::swap(*(start),*(end));

        //If there is a black hair baby at the pointer in the middle of the list 
        //and not a black hair baby at the pointer to the end of the list then swap them
        } else if(*(middle) == "Black" && *(end) != "Black"){
            //swap
            std::swap(*(middle),*(end));
        }

        //Updating pointers

        //if the pointer at the start of the list is pointing at a brown hair baby,
        //leave it where it is and move onto the next baby to the right of the brown hair baby
        if(*(start) == "Brown"){
            start++;
        }

        //if the pointer at the middle of the list is pointing at a brown hair baby,
        // or a purple hair baby leave it where it is and move onto the next baby
        //to the right of the purple or brown hair baby
        if(*(middle) == "Brown" || *(middle) == "Purple"){
            middle++;
        }

        //if the pointer at the end of the list is pointing at a Black hair baby,
        //leave it where it is and move onto the next baby to the left of the black hair baby
        if(*(end) == "Black"){
            end--;
        }
    }
}

int main(void){
    std::string arr [] = {"Brown","Purple","Brown","Purple","Brown","Purple","Brown","Purple","Brown","Purple"};
    int n = sizeof(arr)/sizeof(arr[0]);
    std::cout<<n<<std::endl;
    for(int i =0; i < n;i++){
        std::cout<< arr[i];
    }
    std::cout<<std::endl;

    Sort_two_types(arr,n);
    
    for(int i =0; i < n;i++){
        std::cout<< arr[i];
    }
    std::cout<<std::endl;

    std::string arr2 [] = {"Brown","Purple","Black","Brown","Purple","Black","Brown","Purple","Black","Brown","Purple","Black"};
    int n2 = sizeof(arr2)/sizeof(arr2[0]);
    std::cout<<n<<std::endl;
    for(int i =0 ; i < n2; i++){
        std::cout<< arr2[i];
    }
    std::cout<<std::endl;

    Sort_three_types(arr2,n2);
    
    for(int i =0; i < n2;i++){
        std::cout<< arr2[i];
    }
    std::cout<<std::endl;
}