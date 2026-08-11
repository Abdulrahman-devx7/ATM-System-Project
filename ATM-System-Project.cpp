#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <string>
#include <cctype>
#include <iomanip>
#include <climits>
#include <limits>
#include <algorithm>
#include <unordered_map>

using namespace std;
const string CLIENTS_FILE_NAME = "clients.txt";
const string UI_LINE_BOUNDS(44, '=');

enum enRunningState {
    InLoginScreen = 1,
    InsideMainMenu = 2,
};

enum class enMenuChoice {
    QuickWithdraw = 1,
    NormalWithdraw = 2,
    Deposit = 3,
    CheckBalance = 4,
    Logout = 5,
};

enum class enQuickWithdraw {
    Twenty = 1,
    Fifty = 2,
    OneHundred = 3,
    TwoHundred = 4,
    FourHundred = 5,
    SixHundred = 6,
    EightHundred = 7,
    OneThousand = 8,
    Exit = 9
};

struct stNumericInputData
{
    string inputMessage;
    int from = INT_MIN;
    int to = INT_MAX;
    string validationErrorMessage = "Please, enter a valid input!\n";
};

struct stClientData
{
    string accountNumber = "";
    string user_name = "";
    string phoneNumber = "";
    string PIN_Number = "";

    long long balanceUSD = 0;
    bool MarkForDelete = false;
};

struct stLoginCredentials
{
    string accountNumber;
    string inputPassword;
};

void PromptUserToGetMenu()
{
    cout << "\n\nPress any button to get back to the previous menu...";
    system("pause>0");
}

void ShowMainMenu()
{
    cout << UI_LINE_BOUNDS << "\n";
    cout << right << setw(22) << "MAIN MENU" << "\n";
    cout << UI_LINE_BOUNDS << "\n";

    cout << right << setw(10) << "[1]" << " Quick Withdraw" << "\n";
    cout << right << setw(10) << "[2]" << " Normal Withdraw" << "\n";
    cout << right << setw(10) << "[3]" << " Deposit" << "\n";
    cout << right << setw(10) << "[4]" << " Check Balance" << "\n";
    cout << right << setw(10) << "[5]" << " Logout" << "\n";

    cout << UI_LINE_BOUNDS << "\n";
}

vector<string> SplitString(string& S1, string delimiter = "#//#")
{
    vector<string> Words;
    int pos = 0;
    string sWord;

    while ((pos = S1.find(delimiter)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            Words.push_back(sWord);
        }
        S1.erase(0, pos + delimiter.length());
    }

    if (S1 != "")
    {
        Words.push_back(S1);
    }

    return Words;
}

stClientData ConvertClientLineToRecord(string Line, string delimiter = "#//#")
{
    stClientData client;
    vector<string> vClientData = SplitString(Line, delimiter);

    if (vClientData.size() >= 5)
    {
        client.accountNumber = vClientData[0];
        client.PIN_Number = vClientData[1];
        client.user_name = vClientData[2];
        client.phoneNumber = vClientData[3];
        client.balanceUSD = stold(vClientData[4]);

        if (vClientData.size() >= 6)
            client.MarkForDelete = (vClientData[5] == "1");
    }

    return client;
}

void LoadFromFile(string fileName, vector<stClientData>& clients, string delimiter = "#//#")
{
    fstream file;
    file.open(fileName, ios::in);

    if (file.is_open())
    {
        string line = "";
        stClientData client;

        while (getline(file, line))
        {
            client = ConvertClientLineToRecord(line, delimiter);

            if (!client.MarkForDelete)
                clients.push_back(client);
        }
        file.close();
    }
    else return;

}

void LoadFromFile(string fileName, unordered_map<string, stClientData>& clients, string delimiter = "#//#")
{
    fstream file;
    file.open(fileName, ios::in);

    if (file.is_open())
    {
        string line = "";
        stClientData client;

        while (getline(file, line))
        {
            client = ConvertClientLineToRecord(line, delimiter);

            if (!client.MarkForDelete)
                clients.insert({ client.accountNumber, client });
        }
        file.close();
    }
    else return;

}

int ReadNumber(const stNumericInputData& input)
{
    int Number = 0;
    cout << input.inputMessage << endl;
    cin >> Number;

    while (cin.fail() || Number < input.from || Number > input.to
        || (std::cin.peek() != '\n' && std::cin.peek() != EOF))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << input.validationErrorMessage;

        cin >> Number;
    }
    return Number;
}

void ResetScreen()
{
    system("cls");
    system("color 0f");
}

