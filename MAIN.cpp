#include "Welcome.h"
#include "Register.h"

void clearScreen();
string Make_Lower(string);

int main(void){
    Welcome_hotel_starter();
    string user_status;
    getline(cin,user_status);

    while(true){
        //REGISTER
        if(user_status=="1" || Make_Lower(user_status)=="register"){
            Register();
            break;
        }

        //LOG-IN
        else if(user_status=="2" || Make_Lower(user_status)=="login"){
            clearScreen();
            cout << "Your status is Login.\n";
            break;
        }

        cout << "ERROR . . . Your Answer is not Correct\n";
        cout << "Please choose your option(1/2/3) : ";
        getline(cin,user_status);
    }

    cout << "Thank You :)";
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