#include "user_management/Register.h" //เพิ่ม header ทั้งหมด
#include "user_management/LOGIN.h"
#include "service_management/search.h"
#include <chrono>
#include <thread>

user customer;

void slowPrint(string, int); //function template ตกแต่ง UI
void clearScreen();
string Make_Lower(string);//ทำให้ข้อความกลายเป็นพิมพ์เล็ก

int main(void){
    bool exit = false;
    // Welcome_hotel_starter();

    slowPrint(" --------------------------------------- \n",20);
    slowPrint("|\tWELCOME TO HILBERT HOTEL	|\n",20);  //หน้าจอแสดงผลตอนเริ่มโปรแกรม
    slowPrint(" --------------------------------------- \n",20); 
    slowPrint("|\t       ------------         	|\n",20);
    slowPrint("|\t      | 1.Register |            |\n",20);
    slowPrint("|\t      | 2.Login    |            |\n",20);
    slowPrint("|\t      | 3.Exit     |            |\n",20);
    slowPrint("|\t       ------------         	|\n",20);
    slowPrint("|                                       |\n",20);
    slowPrint(" --------------------------------------- \n",20);
    slowPrint("Please choose your option(1/2/3) : ",20);
    string user_status;
    getline(cin,user_status);

    while(true){
        //REGISTER
        if(user_status=="1" || Make_Lower(user_status)=="register"){ //ผู้ใช้งานเลือกลงทะเบียน
            Register();//function การลงทะเบียน User ใหม่

            while(true){//หลังลงทะเขียนเสร็จ
                cout << "You want to Login?(Yes/No) : ";
                string agian;
                getline(cin,agian);
                if(Register_Make_Lower(agian)=="yes"){//เลือก login
                    clearScreen();
                    login(customer);//function login
                    break;
                }
                else if(Register_Make_Lower(agian)=="no"){//เลือกไม่ login
                    cout << "Thank You for visiting.";
                    return 0;//จบโปรแกรม
                }
                else{
                    cout << "ERROR . . . Your Answer is not Correct\n";//คำตอบไม่ตรง ทำใหม่ซ้ำ
                    continue;
                }
            }
            break;
        }

        //LOG-IN
        else if(user_status=="2" || Make_Lower(user_status)=="login"){ //เลือก login
            clearScreen();
            login(customer);//function login
            break;
        }
        else if(user_status=="3" || Make_Lower(user_status)=="exit"){//เลือก Exit
            cout << "Thank You for visiting." << endl;
            return 0;//จบโปรแกรม
        }
        else{

        cout << "ERROR . . . Your Answer is not Correct\n";//ไม่ได้พิมพ์ 1 2 3
        cout << "Please choose your option(1/2/3) : ";//กลับไปเลือกใหม่
        getline(cin,user_status);
        }  
    }

    // Services Section
    clearScreen();
    cout << "Log in success.\n";
    cout << "Hello " << customer.username << ". Welcome to Hilbert Hotel. \n";
    

    while(true){
        cout << "1.Check in and Check out.\n";
        cout << "2.Show user data and history.\n";
        cout << "3.Exit\n";
        cout << "Please choose your option(1/2/3) : ";
        getline(cin,user_status);
        RoomInfo info[20]; //สร้าง array เก็บข้อมูลห้อง
        int roomleft;
        if(user_status=="1"){
            clearScreen();
            checkin(exit);  //ระบบ check in และ check out 
            clearScreen();
            cout << "Your check-in date is " << check_in.day << "/" << check_in.month << "/" << check_in.years << endl;
            checkout(exit);

            if (exit) { //เลือกจบการใช้งาน
                cout << "Thank You for visiting." << endl;
                return 0; 
            }

            clearScreen();

            cout << "Your check-in date is " << check_in.day << "/" << check_in.month << "/" << check_in.years << endl;
            cout << "Your check-out date is " << check_out.day << "/" << check_out.month << "/" << check_out.years << endl;
            cout << endl;

            int day_num; //นับจำนวนวันที่จอง
            day_num = countDays(check_out) - countDays(check_in);

            cout << "This is a room that Avaliable" << endl;

            
            int roomCount = readfile_pasteinfo(info); //อ่านไฟล์ข้อมูลของห้องพัก
            roomleft=0;
            for (int i = 0; i < roomCount; i++){   //นับจำนวนห้องที่ว่าง
                if (info[i].getTypePtr() != nullptr &&
                    isRoomAvailable(info[i].getNumber(), check_in, check_out)){ //return true or false
                     roomleft++;
                }
            }

             headerinformation();//สร้างหัวตารางสำหรับแสดงรายละเอียดห้อง

            for (int i = 0; i < roomCount; i++){  //แสดงรายละเอียดห้องที่ว่าง (ตาราง)
                if (info[i].getTypePtr() != nullptr &&
                    isRoomAvailable(info[i].getNumber(), check_in, check_out)){
            
                    cout <<"|"<< info[i].getNumber() << " | "
                    << changetype(info[i].getTypePtr()->getType()) << " | ";
                    if(roomleft<10){// ราคาผันตามห้องที่ว่าง
                        cout << info[i].getTypePtr()->getPrice()*1.05*day_num << " Baths" <<"|"<< endl;
                    }else if(roomleft>=18){
                        cout << info[i].getTypePtr()->getPrice()*0.95*day_num << " Baths" <<"|"<< endl;
                    }else{
                        cout << info[i].getTypePtr()->getPrice()*day_num << " Baths" <<"|"<< endl;
                    }
                }
            }
            cout << "-------------------------------------------------------" << endl;

            choose_room(info,roomCount,customer,day_num); //function ให้ผู้ใช้งานเลือกห้อง
            customer.AddHistory(); //บันทึกลงในประวัติการจอง
            cin.get();

            cout << "1.Go back\n"; //กลับมาหน้าหลัก
            cout << "2.Exit\n";
            cout << "Do you want to go back? (1/2) : ";
            getline(cin,user_status);
            while(true){
                if(Make_Lower(user_status) == "1") break;
                else if(Make_Lower(user_status) == "2") {
                    user_status = "3";
                    cout << "Thank You for visiting." << endl;
                    return 0;
                }
                else {
                    cout << "ERROR . . . Your Answer is not Correct\n";
                    cout << "Do you want to go back? (1/2) : ";
                    getline(cin,user_status);
                }
            }

        }

        //LOG-IN
        else if(user_status=="2"){
            clearScreen(); 
            customer.showuserdata(); //แสดงประวัติการของของผู้ใช้งาน
            cout << "1.Go back\n";
            cout << "2.Exit\n";
            cout << "Do you want to go back? (1/2) : ";
            getline(cin,user_status);
            while(true){
                if(Make_Lower(user_status) == "1") break;
                else if(Make_Lower(user_status) == "2") {
                    user_status = "3";
                    cout << "Thank You for visiting." << endl;
                    return 0;
                }
                else {
                    cout << "ERROR . . . Your Answer is not Correct\n";
                    cout << "Do you want to go back? (1/2) : ";
                    getline(cin,user_status);
                }
            }
        }

        else if(user_status=="3" || Make_Lower(user_status)=="exit"){
            cout << "Thank You for visiting." << endl;
            return 0;
        }

        else{
            cout << "ERROR . . . Your Answer is not Correct\n";
            cout << "Please choose your option(1/2/3) : ";
            getline(cin,user_status);      
        }
        clearScreen();
    }
    return 0;
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        // Assume POSIX or other non-Windows
        system("clear");
    #endif
    return;
}

string Make_Lower(string s){ //แปลงข้อความเป็นตัวเล็ก
    string result="";
    for(int i=0;i<s.size();i++) result+=tolower(s[i]);
    return result;
}

void slowPrint(string text, int delay){//แสดงผลบนหน้าจอแบบปรับดีเลย์ได้
    for(char c : text){
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}
