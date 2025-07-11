# include <iostream>
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
int NumberOfDaysInMonth(int month, int year) {
	int MonthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (IsLeapYear(year) && month == 2)
		return 29;
	else
		return MonthDays[month - 1];
}
int DayOrderInWeek(int day, int month, int year) {
	int a = (4 - month) / 12;
	int y = year - a;
	int m = month + 12 * a - 2;
	return (day + y + (y / 4) - (y / 100) + (y / 400) + (31 * m) / 12) % 7;
}
string MonthName(int month) {
	string months[12] = { "January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};
	return months[month - 1];
}
void MonthCalendarHeader(int month, int year) {
	cout << "\n_____________________ [" << MonthName(month) << "/" << year << "] ____________________________\n\n";
	cout << "Sun\tMon\tTue\tWed\tThu\tFri\tSat\n";
}
void MonthCalendar(int month, int year) {
	MonthCalendarHeader(month, year);
	int start = DayOrderInWeek(1, month, year);
	int MonthDays = NumberOfDaysInMonth(month, year);
	for (int i = 0; i < start; i++) {
		cout << "\t";
	}
	int j = start;
	int counter = 1;
	for (int i = 1; i <= MonthDays; i++) {
		printf("%0*d\t", 2, i);

		j++;
		if (j == 7) {
			cout << endl;
			j = 0;
		}
	}
	cout << "\n______________________________________________________________\n";
}
void YearCalendar(int year) {
	cout << "\n______________________________________________________________\n\n";
	cout << "\t\t Calendar - " << year << endl;
	cout << "______________________________________________________________\n";
	for (int i = 1; i <= 12; i++) {
		MonthCalendar(i, year);
	}
}
int main() {
	int year = ReadNumber("Please Enter The Year: ");
	YearCalendar(year);



	return 0;
}