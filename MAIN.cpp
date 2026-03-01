#include "user_management/Register.h"
#include "user_management/LOGIN.h"
#include "service_management/search.h"



user customer;

void clearScreen();
string Make_Lower(string);

int main(void){
    // Welcome_hotel_starter();

    cout << "-Welcome to Hilbert-Hotel-\n";
    cout << "1.Register\n";
    cout << "2.Login\n";
    cout << "Please choose your option(1/2) : ";
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

        cout << "ERROR . . . Your Answer is not Correct\n";
        cout << "Please choose your option(1/2) : ";
        getline(cin,user_status);
    }

    // Services Section
    clearScreen();
    cout << "Log in success.\n";
    cout << "Hello " << customer.username << ". Welcome to Hilbert Hotel. \n";
    

    while(true){
        cout << "1.Searching Room\n";
        cout << "2.Show user data and history.\n";
        cout << "Please choose your option(1/2) : ";
        getline(cin,user_status);
        if(user_status=="1"){
            cout << "coming soon...\n";
            while(true){
                if(Make_Lower(user_status) == "yes") break;
                else getline(cin,user_status);
            }
        }

        //LOG-IN
        else if(user_status=="2"){
            clearScreen();
            customer.showuserdata();
            cout << "Do you want to go back? (Yes) : ";
            getline(cin,user_status);
            while(true){
                if(Make_Lower(user_status) == "yes") break;
                else getline(cin,user_status);
            }
        }

        else{
            cout << "ERROR . . . Your Answer is not Correct\n";
            cout << "Please choose your option(1/2) : ";
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