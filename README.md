# 💳 ATM System (C++)

A console-based Automated Teller Machine (ATM) system built in C++. This project simulates core banking operations including authentication, balance checking, deposits, and withdrawals.

## 🚀 Features
- **User Authentication**: Secure login using Account Number and Pin Code.
- **Quick Withdraw**: Predefined amounts for fast transactions (20 to 1000).
- **Normal Withdraw**: Custom amount withdrawal (multiples of 5).
- **Deposit**: Add funds to the account with confirmation prompts.
- **Balance Check**: Real-time balance inquiry.
- **Data Persistence**: Client data is saved and loaded from a local text file (`Clients.txt`).
- **Input Validation**: Robust error handling for invalid inputs (e.g., negative amounts, non-numeric characters).

## 🛠️ Technologies Used
- **Language**: C++
- **IDE**: Visual Studio 2022
- **Version Control**: Git & GitHub
- **Concepts Applied**: File Handling (`fstream`), Data Structures (`struct`, `vector`), String Manipulation, and Modular Programming.

## 📂 Project Structure
- `ATM-System.cpp`: Main source code containing all logic, menus, and file operations.
- `Clients.txt`: Local database file storing client records (Format: `AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance`).

## 🏃 How to Run
1. Clone the repository:  
   `git clone https://github.com/abdulrahamanharitani-ai/ATM-System-CPP.git`
2. Open the solution in **Visual Studio 2022**.
3. Ensure `Clients.txt` exists in the project directory (or create it with sample data).
4. Build and Run (`Ctrl + F5`).

## 🔄 Future Improvements (OOP Refactoring)
*This project is currently built using Procedural Programming. As part of my journey to master Object-Oriented Programming (OOP), the next step is to refactor this code by:*
- Converting `stClient` into a `Client` **class** with `private` attributes and `public` getters/setters (**Encapsulation**).
- Creating an `ATM` or `Bank` class to handle transactions and menu navigation.
- Using **Polymorphism** for different types of accounts (e.g., Savings vs. Current).

---
*Built with ❤️ by Abdulrahman Al-Haritani*
