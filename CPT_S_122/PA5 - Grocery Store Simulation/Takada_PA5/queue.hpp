#pragma once
#include "library.hpp"
#include "queuenode.hpp"

class Queue{
public: // Member functions

    Queue(QueueNode* newPHead = nullptr, QueueNode* newPTail = nullptr);
    ~Queue();

    QueueNode* getPHead() const;
    QueueNode* getPTail() const;

    void setPHead(QueueNode* newPHead);
    void setPTail(QueueNode* newPTail);

    bool isEmpty() const;

    void printQueue();

    int findTotalTime(int& serviceTime);

    bool enqueue(Data const& newData);
    int dequeue();

private:

    QueueNode* pHead;
    QueueNode* pTail;

};