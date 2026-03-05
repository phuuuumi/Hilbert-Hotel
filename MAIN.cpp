#include "user_management/Register.h"
#include "user_management/LOGIN.h"
#include "service_management/search.h"

user customer;

void clearScreen();
string Make_Lower(string);

int main(void){
    bool exit = false;
    // Welcome_hotel_starter();

    cout << "------------------------" << endl;
    cout << "WELCOME TO HILBERT HOTEL" << endl; //show in screen
    cout << "------------------------" << endl << endl;

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
            while(true){
                cout << "You want to Login?(Yes/No) : ";
                string agian;
                getline(cin,agian);
                if(Register_Make_Lower(agian)=="yes"){
                    clearScreen();
                    login(customer);
                    break;
                }
                else if(Register_Make_Lower(agian)=="no"){
                    cout << "Thank You for visiting.";
                    return 0;
                }
                else{
                    cout << "ERROR . . . Your Answer is not Correct\n";
                    continue;
                }
            }
            break;
        }

        //LOG-IN
        else if(user_status=="2" || Make_Lower(user_status)=="login"){
            clearScreen();
            login(customer);
            break;
        }
        else if(user_status=="3" || Make_Lower(user_status)=="exit"){
            cout << "Thank You for visiting." << endl;
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
        RoomInfo info[20];
        int roomleft;
        if(user_status=="1"){
            clearScreen();
            checkin(exit);  /*check in and checkout system for customer*/
            clearScreen();
            cout << "Your check-in date is " << check_in.day << "/" << check_in.month << "/" << check_in.years << endl;
            checkout(exit);

            if (exit) {
                cout << "Thank You for visiting." << endl;
                return 0; // Exit the program if user wants to exit
            }

            clearScreen();

            cout << "Your check-in date is " << check_in.day << "/" << check_in.month << "/" << check_in.years << endl;
            cout << "Your check-out date is " << check_out.day << "/" << check_out.month << "/" << check_out.years << endl;
            cout << endl;

            int day_num;
            day_num = countDays(check_out) - countDays(check_in);

            cout << "This is a room that Avaliable" << endl;

            
            int roomCount = readfile_pasteinfo(info);
            roomleft=0;
            for (int i = 0; i < roomCount; i++){  
                if (info[i].getTypePtr() != nullptr &&
                    isRoomAvailable(info[i].getNumber(), check_in, check_out)){
                     roomleft++;
                }
            }

             headerinformation();

            for (int i = 0; i < roomCount; i++){  //show all room that avaliable from screen.
                if (info[i].getTypePtr() != nullptr &&
                    isRoomAvailable(info[i].getNumber(), check_in, check_out)){
            
                    cout <<"|"<< info[i].getNumber() << " | "
                    << changetype(info[i].getTypePtr()->getType()) << " | ";
                    if(roomleft<10){
                        cout << info[i].getTypePtr()->getPrice()*1.05*day_num << " Baths" <<"|"<< endl;
                    }else if(roomleft>=18){
                        cout << info[i].getTypePtr()->getPrice()*0.95*day_num << " Baths" <<"|"<< endl;
                    }else{
                        cout << info[i].getTypePtr()->getPrice()*day_num << " Baths" <<"|"<< endl;
                    }
                }
            }
            cout << "-------------------------------------------------------" << endl;

            choose_room(info,roomleft,customer,day_num); //for user to input room.
            customer.AddHistory();
            cin.get();

            cout << "1.Go back\n";
            cout << "2.Exit\n";
            cout << "Do you want to go back? (1/2) : ";
            getline(cin,user_status);
            while(true){
                if(Make_Lower(user_status) == "1") break;
                else if(Make_Lower(user_status) == "2") {
                    user_status = "3";
                    cout << "Thank You for visiting." << endl;
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
            cout << "Do you want to go back? (1/2) : ";
            getline(cin,user_status);
            while(true){
                if(Make_Lower(user_status) == "1") break;
                else if(Make_Lower(user_status) == "2") {
                    user_status = "3";
                    cout << "Thank You for visiting." << endl;
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
            cout << "Thank You for visiting." << endl;
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
