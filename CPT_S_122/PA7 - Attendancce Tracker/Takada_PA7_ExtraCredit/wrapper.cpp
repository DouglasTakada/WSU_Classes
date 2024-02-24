#include "wrapper.hpp"

wrapper::wrapper() {

}
wrapper::~wrapper() {

}

void wrapper::run() {
	int option = 0;
	option = menu();

	while (option != 7) {
		switch (option) {
		case 1:
			importCourse();
			option = menu();
			break;
		case 2:
			loadMaster();
			option = menu();
			break;
		case 3:
			storeMaster();
			option = menu();
			break;
		case 4:
			markAbsences();
			option = menu();
			break;
		case 5:
			editAbsences();
			option = menu();
			break;
		case 6:
			generateReport();
			option = menu();
			break;
		case 7:
			//Never executes
			option = menu();
			break;
		}
	}
}

int wrapper::menu() {
	int choice = 0;
	cout << "\t1. Import Course List\n\t" <<
		"2. Load Master List\n\t3. Store Master List\n\t" <<
		"4. Mark absences\n\t5. Edit Absences\n\t" <<
		"6. Generate Report\n\t7. Exit\n\n\t>";
	cin >> choice;
	while (choice > 7 || choice < 1) {
		cout << "\n\tInvalid option chooose again" << endl;
		cout << "\t1. Import Course List\n\t" <<
			"2. Load Master List\n\t3. Store Master List\n\t" <<
			"4. Mark absences\n\t5. Edit Absences\n\t" <<
			"6. Generate Report\n\t7. Exit\n\n\t>";
		cin >> choice;
	}
	return choice;
}

void wrapper::importCourse() {
	ifstream input;
	char chunk[75] = "";
	data newStud;
	input.open("classList.csv");
	if (input.is_open()) {
		input.getline(chunk, 75);// gets the header of file
		while (input) {
			input.getline(chunk, 75, ',');
			newStud.setRecNum(atoi(chunk));
			input.getline(chunk, 75, ',');
			newStud.setIDNum(atoi(chunk));
			input.getline(chunk, 75, ',');
			newStud.setLast(chunk);
			input.getline(chunk, 75, ',');
			newStud.setFirst(chunk);
			input.getline(chunk, 75, ',');
			newStud.setEmail(chunk);
			input.getline(chunk, 75, ',');
			newStud.setUnits(chunk);
			input.getline(chunk, 75, ',');
			newStud.setProgram(chunk);
			input.getline(chunk, 75, '\n');
			newStud.setLevel(chunk);
			masterList.insertFront(newStud);
		}
		node<data>* temp = masterList.getPHead();
		masterList.setPHead(temp->getNxtPtr());
		delete temp;//deletes first node becasue it creates a extra node
		cout << "Successfully stored data from"<<
			" classList.csv file into the Master List!\n";
		input.close();
	}
	else {
		cout << "could not open classList.csv file :[\n" << endl;
	}
}
void wrapper::loadMaster() {
	ifstream input;
	char chunk[75] = "";
	data newStud;
	input.open("master.txt");
	if (input.is_open()) {
		while (input) {
			input.getline(chunk, 75, ',');
			newStud.setRecNum(atoi(chunk));
			input.getline(chunk, 75, ',');
			newStud.setIDNum(atoi(chunk));
			input.getline(chunk, 75, ',');
			newStud.setLast(chunk);
			input.getline(chunk, 75, ',');
			newStud.setFirst(chunk);
			input.getline(chunk, 75, ',');
			newStud.setEmail(chunk);
			input.getline(chunk, 75, ',');
			newStud.setUnits(chunk);
			input.getline(chunk, 75, ',');
			newStud.setProgram(chunk);
			input.getline(chunk, 75, '\n');
			newStud.setLevel(chunk);
			masterList.insertFront(newStud);
		}
		node<data>* temp = masterList.getPHead();
		masterList.setPHead(temp->getNxtPtr());
		delete temp;//deletes first node becasue it creates a extra node
		cout << "Successfully stored data from" <<
			" master.txt file into the Master List!\n";
		input.close();
	}
	else {
		cout << "could not open master.txt file to read :[\n" << endl;
	}
}

void wrapper::storeMaster() {
	ofstream output;
	output.open("master.txt");
	node<data>* temp = masterList.getPHead();
	if (output.is_open()) {
		while (temp != nullptr) {
			output << temp->getData();
			temp = temp->getNxtPtr();
		}
		output.close();
		cout << "Successfully stored data from" <<
			" the Master List into the master.txt file!\n";
	}
	else {
		cout << "could not open master.txt file to write:[\n" << endl;
	}
}

