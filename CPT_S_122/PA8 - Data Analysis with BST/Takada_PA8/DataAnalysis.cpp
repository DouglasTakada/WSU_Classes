#include "DataAnalysis.hpp"
//Constructor
DataAnalysis::DataAnalysis() {
	//cout << "Inside DataAnalysis Constructor" << endl;
}
//Destructor
DataAnalysis::~DataAnalysis() {
	//cout << "Inside DataAnalysis Destructor" << endl;
}
//Main driver of program, calls all the private member functions
// - openFile
// - treeCalculations
// - trend
void DataAnalysis::runAnalysis() {
	cout << "Opening Data File..." << endl;
	if (openFile()) {
		cout << "File was successfully opened" << endl;
	}
	else {
		cout << "File could not be opened" << endl;
	}
	treeCalculations();
	trend();
}

//Function that opens the desired file for it to be read from
//returns a boolean to see if it was successful in opening or not
//Opens file stream through the member function within this class
bool DataAnalysis::openFile() {
	csvStream.open("data.csv",ios::in);
	return csvStream.is_open();
}
//Looks inside the file and reads one line from the file and parses it
//so they are orgonized in units, product, and the transaction type
//uses the csvStream member variable
void DataAnalysis::ReadOneLine(int& units, string& type, string& transaction) {
	char temp[50];
	csvStream.getline(temp, 50, ',');
	units = atoi(temp);
	csvStream.getline(temp, 50, ',');
	type = temp;
	csvStream.getline(temp, 50, '\n');
	transaction = temp;
}
//Function that checks for invalid data from the file and inserts the new data
//into the proper tree
void DataAnalysis::treeChoice(int& units, string& type, string& transaction) {
	if (units != 0) {//Invalid data

		if (transaction == "Purchased") {//put it in purchased tree
			TreePurchased.insert(type, units);
		}
		else {//put it in sold tree
			TreeSold.insert(type, units);
		}
	}
}
//function that is called from runAnalysis that calls ReadOneLine until it reaches the end
// of the file. This function also calls the inOrderTraversal functions to print both the 
// Purchased and sold tree data
void DataAnalysis::treeCalculations() {
	int units = 0;
	string type = "", transaction = "";
	ReadOneLine(units, type, transaction);//Gets rid of the title
	while (csvStream) {//While not at end of file
		ReadOneLine(units,type,transaction);
		treeChoice(units, type, transaction);
	}
	cout << "\nPurchased tree: " << endl;
	TreePurchased.inOrderTraversal();
	cout << "\nSold tree: " << endl;
	TreeSold.inOrderTraversal();
}
//Last function that is called from runAnalysis. Prints out the analysis in a format
//for the user to easily read including the product types that were sold the most and least
//as well as the products that were bough the most with the number of units and the product name
void DataAnalysis::trend() {
	cout << "\nThe product that type and number of units that sold the most" << endl;
	cout << "product Name: ";
	this->TreeSold.findLargest().printData();
	cout << "Number of Units sold: " << TreeSold.findLargest().getUnits() << endl;
	cout << "The product that type and number of units that sold the least: " << endl;
	cout << "product Name: ";
	this->TreeSold.findSmallest().printData();
	cout << "Number of Units sold: " << TreeSold.findSmallest().getUnits() << endl;
	cout << "The product that type and number of units that were purchased the most: "<< endl;
	cout << "product Name: ";
	this->TreePurchased.findLargest().printData();
	cout << "Number of Units sold: " << TreePurchased.findLargest().getUnits() << endl;
	cout << "The product that type and number of units that were purchased the least: "<< endl;
	cout << "product Name: ";
	this->TreePurchased.findSmallest().printData();
	cout << "Number of Units sold: " << TreePurchased.findSmallest().getUnits() << endl;
}