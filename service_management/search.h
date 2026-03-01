#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
#include <string>

void checkin(bool&); //all function template here.
void checkout(bool&);


using namespace std;

struct Date{
    int day;
    int month;
    int years;
        
};

struct Reservation{
    Date check_in;
    Date check_out;
};
int daysInMonth(int month, int year) {
    if (month == 2) {

        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            return 29;
        return 28;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
        return 30;


    return 31;
}

bool isBefore(Date a, Date b){
    if (a.years != b.years) return a.years < b.years;
    if (a.month != b.month) return a.month < b.month;
    return a.day <= b.day;
}

//function to check if that room are avaliable for current customer. 
 bool isRoomAvailable(string roomNumber, Date new_in, Date new_out){

    fstream file("reservation.txt");
    if (!file) {
        return true;
    } //can choose if nothing on files.

    string line;
    while (getline(file, line)){
        stringstream ss(line);

        string num_s, y1,m1,d1,y2,m2,d2;

        getline(ss, num_s, ',');
        getline(ss, y1, ',');
        getline(ss, m1, ',');
        getline(ss, d1, ',');
        getline(ss, y2, ',');
        getline(ss, m2, ',');
        getline(ss, d2, ',');

        if (num_s != roomNumber) continue; //if not the same room then can check another line.
        
        if (line.empty()) continue;

        Date old_in  = {stoi(d1), stoi(m1), stoi(y1)}; //the old customer check in and out.
        Date old_out = {stoi(d2), stoi(m2), stoi(y2)};

         bool overlap =
            !( isBefore(new_out, old_in) ||
               isBefore(old_out, new_in) );

        if (overlap){
            file.close();
            return false;
        }
    }

    file.close();
    return true;
}
string changetype(string);
string respond;
Date check_in, check_out;
//function that manage check-in system.
void checkin(bool& exit){
    if (exit) {
        cout << "Exiting check-in process." << endl;
        return; // Exit the function if user wants to exit
    }
    string input;
    cout << "\nPlease select date you want to check in" << endl;
    cout << "Years (in A.D) : ";
    cin >> input;
    if (input == "Exit") {
            cout << "Exiting the process." << endl;
            exit = true;
            return; // Exit the function if user wants to exit
        }
    
    try {
        check_in.years = stoi(input); // Convert input to integer for year
    } catch (const exception&) {
        cout << "Invalid input for year. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); // Discard invalid input
        check_in.years = 0; // Reset year to avoid confusion
        checkin(exit); // Restart the check-in process
        return;
    }
    input.clear(); // Clear the input string for the next input
    if (check_in.years < 2026) {
        cout << "Check-in year cannot be in the past. Please re-enter." << endl;
        check_in.years = 0; // Reset year to avoid confusion
        checkin(exit); // Restart the check-in process
        return;
    }
    cout << "Month (1-12) : ";
    cin >> input;
    if (input == "Exit") {
            cout << "Exiting check-in process." << endl;
            exit = true;
            return; // Exit the function if user wants to exit
        }
    try {
        check_in.month = stoi(input); // Convert input to integer for month
    } catch (const exception&) {
        cout << "Invalid input for month. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); // Discard invalid input
        check_in.month = 0; // Reset month to avoid confusion
        checkin(exit); // Restart the check-in process
        return;
    }
    input.clear(); // Clear the input string for the next input
    if (check_in.month < 1 || check_in.month > 12) {
        cout << "Invalid month. Please enter a value between 1 and 12." << endl;
        check_in.month = 0; // Reset month to avoid confusion
        checkin(exit); // Restart the check-in process
        return;
    }

    cout << "Date (1-" << daysInMonth(check_in.month, check_in.years) << ") : ";
    cin >> input;
    if (input == "Exit") {
            cout << "Exiting the process." << endl;
            exit = true;
            return; // Exit the function if user wants to exit
        }
    try {
        check_in.day = stoi(input); // Convert input to integer for day
    } catch (const exception&) {
        cout << "Invalid input for day. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); // Discard invalid input
        check_in.day = 0; // Reset day to avoid confusion
        checkin(exit); // Restart the check-in process
        return;
    }
    input.clear(); // Clear the input string for the next input
    if (check_in.day < 1 || check_in.day > daysInMonth(check_in.month, check_in.years)) {
        cout << "Invalid day for the given month and year. Please re-enter." << endl;
        check_in.day = 0; // Reset day to avoid confusion
        checkin(exit); // Restart the check-in process
        return;
    }
    cout << "You want to check in at "<< check_in.day << "/" << check_in.month << "/" << check_in.years << endl;       
    
    cout << "Do you want to confirm? (Y/N) :";
    cin >> input;
    if (cin.fail()) {
        cout << "Invalid input. Please enter 'Y' for yes or 'N' for no." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); // Discard invalid input
        check_in = {0, 0, 0}; // Reset check-in date to avoid confusion
        checkin(exit); // Restart the check-in process
        return;
    }
    if (input == "N" || input == "n") {
        check_in = {0, 0, 0}; // Reset check-in date to avoid confusion
        checkin(exit); // Restart the check-in process
    } else if (input == "Y" || input == "y") {
        cout << "Check-in date confirmed: " << check_in.day << "/" << check_in.month << "/" << check_in.years << endl;
        return; // Exit the loop after successful confirmation
    } else {
        cout << "Invalid input. Please enter 'Y' for yes or 'N' for no." << endl;
        checkin(exit); // Restart the check-in process if input is invalid
    }
 }

