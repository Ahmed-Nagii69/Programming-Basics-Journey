# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <vector>
using namespace std;

enum en_MainMenueOptions { Show = 1, Add = 2, Delete = 3, Update = 4, Find = 5, Transactions = 6, Exit = 7 };
enum en_TransactionsMenueOptions { Deposite = 1, WithdraW = 2, Total = 3, Main = 4 };

void ShowMainMenueScreen();
void ShowTransactionsScreen();

en_MainMenueOptions ReadMainMenue() {
	int n;
	cin >> n;
	return en_MainMenueOptions(n);
}
en_TransactionsMenueOptions ReadTransactionsMenueOption() {
	int n;
	cin >> n;
	return en_TransactionsMenueOptions(n);
}

string FileName = "ClientsInfo.txt";

struct st_ClientInfo {
	string Name, AccountNumber, PhoneNumber, PinCode;
	double AccountBalance;
	bool DeleteFlag = false;
};

int ReadNumber(string message) {
	int n;
	cout << message;
	cin >> n;
	return n;
}

st_ClientInfo ReadClientInfo() {
	st_ClientInfo ClientInfo;
	cout << "Please Enter Client Info: \n\n";
	cout << "Account Number: ";
	cin.ignore();
	getline(cin, ClientInfo.AccountNumber);
	cout << "Name: ";
	getline(cin, ClientInfo.Name);
	cout << "Pin Code:  ";
	getline(cin, ClientInfo.PinCode);
	cout << "Phone Number:  ";
	getline(cin, ClientInfo.PhoneNumber);
	cout << "Account Balance:  ";
	cin >> ClientInfo.AccountBalance;
	cin.ignore();
	return ClientInfo;
}

void PrintClientInfo(st_ClientInfo FilledClient) {
	cout << "_______________________________________________________________\n\n";
	cout << "Account Number: " << FilledClient.AccountNumber << endl;
	cout << "Name: " << FilledClient.Name << endl;
	cout << "Pin Code: " << FilledClient.PinCode << endl;
	cout << "Phone Number: " << FilledClient.PhoneNumber << endl;
	cout << "Account Balance: " << FilledClient.AccountBalance << endl;
	cout << "_______________________________________________________________\n";
}

string ConvertRecordToLine(st_ClientInfo ClientRecord, string Delim = "(**)") {
	string line = "";
	line += ClientRecord.AccountNumber + Delim;
	line += ClientRecord.PinCode + Delim;
	line += ClientRecord.Name + Delim;
	line += ClientRecord.PhoneNumber + Delim;
	line += to_string(ClientRecord.AccountBalance);
	return line;
}

vector <string> SplitString(string s, string Delim = "(**)") {
	string word = "";
	int pos = 0;
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

st_ClientInfo ConvertLineToRecord(string ClientLine, string Delim = "(**)") {
	vector <string> ClientData;
	st_ClientInfo ClientInfo;
	ClientData = SplitString(ClientLine, Delim);
	ClientInfo.AccountNumber = ClientData[0];
	ClientInfo.PinCode = ClientData[1];
	ClientInfo.Name = ClientData[2];
	ClientInfo.PhoneNumber = ClientData[3];
	ClientInfo.AccountBalance = stod(ClientData[4]);
	return ClientInfo;
}

void SaveClientInfoToFile(st_ClientInfo Client) {
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << ConvertRecordToLine(Client) << endl;
		MyFile.close();
	}
}

vector <st_ClientInfo> LoadDataFromFile() {
	vector <st_ClientInfo> AllClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);
	string line;
	if (MyFile.is_open()) {
		while (getline(MyFile, line)) {
			AllClients.push_back(ConvertLineToRecord(line));
		}
		MyFile.close();
	}
	return AllClients;
}

void AddNewClientToFile() {
	st_ClientInfo NewClient = ReadClientInfo();
	SaveClientInfoToFile(NewClient);
	cout << "Client Saved To File Successfully!\n";
}

void AddNewClients() {
	char AddMore = 'y';
	do {
		system("cls");
		AddNewClientToFile();
		cout << "Do You Want Add More Clients [y , n]: ";
		cin >> AddMore;
	} while (tolower(AddMore) == 'y');
}

void ShowAllClientsInfo(vector <st_ClientInfo> AllClients) {
	cout << "\t\t\t[  Clients List Contians: " << AllClients.size() << " Client(s)  ]\n\n";
	for (st_ClientInfo Client : AllClients) {
		PrintClientInfo(Client);
	}
}

string ReadAccountNumber() {
	string s;
	cout << "Please Enter Account Number: ";
	cin >> s;
	return s;
}

void SaveClientsToFileAfterEdit(vector <st_ClientInfo> AllClients) {
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open()) {
		for (st_ClientInfo Client : AllClients) {
			if (!Client.DeleteFlag)
				MyFile << ConvertRecordToLine(Client) << endl;
		}
		MyFile.close();
	}
}

