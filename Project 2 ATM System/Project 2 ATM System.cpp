// Project 2: ATM System.cpp
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<limits>
#include<cctype>
using namespace std;

void Login();
void ShowMainMenu();
void GoBackToMainMenu();
void ShowDepositScreen();
void ShowCheckBalanceScreen();
void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();

//========== Structs & Enums ==========
struct stClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
enum enMainMenuOptions {
	eQuickWithdraw = 1, eNormalWithdraw, eDposit,
	eCheckBalance, eExit = 5
};

stClient CurrentClient;
const string ClientsFileName = "Clients.txt";
void PerformMainMenuOption(enMainMenuOptions);

//========== File Functions ==========
vector<string>Split(string MyString, string Seprartor = "#//#") {
	
	string Word = "";
	vector<string>vString;
	short pos = 0;

	while ((pos = MyString.find(Seprartor))!=std::string::npos) {
		Word = MyString.substr(0, pos);
		if (Word != "")
			vString.push_back(Word);
		MyString.erase(0, pos + Seprartor.length());
	}
	
	if (MyString != "")
		vString.push_back(MyString);

	return vString;
}
stClient ConvertLineToRecord(string MyString, string Seprartor = "#//#") {

	stClient Client;
	vector<string>vClientData = Split(MyString, Seprartor);

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}
string ConvertRecordToLine(stClient Client, string Seprartor = "#//#") {

	string ClientLine = "";

	ClientLine += Client.AccountNumber + Seprartor;
	ClientLine += Client.PinCode + Seprartor;
	ClientLine += Client.Name + Seprartor;
	ClientLine += Client.Phone + Seprartor;
	ClientLine += to_string(Client.AccountBalance);

	return ClientLine;
}
vector<stClient>LoadClientsDataFromFile(const string& FileName) {

	fstream MyFile;
	vector<stClient>vClients;
	string Line;
	stClient Client;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open()) {

		while (getline(MyFile,Line)) {
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}

	return vClients;
}
void SaveClientsDataToFile(const string& FileName, vector<stClient>& vClients) {

	fstream MyFile;
	string Line;

	MyFile.open(FileName, ios::out);

	if (MyFile.is_open()) {
		for (stClient Client : vClients) {
			if (!Client.MarkForDelete) {
				Line = ConvertRecordToLine(Client);
				MyFile << Line << endl;
			}
		}
		MyFile.close();
	}
}

//========== Reading Functions ==========
string ReadAccountNumber() {
	
	string AccountNumber;

	cout << "Enter Account Number? ";
	getline(cin >> ws, AccountNumber);

	return AccountNumber;
}
string ReadPinCode() {

	string PinCode;

	cout << "Enter Pin? ";
	getline(cin >> ws, PinCode);

	return PinCode;
}
double ReadDpositAmount() {

	double Amount = 0;

	cout << "Enter a positive Deposit Amount? ";
	while (!(cin >> Amount) || Amount <= 0) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Amount!, Enter a positive Deposit Amount? ";
	}

	return Amount;
}
char ReadAnswer(const string& UserInput)
{
	char answer = ' ', res = ' ';

	do {
		cout << UserInput;
		cin >> answer;
		res = tolower(answer);
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	} while (res != 'y' && res != 'n');

	return res;
}
int ReadWithdrawAmount() {

	int Amount = 0;

	cout << "Enter an amount multiple of 5's ? ";
	while (!(cin >> Amount) || Amount % 5 != 0 || Amount <= 0) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid! Amount!, Enter an amount multiple of 5's ? ";
	}

	return Amount;
}
short ReadQuickWithdrawOption() {

	short Option = 0;

	cout << "Choose what to do from [1] to [9] ? ";
	while (!(cin >> Option) || Option <= 0 || Option < 1 || Option > 9) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid! Choice!, Choose what to do from [1] to [9] ? ";
	}

	return Option;
}
enMainMenuOptions ReadMainMenuOption() {

	short Option = 0;

	cout << "Choose what do you want to do? [1 to 5]? ";
	while (!(cin >> Option) || Option <= 0 || Option < 1 || Option > 5) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid! Choice!, Choose what do you want to do? [1 to 5]? ";
	}
	
	return static_cast<enMainMenuOptions>(Option);
}

//========== Search & Authentication Functions ==========
bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, stClient& Client) {

	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);

	for (stClient C : vClients) {
		if (AccountNumber == C.AccountNumber && PinCode == C.PinCode) {
			Client = C;
			return true;
		}
	}

	return false;
}
bool LoadClientInfo(string AccountNumber, string PinCode) {

	if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
		return true;
	else 
		return false;
}
void Login() {

	string AccountNumber, PinCode;
	bool LoginFalid = false;

	do {

		system("cls || clear");
		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen\n";
		cout << "---------------------------------\n";
		
		if (LoginFalid)
			cout << "Invalid Account Number/PinCode!\n";

		AccountNumber = ReadAccountNumber();
		PinCode = ReadPinCode();
		LoginFalid = !LoadClientInfo(AccountNumber, PinCode);

	} while (LoginFalid);

	ShowMainMenu();
}

