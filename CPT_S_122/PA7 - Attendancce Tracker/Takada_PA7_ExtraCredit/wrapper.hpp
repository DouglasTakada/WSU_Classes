#include "list.hpp"

class wrapper {
public:
	wrapper();
	~wrapper();

	void run();
	int menu();

	void importCourse();
	void loadMaster();
	void storeMaster();
	void markAbsences();
	void editAbsences();
	void generateReport();
	void allStudents();
	void skippingStudents();

private:
	list<data> masterList;
};