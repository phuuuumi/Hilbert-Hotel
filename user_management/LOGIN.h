class user{
    private:
        string useremail;
        string userphone;
        string userpassword;
    public:
        string username;
        vector<string> userhistory;
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
    userphone = input[2];
    userpassword = input[3];

    string history = "";
    for(char a: input[5]){
        if(a == '+'){
            userhistory.push_back(history);
            history = "";
        }else history = history + a;
    }
}

vector<string> get_userinfo(string input){
    ifstream user_file("user_management/user.txt");
    if (!user_file){
    cout << "Cannot open user.txt\n";
    return {"", "", "", "", "0", ""};
    }
    string line, phone, name, email, password, history;
    string user_found = "0";
    while(getline(user_file,line)){
        if(line=="--------------------------------------"){
            getline(user_file,phone);
            getline(user_file,email);
            if(phone == input || email== input){
                user_found = true;
                getline(user_file,name);
                getline(user_file, password);
                getline(user_file, line);
                history = "";
                for(int i=0; i<atoi(line.c_str()); i++){
                    getline(user_file, line);
                    history = history + line + "+";
                }
                user_file.close();
                return {name, email, phone, password, user_found, history};
            }
        }
    }
    user_file.close();
    // str ใส่ไว้ให้user_found อยู่ตำแหน่งตรงใช้เช็คใน if
    return {"name", "email", "phone", "password", user_found, "history"};
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
    if(userhistory.size() == 0) cout << "History not found!!\n";
    else {
        cout << userhistory.size()-1 << " History\n";
        cout << "------------------------------------------------\n";
        for(int i=0; i<userhistory.size()-1; i++){

            string text = "";
            for(char a: userhistory[i]){
                if(a == ','){
                    cout << text << "\n";
                    text = "";
                }else text += a;
            }
            cout << "------------------------------------------------\n";
        }
    }       
}