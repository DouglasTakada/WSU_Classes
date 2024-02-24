#pragma once
#include "BST.hpp"

class DataAnalysis {
public:
	DataAnalysis();
	~DataAnalysis();

	void runAnalysis();

private:
	bool openFile();
	void ReadOneLine(int &units, string &type, string &transaction);
	void treeChoice(int& units, string& type, string& transaction);
	void treeCalculations();
	void trend();
	BST TreeSold;
	BST TreePurchased;
	ifstream csvStream;
};