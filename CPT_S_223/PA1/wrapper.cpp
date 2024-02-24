#include "wrapper.hpp"

wrapper::wrapper(){
	
}

wrapper::~wrapper(){
	
}

void wrapper::uploadcmd(void){
	ifstream input;
	char chunk[200] = "";
	//input.open("wsl$\\Ubuntu\\home\\douglastakada\\PA1\\cmakePA1\\commands.csv");
	//input.open("commands.csv.c_str()");
	input.open("commands.csv");
	string cmd = "", def = "";
	
	if(input.is_open()){
		input.getline(chunk, 200);//Skips header
		while(input){
			input.getline(chunk, 200, ',');
			cmd = chunk;
			input.getline(chunk, 200, '\"');
			input.getline(chunk, 200, '\"');
			def = chunk;
			input.getline(chunk, 200, '\n');
			if (cmd != "" && def != "") {
				cmdlist.insertAtFront(cmd, def);
			}
		}
	} else{
		cout<<"Could not open commands.csv file"<<endl;
		cin.get();
	}
	input.close();//closes file
}

void wrapper::uploadprof() {
	ifstream input;
	char chunk[50] = "";
	//input.open("wsl$\\Ubuntu\\home\\douglastakada\\PA1\\cmakePA1\\commands.csv");
	//input.open("commands.csv.c_str()");
	input.open("profiles.csv");
	string name = "";
	int points = 0;

	if (input.is_open()) {
		input.getline(chunk, 200);//Skips header
		while (input) {
			input.getline(chunk, 200, ',');
			name = chunk;
			input.getline(chunk, 200, '\n');
			points = atoi(chunk);
			if (name != "") {
				profiles.add(name, points);
			}
		}
	}
	else {
		cout << "Could not open commands.csv file" << endl;
		cin.get();
	}
	input.close();//closes file
}

void wrapper::run(){
	uploadcmd();
	uploadprof();
	int input = 0, index = 0;
	string name;
	int playerPoints = 0;
	string username = "";
	while(input !=6){
		//This is a string of special characters that translate to clear the screen command. Found it on stack overflow
		input = menu(name, playerPoints);
		switch(input){
			case 1:
				rules();
				cout << "\033[2J\033[1;1H";
			break;
			case 2:
				game(name,playerPoints);
				cout << "\033[2J\033[1;1H";
			break;
			case 3:
				game(name, playerPoints);
				cout << "\033[2J\033[1;1H";
			break;
			case 4:
				addcmd();
				cout << "\033[2J\033[1;1H";
			break;
			case 5:
				removecmd();
				cout << "\033[2J\033[1;1H";
			break;
			case 6:
				//Save stuff
				cmdlist.save();
				profiles.saveProf();
				cout << "\033[2J\033[1;1H";
			break;
		}
	}
}



void wrapper::rules(){
	int dumm = 0;
	cout<< "Welcome to the Linux Command Guessing Game!\n Happy to have you here fella!"<<" Here are the rules:\n\t1. choose 1 of the 3 multiple choice definitions that\n\t"
	<<"fit the Linux command the most accurately.\n\t2.Try to get as many points as possilbe!\n\t\tGood Luck\n\n\t\t Enter 1 to Continue"<<endl;
	cin >> dumm;
}

int wrapper::menu(string& name, int& playerPoints){
	int choice = 0;
	string disp = "\t\tSeclect one of the options below!\n\t 1. Game Rules\n\t 2. Play Game\n\t 3. Load Previous Game\n\t 4. Add Command\n\t 5. Remove Command\n\t 6. Exit";
	cout<<disp<<endl;
	cin >> choice;
	while(choice >6 || choice <1) {
		cout<<"You input a invalid option... Try again"<<disp<<endl;
		cin>>choice;
	}
	if (choice == 2 || choice == 3) {//ask for name and see if it is in list
		cout << "Enter your name: ";
		cin >> name;
		if (!profiles.searchFor(name, playerPoints)) {
			profiles.add(name, playerPoints);
			cout << "We could not find your name in our system.\n your profile was created with the name: " << name << endl;
		}
	}
	return choice;
}

