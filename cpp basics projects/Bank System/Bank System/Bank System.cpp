#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;
const string FileName = "ClientsData.txt";
struct st_ClientInfo {
	string Name, AccountNumber, PhoneNumber, PinCode;
	double AccountBalance;
	bool DeleteFlag = false;
};
enum en_MainMenue { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Exit = 6 };
string ReadAccountNumber() {
	string s;
	cout << "Please Enter Account Number: ";
	getline(cin, s);
	return s;
}
en_MainMenue ReadFromMainMenue() {
	int n;
	system("cls");
	cout << "\n==========================================================================\n";
	cout << "\t\t\t Main Menue Screeen\n";
	cout << "\n==========================================================================\n";
	cout << "\t\t[1] Show Client List.\n";
	cout << "\t\t[2] Add New Client.\n";
	cout << "\t\t[3] Delete Client.\n";
	cout << "\t\t[4] Update Client.\n";
	cout << "\t\t[5] Find Client.\n";
	cout << "\t\t[6] Exit.\n";
	cout << "==========================================================================\n";
	cout << "Choose What Do You Want To Do: ";
	cin >> n;
	cin.ignore();
	while (cin.fail() || n < 0 || n > 6) {
		cin.clear();
		cin.ignore(numeric_limits <streamsize>::max(), '\n');
		cout << "Invalid Input! Try Again: ";
		cin >> n;
		cin.ignore();
	}
	return en_MainMenue(n);
}
st_ClientInfo ReadClientInfo() {
	st_ClientInfo ClientInfo;
	cout << "Please Enter The Client Data: \n\n";
	cout << "Account Number: ";
	getline(cin, ClientInfo.AccountNumber);
	cout << "Pin Code: ";
	getline(cin, ClientInfo.PinCode);
	cout << "Name: ";
	getline(cin, ClientInfo.Name);
	cout << "Phone Number: ";
	getline(cin, ClientInfo.PhoneNumber);
	cout << "Account Balance: ";
	cin >> ClientInfo.AccountBalance;
	cin.ignore();
	return ClientInfo;
}
void PrintClientInfo(st_ClientInfo FilledClientInfo) {
	cout << "Account Number: " << FilledClientInfo.AccountNumber << endl;
	cout << "Pin Code: " << FilledClientInfo.PinCode << endl;
	cout << "Name: " << FilledClientInfo.Name << endl;
	cout << "Phone Number: " << FilledClientInfo.PhoneNumber << endl;
	cout << "Account Balance: " << FilledClientInfo.AccountBalance << endl;
}
string ConvertRecordToLine(st_ClientInfo Record, string Delim = "(**)") {
	string line = "";
	line += Record.AccountNumber + Delim;
	line += Record.PinCode + Delim;
	line += Record.Name + Delim;
	line += Record.PhoneNumber + Delim;
	line += to_string(Record.AccountBalance);
	return line;
}
void SaveClientToFile(st_ClientInfo ClientData) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << ConvertRecordToLine(ClientData) << endl;
		MyFile.close();
	}
}
void AddNewClientToFile() {
	st_ClientInfo NewClient;
	NewClient = ReadClientInfo();
	SaveClientToFile(NewClient);
	cout << "Client Added Successfully.\n";
}
void AddClients() {
	char AddMore = 'y';
	do {
		AddNewClientToFile();
		cout << "Do You Want Add More: ";
		cin >> AddMore;
		system("cls");
		cin.ignore();
	} while (tolower(AddMore) == 'y');
}
vector <string> VSplitString(string s, string Delim = "(**)") {
	int pos = 0;
	string word = "";
	vector <string> Vwords;
	while ((pos = s.find(Delim)) != s.npos) {
		word = s.substr(0, pos);
		if (word != "")
			Vwords.push_back(word);
		s.erase(0, pos + Delim.length());
	}
	if (s != "")
		Vwords.push_back(s);
	return Vwords;
}
st_ClientInfo ConvertLineToRecord(string Line, string Delim = "(**)") {
	vector<string> VClientData = VSplitString(Line);
	st_ClientInfo ClientData;
	ClientData.AccountNumber = VClientData[0];
	ClientData.PinCode = VClientData[1];
	ClientData.Name = VClientData[2];
	ClientData.PhoneNumber = VClientData[3];
	ClientData.AccountBalance = stod(VClientData[4]);
	return ClientData;
}
vector <st_ClientInfo> VLoadDataFromFile() {
	st_ClientInfo ClientInfo;
	vector <st_ClientInfo> VAllClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	string l;
	if (MyFile.is_open()) {
		while (getline(MyFile, l)) {
			ClientInfo = ConvertLineToRecord(l);
			VAllClients.push_back(ClientInfo);
		}
		MyFile.close();
	}
	return VAllClients;
}
void PrintAllClientsInfo(vector<st_ClientInfo> VAllClients) {
	cout << "\n\t\t\t\t\tClient List (" << VAllClients.size() << ") Client(s).\n";
	cout << "\n_________________________________________________________________________________\n";
	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << setw(10) << "Pin Code"
		<< "| " << setw(20) << "Name"
		<< "| " << setw(15) << "Phone Number"
		<< "| " << setw(15) << "Balance" << " |\n";
	cout << "---------------------------------------------------------------------------------\n";

	for (st_ClientInfo Client : VAllClients) {
		cout << "| " << left << setw(15) << Client.AccountNumber
			<< "| " << setw(10) << Client.PinCode
			<< "| " << setw(20) << Client.Name
			<< "| " << setw(15) << Client.PhoneNumber
			<< "| " << setw(15) <<  Client.AccountBalance << " |\n";
	}
	cout << "_________________________________________________________________________________\n";
}
bool FindClientByAccountNumber(string AccountNumber, vector <st_ClientInfo> VAllClients, st_ClientInfo& Client) {
	for (st_ClientInfo C : VAllClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}
void SaveAllClientsToFileAfterEdite(vector<st_ClientInfo> VAllClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (st_ClientInfo C : VAllClients) {
			if (C.DeleteFlag == false)
				MyFile << ConvertRecordToLine(C) << endl;
		}
		MyFile.close();
	}
}
bool MarkClientFlagToDelete(string AccountNumber, vector <st_ClientInfo>& VAllClients) {
	for (st_ClientInfo& C : VAllClients) {
		if (C.AccountNumber == AccountNumber) {
			C.DeleteFlag = true;
			return true;
		}
	}
	return false;
}
bool DeleteClientFromFile(string AccountNumber, vector<st_ClientInfo>& VAllClients) {
	VAllClients = VLoadDataFromFile();
	st_ClientInfo Client;
	char DeleteClient = 'n';
	if (FindClientByAccountNumber(AccountNumber, VAllClients, Client)) {
		PrintClientInfo(Client);
		cout << "\nAre You Sure You Want To Delete This Client? [y/n]: ";
		cin >> DeleteClient;
		if (tolower(DeleteClient) == 'y') {
			if (MarkClientFlagToDelete(AccountNumber, VAllClients)) {
				SaveAllClientsToFileAfterEdite(VAllClients);
				cout << "Client Deleted Successfully.\n";
				return true;
			}
		}
		else {
			cout << "Client Not Deleted.\n";
		}
	}
	else {
		cout << "\nClient with Account Number " << AccountNumber << " is Not Found!\n";
	}
	return false;
}
st_ClientInfo ChangeClientRecord(string AccountNumber) {
	st_ClientInfo Client;
	Client.AccountNumber = AccountNumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin,Client.PinCode);
	cout << "Enter Name? ";
	getline(cin, Client.Name);
	cout << "Enter Phone? ";
	getline(cin, Client.PhoneNumber);
	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;
	cin.ignore();
	return Client;
}
bool UpdateClientInfo(string AccountNumber, vector<st_ClientInfo>& VAllClients) {
	VAllClients = VLoadDataFromFile();
	st_ClientInfo Client;
	char UpdateClient = 'n';
	if (FindClientByAccountNumber(AccountNumber, VAllClients, Client)) {
		PrintClientInfo(Client);
		cout << "\nAre You Sure You Want To Update This Client? [y/n]: ";
		cin >> UpdateClient;
		if (tolower(UpdateClient) == 'y') {
			for (st_ClientInfo& C : VAllClients) {
				if (C.AccountNumber == AccountNumber) {
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveAllClientsToFileAfterEdite(VAllClients);
			cout << "Client Updated Successfully.\n";
			return true;
		}
	}
	else {
		cout << "\nClient with Account Number " << AccountNumber << " is Not Found!\n";
	}
	return false;
}
void DoSomeThing(en_MainMenue MainMenueChoice) {
	vector <st_ClientInfo> VAllClients = VLoadDataFromFile();
	if (MainMenueChoice == en_MainMenue::Add) {
		system("cls");
		cout << "\n-----------------------------------------------\n";
		cout << "\tAdd New Clients Screen";
		cout << "\n-----------------------------------------------\n";
		AddClients();
	}
	else if (MainMenueChoice == en_MainMenue::Show) {
		system("cls");
		PrintAllClientsInfo(VAllClients);
	}
	else if (MainMenueChoice == en_MainMenue::Find) {
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "\tFind Client Screen";
		cout << "\n-------------------------------------------\n";
		string AccountNumber = ReadAccountNumber();
		st_ClientInfo Client;
		if (FindClientByAccountNumber(AccountNumber, VAllClients, Client))
			PrintClientInfo(Client);
		else {
			cout << "Client with Account Number " << AccountNumber << " Is Not Found!\n";
		}
	}
	else if (MainMenueChoice == en_MainMenue::Delete) {
		system("cls");
		cout << "\n-------------------------------------------\n";
		cout << "\tDelete Client Screen";
		cout << "\n-------------------------------------------\n\n";
		string AccountNumber = ReadAccountNumber();
		DeleteClientFromFile(AccountNumber, VAllClients);
	}
	else if (MainMenueChoice == en_MainMenue::Update) {
		system("cls");
		cout << "\n------------------------------------------\n";
		cout << "\tUpdate Client Info Screen";
		cout << "\n------------------------------------------\n\n";
		string AccountNumber = ReadAccountNumber();
		UpdateClientInfo(AccountNumber, VAllClients);
	}
	else if (MainMenueChoice == en_MainMenue::Exit) {
		system("cls");
		cout << "\n-----------------------------------------------\n";
		cout << "\nExiting program... Goodbye :( \n";
		cout << "\n-----------------------------------------------\n\n";
		exit(0);
	}
	cout << "\nPress Enter to return to Main Menu...";
	cin.get();
}
int main() {
	while (true) {
		DoSomeThing(ReadFromMainMenue());
	}
	return 0;
}