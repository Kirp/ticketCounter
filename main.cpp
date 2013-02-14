#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <map>
#include <utility>
#include "timestamper.h"
#include "dateStamper.h"

using namespace std;

//reserved for functions
string openTxt(string inp);
void manipulateString();
void ticketEntry();
void showTickets();
void showMinutes();

//global variables here
static bool filePresent;
int minutesDone = 0;
int eventTickets = 0;
int simpleTickets = 0;
static int workMinutes = 480;
bool loopMain = true;
string fileNameTxt;

map <int, string> tickets;

int main() //version 3 revision 1
{
    cout<<"Welcome to session for date :"<<timestamper()<<endl<<endl;
    fileNameTxt = dateStamper();
    string ticknumpre;
    string eventnum;
    int ticknumcnv;


    ifstream readFromTxt(fileNameTxt.c_str()); //check if text file exists and if it does then load it to the map array
    if (!readFromTxt)
    {
        cout<<"No save file detected for today, Creating new file"<<endl;
        filePresent = false;
    } else
    {
        cout<<"Detected save file "<<fileNameTxt<<" loading data to memory";
        filePresent = true;

        while(readFromTxt.good())
        {
            getline(readFromTxt, ticknumpre);
            getline(readFromTxt, eventnum);
            ticknumcnv = atoi(ticknumpre.c_str());
            if(ticknumcnv != 0 && eventnum == "event")
            {
                minutesDone+=5;
                eventTickets++;
            }else
            if (ticknumcnv != 0)
            {
                minutesDone+=4;
                simpleTickets++;
            }
            tickets.insert(std::make_pair<int, string>(ticknumcnv,eventnum));
        }
        readFromTxt.close();
    }


    while(loopMain)
    {
        int selectionz = 0;
        cout<<endl<<endl;
        cout<<"Selection are as follows"<<endl;
        cout<<"0 - Save and exit"<<endl;
        cout<<"1 - Start answering Tickets"<<endl;
        cout<<"2 - Display Tickets"<<endl;
        cout<<"3 - Display minutes Done"<<endl<<endl;
        cout<<"Selection: ";
        cin>>selectionz; cout<<endl;
        switch(selectionz)
        {
            case 0:
                loopMain = false;
                break;
            case 1:
                ticketEntry();
                break;
            case 2:
                showTickets();
                break;
            case 3:
                showMinutes();
                break;
            default:
                cout<<"Invalid Selection. Try again."<<endl;
                break;
        }


    }






    if(tickets.size()>0) //this part saves the ticket to a txt file
    {
        ofstream fileOpen(fileNameTxt.c_str());
        if (fileOpen.is_open())
        {

            for(map<int,string>::iterator ii=tickets.begin(); ii!=tickets.end(); ++ii)
            {
                int holder = (*ii).first;

                if (holder == 0 )
                {
                    continue;
                }

                fileOpen<<holder<<"\n";
                fileOpen<<(*ii).second<<"\n";

            }
            fileOpen.close();
        }

    }




    cout << "end of program holder"<<endl;
    cout<<timestamper();
    return 0;
}


string openTxt(string inp){

    return 0;
}

void manipulateString()
{

}

void showMinutes()
{
    cout<<endl;
    cout<<"---------------------------------------------------------"<<endl;
    if(filePresent==false)
    {
    cout<<"You have answered "<<tickets.size()<<" tickets."<<endl;
    }
    else
    {
    cout<<"You have answered "<<tickets.size()-1<<" tickets."<<endl;
    }
    cout<<"You have done "<<minutesDone<<" minutes of work to reach the quota of "<<workMinutes<<endl;
    cout<<"Simple Tickets: "<<simpleTickets<<endl;
    cout<<"Event Tickets : "<<eventTickets<<endl;
    cout<<"You need to do "<<workMinutes - minutesDone<< " minutes more"<<endl;
    cout<<"---------------------------------------------------------"<<endl;
}

void showTickets()
{
    if (tickets.size()<1)
    {
        cout<<"You have not answered any tickets for today ("<<timestamper()<<")"<<endl;

    }else{
        cout<<"---------------------------------------------------------"<<endl;

    for(map<int,string>::iterator ii=tickets.begin(); ii!=tickets.end(); ++ii)
        {
                int holder = (*ii).first;
                if (holder == 0 )
                {
                    continue;
                }
            cout<<(*ii).first <<": "<<(*ii).second << endl;
        }
        cout<<"---------------------------------------------------------"<<endl;
    }
}

void ticketEntry()
{
    int selection = 1;
    int entrySel;
    string entrySelType;
    cout<<"Welcome to ticket entry mode: "<<endl<<endl;


    while (!selection == 0)
    {
        cout<<"Enter Ticket ID(0 to exit): ";
        cin>>selection;

        if (selection == 0||selection >= 2147483647)
        {
        break;
        }

        cout<<"Enter type(1 - Event ticket, 2 - simple ticket): ";
        cin>>entrySel;
        if (entrySel==1)
        {
            entrySelType = "Event";

        }else entrySelType = "Simple";

        if(entrySelType=="Event")
        {
                minutesDone+=5;
                eventTickets++;
        }else
        {
                minutesDone+=4;
                simpleTickets++;
        }

        tickets.insert(std::pair<int, string>(selection,entrySelType));
        if (filePresent==false)
        {
            cout<<"You have answered a total of "<<tickets.size()<<endl;
        }else cout<<"You have answered a total of "<<tickets.size()-1<<endl;
        timestamper(); cout<<endl;

    }
}