//========== Transactions ==========
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<stClient>&vClients) {

	char Answer = tolower(ReadAnswer("Are you sure you want to perform this transaction? (y/n): "));

	if (Answer == 'y') {
		for (stClient &Client : vClients) {
			if (Client.AccountNumber == AccountNumber) {
				Client.AccountBalance += Amount;
				CurrentClient.AccountBalance += Amount;
				cout << "\n\nDone Successfully. New balance is: " << Client.AccountBalance << "\n";
				break;
			}
		}
		SaveClientsDataToFile(ClientsFileName, vClients);

		return true;
	}
	
	return false;
}
bool WithdrawBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector<stClient>& vClients) {

	return DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vClients);
}
bool QuickWithdrawBalanceToClientByAccountNumber(string AccountNumber, short QuickWithdrawAmount, vector<stClient>& vClients) {

	return DepositBalanceToClientByAccountNumber(AccountNumber, QuickWithdrawAmount * -1, vClients);
}
short GetQuickWithdrawAmount(short QuickWithdrawOption) {

	if (QuickWithdrawOption == 9) 
		return 0;
	
	const short arrQuickWithdrawOptions[8] = {
		20,50,100,200,400,600,800,1000 };

	return arrQuickWithdrawOptions[QuickWithdrawOption - 1];
}

//========== Perform Functions ==========
void PerformMainMenuOption(enMainMenuOptions MainOption) {

	switch (MainOption) {

	case enMainMenuOptions::eQuickWithdraw:
		ShowQuickWithdrawScreen();
		break;

	case enMainMenuOptions::eNormalWithdraw:
		ShowNormalWithdrawScreen();
		break;

	case enMainMenuOptions::eDposit:
		ShowDepositScreen();
		break;

	case enMainMenuOptions::eCheckBalance:
		ShowCheckBalanceScreen();
		break;

	case enMainMenuOptions::eExit:
		Login();
		break;
	}
}
void PerformQuickWithdrawOption(short QuickWithdrawOption) {

	if (QuickWithdrawOption == 9) // exit
		return;
	
	short QuickWithdrawAmount = GetQuickWithdrawAmount(QuickWithdrawOption);

	if (QuickWithdrawAmount > CurrentClient.AccountBalance) {
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Any key to continue...";
		system("pause>0");
		ShowQuickWithdrawScreen();
		return;
	}

	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	QuickWithdrawBalanceToClientByAccountNumber(CurrentClient.AccountNumber,QuickWithdrawAmount, vClients);
}
void PerfromNormalWithdrawOption() {

	int WithdrawAmount = ReadWithdrawAmount();

	if (WithdrawAmount > CurrentClient.AccountBalance) {
		cout << "\nThe amount exceeds you balance, make another choice.\n";
		cout << "Press Any key to continue...";
		system("pause>0");
		ShowNormalWithdrawScreen();
		return;
	}

	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	WithdrawBalanceToClientByAccountNumber(CurrentClient.AccountNumber,WithdrawAmount, vClients);
}
void PerformDepositOption() {

	double DepositAmount = ReadDpositAmount();
	vector<stClient>vClients = LoadClientsDataFromFile(ClientsFileName);
	DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber,DepositAmount, vClients);
}

//========== Menu & Screen Functions ==========
void ShowMainMenu() {

	system("cls || clear");
	cout << "===========================================\n";
	cout << "\t\tAIM Main Menu Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.\n";
	cout << "===========================================\n";

	PerformMainMenuOption(ReadMainMenuOption());
}
void ShowQuickWithdrawScreen() {

	system("cls || clear");
	cout << "===========================================\n";
	cout << "\t\tQuick Withdraw Screen\n";
	cout << "===========================================\n";
	cout << "\t[1] 20\t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 600\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "===========================================\n";
	cout << "Your Balance is: " << CurrentClient.AccountBalance << endl;

	PerformQuickWithdrawOption(ReadQuickWithdrawOption());
	GoBackToMainMenu();
}
void ShowNormalWithdrawScreen() {

	system("cls || clear");
	cout << "===========================================\n";
	cout << "\t\tNormal Withdraw Screen\n";
	cout << "===========================================\n";

	PerfromNormalWithdrawOption();
	GoBackToMainMenu();
}
void ShowDepositScreen() {

	system("cls || clear");
	cout << "===========================================\n";
	cout << "\tDeposit Screen\n";
	cout << "===========================================\n";

	PerformDepositOption();
	GoBackToMainMenu();
}
void ShowCheckBalanceScreen() {

	system("cls || clear");
	cout << "===========================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "===========================================\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
	
	GoBackToMainMenu();
}
void GoBackToMainMenu() {

	cout << "\n\nPress any key to go back to Main Menu...\n";
	system("pause>0");
	ShowMainMenu();
}

int main() {

	Login();

	system("pause>0");
	return 0;
}