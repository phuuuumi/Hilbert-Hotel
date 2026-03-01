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