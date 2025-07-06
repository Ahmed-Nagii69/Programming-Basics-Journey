#include <iostream>
#include <iomanip>
using namespace std;

int ReadNumber(string message) {
    int n;
    cout << message;
    cin >> n;
    return n;
}

bool IsLeapYear(int year) {
    return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}

int DaysInMonth(int month, int year) {
    int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (IsLeapYear(year) && month == 2)
        return 29;
    else
        return days[month - 1];
}

string MonthName(int month) {
    string months[12] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return months[month - 1];
}

int DayOrder(int day, int month, int year) {
    int a = (14 - month) / 12;
    int y = year - a;
    int m = month + 12 * a - 2;
    return (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m / 12)) % 7;
}

void CalendarHeader(int month, int year) {
    cout << "____________________________ " << MonthName(month) << " " << year << " __________________________\n\n";
    cout << "Sun\tMon\tTue\tWed\tThu\tFri\tSat\n";
}

void MonthCalendar(int month, int year) {
    CalendarHeader(month, year);

    int daysInMonth = DaysInMonth(month, year);
    int start = DayOrder(1, month, year);

    for (int i = 0; i < start; i++)
        cout << "\t";

    for (int day = 1; day <= daysInMonth; day++) {
        printf("%0*d\t", 2, day);

        if ((start + day) % 7 == 0)
            cout << "\n";
    }

    cout << "\n____________________________________________________________________\n\n";
}

void YearCalendar(int year) {
    cout << "____________________________________________________________________\n";
    cout << "\t\t Calender " << year << endl;
    cout << "____________________________________________________________________\n\n";
    for (int i = 1; i <= 12; i++)
        MonthCalendar(i, year);
}

int main() {
    int year = ReadNumber("Please Enter The Year: ");
    YearCalendar(year);
    return 0;
}
