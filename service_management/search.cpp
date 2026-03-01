#include "hotel_class.h"
void checkin(); //all function template here.
void checkout();
bool isRoomAvailable(string, Date,Date);
int readfile_pasteinfo(RoomInfo []);

string changetype(string);

Date check_in, check_out;
void headerinformation();


int main(){
    fstream  files("D:\\CPP\\Hilbert_Hotel\\Hotel_Room.txt"); //read database file.
    if (!files) cerr << "Error";

    cout << "------------------------" << endl;
    cout << "WELCOME TO HILBERT HOTEL" << endl; //show in screen
    cout << "------------------------" << endl;

    bool exit = false;
    checkin(exit);  /*check in and checkout system for customer*/
    checkout(exit);

    cout << "This is a room that Avaliable" << endl;

    RoomInfo info[20];
    int roomCount = readfile_pasteinfo(info);

    headerinformation();

    for (int i = 0; i < roomCount; i++){  //show all room that avaliable from screen.
        if (info[i].getTypePtr() != nullptr &&
            isRoomAvailable(info[i].getNumber(), check_in, check_out)){
            
            cout <<"|"<< info[i].getNumber() << " | "
                 << changetype(info[i].getTypePtr()->getType()) << " | "
                 << info[i].getTypePtr()->getPrice() << " Baths" <<"|"<< endl;
        }
    }
    cout << "-------------------------------------------------------" << endl;

    
    string room_choose; //choose room system. 
    cout << "Which room do you prefer (please enter room number) :";
    cin >> room_choose;


    ofstream dest("D:\\CPP\\Hilbert_Hotel\\reservation.txt",ios::app); //record into history.
    if(!dest) cerr << "Error";
    dest << room_choose ; 
    dest << ',' << check_in.years << ',' << check_in.day << ',' << check_in.month;
    dest << ',' << check_out.years << ',' << check_out.day << ',' << check_out.month << endl;
    dest.close();


}

//function that manage check-in system.
void checkin(){
    cout << "\nPlease select date you want to check in" << endl;
    cout << "Years (in A.D) : ";
    cin >> check_in.years;
    if (cin.fail()) {
        cout << "Invalid input for year. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        check_in.years = 0; // Reset year to avoid confusion
        checkin(); // Restart the check-in process
        return;
    }
    if (check_in.years < 2026) {
        cout << "Check-in year cannot be in the past. Please re-enter." << endl;
        check_in.years = 0; // Reset year to avoid confusion
        checkin(); // Restart the check-in process
        return;
    }
    cout << "Month (1-12) : ";
    cin >> check_in.month;
    if (cin.fail()) {
        cout << "Invalid input for month. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        check_in.month = 0; // Reset month to avoid confusion
        checkin(); // Restart the check-in process
        return;
    }
    if (check_in.month < 1 || check_in.month > 12) {
        cout << "Invalid month. Please enter a value between 1 and 12." << endl;
        check_in.month = 0; // Reset month to avoid confusion
        checkin(); // Restart the check-in process
        return;
    }

    cout << "Date (1-" << daysInMonth(check_in.month, check_in.years) << ") : ";
    cin >> check_in.day;
    if (cin.fail()) {
        cout << "Invalid input for day. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        check_in.day = 0; // Reset day to avoid confusion
        checkin(); // Restart the check-in process
        return;
    }
    if (check_in.day < 1 || check_in.day > daysInMonth(check_in.month, check_in.years)) {
        cout << "Invalid day for the given month and year. Please re-enter." << endl;
        check_in.day = 0; // Reset day to avoid confusion
        checkin(); // Restart the check-in process
        return;
    }
    cout << "You want to check in at "<< check_in.day << "/" << check_in.month << "/" << check_in.years << endl;       
    
    cout << "Do you want to confirm? (Y/N) :";
    cin >> respond;
    if (respond == "N" || respond == "n") {
        check_in = {0, 0, 0}; // Reset check-in date to avoid confusion
        checkin(); // Restart the check-in process
    } else if (respond == "Y" || respond == "y") {
        cout << "Check-in date confirmed: " << check_in.day << "/" << check_in.month << "/" << check_in.years << endl;
        return; // Exit the loop after successful confirmation
    } else {
        cout << "Invalid input. Please enter 'Y' for yes or 'N' for no." << endl;
        checkin(); // Restart the check-in process if input is invalid
    }
 }

