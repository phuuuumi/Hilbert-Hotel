#include<iostream>
#include<string>
#include<fstream>
#include<cctype> //tolower isdigit
#include<cstdlib> //system("clear");
#include<vector>
#include<ctime> // not used now
#include<iomanip> // not used now
#include<algorithm> //binary_search and sort

using namespace std;
// ***dont change data in user.txt because line is important!

// Global Variable Zone
vector<string> all_phone,all_gmail;

// Function Name Zone
void Register(),Login(),clearScreen(),CollectAllUserData(),ReadUser(string);
string Make_Lower(string);
bool All_Digits(string);

//Function Zone
void Register(){
    CollectAllUserData();
    string user_name,user_phone,user_gmail;
    cout<<"Input your Full Name : ";
    getline(cin,user_name);
    while(true){
        cout<<"Input your Phone Number : ";
        getline(cin,user_phone);

        if(user_phone.empty()) cout<<"ERROR . . . Input cannot be empty\n";
        else if(!All_Digits(user_phone)) cout<<"ERROR . . . Numbers only\n";
        else if(binary_search(all_phone.begin(),all_phone.end(),user_phone)) cout<<"ERROR . . . Number already used\n";
        else break;
    }
    while(true){
        cout<<"Input your Email Address : ";
        getline(cin,user_gmail);

        if(user_gmail.empty()) cout<<"ERROR . . . Input cannot be empty\n";
        else if(binary_search(all_gmail.begin(),all_gmail.end(),user_gmail)) cout<<"ERROR . . . This Email is already used\n";
        else break;
    }
    //(Add) Confirm To create Account or Not
    ofstream user_file("user.txt",ios::app);
    user_file<<user_phone<<"\n"<<user_gmail<<"\n"<<user_name<<"\n";
    user_file<<"> History\n--------------------------------------\n";
    user_file.close();
    cout<<"Your user was created.\n";
    //(Add) Add new Account in vector -> sort it
    //(Add) Want to Login?
}

//(Add) Login function
void Login(){
    // string USERDATA;
    // cout<<"Input Gmail/Phone : ";
    // getline(cin,USERDATA);
    // ReadUser(USERDATA);
}

string Make_Lower(string s){
    string result="";
    for(int i=0;i<s.size();i++) result+=tolower(s[i]);
    return result;
}

bool All_Digits(string s){
    for(int i=0;i<s.size();i++){
        if(!isdigit(s[i])) return false;
    }
    return true;
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        // Assume POSIX or other non-Windows
        system("clear");
    #endif
}

void CollectAllUserData(){
    ifstream user_file("user.txt");
    string line,user_phone,user_gmail;
    while(getline(user_file,line)){
        if(line=="--------------------------------------"){
            if(getline(user_file,user_phone)){
                getline(user_file,user_gmail);
                all_phone.push_back(user_phone);
                all_gmail.push_back(user_gmail);
            }
        }
    }
    sort(all_phone.begin(),all_phone.end());
    sort(all_gmail.begin(),all_gmail.end());
    user_file.close();
}

//ReadUser for Read user account file(Want to remake).
void ReadUser(string USERDATA){
    ifstream user_file("user.txt");
    string line,user_phone,user_name,user_gmail;
    bool user_found = false;
    while(getline(user_file,line)){
        if(line=="--------------------------------------"){
            getline(user_file,user_phone);
            getline(user_file,user_gmail);
            if(user_phone==USERDATA || user_gmail==USERDATA){
                user_found = true;
                getline(user_file,user_name);

                cout<<"Username : "<<user_name<<"\n";
                cout<<"Phone Number : "<<user_phone<<"\n";
                cout<<"Email Account : "<<user_gmail<<"\n";
                
                int num_booking = 0;
                string room,price;
                getline(user_file,line); // > History
                while(getline(user_file,line)){
                    if(line=="--------------------------------------"){
                        if(num_booking==0) cout<<"Not Found History.\n";
                        break;
                    }
                    num_booking++;
                    getline(user_file,room);
                    getline(user_file,price);
                    cout<<"Booking "<<num_booking<<"\n";
                    cout<<"Type Room : "<<room<<"\n";
                    cout<<"Price : "<<price<<"\n";
                    cout<<"Time : "<<line<<"\n";
                }
                break;
            }
        }
    }
    user_file.close();
    if(user_found) cout<<"READ SUCCESS!";
    else cout<<"NOT FOUND.";
}