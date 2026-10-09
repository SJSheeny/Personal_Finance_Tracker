# Personal Finance Tracker

## Overview

Personal Finance Tracker is a console-based application developed in C++ that helps users manage their income, expenses and savings goals. It includes a login and registration system and uses file handling to store transaction records and savings goals for future sessions.

## Features

* **User Registration and Login:** Allows users to create accounts and log in with their credentials.
* **Income Management:** Records income under categories such as salary, business, investment and gifts.
* **Expense Management:** Records expenses under categories such as rent, groceries, transport, education and healthcare.
* **Balance Calculation:** Calculates the current balance by subtracting total expenses from total income.
* **Savings Goals:** Allows users to set a savings goal and check their progress.
* **Transaction History:** Displays transaction dates, categories, amounts and transaction types.
* **Automatic Data Saving:** Saves transaction records and savings goals to text files.
* **Input Validation:** Checks for invalid menu choices and non-positive monetary amounts.

## Technologies Used

* C++
* Object-Oriented Programming
* File Handling
* Standard Template Library (STL)
* Vectors and Strings

## How to Run

1. Install a C++ compiler such as GCC or MinGW.

2. Download or clone this repository.

3. Open a terminal in the project directory.

4. Compile the source file:

   ```bash
   g++ personal_finance_tracker.cpp -o tracker
   ```

5. Run the program.

   **On Windows:**

   ```bash
   tracker.exe
   ```

   **On Linux or macOS:**

   ```bash
   ./tracker
   ```

**Note:** Make sure the source filename matches `personal_finance_tracker.cpp`. If your file has a different extension or name, update the compile command accordingly.

## Data Storage

The application stores user credentials in `user.txt`, transaction records in user-specific data files and savings goals in separate user-specific files. These files are used to save and retrieve data between sessions.

## Learning Outcomes

* Practiced object-oriented programming using classes and inheritance.
* Applied file handling to store and retrieve user data.
* Used vectors and structures to manage transaction records.
* Implemented calculations for income, expenses and savings goals.
* Practiced input validation and menu-driven program design.

## Project Type

Personal C++ programming project.