//function that manage check-out system.
void checkout(bool& exit){
    string input;
    if (exit) {
        cout << "Exiting check-out process." << endl;
        return; // Exit the function if user wants to exit
    }
    cout << "\nPlease select date you want to check out" << endl;
    cout << "Years (in A.D) : ";
    cin >> input;
    if (input == "Exit") {
            cout << "Exiting the process." << endl;
            exit = true;
            return; // Exit the function if user wants to exit
        }
    try {
        check_out.years = stoi(input); // Convert input to integer for year
    } catch (const exception&) {
        cout << "Invalid input for year. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); // Discard invalid input
        check_out.years = 0; // Reset year to avoid confusion
        checkout(exit); // Restart the check-out process
        return;
    }
    input.clear(); // Clear the input string for the next input
    if (check_out.years < check_in.years) {
        cout << "Check-out year cannot be before check-in year. Please re-enter." << endl;
        check_out.years = 0; // Reset year to avoid confusion
        checkout(exit); // Restart the check-out process
        return;
    }
    cout << "Month (1-12) : ";
    cin >> input;
    if (input == "Exit") {
        cout << "Exiting the process." << endl;
        exit = true;
        return; // Exit the function if user wants to exit
    }
    try {
        check_out.month = stoi(input); // Convert input to integer for month
    } catch (const exception&) {
        cout << "Invalid input for month. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); // Discard invalid input
        check_out.month = 0; // Reset month to avoid confusion
        checkout(exit); // Restart the check-out process
        return;
    }
    input.clear(); // Clear the input string for the next input
    if (check_out.month < 1 || check_out.month > 12) {
        cout << "Invalid month. Please enter a value between 1 and 12." << endl;
        check_out.month = 0; // Reset month to avoid confusion
        checkout(exit); // Restart the check-out process
        return;
    }

    if (check_out.years == check_in.years && check_out.month < check_in.month) {
        cout << "Check-out month cannot be before check-in month in the same year. Please re-enter." << endl;
        check_out.month = 0; // Reset month to avoid confusion
        checkout(exit); // Restart the check-out process
        return;
    }
    cout << "Date (1-" << daysInMonth(check_out.month, check_out.years) << ") : ";
    cin >> input;
    if (input == "Exit") {
        cout << "Exiting the process." << endl;
        exit = true;
        return; // Exit the function if user wants to exit
    }
    try {
        check_out.day = stoi(input); // Convert input to integer for day
    } catch (const exception&) {
        cout << "Invalid input for day. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); // Discard invalid input
        check_out.day = 0; // Reset day to avoid confusion
        checkout(exit); // Restart the check-out process
        return;
    }
    input.clear(); // Clear the input string for the next input
    if (check_out.day < 1 || check_out.day > daysInMonth(check_out.month, check_out.years)) {
        cout << "Invalid day for the given month and year. Please re-enter." << endl;
        check_out.day = 0; // Reset day to avoid confusion
        checkout(exit); // Restart the check-out process
        return;
    }

    if (check_out.years == check_in.years && check_out.month == check_in.month && check_out.day <= check_in.day) {
        cout << "Check-out date cannot be before or the same as check-in date in the same month and year. Please re-enter." << endl;
        check_out.day = 0; // Reset day to avoid confusion
        checkout(exit); // Restart the check-out process
        return;
    }
    cout << "You want to check out at "<< check_out.day << "/" << check_out.month << "/" << check_out.years << endl;
    cout << "Do you want to confirm? (Y/N) :";
    cin >> input;
    if (cin.fail()) {
        cout << "Invalid input. Please enter 'Y' for yes or 'N' for no." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); // Discard invalid input
        check_out = {0, 0, 0}; // Reset check-out date to avoid confusion
        checkout(exit); // Restart the check-out process
        return;
    }
    if (input == "N" || input == "n") {
        check_out = {0, 0, 0}; // Reset check-out date to avoid confusion
        checkout(exit); // Restart the check-out process
    } else if (input == "Y" || input == "y"){
        cout << "Check-out date confirmed: " << check_out.day << "/" << check_out.month << "/" << check_out.years << endl;
        return; // Exit the loop after successful confirmation
    } else {
        cout << "Invalid input. Please enter 'Y' for yes or 'N' for no." << endl;
        checkout(exit); // Restart the check-out process if input is invalid
    }
 }

 class Room; 

