#include "linkedlist.hpp"
#include "myarr.hpp"
class wrapper{

private:
    linked_list<string, string> cmdlist;
    myArr profiles;

public:
    /*Extract data for game
    read from commands.csv file and put it into linked List: 2 Parameter Template
    read from profiles.csv and insert into array: Insert at front
    */
    wrapper();
    /*Save data
    Save Linked List into commands.csv
    deallocate memory from list
    Save Array into profiles.csv
    deallocate memory from array
    */
    ~wrapper();

    /*Contains logic of game
    1. Game Rules
    2. Play Game
    3. Load Previous Game
    4. Add Command //Check for Duplicates// Ask for another
    5. Remove Command
    6. Exit*/
    void uploadcmd(); //-----

    void uploadprof();//---

    void run();
    /*Displys menu options
    returns valid option number
    */
    int menu(string& name, int& playerPoints);//------
    /*Play Game
        a. number of guesses
        b. score
    */
    void rules();//-------
    
    void game(string& name,int &playerPoints); //


    void addcmd();//From player

    void removecmd();//From player
};