void wrapper::game(string& name, int& playerPoints){
	int numQuest = 0;
	cout << "How many questions would you like to be asked?\nPick a range between 5 - 30" << endl;
	cin >> numQuest;
	while (numQuest < 5 || numQuest > 30) {
		cout << "Pick a range between 5 - 30" << endl;
		cin >> numQuest;
	}
	int lenList = cmdlist.listLeng();
	int arints[3];
	int* freqAr1 = (int*)malloc(sizeof(int) * lenList);
	int randNum = 0, dummyVar = 1;
	node <string, string> nodes[3];
	node <string, string> temp;
	int checker = 0,num = 0;
	int  choiceNum = 0, ansNum = 0, tempint = 0, trackatleastone = 0, ansind = 0;

	for (int w = 0; w < lenList - 1; w++) {//initialize frequency array only once
		freqAr1[w] = 0;
	}

	for (int j = 0; j < numQuest; j++) {//for the number of questions
		tempint = -1;

		for (int w = 0; w < 1;) {// check if there is atleast one index in arint that is not taken
			for (int i = 0; i < 3; i++) {//initialize int array
				arints[i] = -1;
			}
			for (int k = 0; k < 3;) {//while arints does not have duplicates winthin the array keep assigning numbers
				randNum = (rand() % (lenList));
				if (randNum != arints[0] && randNum != arints[1] && randNum != arints[2]) {
					arints[k] = randNum;
					k++;
				}
			}
			for (int w1 = 0; w1 < 3; w1++) {
				if (freqAr1[arints[w1]] != 1) {//if the number in the arint is in the freq ar increment by 1
					w++;
				}
			}
			//this will kepp repeating until there is atleast one number in the arint that is not in the freq ar
		}
			

		/*while (arints[0] == -1 || arints[1] == -1 || arints[2] == -1) {

			//for (int i = 0; i < 3; i++) {//unneccessary?

				randNum = (rand() % (lenList));

				if (freqAr1[randNum] != 1 || randNum != arints[1] || randNum != arints[2] || randNun = arints[3]) {//
					for (int j = 0; j < 3; j++) {
						if (freqAr1[randNum] != 1 && arints[j] == -1) {//set it equal to randnum
							freqAr1[randNum] = 1;
							arints[j] = randNum;
						}
					}
				}
			//}
		}*/
		ansind = (rand() % (3));
		ansNum = arints[ansind];
		while (freqAr1[ansNum] == 1) {
			ansind = (rand() % (3));
			ansNum = arints[ansind];
		}
		freqAr1[ansNum] = 1;//when it break out of while loop that means it found one that has not been used yet. now make it so next one can't use this one

		cout << cmdlist.returnElm(ansNum).getcmd() << endl;
		for (int i = 1; i < 4; i++) {

			cout << i << ". " << cmdlist.returnElm(arints[i - 1]).getdef() << endl;;
		}
		cout << "You have: " << playerPoints << " Points\nYour Answer : ";
		cin >> num;



		if (--num == ansind) {
			cout << "Congratulations! you got it right! +1\n";
			++playerPoints;

		}
		else {
			
			cout << "Incorrect :( -1\n";
			--playerPoints;
		}
		cout << cmdlist.returnElm(ansNum).getcmd() << " - "
			<< cmdlist.returnElm(ansNum).getdef() << "\nCurrent Score: " << playerPoints << "\n";
		cout << "Enter 1 to continue" << endl;
		cin >> num;
	}
	cout << "Final Score: " << playerPoints <<endl;
	cout << "Enter 1 to continue" << endl;
	cin >> num;
	//Once game is over save new points for the name=
	profiles.modAt(name, playerPoints);

}

void wrapper::addcmd() {
	//ask for command - search for command in list if it exits then tell them to exit or type another command
	//ask for command definition
	//add into linked list
	string usercmd, usercmd1, userdef;
	int x = 0;
	cout << "Enter the Command name you want to add: ";
	cin.ignore(256, '\n');
	getline(cin, usercmd);
	usercmd1 = usercmd;
	while (cmdlist.checkCmd(usercmd1)) {//If it is in list
		cout << "The command name you entered already exists\n\n\t";
		cout << "1. Enter another command\n2. Exit.\n";
		cin >> x;
		if (x == 2) {
			break;
		}
		else {
			cout << "Enter the Command name you want to add: ";
			getline(cin, usercmd);
			usercmd1 = usercmd;
			cin.ignore(256, '\n');
		}
	}
	if (x != 2) {
	cout << "Enter the command defintion: ";
	getline(cin, userdef);
	cmdlist.insertAtFront(usercmd1, userdef);
	cout << "Your command has been inserted at the front" << endl;
	cout << "Enter 1 to continue" << endl;
	cin >> x;
	}

}
void wrapper::removecmd(){
	//ask for command - search for command in list if it does NOT exits then tell them to exit or type another command
	//delete command from linked list
	string usercmd = "", userdef = "";
	int x = 0;
	cout << "Enter the Command name you want to remove: ";
	cin >> usercmd;
	if (cmdlist.checkCmd(usercmd)) {//If it is in list
		cout << "The command name and definition in the list are you sure you want to delete it?\n\n\t";
		cout << "1. Yes\n\t2. No, Exit.\n";
		cin >> x;
		if(x == 1){
			cmdlist.delnode(usercmd);
			cout << "Your command has been deleted from the list" << endl;
		}
	}
	else {
		cout << "The command name and definition is not in the list\n\n\t";
		cout << "1. Enter another command\n\t2. Exit.\n";
		cin >> x;
		if (x == 1) {
			removecmd();
		}
	}
}