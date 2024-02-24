#include <map>
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    // Schema: UserName,Last,First,Email,NumTweets,MostViewedCategory
    string raw_data[5][6] = { {"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
                             {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
                             {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
                             {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
                             {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"} };
    TwitterData* twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }

    std::map<string, TwitterData> mapCase1;

    //Key will be usernames

    for (int i = 0; i < 5; i++) {

        mapCase1[twitter_data[i].getUserName()] = twitter_data[i];
    }

    for (auto x : mapCase1){
        cout <<"\n" << x.first << "->" << x.second.print() << endl;
    }

    for (auto x : mapCase1) {
        if (x.first == "savage1") {//print out entire record
            cout << "Entire record of savage1: " << x.second.print() << endl;
        }
    }

    //now removing his record
    mapCase1.erase("savage1");

    cout<<"\n\nMap without savage1: ";
    for (auto x : mapCase1) {
        cout << "\n" << x.first << "->" << x.second.print() << endl;
    }

    //Scenario #2

    //Key will be email

    std::map<string, TwitterData> mapCase2;

    for (int i = 0; i < 5; i++) {
        mapCase2[twitter_data[i].getEmail()] = twitter_data[i];
    }

    for (auto x : mapCase2) {
        cout << "\n" << x.first << "->" << x.second.print() << endl;
    }

    for (auto x : mapCase2) {
        if (x.first == "kat@gmail.com") {//print out entire record
            cout << "Entire record of kat@gmail.com: " << x.second.print() << endl;
            
        }
    }

    //now removing record
    mapCase2.erase("kat@gmail.com");

    cout << "\n\nMap without kat@gmail.com: ";
    for (auto x : mapCase2) {
        cout << "\n" << x.first << "->" << x.second.print() << endl;
    }

    return 0;
}