#include "data.hpp"
#include "library.hpp"

//Constructor
Data::Data(int newCostomerNumber, int newServiceTime, int newTotalTime) {
    this->customerNumber = newCostomerNumber;
    this->serviceTime = newServiceTime;
    this->totalTime = newTotalTime;
}

Data::Data(const Data& newData) {
    this->customerNumber = newData.customerNumber;
    this->serviceTime = newData.serviceTime;
    this->totalTime = newData.totalTime;
}

//Destructor
Data::~Data() {}

//Getters
int Data::getCustomerNumber() const {
    return customerNumber;
}

int Data::getServiceTime() const {
    return serviceTime;
}

int Data::getTotalTime() const {
    return totalTime;
}

//Setters
void Data::setCustomerNumber(int newCustomerNumber) {
    this->customerNumber = newCustomerNumber;
}
void Data::setServiceTime(int newServiceTime) {
    this->serviceTime = newServiceTime;
}
void Data::setTotalTime(int newTotalTime) {
    this->totalTime = newTotalTime;
}