#pragma once
#include "library.hpp"
#include "data.hpp"

class QueueNode{
public: // Member functions

    QueueNode(Data const& newData);
    ~QueueNode();

    QueueNode* getPNext() const;
    Data* getPData() const;

    void setPNext(QueueNode* newPNext);
    void setPData(Data* newPData);

private:

    Data* pData;    // The memory for Data will need to be allocated on the heap as well!
    QueueNode* pNext;

};

ostream& operator << (ostream& out, QueueNode* node);