string readAccountNumber()
{
    cout << "Please enter the account number: ";
    string userInput = "";
    cin >> userInput;

    return userInput;
}

string ReadPassword()
{
    string password = "";
    cout << "\nEnter the password: ";
    cin >> password;

    return password;
}


stLoginCredentials ReadLoginCredentials()
{
    stLoginCredentials loginData;

    loginData.accountNumber = readAccountNumber();
    loginData.inputPassword = ReadPassword();

    return loginData;
}

bool VerifyLogin(const stLoginCredentials& loginData, const unordered_map<string, stClientData>& clients)
{
    if (clients.find(loginData.accountNumber) == clients.end())
        return false;
    else
    {
        auto fetchedPassword = clients.find(loginData.accountNumber);
        return loginData.inputPassword == fetchedPassword->second.PIN_Number;
    }
}

void PrintScreenHeader(string ScreenTitle)
{
    cout << "---------------------------------------------\n";
    cout << right << setw(30) << ScreenTitle << "\n";
    cout << "---------------------------------------------\n\n";
}

void ShowQuickWithdrawMenu()
{
    cout << UI_LINE_BOUNDS << "\n";
    cout << right << setw(27) << "Quick Withdraw" << "\n";
    cout << UI_LINE_BOUNDS << "\n";

    cout << left << setw(15) << "[1] 20" << left << setw(15) << "[2] 50" << "\n";
    cout << left << setw(15) << "[3] 100" << left << setw(15) << "[4] 200" << "\n";
    cout << left << setw(15) << "[5] 400" << left << setw(15) << "[6] 600" << "\n";
    cout << left << setw(15) << "[7] 800" << left << setw(15) << "[8] 1000" << "\n";
    cout << left << setw(15) << "[9] Exit" << "\n";

    cout << UI_LINE_BOUNDS << "\n";
}

char DetermineAgain(string message)
{
    char PlayAgain;
    cout << message;
    cin >> PlayAgain;

    while (cin.fail() || (toupper(PlayAgain) != 'N' && toupper(PlayAgain) != 'Y')
        || (std::cin.peek() != '\n' && std::cin.peek() != EOF))
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Please, enter a valid Choice (Y/N)!\n";

        cin >> PlayAgain;
    }
    cin.ignore();

    return PlayAgain;
}

auto FindClientByAccountNumber(const string& userInputAccNumber, unordered_map<string, stClientData>& clients)
{
    auto clientIt = clients.find(userInputAccNumber);

    if (clientIt != clients.end() && clientIt->second.MarkForDelete)
        return clients.end();

    return clientIt;
}

bool CheckExistence(string accountNumber, unordered_map<string, stClientData>& clients)
{
    return clients.contains(accountNumber);
}

int ReadDepositNumber()
{
    stNumericInputData inputData;
    inputData.inputMessage = "Please, enter the amount you would like to deposit\n";
    inputData.from = 0;

    return ReadNumber(inputData);
}

int ReadWithdrawNumber()
{
    stNumericInputData inputData;
    inputData.inputMessage = "\n\nPlease, enter the amount you would like to withdraw.\nThe amount must be a multiple of 5";
    inputData.from = 0;

    return ReadNumber(inputData);
}


void EvaluateMenuChoice(enMenuChoice& menuChoice)
{
    stNumericInputData inputData;
    inputData.inputMessage = "Choose the operation you'd like to do (1-5)\n";
    inputData.from = 1;
    inputData.to = 5;
    inputData.validationErrorMessage = "\nPlease, enter a number in a valid range from the menu (1-5)!\n";

    menuChoice = enMenuChoice(ReadNumber(inputData));
}

void EvaluateMenuChoice(enQuickWithdraw& menuChoice)
{
    stNumericInputData inputData;
    inputData.inputMessage = "Choose what to withdraw from[1] to [8] ? \n";
    inputData.from = 1;
    inputData.to = 9;
    inputData.validationErrorMessage = "\nPlease, enter a number in a valid range from the menu (1-9)!\n";

    menuChoice = enQuickWithdraw(ReadNumber(inputData));
}

int GetQuickWithdrawAmount(const enQuickWithdraw& choice)
{
    switch (choice)
    {
    case enQuickWithdraw::Twenty:
        return 20;
    case enQuickWithdraw::Fifty:
        return 50;
    case enQuickWithdraw::OneHundred:
        return 100;
    case enQuickWithdraw::TwoHundred:
        return 200;
    case enQuickWithdraw::FourHundred:
        return 400;
    case enQuickWithdraw::SixHundred:
        return 600;
    case enQuickWithdraw::EightHundred:
        return 800;
    case enQuickWithdraw::OneThousand:
        return 1000;
    case enQuickWithdraw::Exit:
        return 0;
    default:
        return 0;
    }
}