//function that manage check-out system.
void checkout(){
    cout << "\nPlease select date you want to check out" << endl;
    cout << "Years (in A.D) : ";
    cin >> check_out.years;
    if (cin.fail()) {
        cout << "Invalid input for year. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        check_out.years = 0; // Reset year to avoid confusion
        checkout(); // Restart the check-out process
        return;
    }
    if (check_out.years < check_in.years) {
        cout << "Check-out year cannot be before check-in year. Please re-enter." << endl;
        check_out.years = 0; // Reset year to avoid confusion
        checkout(); // Restart the check-out process
        return;
    }
    cout << "Month (1-12) : ";
    cin >> check_out.month;
    if (cin.fail()) {
        cout << "Invalid input for month. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        check_out.month = 0; // Reset month to avoid confusion
        checkout(); // Restart the check-out process
        return;
    }
    if (check_out.month < 1 || check_out.month > 12) {
        cout << "Invalid month. Please enter a value between 1 and 12." << endl;
        check_out.month = 0; // Reset month to avoid confusion
        checkout(); // Restart the check-out process
        return;
    }

    if (check_out.years == check_in.years && check_out.month < check_in.month) {
        cout << "Check-out month cannot be before check-in month in the same year. Please re-enter." << endl;
        check_out.month = 0; // Reset month to avoid confusion
        checkout(); // Restart the check-out process
        return;
    }
    cout << "Date (1-" << daysInMonth(check_out.month, check_out.years) << ") : ";
    cin >> check_out.day;
    if (cin.fail()) {
        cout << "Invalid input for day. Please enter a valid number." << endl;
        cin.clear(); // Clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        check_out.day = 0; // Reset day to avoid confusion
        checkout(); // Restart the check-out process
        return;
    }
    if (check_out.day < 1 || check_out.day > daysInMonth(check_out.month, check_out.years)) {
        cout << "Invalid day for the given month and year. Please re-enter." << endl;
        check_out.day = 0; // Reset day to avoid confusion
        checkout(); // Restart the check-out process
        return;
    }

    if (check_out.years == check_in.years && check_out.month == check_in.month && check_out.day <= check_in.day) {
        cout << "Check-out date cannot be before or the same as check-in date in the same month and year. Please re-enter." << endl;
        check_out.day = 0; // Reset day to avoid confusion
        checkout(); // Restart the check-out process
        return;
    }
    cout << "You want to check out at "<< check_out.day << "/" << check_out.month << "/" << check_out.years << endl;
    cout << "Do you want to confirm? (Y/N) :";
    cin >> respond;
    if (respond == "N" || respond == "n") {
        check_out = {0, 0, 0}; // Reset check-out date to avoid confusion
        checkout(); // Restart the check-out process
    } else if (respond == "Y" || respond == "y"){
        cout << "Check-out date confirmed: " << check_out.day << "/" << check_out.month << "/" << check_out.years << endl;
        return; // Exit the loop after successful confirmation
    } else {
        cout << "Invalid input. Please enter 'Y' for yes or 'N' for no." << endl;
        checkout(); // Restart the check-in process if input is invalid
    }
 }

 //function to check if that room are avaliable for current customer. 
 bool isRoomAvailable(string roomNumber, Date new_in, Date new_out){
    fstream file("D:/CPP/Hilbert_Hotel/reservation.txt");
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

//function to read files from database.
int readfile_pasteinfo(RoomInfo info[]){
    fstream  files("D:\\CPP\\Hilbert_Hotel\\Hotel_Room.txt"); 
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
        


        


        

        

    








