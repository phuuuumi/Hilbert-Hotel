#include "user_management/Register.h"
#include "user_management/LOGIN.h"
#include "service_management/search.h"


user customer;

void clearScreen();
string Make_Lower(string);

int main(void){
    bool exit = false;
    // Welcome_hotel_starter();

    cout << "-Welcome to Hilbert-Hotel-\n";
    cout << "1.Register\n";
    cout << "2.Login\n";
    cout << "3.Exit\n";
    cout << "Please choose your option(1/2/3) : ";
    string user_status;
    getline(cin,user_status);

    while(true){
        //REGISTER
        if(user_status=="1" || Make_Lower(user_status)=="register"){
            Register();
            login(customer);
            break;
        }

        //LOG-IN
        else if(user_status=="2" || Make_Lower(user_status)=="login"){
            clearScreen();
            login(customer);
            break;
        }
        else if(user_status=="3" || Make_Lower(user_status)=="exit"){
            cout << "Exiting the program." << endl;
            return 0;
        }
        else{

        cout << "ERROR . . . Your Answer is not Correct\n";
        cout << "Please choose your option(1/2/3) : ";
        getline(cin,user_status);
        }  
    }

    // Services Section
    clearScreen();
    cout << "Log in success.\n";
    cout << "Hello " << customer.username << ". Welcome to Hilbert Hotel. \n";
    

    while(true){
        cout << "1.Check in and Check out\n";
        cout << "2.Show user data and history.\n";
        cout << "3.Exit\n";
        cout << "Please choose your option(1/2/3) : ";
        getline(cin,user_status);
        if(user_status=="1"){
            /*cout << "coming soon...\n";
            while(true){
                if(Make_Lower(user_status) == "yes") break;
                else getline(cin,user_status);
            }*/
           
            cout << "------------------------" << endl;
            cout << "WELCOME TO HILBERT HOTEL" << endl; //show in screen
            cout << "------------------------" << endl;

            checkin(exit);  /*check in and checkout system for customer*/
            checkout(exit);

            if (exit) {
                cout << "Exiting the program." << endl;
                return 0; // Exit the program if user wants to exit
            }

            clearScreen();

            cout << "Your check-in date is " << check_in.day << "/" << check_in.month << "/" << check_in.years << endl;
            cout << "Your check-out date is " << check_out.day << "/" << check_out.month << "/" << check_out.years << endl;
            cout << endl;

            cout << "This is a room that Avaliable" << endl;

            RoomInfo info[20];
            int roomCount = readfile_pasteinfo(info);
             headerinformation();

            for (int i = 0; i < roomCount; i++){  //show all room that avaliable from screen.
                if (info[i].getTypePtr() != nullptr &&
                    isRoomAvailable(info[i].getNumber(), check_in, check_out)){
            
                    cout <<"|"<< info[i].getNumber() << " | "
                    << changetype(info[i].getTypePtr()->getType()) << " | "
                    << info[i].getTypePtr()->getPrice() << " Baths" <<"|"<< endl;
                }
            }
    cout << "-------------------------------------------------------" << endl;

    choose_room(); //for user to input room.

    cout << "1.Go back\n";
    cout << "2.Exit\n";
    user_status = "";
    cout << "Do you want to go back? (1/2) : ";
    getline(cin,user_status);
    while(true){
        if(Make_Lower(user_status) == "1") break;
        else if(Make_Lower(user_status) == "2") {
            user_status = "3";
            cout << "Exiting the program." << endl;
            return 0;
        }
        else {
            cout << "ERROR . . . Your Answer is not Correct\n";
            cout << "Do you want to go back? (1/2) : ";
            getline(cin,user_status);
        }
    }

        }

        //LOG-IN
        else if(user_status=="2"){
            clearScreen();
            customer.showuserdata();
            cout << "1.Go back\n";
            cout << "2.Exit\n";
            user_status="";
            cout << "Do you want to go back? (1/2) : ";
            getline(cin,user_status);
            while(true){
                if(Make_Lower(user_status) == "1") break;
                else if(Make_Lower(user_status) == "2") {
                    user_status = "3";
                    cout << "Exiting the program." << endl;
                    return 0;
                }
                else {
                    cout << "ERROR . . . Your Answer is not Correct\n";
                    cout << "Do you want to go back? (1/2) : ";
                    getline(cin,user_status);
                }
            }
        }

        else if(user_status=="3" || Make_Lower(user_status)=="exit"){
            cout << "Exiting the program." << endl;
            return 0;
        }

        else{
            cout << "ERROR . . . Your Answer is not Correct\n";
            cout << "Please choose your option(1/2/3) : ";
            getline(cin,user_status);      
        }
        clearScreen();
    }
    return 0;
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        // Assume POSIX or other non-Windows
        system("clear");
    #endif
    return;
}

string Make_Lower(string s){
    string result="";
    for(int i=0;i<s.size();i++) result+=tolower(s[i]);
    return result;
}