string ConvertRecordToLine(const stClientData& data, string delimiter = "#//#")
{
    string recordLine = "";

    recordLine += data.accountNumber + delimiter;
    recordLine += data.PIN_Number + delimiter;
    recordLine += data.user_name + delimiter;
    recordLine += data.phoneNumber + delimiter;
    recordLine += to_string(data.balanceUSD) + delimiter;
    recordLine += (data.MarkForDelete ? "1" : "0");

    return recordLine;
}


void SaveToFile(string fileName, unordered_map<string, stClientData>& clients)
{
    fstream file;
    file.open(fileName, ios::out);

    if (file.is_open())
    {
        for (auto& [accountNumber, client] : clients)
        {
            string line = ConvertRecordToLine(client);

            file << line << "\n";
        }
        file.close();
    }
}

bool CheckBalanceForWithdrawal(const stClientData& client, int withdrawalAmount)
{
    if (withdrawalAmount > client.balanceUSD)
        return false;

    else return true;
}


void VerifyBalanceForWithdraw(unordered_map<string, stClientData>::iterator& clientIt, int withdrawAmount)
{
    if (toupper(DetermineAgain("\nAre you sure you want to perform this transaction (Y/N)? ")) == 'Y')
    {
        if (CheckBalanceForWithdrawal(clientIt->second, withdrawAmount))
        {
            clientIt->second.balanceUSD -= withdrawAmount;
            cout << "\n\nDone! Your withdrawal of " << withdrawAmount << " has been successfully completed. Your new balance is: "
                << clientIt->second.balanceUSD << " $\n\n";
        }
    }
}

void VerifyDeposit(unordered_map<string, stClientData>::iterator& clientIt, int depositAmount)
{
    if (toupper(DetermineAgain("\nAre you sure you want to perform this transaction (Y/N)? ")) == 'Y')
    {
        clientIt->second.balanceUSD += depositAmount;

        cout << "\n\nDone! Your deposit of " << depositAmount << " has been added successfully. Your new balance is: "
            << clientIt->second.balanceUSD << " USD\n\n";
    }
}

void DepositLogic(unordered_map<string, stClientData>& systemClients, const string& loggedInAccountNumber)
{
    unordered_map<string, stClientData>::iterator clientIt;

    if ((clientIt = systemClients.find(loggedInAccountNumber)) != systemClients.end())
    {
        int depositAmount = ReadDepositNumber();

        VerifyDeposit(clientIt, depositAmount);
        SaveToFile(CLIENTS_FILE_NAME, systemClients);
    }
}

void QuickWithdrawLogic(unordered_map<string, stClientData>& systemClients, const string& loggedInAccountNumber)
{
    stClientData client = systemClients.find(loggedInAccountNumber)->second;
    cout << "Your balance is: " << client.balanceUSD << " $\n\n";

    enQuickWithdraw quickWithdrawChoice = enQuickWithdraw::Exit;
    EvaluateMenuChoice(quickWithdrawChoice);

    if (quickWithdrawChoice != enQuickWithdraw::Exit)
    {
        int withdrawalAmount = GetQuickWithdrawAmount(quickWithdrawChoice);

        auto clientIt = FindClientByAccountNumber(loggedInAccountNumber, systemClients);

        if (clientIt != systemClients.end())
        {
            VerifyBalanceForWithdraw(clientIt, withdrawalAmount);
            SaveToFile(CLIENTS_FILE_NAME, systemClients);
        }
        else
            cout << "\nClient account not found!\n";
    }
}

void NormalWithdrawLogic(unordered_map<string, stClientData>& systemClients, const string& loggedInAccountNumber)
{
    auto clientIt = FindClientByAccountNumber(loggedInAccountNumber, systemClients);

    if (clientIt != systemClients.end())
    {
        cout << "Your balance is: " << clientIt->second.balanceUSD << " $\n\n";

        int withdrawalAmount = ReadWithdrawNumber();

        if (!CheckBalanceForWithdrawal(clientIt->second, withdrawalAmount))
            cout << "\nThe amount exceeds your balance.\n" <<
            "You can withdraw up to " << clientIt->second.balanceUSD;

        else if (withdrawalAmount % 5 != 0)
        {
            cout << "\nThe inputted number is sufficient but not a multiple of 5.\n";
            cout << "Please ensure your withdrawal amount is a multiple of 5.\n";
        }
        else
        {
            VerifyBalanceForWithdraw(clientIt, withdrawalAmount);
            SaveToFile(CLIENTS_FILE_NAME, systemClients);
        }
    }
    else
        cout << "\nClient account not found!\n";
}

