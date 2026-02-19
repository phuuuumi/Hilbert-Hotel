#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;
// (Add) write time in file if booking success(choose room too);

/* 
In file booking_test.txt (*All days are sorted)
ROOM 4
2026/03/01 -> Check-In 1
2026/03/03 -> Check-Out 1
2026/08/01 -> Check-In 2
2026/08/05 -> Check-Out 2
2027/02/14 -> Check-In 3
2027/02/16 -> Check-Out 3
*/

void Bookingtest_Find_Room(int,int);
int make_time(string);

int main(void){
    string time_in,time_out;
    cout<<"Input Check-In time(Y/M/D) : ";
    getline(cin,time_in);
    cout<<"Input Check-Out time(Y/M/D) : ";
    getline(cin,time_out);

    Bookingtest_Find_Room(make_time(time_in),make_time(time_out));
    return 0;
}

int make_time(string s){ // Year/Month/Day
    string result="";
    for(int i=0;i<s.size();i++){
        if(isdigit(s[i])) result+=s[i];
    }
    return stoi(result);
}

void Bookingtest_Find_Room(int request_in,int request_out){
    ifstream booking_file("booking_test.txt");
    while(true){
        string room;
        if(!getline(booking_file,room)) break;

        vector<int> data_booking;
        bool can_booking = true;

        // Read + Collect data
        string line;
        while(getline(booking_file,line)){
            if(line == "---------------------------------------") break;
            data_booking.push_back(make_time(line));
        }

        // Algorithm
        for(int i=0;i<data_booking.size();i+=2){
            if(request_in<data_booking[i+1] && request_out>data_booking[i]){
                can_booking = false;
                break; 
            }
            if(request_out<=data_booking[i]) break;
        }

        if(can_booking) cout<<"Can Booking "<< room <<"\n";
        else cout<<"Can not Booking "<< room <<"\n";
    }

    booking_file.close();
    return;
}