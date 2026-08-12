# The ATM Machine 
A simple extension of the bank management system project, built with a similar structure to the bank system, but specifically for clients to interact with like an actual ATM
## 📝 The Objectives
- Practice function reusability involving several purposes (e.g., File I/O, string manipulation, UI, and business logic functions)
- Create a specialized client interface that serves and interacts with the main bank management system.
- Practice something closer to actual SWE environments, in which a restricted subsystem would be needed to fetch data from a larger system for the user to interact with.
- Use a different flow for data, in which a direct reference to the user is initialized and is passed between the ATM utilities to grant quick, direct access instead of needing to search every time an operation is done.
## 🚀 Core features
- A simple login page that authorizes access to the ATM using the account number and PIN number.
- A numerical validation that prevents crashes or infinite loops in input fields where a numerical value is expected.
- A basic UI menu that presents the users with basic ATM services:
  - A quick withdraw menu with varying values to withdraw fixed values directly.
  - An option for normal withdraw with a condition of inputting a value that's a multiple of 5
  - An option for depositing any value
  - The ability to check your current balance 
- Inside every menu option, the user is shown its current balance before giving the input to do an operation
## ⚙️ Architecture and engineering choices 
- A state-driven solution that uses Enums with switch cases to route the user to different sub-programs depending on the input.
- An scalable, manageable flow led by initializer and router functions like `LoginScreen` and `RunATMServices`.
- A utilization of the `unordered_map` iterator to create a reference variable that's initialized after login. Such an iterator is then passed by reference to the sub-programs in the switch router in `PerformMainMenuOption` to maintain direct quick access in memory, which is then followed by saving into the file. This prevents guarantees the file content is only loaded from the source one time. 
- The decision of using an iterator to the client's information in memory and passing that 
- Dedicated Enums for the two menus in the ATM to help with the program flow.
- A robust separation of concerns between UI, logic involving transactions and verification in function like `NormalWithdrawScreen`, `DepositScreen`, etc. which pass their parameters to the **logic functions,** and validated input evaluation. Thus improving scalability involving **UI**, or **security**, or **verification** features.
## 📦 Installation & Build

This project has no external dependencies. It requires a **C++20-compatible compiler**, such as Microsoft Visual C++ (MSVC) through Visual Studio.

### 🟪 Using Visual Studio

1. Clone or download this repository.
2. Open the project in Visual Studio.
3. Make sure the project is configured to use C++20 or later.
4. Make sure `clients.txt` is located in the program's working directory.
5. Build and run the project.

### 🔃 Using Git

```bash
git clone https://github.com/Abdulrahman-devx7/ATM-System-Project.git
cd ATM-System-Project
```

After cloning, open the source file in Visual Studio and build the project using C++20.

### Command-Line Build

If you have a C++20-compatible compiler such as MinGW/G++, you can build the project from the command line:

```bash
g++ -std=c++20 ATM-System-Project.cpp -o bank
```

Then run the generated executable:

```bash
bank.exe
```
Make sure `clients.txt` is in the same working directory as the executable.
### ⚠️Important note
This project was developed for Windows and uses Windows console commands such as `system("cls")`, `system("color 0f")`, and `system("pause>0")` for screen handling. These commands are Windows-specific and may not function as intended on Linux or macOS.
