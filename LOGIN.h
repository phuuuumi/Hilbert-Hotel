class user{
    private:
        string useremail;
        string userphone;
        string userpassword;
    public:
        string username;
        void getinfo(vector<string>);
        void showuserdata();
};

void Login_clearScreen();

void Login_clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        // Assume POSIX or other non-Windows
        system("clear");
    #endif
    return;
}

void user::getinfo(vector<string> input){
    username = input[0];
    useremail = input[1];
    useremail = input[2];
    userpassword = input[3];
}

vector<string> get_userinfo(string input){
    ifstream user_file("user.txt");
    string line, phone, name, email, password;
    string user_found = "0";
    while(getline(user_file,line)){
        if(line=="--------------------------------------"){
            getline(user_file,phone);
            getline(user_file,email);
            if(phone == input || email== input){
                user_found = true;
                getline(user_file,name);
                getline(user_file, password);
                return {name, email, phone, password, user_found};
            }
        }
    }
    user_file.close();
    return {"name", "email", "phone", "password", user_found};
}



void login(user &consumer){
    string input;
    cout << "Your status is Login.\n";
    //collect user phone/email
    while(true){
        cout << "Enter your phone number or email : ";
        getline(cin, input);
        vector<string> info = get_userinfo(input);
        if(info[4][0] - '0'){

            //Checking password
            while(true){
                cout << "Enter Your password: ";
                getline(cin, input);
                if(info[3] == input){
                    consumer.getinfo(info);
                    break;
                }else{
                    Login_clearScreen();
                    cout << "Your password is incorrect. Try again\n";
                }
            }
            break;
        }
        Login_clearScreen();
        cout << "Not found pls try again.\n";
    }
}

void user::showuserdata(){
    cout << "Name : " << username << "\n";
    cout << "Phone number : " << userphone << "\n";
    cout << "Email : " << useremail << "\n";
    cout << "History : " << "coming soon..." << "\n";
}