bool IsClientExist(vector <st_ClientInfo> AllClients, string AccNum, st_ClientInfo& C) {
	for (st_ClientInfo Client : AllClients) {
		if (Client.AccountNumber == AccNum) {
			C = Client;
			return true;
		}
	}
	return false;
}

bool MarkFlagToDeleteClient(vector <st_ClientInfo>& AllClients, string AccNum) {
	for (st_ClientInfo& Client : AllClients) {
		if (Client.AccountNumber == AccNum) {
			Client.DeleteFlag = true;
			return true;
		}
	}
	return false;
}

bool DeleteClientByAccountNumber(vector<st_ClientInfo>& AllClients, string AccNum) {
	st_ClientInfo c;
	char DeleteClient = 'n';
	if (IsClientExist(AllClients, AccNum, c)) {
		PrintClientInfo(c);
		cout << "\nAre You Sure You Want To Delete This Client? [y/n]: ";
		cin >> DeleteClient;
		if (tolower(DeleteClient) == 'y') {
			MarkFlagToDeleteClient(AllClients, AccNum);
			SaveClientsToFileAfterEdit(AllClients);
			cout << "\nClient Deleted Successfully!\n";
			return true;
		}
		else {
			cout << "\nClient Deletion Cancelled :)\n";
		}
	}
	else {
		cout << "\nClient Not Found :(\n";
	}
	return false;
}

st_ClientInfo UpdateClient(string AccNum) {
	st_ClientInfo Client;
	Client.AccountNumber = AccNum;
	cout << "Please Enter New Client Info:\n\n";
	cout << "New Name: ";
	cin.ignore();
	getline(cin, Client.Name);
	cout << "New Pin Code: ";
	getline(cin, Client.PinCode);
	cout << "New Phone Number: ";
	getline(cin, Client.PhoneNumber);
	cout << "New Account Balance: ";
	cin >> Client.AccountBalance;
	cin.ignore();
	return Client;
}

bool UpdateClientInfo(vector<st_ClientInfo>& AllClients, string AccNum) {
	st_ClientInfo c;
	char UpdateInfo = 'y';
	if (IsClientExist(AllClients, AccNum, c)) {
		PrintClientInfo(c);
		cout << "\nAre You Sure You Want To Update This Client Info? [y/n]: ";
		cin >> UpdateInfo;
		if (tolower(UpdateInfo) == 'y') {
			for (st_ClientInfo& Client : AllClients) {
				if (Client.AccountNumber == AccNum) {
					Client = UpdateClient(AccNum);
					break;
				}
			}
			SaveClientsToFileAfterEdit(AllClients);
			cout << "\nClient Info Updated Successfully.\n";
			return true;
		}
		else {
			cout << "\nClient Update Cancelled :)\n";
		}
	}
	else {
		cout << "\nClient Not Found :(\n";
	}
	return false;
}

void Deposit() {
	vector <st_ClientInfo> AllClients = LoadDataFromFile();
	st_ClientInfo c;
	string AccNum = ReadAccountNumber();
	if (IsClientExist(AllClients, AccNum, c)) {
		PrintClientInfo(c);
		int d = ReadNumber("\nPlease Enter Deposit Amount: ");
		if (d <= 0) {
			cout << "Amount must be greater than 0.\n";
			return;
		}
		for (st_ClientInfo& Client : AllClients) {
			if (Client.AccountNumber == AccNum) {
				Client.AccountBalance += d;
				SaveClientsToFileAfterEdit(AllClients);
				cout << "\nTransaction Successful.\n";
				break;
			}
		}
	}
	else {
		cout << "Client Not Found:(\n";
	}
}

void Withdraw() {
	vector <st_ClientInfo> AllClients = LoadDataFromFile();
	st_ClientInfo c;
	string AccNum = ReadAccountNumber();
	if (IsClientExist(AllClients, AccNum, c)) {
		PrintClientInfo(c);
		int d = ReadNumber("\nPlease Enter Withdraw Amount: ");
		if (d <= 0) {
			cout << "Amount must be greater than 0.\n";
			return;
		}
		if (d > c.AccountBalance) {
			cout << "Insufficient Balance.\n";
			return;
		}
		for (st_ClientInfo& Client : AllClients) {
			if (Client.AccountNumber == AccNum) {
				Client.AccountBalance -= d;
				SaveClientsToFileAfterEdit(AllClients);
				cout << "\nTransaction Successful.\n";
				break;
			}
		}
	}
	else {
		cout << "Client Not Found:(\n";
	}
}

void DepositScreen() {
	cout << "------------------------------------------\n";
	cout << "\t\t Deposit Screen\n";
	cout << "------------------------------------------\n";
	Deposit();
}

