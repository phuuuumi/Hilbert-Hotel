#include<fstream>
#include<iostream>
using namespace std;

int main(){
    fstream a("reservation.txt");
    string x = "Heloo";
    a << x;
    a << "hello";

    a.close();
    return 0;
}