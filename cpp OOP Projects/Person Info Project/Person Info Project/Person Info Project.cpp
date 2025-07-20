# include <iostream>
using namespace std;
class clsEmployee {
private:
	string _Fname, _Lname, _PhoneNumber, _Email, _Department;
	double _Salary;
	char _Gender;
	int _Age;
	int _Id = 10;
	static int _Counter;
public:
	void SetFname(string Fname) {
		_Fname = Fname;
	}
	void SetLname(string Lname) {
		_Lname = Lname;
	}
	void SetPhoneNumber(string PhoneNumber) {
		_PhoneNumber = PhoneNumber;
	}
	void SetEmail(string Email) {
		_Email = Email;
	}
	void SetAge(int Age) {
		_Age = Age;
	}
	void SetGender(char Gender) {
		_Gender = Gender;
	}
	void SetSalary(double Salary) {
		_Salary = Salary;
	}
	void SetDepartment(string Department) {
		_Department = Department;
	}
	string GetFname() {
		return _Fname;
	}
	string GetLname() {
		return _Lname;
	}
	string GetPhoneNumber() {
		return _PhoneNumber;
	}
	string GetEmail() {
		return _Email;
	}
	string GetDepartment() {
		return _Department;
	}
	double GetSalary() {
		return _Salary;
	}
	char GetGender() {
		return _Gender;
	}
	int GetAge() {
		return _Age;
	}
	int GetId() {
		// Id Is Read Only Class Member So It's Dosn't Have a Setter To Edit it
		return _Id;
	}
	string GetFullName() {
		return _Fname + " " + _Lname;
	}
	void PrintEmpInfo() {
		cout << "\n======================================================\n";
		cout << "               EMPLOYEE [" << _Counter << "] INFORMATION\n";
		cout << "======================================================\n";
		cout << "Id          :      " << _Id << endl;
		cout << "First Name  :      " << _Fname << endl;
		cout << "Last Name   :      " << _Lname << endl;
		cout << "Full Name   :      " << GetFullName() << endl;
		cout << "Gender      :      " << _Gender << endl;
		cout << "Age         :      " << _Age << endl;
		cout << "Email       :      " << _Email << endl;
		cout << "Phone Number:      " << _PhoneNumber << endl;
		cout << "Department  :      " << _Department << endl;
		cout << "Salary      :      " << _Salary << " EGP" << endl;
		cout << "--------------------------------------------------\n";
	}
	void SendEmail(string Sub, string Body) {
		cout << "The Following Message Set Successfully To Email: " << _Email << endl;
		cout << "Subject: " << Sub << endl;
		cout << "Body: " << Body << endl;
	}
	void SendSMS(string M) {
		cout << "The Following Message Set Successfully To Phone: " << _PhoneNumber << endl;
		cout << M << endl;
	}
	static int GetTotalEmployeeCount() {
		return _Counter;
	}
	clsEmployee(int Id, string Fname, string Lname, string Email, string PhoneNumber,
		int Age, double Salary, char Gender, string Department) {
		_Id = Id;
		_Fname = Fname;
		_Lname = Lname;
		_Age = Age;
		_PhoneNumber = PhoneNumber;
		_Email = Email;
		_Department = Department;
		_Salary = Salary;
		_Gender = Gender;
		_Counter++;
	}
};
int clsEmployee::_Counter = 0;
int main() {

	clsEmployee Person1(10, "Ahmed", "Nagi", "ahmednagyii69@gmail.com",
		"01025108205", 19, 5000, 'M', "CS");
	Person1.PrintEmpInfo();
	Person1.SendEmail("Hi", "Nice To Meet U :)");
	Person1.SendSMS("How Are U :)");
	cout << endl << endl;


	clsEmployee Person2(11, "Arwaa", "Nagi", "Arwwaa17@gmail.com",
		"0155929505", 22, 20000, 'F', "IT");
	Person2.PrintEmpInfo();
	Person2.SendEmail("Hi", "Happy To See U :)");
	Person2.SendSMS("How Are U :)");
	cout << endl << endl;
	cout << "Total Employees Count = " << clsEmployee::GetTotalEmployeeCount() << endl;

	return 0;
}