#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype> //tolower isdigit
#include <cstdlib> //system("clear");
#include <algorithm> //binary_search and sort
#include <regex>

using namespace std;
// ***dont change data in user.txt because line is important!

// Global Variable Zone
vector<string> Register_all_phone,Register_all_gmail;

// Function Name Zone
void Register();
void Register_clearScreen();
void Register_CollectAllUserData();
// void Register_ReadUser(string);
bool Register_All_Digits(string);
bool Register_IsValidEmail(string);
bool Register_AddUserData(string,string,string,string);
string Register_Make_Lower(string);

//Function Zone
void Register(){

    Register_CollectAllUserData();
    Register_clearScreen();
    cout<<"Your status is Register.\n";
    
    string user_name,user_phone,user_gmail,user_password,confirmed_user_password;
    // Name
    cout << "Input your Full Name : ";
    getline(cin,user_name);

    // Password
    while(true){
        cout << "Input your Password : ";
        getline(cin,user_password);
        if(user_password.empty()){
            cout << "ERROR . . . Input cannot be empty\n";
            continue;
        }

        cout << "Confirmed your Password : ";
        getline(cin,confirmed_user_password);
        if(confirmed_user_password==user_password) break;
        else{
            cout << "ERROR . . . Your confirmed password is not correct.\n";
            while(true){
                cout << "You want to Register agian?(Yes/No) : ";
                string agian;
                getline(cin,agian);
                if(Register_Make_Lower(agian)=="yes"){
                    Register();
                    return;
                }
                else if(Register_Make_Lower(agian)=="no") return;
                else{
                    cout << "ERROR . . . Your Answer is not Correct\n";
                    continue;
                }
            }
        }
    }

    // Phone
    while(true){
        cout << "Input your Phone Number(Numbers only) : ";
        getline(cin,user_phone);

        if(user_phone.empty()) cout << "ERROR . . . Input cannot be empty\n";
        else if(!Register_All_Digits(user_phone)) cout << "ERROR . . . Numbers only\n";
        else if(binary_search(Register_all_phone.begin(),Register_all_phone.end(),user_phone)) cout << "ERROR . . . Number already used\n";
        else break;
    }

    // Gmail
    while(true){
        cout << "Input your Email Address : ";
        getline(cin,user_gmail);

        if(user_gmail.empty()) cout << "ERROR . . . Input cannot be empty\n";
        else if(!Register_IsValidEmail(user_gmail)) cout << "ERROR . . . Your Answer is not Email Address\n";
        else if(binary_search(Register_all_gmail.begin(),Register_all_gmail.end(),user_gmail)) cout << "ERROR . . . This Email is already used\n";
        else break;
    }

    Register_clearScreen();
    cout << "-Information-\n";
    cout << "Username : " << user_name << "\n";
    cout << "Phone Number : " << user_phone << "\n";
    cout << "Email Address : " << user_gmail << "\n";
    while(true){
        cout << "Comfirm Your Information(Yes/No) : ";
        string confirm;
        getline(cin,confirm);
        if(Register_Make_Lower(confirm)=="yes"){
            if(Register_AddUserData(user_name,user_phone,user_gmail,user_password)){
                Register_clearScreen();
                cout<<"Your user was created.\n";
                cout<<"Registered Successfully.\n";
            }
            else cout<<"Error. . . Your user was not created.\n";
            break;
        }
        if(Register_Make_Lower(confirm)=="no"){
            while(true){
                cout << "You want to Register agian?(Yes/No) : ";
                string agian;
                getline(cin,agian);
                if(Register_Make_Lower(agian)=="yes"){
                    Register();
                    return;
                }
                else if(Register_Make_Lower(agian)=="no") return;
                else{
                    cout << "ERROR . . . Your Answer is not Correct\n";
                    continue;
                }
            }
        }
    }

    //(Add) Add new Account in vector -> sort it (if used vector gmail)
    //(Add) Want to Login?
}

bool Register_AddUserData(string name,string phone,string gmail,string password){
    bool result = false;
    ofstream user_file("user.txt",ios::app);
    user_file << phone << "\n";
    user_file << gmail << "\n";
    user_file << name << "\n";
    user_file << password << "\n";
    user_file << "> History 0\n";
    user_file << "--------------------------------------\n";
    user_file.close();
    result = true;
    return result;
}

void Register_CollectAllUserData(){
    ifstream user_file("user.txt");
    string line,user_phone,user_gmail;
    while(getline(user_file,line)){
        if(line=="--------------------------------------"){
            if(getline(user_file,user_phone)){
                getline(user_file,user_gmail);
                Register_all_phone.push_back(user_phone);
                Register_all_gmail.push_back(user_gmail);
            }
        }
    }
    sort(Register_all_phone.begin(),Register_all_phone.end());
    sort(Register_all_gmail.begin(),Register_all_gmail.end());
    user_file.close();
    return;
}

bool Register_All_Digits(string s){
    for(int i=0;i<s.size();i++){
        if(!isdigit(s[i])) return false;
    }
    return true;
}

void Register_clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        // Assume POSIX or other non-Windows
        system("clear");
    #endif
    return;
}

bool Register_IsValidEmail(string email) {
    regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$)");
    return regex_match(email,pattern);
}

string Register_Make_Lower(string s){
    string result="";
    for(int i=0;i<s.size();i++) result+=tolower(s[i]);
    return result;
}

//ReadUser for Read user account file(Want to remake).
// void Register_ReadUser(string USERDATA){
//     ifstream user_file("user.txt");
//     string line,user_phone,user_name,user_gmail;
//     bool user_found = false;
//     while(getline(user_file,line)){
//         if(line=="--------------------------------------"){
//             getline(user_file,user_phone);
//             getline(user_file,user_gmail);
//             if(user_phone==USERDATA || user_gmail==USERDATA){
//                 user_found = true;
//                 getline(user_file,user_name);

//                 cout<<"Username : "<<user_name<<"\n";
//                 cout<<"Phone Number : "<<user_phone<<"\n";
//                 cout<<"Email Account : "<<user_gmail<<"\n";
                
//                 int num_booking = 0;
//                 string room,price;
//                 getline(user_file,line); // > History
//                 while(getline(user_file,line)){
//                     if(line=="--------------------------------------"){
//                         if(num_booking==0) cout<<"Not Found History.\n";
//                         break;
//                     }
//                     num_booking++;
//                     getline(user_file,room);
//                     getline(user_file,price);
//                     cout<<"Booking "<<num_booking<<"\n";
//                     cout<<"Type Room : "<<room<<"\n";
//                     cout<<"Price : "<<price<<"\n";
//                     cout<<"Time : "<<line<<"\n";
//                 }
//                 break;
//             }
//         }
//     }
//     user_file.close();
//     if(user_found) cout<<"READ SUCCESS!";
//     else cout<<"NOT FOUND.";
// }