#include<iostream>
#include<string>
#include<fstream>
#include<cctype> //tolower isdigit
using namespace std;
//ํYou must have folder name "user"

//Function name zone
string Make_Lower(string s);
void Register(), Login(), Manager();
bool HaveFileAlready(string), All_Digits(string);

//Main Funnction
int main(void){
    cout<<"-Welcome to Hilbert-Hotel-\n";
    cout<<"1.Register\n2.Login\n3.Manager\n";
    cout<<"Please choose your option(1/2/3) : ";
    string status;
    getline(cin,status);
    while(true){
        //REGISTER
        if(status=="1" || Make_Lower(status)=="register"){
            cout<<"Your status is Register.\n";
            Register();
            break;
        }

        //LOG-IN
        else if(status=="2" || Make_Lower(status)=="login"){
            cout<<"Your status is Login.\n";
            Login();
            break;
        }

        //ADMIN(MANAGER)
        else if(status=="3" || Make_Lower(status)=="manager"){
            cout<<"Your status is Manager.\n";
        
            break;
        }

        cout<<"ERROR . . . Your Answer is not Correct\n";
        cout<<"Please choose your option(1/2/3) : ";
        getline(cin,status);
    }

    return 0;
}

//Function Zone
void Register(){
    string username,phone,gmail,filename,login_status;
    cout<<"Input your Full Name : ";
    getline(cin,username);
    while(true){
        cout<<"Input your Phone Number : ";
        getline(cin,phone);
        filename = "user/" + phone + ".txt";

        if(phone.empty()) cout<<"ERROR . . . Input cannot be empty\n";
        else if(!All_Digits(phone)) cout << "ERROR . . . Numbers only\n";
        else if(HaveFileAlready(filename)) cout << "ERROR . . . Number already used\n";
        else break;
    }
    cout<<"Input your Email Address : ";
    getline(cin,gmail);
    /*---------------------------------------------*/
    
    ofstream user;
    user.open(filename);
    user << username << "\n" << phone << "\n" << gmail;
    user.close();

    /*---------------------------------------------*/
    cout<<"Your name is "<<username<<"\n";
    cout<<"Phone Number : "<<phone<<"\n";
    cout<<"Email Address : "<<gmail<<"\n";
    cout<<"Create Accout Success!\n";
    while(true){
        cout<<"You want to Login(Yes/No)? : ";
        getline(cin,login_status);
        if(Make_Lower(login_status)=="yes"){
            Login();
            break;
        }
        else if(Make_Lower(login_status)=="no"){
            break;
        }
    }
    return;
}
void Login(){
    





    return;
}
void Manager(){
    
    
    
    
    
    return;
}
string Make_Lower(string s){
    string result="";
    for(int i=0;i<s.size();i++) result+=tolower(s[i]);
    return result;
}
bool HaveFileAlready(string filename){
    ifstream f(filename);
    return f.good();
}
bool All_Digits(string s){
    for(int i=0;i<s.size();i++){
        if(!isdigit(s[i])) return false;
    }
    return true;
}