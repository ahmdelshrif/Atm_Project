#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
const string ClientsFileName = "Clients.txt";
void Login();
void showQuickWithdraw();
void ShowMainManue();
void showNormalWithdraw();
struct sClient{
string AccountNumber;
string Name;
string PinCode;
string Phone;
double AccountBalance;
bool MarkForDelete = false;
};

enum EnAtmClinets{qwithdraw=1, Nwithdraw=2, Deposit=3, CheckBalnce=4, Exit=5};

sClient consClient;

vector<string> SplitString(string S1, string Delim) {
	vector<string> vString;
	short pos = 0;
	string SWord;
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		SWord = S1.substr(0, pos);    
		if (SWord !=""){
			vString.push_back(SWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
sClient ConvertLinetoRecord(string Line, string Seperator = "//")
{
	vector<string> Vstring = SplitString(Line, Seperator);
	sClient Client;
	Client.AccountNumber = Vstring[0];
	Client.Name = Vstring[1];
    Client.PinCode=Vstring[2];
	Client.Phone = Vstring[3];
	Client.AccountBalance =stoi(Vstring[4]);
	return Client;
}
string ConvertRecordtoLine(sClient Client)
{
	string Line;
	Line = Client.AccountNumber + "//";
	Line += Client.Name + "//";
	Line += Client.PinCode + "//";
	Line += Client.Phone + "//";
	Line += to_string(Client.AccountBalance);
	return Line;
}
vector<sClient> LoadDateFromFile(string Clints)
{
	vector<sClient>Vsclinet;
	string line;
	sClient client;
	fstream Myfile;

	Myfile.open(Clints, ios::in);
	{
		if (Myfile.is_open())
		{
			while (getline(Myfile, line))
			{
				client = ConvertLinetoRecord(line, "//");
				Vsclinet.push_back(client);
			}
		}
		Myfile.close();
	}
	return Vsclinet;
}
bool CheckAccountAndPin(string Accoun,string pin, sClient &User)
{
	vector <sClient> vsclinet=LoadDateFromFile(ClientsFileName);
	for (sClient  U : vsclinet)
	{
		if ( U.AccountNumber==Accoun && U.PinCode==pin) {
			User = U;
			return true;
		}
	}
		return false;
}
bool LoadAccounInfo(string Accoun,string pin)
{
	if (CheckAccountAndPin( Accoun, pin, consClient))
		return true;
	else
		return false;

}
void SaveDatefromFile(string Clinet,vector<sClient>V1)
{
	string line;
	fstream Myfile;
	Myfile.open(Clinet, ios::out );
	{
		if (Myfile.is_open())
		{
			for (sClient u : V1)
			{
				if (u.MarkForDelete == false) {

					line = ConvertRecordtoLine(u);
					Myfile << line << endl;

				}
			}
		}
	}
}
void saveDate()
{
	vector <sClient> VClinet = LoadDateFromFile(ClientsFileName);

	for (sClient &u : VClinet) {
		if (u.AccountNumber == consClient.AccountNumber)
		{
			u.AccountBalance = consClient.AccountBalance;
		}
	}

	SaveDatefromFile(ClientsFileName, VClinet);
}
void checkBalnce()
{

	cout << "==================================" << endl;
	cout << setw(10) << " Check Balance        " << endl;
	cout << "====================================" << endl;
	cout << "\nThe Balnce is " << consClient.AccountBalance<<endl;
	cout << "\n\n";

	system("pause");
	system("cls");
	ShowMainManue();
}
bool Balncecheck(short Num)
{
	if (consClient.AccountBalance < Num)
		return false;
	else
		return true;
}
void JokrkWithdrawAndDeposit(int Num)
{
	string  sure ;

	if (Balncecheck(Num)) {
		cout << "\n\nAre you sure you want perform this transaction ? y/n ";
		cin >> sure;

		if (sure == "n" || sure == "N")
		{
			system("cls");
			ShowMainManue();
		}
		else {

			consClient.AccountBalance = consClient.AccountBalance - Num;
			cout << "\n\nDone Succsessfully. Now Balance is : " << consClient.AccountBalance<<endl;
			saveDate();
			system("pause");
			system("cls");

			ShowMainManue();
		}

	}
	else {

		cout << "\n\nSorry The Balance is insufficient The Balnace is : "<<consClient.AccountBalance<<endl ;
		system("pause");
		system("cls");

		showQuickWithdraw();
	}

}
void NormalWithdraw(int i)
{
	if (Balncecheck(i))
	{

		JokrkWithdrawAndDeposit(i);
	}
	else {

		cout << "\n\nSorry The Balance is insufficient The Balnace is : " << consClient.AccountBalance << endl;
		system("pause");
		system("cls");

		showNormalWithdraw();
	}
}
void NormalDepsit()
{
	string sure;

	int i;
	cout << "==================================" << endl;
	cout << setw(10) << " Depsoit       " << endl;
	cout << "====================================" << endl;
	cout << "Enter an amount multiple 5? ";
	cin >> i;
	i = -1 * i;

	JokrkWithdrawAndDeposit(i);
}
void showNormalWithdraw()
{
	int i;
	cout << "==================================" << endl;
	cout << setw(10) << " Normal Withdraw       " << endl;
	cout << "====================================" << endl;

	do {

		cout << "Enter an amount multiple 5? ";
		cin >> i;

	} while (i % 5 != 0);

	NormalWithdraw(i);

}
void showQuickWithdraw()
{
	int Arr[10] = { 0,20,50,100,200,400,600,800,1000,1 };

	int i;
	cout << "==================================" << endl;
	cout << setw(10) << " Quick Withdraw       " << endl;
	cout << "====================================" << endl;
	cout << "   [1] 20                  [2]50" << endl;
	cout << "   [3]100                  [4]200" << endl;
	cout << "   [5]400                  [6]600" << endl;
	cout << "   [7]800                  [8]1000" << endl;
	cout << "   [9]Exit                   " << endl;
	cout << "==========================================" << endl;
	cout << "Your Balnce is " << consClient.AccountBalance<<endl;
	cout << "Chose Number ? ";
	cin >> i;

	if (Arr[i] == 1)
	{

		system("cls");
		ShowMainManue();
	}

	JokrkWithdrawAndDeposit(Arr[i]);
}
void EnteringMenua(EnAtmClinets Number)
{
	switch (Number)
	{
	case EnAtmClinets:: qwithdraw:
		system("Cls");
		showQuickWithdraw();
		break;

	case EnAtmClinets::Nwithdraw:
		system("Cls");
		showNormalWithdraw();
		break;

	case EnAtmClinets::Deposit:
		system("Cls");
		NormalDepsit();
		break;

	case EnAtmClinets::CheckBalnce:
		system("Cls");
		checkBalnce();
		break;

	case EnAtmClinets::Exit:
		system("Cls");
		Login();
		break;
	}
}
void ShowMainManue()
{
	int i;
	cout << setw(10) << "========================================" << endl;
	cout << setw(5) <<  " Main Manue " << endl;
	cout << setw(10) << "========================================" << endl;
	cout << setw(10) << "[1]" << "Quick Withdraw " << endl;
	cout << setw(10) << "[2]" << "Normal Withdraw " << endl;
	cout << setw(10) << "[3]" << "Depos it " << endl;
	cout << setw(10) << "[4]" << "check Balnce " << endl;
	cout << setw(10) << "[5]" << "Login " << endl;
	cout << "=======================================================" << endl;
	cout << "Choose what do you want ?";
	cin >> i;

	EnteringMenua(EnAtmClinets(i));
}
void Login()
{
	bool LoginFild = false;
	string Account, Pincod;
	do {
		cout << setw(10) << "========================================" << endl;
		cout << setw(5) << " Login Screen " << endl;
		cout << setw(10) << "============================================" << endl;

		if (LoginFild)
		{
			cout << "Invaled AccountNum/PinCode"<<endl;
		}
		cout << "Enter AccounNum ? ";
		cin >> Account;

		cout << "Enter Pincode ? ";
		cin >> Pincod;

		LoginFild = !LoadAccounInfo(Account, Pincod);
		system("cls");

	} while (LoginFild);

	system("cls");
	ShowMainManue();
}
int main()
{
	Login();
}