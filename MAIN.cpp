#include "MAIN.h"

int main(void){
    clearScreen();
    cout<<"-Welcome to Hilbert-Hotel-\n1.Register\n2.Login\nPlease choose your option(1/2) : ";
    string user_status;
    getline(cin,user_status);
    while(true){
        //REGISTER
        if(user_status=="1" || Make_Lower(user_status)=="register"){
            clearScreen();
            cout<<"Your status is Register.\n";
            Register();
            break;
        }

        //LOG-IN
        else if(user_status=="2" || Make_Lower(user_status)=="login"){
            clearScreen();
            cout<<"Your status is Login.\n";
            Login();
            break;
        }

        cout<<"ERROR . . . Your Answer is not Correct\nPlease choose your option(1/2/3) : ";
        getline(cin,user_status);
    }

    return 0;
}