void NormalWithdrawScreen(unordered_map<string, stClientData>& systemClients, const string& loggedInAccountNumber)
{
    PrintScreenHeader("NORMAL WITHDRAW");
    NormalWithdrawLogic(systemClients, loggedInAccountNumber);
}

void DepositScreen(unordered_map<string, stClientData>& systemClients, const string& loggedInAccountNumber)
{
    PrintScreenHeader("DEPOSIT");
    DepositLogic(systemClients, loggedInAccountNumber);
}

void QuickWithdrawScreen(unordered_map<string, stClientData>& systemClients, const string& loggedInAccountNumber)
{
    ShowQuickWithdrawMenu();
    QuickWithdrawLogic(systemClients, loggedInAccountNumber);
}

void CheckBalanceScreen(unordered_map<string, stClientData>& systemClients, const string& loggedInAccountNumber)
{
    PrintScreenHeader("BALANCE INQUIRY");

    auto clientIt = FindClientByAccountNumber(loggedInAccountNumber, systemClients);

    if (clientIt != systemClients.end())
        cout << "\nYour current balance is " << clientIt->second.balanceUSD << " $\n";
    else
        cout << "\nClient account not found!\n";
}

void PerformMainMenuOption(const enMenuChoice choice, unordered_map<string, stClientData>& systemClients, const string& loggedInAccountNumber)
{
    switch (choice)
    {
    case enMenuChoice::QuickWithdraw:
        ResetScreen();
        QuickWithdrawScreen(systemClients, loggedInAccountNumber);
        PromptUserToGetMenu();
        break;

    case enMenuChoice::NormalWithdraw:
        ResetScreen();
        NormalWithdrawScreen(systemClients, loggedInAccountNumber);
        PromptUserToGetMenu();
        break;

    case enMenuChoice::Deposit:
        ResetScreen();
        DepositScreen(systemClients, loggedInAccountNumber);
        PromptUserToGetMenu();
        break;

    case enMenuChoice::CheckBalance:
        ResetScreen();
        CheckBalanceScreen(systemClients, loggedInAccountNumber);
        PromptUserToGetMenu();
        break;

    case enMenuChoice::Logout:
        break;
    }
}

void RunATMServices(unordered_map<string, stClientData>& systemClients, const string& loggedInAccountNumber, enRunningState& state)
{
    enMenuChoice runningUtility = enMenuChoice::Logout;

    do
    {
        ResetScreen();
        ShowMainMenu();

        EvaluateMenuChoice(runningUtility);

        if (runningUtility != enMenuChoice::Logout)
            PerformMainMenuOption(runningUtility, systemClients, loggedInAccountNumber);


    } while (runningUtility != enMenuChoice::Logout);

    state = enRunningState::InLoginScreen;
}

void LoginScreen(unordered_map<string, stClientData>& users, enRunningState& runningState, string& loggedInAccountNumber)
{
    bool isValidUsernameOrPass = true;
    stLoginCredentials loginDetails;

    do
    {
        ResetScreen();
        PrintScreenHeader("LOGIN SCREEN");

        if (!isValidUsernameOrPass)
        {
            cout << "Invalid Username or Password!\n";
            loginDetails = ReadLoginCredentials();
        }
        else
            loginDetails = ReadLoginCredentials();

    } while (!(isValidUsernameOrPass = VerifyLogin(loginDetails, users)));

    loggedInAccountNumber = users.find(loginDetails.accountNumber)->first;

    runningState = enRunningState::InsideMainMenu;
}


void StartATMSystem()
{
    enRunningState RunningState = enRunningState::InLoginScreen;
    string loggedInAccountNumber;

    unordered_map<string, stClientData> systemClients;
    LoadFromFile(CLIENTS_FILE_NAME, systemClients, "#//#");

    do
    {
        if (RunningState == enRunningState::InLoginScreen)
            LoginScreen(systemClients, RunningState, loggedInAccountNumber);

        if (RunningState == enRunningState::InsideMainMenu)
            RunATMServices(systemClients, loggedInAccountNumber, RunningState);

    } while (true);

}

int main()
{
    StartATMSystem();
}