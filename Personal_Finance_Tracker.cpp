#include<iostream>
#include<fstream>   //for file handling
#include<string>
#include<vector>    // for dynamic array
#include<iomanip>   // for formatted output(setw())
#include<limits>
#include<ctime>     //for local time
using namespace std;

class user // base class
{
protected:
    string username;
    string password;
public:
    user() {}
    user(string name, string pass)
    {
        username = name;
        password = pass;
    }
    virtual bool login(string name, string pass)
    {
        return (username == name && password == pass);
    }
    virtual void sign_up(string name, string pass)
    {
        username = name;
        password = pass;
    }
    string get_user_name()
    {
        return username;
    }
};

class expense_tracker : public user // derived class
{
private:
    //struct used to group all the variables for transaction
    struct transaction
    {
        string category;
        string type;
        string date;
        double amount;
    };
    vector<transaction> transactions;
    double savings_goal;

    // function for reading local time
    string get_current_date()
    {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char buffer[20];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y", ltm);
        return string(buffer);
    }

public:
    // constructors
    expense_tracker()
    { savings_goal = 0; }
    expense_tracker(string name, string pass)
    {
        sign_up(name, pass);
        savings_goal = 0;
    }

    // function for adding income
    void add_income(string category, double amount)
    {
        transaction t;
        t.date = get_current_date();
        t.category = category;
        t.amount = amount;
        t.type = "Income";
        transactions.push_back(t);
        cout << "Income added successfully!" << endl;
        save_user_data(); //function  called for auto saving
    }
    // function for adding expense
    void add_expense(string category, double amount)
    {
        transaction t;
        t.date = get_current_date();
        t.category = category;
        t.amount = amount;
        t.type = "Expense";
        transactions.push_back(t);
        cout << "Expense added successfully!" << endl;
        save_user_data(); //function called for auto saving
    }
    //function for calculating balance
    double calculate_balance()
    {
        double total_income = 0, total_expense = 0;
        for (auto& t : transactions)
        {
            if (t.type == "Income")
            {
                total_income += t.amount;
            }
            else
            {
                total_expense += t.amount;
            }
        }
        return total_income - total_expense;
    }

    // function for setting savings goal
    void set_savings_goal(double goal)
    {
        savings_goal = goal;
        cout << "Savings goal set to: " << goal << endl;
        save_user_data(); // functioned called for auto saving
    }
    //function for checking the progress of savings goal
    void check_savings_goal()
    {
        double balance = calculate_balance();
        cout << "Current balance: " << balance << endl;
        cout << "Savings goal: " << savings_goal << endl;
        if (balance < savings_goal)
        {
            cout << "Not reached yet! Need " << (savings_goal - balance) << " more." << endl;
        }
        else
        {
            cout << "Savings goal reached!" << endl;
        }
    }

    // function for displaying transactions
    void display_transaction()
    {
        if (transactions.empty())
        {
            cout << "No transaction history found." << endl;
            return;
        }
        cout << "-----Transaction Summary-----" << endl;
        //setw used to set width, spaces for aligning the table
        cout << left << setw(15) << "Date" << setw(20) << "Category"
             << setw(10) << "Amount" << setw(10) << "Type" << endl;
        cout << "----------------------------------------------------" << endl;
        for (auto& t : transactions)
        {
            cout << setw(15) << t.date << setw(20) << t.category
                 << setw(10) << t.amount << setw(10) << t.type << endl;
        }
        cout << "----------------------------------------------------" << endl;
        cout << setw(35) << "Current Balance: " << calculate_balance() << endl;
    }

    // login and signup
    bool login(string name, string pass)
    override {
        ifstream user_file("user.txt");
        if (!user_file.is_open())
        {
            cerr << "Error: Could not open user.txt" << endl;
            return false;
        }
        string stored_name, stored_pass;
        while (user_file >> stored_name >> stored_pass)
        {
            if (stored_name == name && stored_pass == pass)
            {
                username = name;
                password = pass;
                load_user_data();
                user_file.close();
                return true;
            }
        }
        user_file.close();
        return false;
    }

   void sign_up(string name, string pass)
   override {
    ifstream check_file("user.txt");
    string stored_name, stored_pass;
    while (check_file >> stored_name >> stored_pass)
    {
        if (stored_name == name)
        {
            cout << "Error: Username already exists! Please try a different one.\n";
            check_file.close();
            return;
        }
    }
    check_file.close();

    ofstream user_file("user.txt", ios::app);
    if (!user_file.is_open())
    {
        cerr << "Error: Could not open user.txt for writing" << endl;
        return;
    }
    user_file << name << " " << pass << endl;
    user_file.close();
    username = name;
    password = pass;
    cout << "Registration successful!" << endl;
}