class RoomInfo{
    private:
        string room_number;
        Room* room_type;
        bool occupied;
        vector<Reservation> bookings;
        public:
            void setRoom(string num, Room* type, bool occ) {
                room_number = num;
                room_type = type;
                occupied = occ;
            }
            string getNumber() const {
                return room_number;
            }

            Room* getTypePtr() const {
                return room_type;
            }

            bool isOccupied() const {
                return occupied;
            }
};

class Room{
    private:
        string room_type;
        int guest;
        map <string,int> bed;
        string bathroom;
        bool living_room;
        double price;
    public:
        void set_data(string ,int ,map <string,int> ,string ,bool ,double );
        void show() const {
            cout << room_type << " "
                 << guest << " "
                << bathroom << " "
                << living_room << " "
                << price << endl;
        }
        string getType() const {
            return room_type;
        }

        double getPrice() const {
            return price;
        }

};

void Room::set_data(string r,int g,map <string,int> b,string bath,bool l,double p){
    room_type = r;
    guest = g;
    bed = b;
    bathroom = bath;
    living_room = l;
    price = p;

}

int readfile_pasteinfo(RoomInfo info[]){
    fstream  files("service_management/Hotel_Room.txt"); 
    if (!files) cerr << "Error";
    static Room rooms[5];
    int t_count = 0;
    string line;
    while (getline(files, line) && t_count < 5) {
        stringstream ss(line);

        string type, guest_s, bedcount_s, bedtype, bath, living_s, price_s;

        getline(ss, type, ',');
        getline(ss, guest_s, ',');
        getline(ss, bedcount_s, ',');
        getline(ss, bedtype, ',');
        getline(ss, bath, ',');
        getline(ss, living_s, ',');
        getline(ss, price_s, ',');

        int guest = stoi(guest_s);
        int bedcount = stoi(bedcount_s);
        bool living = (living_s == "Y");
        double price = stod(price_s);

        map<string,int> bed;
        bed[bedtype] = bedcount;

        rooms[t_count].set_data(type, guest, bed, bath, living, price);

        t_count++;
    }

        map<string, Room*> typeMap;
        for(int i = 0; i < t_count; i++){
            typeMap[rooms[i].getType()] = &rooms[i];
        }

        int r_count = 0;
        while (r_count < 20 && getline(files, line)) {
            if(line.empty()) continue;   

            stringstream ss(line);

            string num_s, type, occ_s,num;

            getline(ss, num_s, ',');
            getline(ss, type, ',');
            getline(ss, occ_s, ',');

            
            bool occ = (occ_s == "YES");

            Room* rtype = typeMap[type];
            info[r_count].setRoom(num_s, rtype, occ);
            r_count ++;
            
        }
        files.close();
        return r_count;

}

//function to show room detail.
string changetype(string type){
    if (type == "STR")  return "Standard Room (2 person limits)   ";
    if (type == "DR")   return "Deluxe Room (2 person limits)     ";
    if (type == "TWR")  return "Twin Room (4 person limits)       ";
    if (type == "DTWR") return "Deluxe Twin Room (4 person limits)";
    if (type == "SUR")  return "Suite Room (2 person limits)      ";
                        return "No Room type                      ";

}

//function to show header of information.
void headerinformation(){
    cout << " _____________________________________________________" << "\n";
    cout << "|No. |Type name                           | Price     |" << "\n";
    cout << "-------------------------------------------------------" << "\n";
}

void choose_room(){
    string room_choose; //choose room system. 
    cout << "Which room do you prefer (please enter room number) :";
    cin >> room_choose;
    if (cin.fail()){
        cout << "Invalid input . Please enter valid room number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); 
        choose_room();
    }else if(room_choose.size() > 3){
        cout << "Invalid input . Please enter valid room number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); 
        choose_room();

    }else if(stoi(room_choose) < 1 or stoi(room_choose) > 20){
        cout << "Invalid input . Please enter valid room number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(1000, '\n'); 
        choose_room();
    }else{
        ofstream dest("service_management/reservation.txt",ios::app); //record into history.
        if(!dest) cerr << "Error";
        dest << room_choose ; 
        dest << ',' << check_in.years << ',' << check_in.day << ',' << check_in.month;
        dest << ',' << check_out.years << ',' << check_out.day << ',' << check_out.month << endl;
        dest.close();
    }

}
