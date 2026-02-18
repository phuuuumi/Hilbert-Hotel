#include <iostream>
#include <cstdlib>

using namespace std;

// Function Name Zone
void Welcome_clearScreen();
void Welcome_hotel_starter();

void Welcome_clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        // Assume POSIX or other non-Windows
        system("clear");
    #endif
    return;
}

void Welcome_hotel_starter(){
    Welcome_clearScreen();
    cout << "-Welcome to Hilbert-Hotel-\n";
    cout << "1.Register\n";
    cout << "2.Login\n";
    cout << "Please choose your option(1/2) : ";
    return;
}