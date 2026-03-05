class user{
    private:
        string useremail;
        string userphone;
        string userpassword;
    public:
        int current_history_line_update;
        int current_line_update;
        string current_data_update;
        string current_historytitle_update;
        string username;
        vector<string> userhistory;
        void getinfo(vector<string>);
        void showuserdata();
        void AddHistory();
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
int target_line,history_title_line;
string new_history_title="";

vector<string> get_userinfo(string input){
    ifstream user_file("user_management/user.txt");
    if (!user_file){
    cout << "Cannot open user.txt\n";
    return {"", "", "", "", "0", ""};
    }
    target_line=0;
    string line, phone, name, email, password, history;
    string user_found = "0";
    while(getline(user_file,line)){
        target_line++;
        if(line=="--------------------------------------"){
            getline(user_file,phone);target_line++;
            getline(user_file,email);target_line++;
            if(phone == input || email== input){
                user_found = true;
                getline(user_file,name);target_line++;
                getline(user_file, password);target_line++;
                getline(user_file, line);target_line++;
                history_title_line = target_line;
                history = "";
                new_history_title = to_string((atoi(line.c_str()))+1)+"  History";
                if(atoi(line.c_str())==0) target_line++;
                for(int i=0; i<atoi(line.c_str()); i++){
                    getline(user_file, line);target_line++;
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

void user::getinfo(vector<string> input){
    username = input[0];
    useremail = input[1];
    userphone = input[2];
    userpassword = input[3];
    current_line_update = target_line;
    current_history_line_update = history_title_line;
    current_historytitle_update = new_history_title;

    string history = "";
    for(char a: input[5]){
        if(a == '+'){
            userhistory.push_back(history);
            history = "";
        }else history = history + a;
    }
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

    if(userhistory.size() == 0){
        cout << "History not found!!\n";
    }
    else {
        cout << userhistory.size() << " History\n";
        cout << "------------------------------------------------\n";

        for(int i=0; i<userhistory.size(); i++){

            string text = "";
            int temp = 1;

            for(char a: userhistory[i]){
                if(a == ','){
                    if(temp==1) cout<<"Date : "<< text << "\n";
                    if(temp==2) cout<<"Type Room : "<< text << "\n";
                    if(temp==3) cout<<"Price : "<< text << " Baths\n";
                    text = "";
                    temp++;
                }
                else text += a;
            }

            cout << "------------------------------------------------\n";
        }
    }
}

void user::AddHistory(){

    string filename = "user_management/user.txt";
    vector<string> lines;
    string line;

    ifstream in_File(filename);
    if (!in_File){
        cout << "Cannot read user.txt\n";
        return;
    }

    while(getline(in_File,line)){
        lines.push_back(line);
    }

    in_File.close();


    lines[current_history_line_update-1] = current_historytitle_update;


    lines.insert(lines.begin()+current_line_update-1, current_data_update);


    ofstream out_File(filename);
    if (!out_File){
        cout << "Cannot write user.txt\n";
        return;
    }

    for(string &l : lines){
        out_File << l << "\n";
    }

    out_File.close();

    userhistory.push_back(current_data_update);

    current_data_update="";
    current_line_update++;
    current_historytitle_update=to_string((atoi(current_historytitle_update.c_str()))+1)+"  History";

    cout<<"Update History Success!\n";
}