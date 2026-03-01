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