    // load & save
    void load_user_data()
    {
        ifstream user_file(username + "_data.txt");
        if (user_file.is_open())
        {
            transactions.clear();
            transaction t;
            while (user_file >> t.date >> t.category >> t.amount >> t.type)
            {
                transactions.push_back(t);
            }
            user_file.close();
        }

        ifstream goal_file(username + "_goal.txt");
        if (goal_file.is_open())
        {
            goal_file >> savings_goal;
            goal_file.close();
        }
    }

    void save_user_data()
    {
        ofstream user_file(username + "_data.txt");
        if (!user_file.is_open())
        {
            cerr << "Error: Could not save data" << endl;
            return;
        }
        for (auto& t : transactions)
        {
            user_file << t.date << " " << t.category << " " << t.amount << " " << t.type << endl;
        }
        user_file.close();

        ofstream goal_file(username + "_goal.txt");
        if (goal_file.is_open())
        {
            goal_file << savings_goal;
            goal_file.close();
        }
    }
};
// menu
void display_menu()
{
    cout << "-----Personal Expense Tracker Menu-----" << endl;
    cout << "1. Add Income" << endl;
    cout << "2. Expense" << endl;
    cout << "3. Set Savings Goal" << endl;
    cout << "4. Check Savings Goal" << endl;
    cout << "5. View Transaction Summary" << endl;
    cout << "6. Save & Logout" << endl;
    cout << "Choose an option: ";
}

// user interaction
void take_user_input(expense_tracker& tracker)
{
    int choice, category_choice;
    string category;
    double amount;

    vector<string> income_categories = {"Salary","Business","Investment","Gift","Others"};
    vector<string> expense_categories = {"Rent","Utilities","Grocery","Transport","Entertainment","Education","HealthCare","Others"};

    while (true)
    {
        display_menu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Select Income Category:" << endl;
            for (int i = 0; i < income_categories.size(); i++)
            {
                cout << i + 1 << ". " << income_categories[i] << endl;
            }
            cout << "Choose Category (1-" << income_categories.size() << "): ";
            cin >> category_choice;
            if (category_choice < 1 || category_choice > income_categories.size())
            {
                cout << "Invalid Choice!" << endl;
                break;
            }
            cout << "Enter amount: ";
            cin >> amount;
            if (cin.fail() || amount <= 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid amount! Please enter a positive number.\n";//ignores invalid input and spaces
                break; // go back to menu
            }
            tracker.add_income(income_categories[category_choice - 1], amount);
            break;
        case 2:
            cout << "Select Expense Category:" << endl;
            for (int i = 0; i < expense_categories.size(); i++)
            {
                cout << i + 1 << " " << expense_categories[i] << endl;
            }
            cout << "Choose Category (1-" << expense_categories.size() << "): ";
            cin >> category_choice;
            if (category_choice < 1 || category_choice > expense_categories.size())
            {
                cout << "Invalid Choice!" << endl;
                break;
            }
            cout << "Enter amount: ";
            cin >> amount;
            // Check if input failed OR entered amount is not positive
            if (cin.fail() || amount <= 0)
                {
                    cin.clear(); // clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
            cout << "Invalid amount! Please enter a positive number.\n";
            break; // go back to menu
            }
            tracker.add_expense(expense_categories[category_choice - 1], amount);
            break;

        case 3:
            cout << "Enter your savings goal: ";
            cin >> amount;
            // Check for invalid or non-positive input
            if (cin.fail() || amount <= 0)
                {
                    cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid amount! Please enter a positive number.\n";
            break; // go back to menu
            }
            tracker.set_savings_goal(amount);
            break;
        case 4:
            tracker.check_savings_goal();
            break;

        case 5:
            tracker.display_transaction();
            break;

        case 6:
            tracker.save_user_data();
            cout << "Data saved successfully!" << endl;
            return;

        default:
            cout << "Invalid Choice. Please try again!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main()
{
    expense_tracker tracker;
    int choice;
    string username, password;

    //menu to take input for user's choice
    cout << "-----Personal Expense Tracker-----" << endl;
    while (true)
    {
        cout << "\n1. Login\n2. Sign Up\n3. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue; // restart loop
        }
        if (choice == 3)
        {
            cout << "Bye! Remember money can't buy happiness but it can definitely buy ICECREAM!!!! \n";
            return 0; // exit properly
        }

        // clear newline left by cin >> choice
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter username: ";
        getline(cin, username);

        cout << "Enter password: ";
        getline(cin, password);

        if (username.empty() || password.empty())
        {
            cout << "Error: Username and password cannot be empty.\n";
            continue; // back to menu
        }

        if (choice == 1)
        {
            if (tracker.login(username, password))
            {
                cout << "Login successful!" << endl;
                take_user_input(tracker);
            }
            else
            {
                cout << "Invalid credentials." << endl;
            }
        }
        else if (choice == 2)
        {
            tracker.sign_up(username, password);
            cout << "Please sign up with your new credentials." << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
