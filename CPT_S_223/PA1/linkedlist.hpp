#include "node.hpp"


template<class T1,class T2>
class linked_list
{
private:
    node<T1,T2> *head,*tail;
public:

    linked_list();
    ~linked_list();

    void insertAtFront(T1 cmd, T2 def);
    void print(void);
    int listLeng(void);
    void save(void);
    void printDef(int num, int incremnt);
    void printCmd(int num, int incremnt);
    node<T1, T2>& returnElm(int index);
    bool checkCmd(string cmd);
    void delnode(string usercmd);
};

template<class T1, class T2>
node<T1, T2>& linked_list<T1,T2>::returnElm(int index) {
    node<T1, T2>* temp = this->head;
    for (int i = 0; i < index; i++) {
        temp = temp->nextPtr();
    }
    return *temp;
}

template<class T1, class T2>
void linked_list<T1,T2>::print(void){
    node<T1,T2>* temp = this->head;
    while(temp->nextPtr() != nullptr) {
        cout<<temp->getcmd() << ", " << temp->getdef() << endl;
        temp = temp->nextPtr();
    }

}

template<class T1, class T2>
int linked_list<T1, T2>::listLeng(void) {
    node<T1, T2>* temp = this->head;
    int i = 1;
    for (; temp != nullptr;i++) {
        temp = temp->nextPtr();
    }
    return i;
}


template<class T1,class T2>
linked_list<T1,T2>::linked_list()
{
      head = nullptr;
      tail = nullptr;
}

template<class T1,class T2>
void linked_list<T1,T2>::insertAtFront(T1 cmd, T2 def)
{
    node<T1,T2> *tmp = new node<T1, T2>(cmd, def);

    if(head == nullptr)
    {
        head = tmp;
      }
     else
     {
        tmp->setnextPtr(head);
         head = tmp;
    }


}

template<class T1,class T2>
linked_list<T1, T2>::~linked_list() {
    node<T1, T2>* temp = this->head->nextPtr();
    while (temp != nullptr) {
        delete head;
        head = temp;
        temp = temp->nextPtr();
    }//properly deallocates memeory
    delete head;
}

template<class T1, class T2>
void linked_list<T1, T2>::save(void) {
    ofstream output;
    output.open("commands.csv");
    if (output.is_open()) {
        output << "command, \"description\"" << endl;
        node<T1, T2>* temp = this->head;
        while (temp != nullptr) {
            output << temp->getcmd() << ",\"" << temp->getdef() << "\"";
            if (temp->nextPtr() != nullptr) {
                output << endl;
            }
            temp = temp->nextPtr();
        }
    }
    output.close();//closes file
}

template<class T1, class T2>
void linked_list<T1, T2>::printCmd(int num, int incremnt) {
    node<T1, T2>* temp = this->head;
    int i = 0;
    for (; i != incremnt; i++) {
        temp = temp->nextPtr();
    }
    if (incremnt == i) {
        ++num;
        cout << "Question #"<<num<<". " << temp->getcmd() << "\n";
        --num;
    }
}

template<class T1, class T2>
void linked_list<T1, T2>::printDef(int num,int incremnt) {
    node<T1, T2>* temp = this->head;
    int i = 0;
    for (; i != incremnt; i++) {
        temp = temp->nextPtr();
    }
    if (incremnt == i) {
        cout << "\t"<<num<<". " << temp->getdef() <<"\n";
    }
}

template <class T1, class T2>
bool linked_list<T1, T2>::checkCmd(string cmd) {
    char newcmd[100],curcmd[100];
    strcpy(newcmd, cmd.c_str());
    node<T1, T2>* temp = this->head;
    while (temp != nullptr) {
        strcpy(curcmd, temp->getcmd().c_str());
        if (strcmp(newcmd, curcmd) == 0) {//cmd already in list 
            return true;
        }
        temp = temp->nextPtr();
    }
    return false;
}

template<class T1, class T2>
void linked_list<T1,T2>::delnode(string usercmd) {
    //First find node then do pointer arithmetic

    //cases to rmemeber where to delete
    // 1. empty list ----
    // 2. one node in list
    // 3. delete in middle
    // 4. delete very last node - if nextptr == nullptr 
    //

    char newcmd[100], curcmd[100];
    strcpy(newcmd, usercmd.c_str());
    if (head != nullptr) {
        node<T1, T2>* temp = this->head;
        node<T1, T2>* temp1 = this->head;//leading
        while (1) {
            strcpy(curcmd, temp1->getcmd().c_str());
            if (strcmp(newcmd, curcmd) == 0) {//found cmd
                if (temp1 == head) {
                    temp = temp->nextPtr();
                    head = temp;
                    temp1->setnextPtr(nullptr);
                    delete temp1;
                    break;
                }
                if (temp1 != nullptr&& temp1->nextPtr() != nullptr) {//middle
                    temp->setnextPtr(temp1->nextPtr());
                    temp1->setnextPtr(nullptr);
                    delete temp1;
                    break;
                }
                else if (temp1->nextPtr() == nullptr) {//lastnolde
                    temp->setnextPtr(nullptr);
                    tail = temp;
                    delete temp1;
                    break;
                }
            }
            temp = temp1;
            temp1 = temp1->nextPtr();


        }
    }
    else {
        cout << "You have a empty list" << endl;
    }
}