void wrapper::markAbsences() {
	node<data>* temp = masterList.getPHead();
	int option = 0;
	while (temp != nullptr) {
		cout << "Was " << temp->getData()->getLast() << ", " << temp->getData()->getFirst()
			<< " absent?\n\t1. Yes\n\t2. No\n\n\t>";
		cin >> option;
		while (option != 1 && option!= 2) {
			cout << "\n\tYou entered a invalid option try again" << endl;
			cout << "Was " << temp->getData()->getLast() << ", " << temp->getData()->getFirst()
				<< "absent?\n\t1. Yes\n\t2. No\n\n\t>";
			cin >> option;
		}
		if (option ==1) {//mark absent
			cout << "this student was marked absecent on: ";
			temp->getData()->incrementAbscences();
		}
		else {
			cout << "This student was not marked absecent!"<<endl;
		}
		temp = temp->getNxtPtr();
	}
}
void wrapper::editAbsences() {
	node<data>* tempStud = this->masterList.getPHead();//temp node to interate through list
	stack tempStack;//temp stack to put the reccently popped
	//values into from the original stack

	//Using SID find student
	int SID = 0;
	string newDate = "";
	cout << "enter the ID of the student's record you would like to edit:\n\n\t>";
	cin >> SID;
	while (tempStud != nullptr && tempStud->getData()->getIDNum() != SID) {
		tempStud = tempStud->getNxtPtr();
	}
	if (tempStud->getData()->getIDNum() == SID) {
		while (!tempStud->getData()->getDateOfAbsenses()->isEmpty()) {//check the date and ask
			newDate = tempStud->getData()->getDateOfAbsenses()->peak();
			cout << "was " << tempStud->getData()->getLast() << ", " <<
				tempStud->getData()->getFirst() << " absent on " <<
				newDate << "?" << endl;
			cout << " absent?\n\t1. Yes\n\t2. No\n\n\t>";
			cin >> SID;
			while (SID != 1 && SID != 2) {
				cout << "was " << tempStud->getData()->getLast() << ", " <<
					tempStud->getData()->getFirst() << " absent on " <<
					newDate << "?" << endl;
				cout << " absent?\n\t1. Yes\n\t2. No\n\n\t>";
				cin >> SID;
			}

			if (SID ==1) {
				tempStack.push(newDate);//Dont decrement the number of absences
				//just push to other stack
			}
			else {
				tempStud->getData()->decrementAbscences();
			}
			tempStud->getData()->getDateOfAbsenses()->pop();
		}//Now I need to put the dates back in the right order so I'll just move the dates
		//back into the OG stack
		while (!tempStack.isEmpty()) {
			newDate = tempStack.peak();
			tempStud->getData()->getDateOfAbsenses()->push(newDate);
			tempStack.pop();
		}
	}
	else {
		cout << "Sorry, we could not find a student with that Student ID number" << endl;
	}

}
void wrapper::generateReport() {
	int option = 0;
	cout << "what kind of report would you like to generate?" <<
		"\n\t1. Report of All students\n\t2. Report of students" <<
		" with a certain number of absences\n\n\t>";
	cin >> option;
	while (option != 1 && option != 2) {
		system("cls");
		cout << "\n\tInvalid option try again.\n" << endl;
		cout << "What kind of report would you like to generate?" <<
			"\n\t1. Report of All students\n\t2. Report of students" <<
			" with a certain number of absences\n\n\t>";
		cin >> option;
	}
	if (option == 2) {
		skippingStudents();
	}
	else {
		allStudents();
	}

}

void wrapper::allStudents() {
	node<data>* tempStud = this->masterList.getPHead();
	while (tempStud != nullptr) {
		if (tempStud->getData()->getNumAbscences()>0) {
			cout << "\n\t" << tempStud->getData()->getLast() << ", " << tempStud->getData()->getFirst()
				<< " most reccent absence was on " << tempStud->getData()->getDateOfAbsenses()->peak()
				<< endl;
		}
		else {
			cout << "\n\t" << tempStud->getData()->getLast() << ", " << tempStud->getData()->getFirst()
				<< " has not been absent!!!"<< endl;
		}
		tempStud = tempStud->getNxtPtr();
	}
}
void wrapper::skippingStudents() {
	node<data>* tempStud = this->masterList.getPHead();
	int min = 0;
	cout << "The students with how many absences would you like to be displayed?" << endl;
	cin >> min;
	while (tempStud != nullptr) {
		if (tempStud->getData()->getNumAbscences()>= min) {
			cout << "\n\t" << tempStud->getData()->getLast() << ", " << tempStud->getData()->getFirst()
				<< " most reccent absence was on " << tempStud->getData()->getDateOfAbsenses()->peak()
				<< endl;
		}
		tempStud = tempStud->getNxtPtr();
	}
}