void WithdrawScreen() {
	cout << "------------------------------------------\n";
	cout << "\t\t Withdraw Screen\n";
	cout << "------------------------------------------\n";
	Withdraw();
}

void PrintClientBalance(st_ClientInfo Client) {
	cout << "------------------------------------------\n";
	cout << "Client Account Number: " << Client.AccountNumber << endl;
	cout << "Client Name: " << Client.Name << endl;
	cout << "Client Balance: " << Client.AccountBalance << endl;
	cout << "------------------------------------------\n";
}

void TotalBalancesScreen(vector <st_ClientInfo> AllClients) {
	double totalbalance = 0;
	for (st_ClientInfo Client : AllClients) {
		PrintClientBalance(Client);
		totalbalance += Client.AccountBalance;
	}
	cout << "\n\t\t\tAll Clients Balance = " << totalbalance << endl;
}

void GoBackToTransactionsScreen() {
	cout << "\n\n\nPress any key to go back to Transactions Screen....\n";
	system("pause>0");
	system("cls");
	ShowTransactionsScreen();
}

void GoBackToMainMenueScreen() {
	cout << "\n\n\nPress any key to go back to main menue....\n";
	system("pause>0");
	system("cls");
	ShowMainMenueScreen();
}

void PerformTransactionOption(en_TransactionsMenueOptions Option) {
	vector <st_ClientInfo> AllClients = LoadDataFromFile();
	if (Option == en_TransactionsMenueOptions::Deposite) {
		system("cls");
		DepositScreen();
		GoBackToTransactionsScreen();
	}
	if (Option == en_TransactionsMenueOptions::WithdraW) {
		system("cls");
		WithdrawScreen();
		GoBackToTransactionsScreen();
	}
	if (Option == en_TransactionsMenueOptions::Total) {
		system("cls");
		TotalBalancesScreen(AllClients);
		GoBackToTransactionsScreen();
	}
	if (Option == en_TransactionsMenueOptions::Main) {
		system("cls");
		GoBackToMainMenueScreen();
	}
}

void PerformMainMenueOption(en_MainMenueOptions Option) {
	vector <st_ClientInfo > AllClients = LoadDataFromFile();
	if (Option == en_MainMenueOptions::Show) {
		system("cls");
		ShowAllClientsInfo(AllClients);
		GoBackToMainMenueScreen();
	}
	if (Option == en_MainMenueOptions::Add) {
		system("cls");
		AddNewClients();
		GoBackToMainMenueScreen();
	}
	if (Option == en_MainMenueOptions::Find) {
		system("cls");
		st_ClientInfo C;
		string AccNum = ReadAccountNumber();
		if (IsClientExist(AllClients, AccNum, C))
			PrintClientInfo(C);
		else
			cout << "Client With Account Number: " << AccNum << " Isn't Exist\n";
		GoBackToMainMenueScreen();
	}
	if (Option == en_MainMenueOptions::Exit) {
		system("cls");
		exit(0);
	}
	if (Option == en_MainMenueOptions::Delete) {
		system("cls");
		string AccNum = ReadAccountNumber();
		DeleteClientByAccountNumber(AllClients, AccNum);
		GoBackToMainMenueScreen();
	}
	if (Option == en_MainMenueOptions::Update) {
		system("cls");
		string AccNum = ReadAccountNumber();
		UpdateClientInfo(AllClients, AccNum);
		GoBackToMainMenueScreen();
	}
	if (Option == en_MainMenueOptions::Transactions) {
		system("cls");
		ShowTransactionsScreen();
	}
}

void ShowTransactionsScreen() {
	cout << "==========================================================\n";
	cout << "\t\t Transactions Menue Screen\n";
	cout << "==========================================================\n";
	cout << "[1] Deposite.\n";
	cout << "[2] Withdraw.\n";
	cout << "[3] Total Balances.\n";
	cout << "[4] Main Menue.\n";
	cout << "==========================================================\n";
	cout << "Choose What Do You Want To Do? [1 to 4]: ";
	PerformTransactionOption(ReadTransactionsMenueOption());
}

void ShowMainMenueScreen() {
	cout << "==========================================================\n";
	cout << "\t\t Main Menue Screen\n";
	cout << "==========================================================\n";
	cout << "[1] Show Clients List.\n";
	cout << "[2] Add New Client.\n";
	cout << "[3] Delete Client.\n";
	cout << "[4] Update Client.\n";
	cout << "[5] Find Client.\n";
	cout << "[6] Transactions Menue.\n";
	cout << "[7] Exit Screen.\n";
	cout << "==========================================================\n";
	cout << "Choose What Do You Want To Do? [1 to 7]: ";
	PerformMainMenueOption(ReadMainMenue());
}

int main() {
	ShowMainMenueScreen();
	return 0;
}
