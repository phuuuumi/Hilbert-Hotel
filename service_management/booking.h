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

