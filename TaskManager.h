#include <string>
#include <iostream>

using namespace std;

class TaskManager {
private:
    string username;
    string password;

    string title;
    string description;
    int status;
    string assignedTo;

    int dueDayDate;
    int dueMonthDate;
    int dueYearDate;

    string priority;
    int priorityHigh;
    int priorityMid;
    int priorityLow;

public:
    // Constructor
    TaskManager(string u, string p, string t, string d, int s, string a, int ddd, int dmd, int dyd, string pr ,int pH = 1, int pM = 2, int pL =3) {
        username = u;
        password = p;

        title = t;
        description = d;
        status = s;
        assignedTo = a;

        dueDayDate = ddd;
        dueMonthDate = dmd;
        dueYearDate = dyd;

        priority = pr;
        priorityHigh = pH;
        priorityMid = pM;
        priorityLow = pL;
    }
    
    // Destructor
    ~TaskManager() {}


    // Setters   
    void setUsername(string u) {username = u;}
    void setPassword(string p) {password = p;}

    void setTitle(string t) {title = t;}
    void setDescription(string d) {description = d;}
    void setStatus(int s) {status = s;}
    void setAssignedTo(string a) {assignedTo = a;}

    void setDueDate(int ddd) {dueDayDate = ddd;}
    void setDueMonthDate(int dmd) {dueMonthDate = dmd;}
    void setDueYearDate(int dyd) {dueYearDate = dyd;}

    void setPriority(string pr, int pH, int pM, int pL) {
        priority = pr;
        priorityHigh = pH;
        priorityMid = pM;
        priorityLow = pL;
    }

    // Getters

    string getUsername() {return username;}
    string getPassword() {return password;}
    
    string getTitle() {return title;}
    string getDescription() {return description;}   
    int getStatus() {return status;}
    string getAssignedTo() {return assignedTo;}
    int getDueDayDate() {return dueDayDate;}
    int getDueMonthDate() {return dueMonthDate;}
    int getDueYearDate() {return dueYearDate;}
    string getPriority() {return priority;}
    int getPriorityHigh() {return priorityHigh;}
    int getPriorityMid() {return priorityMid;}
    int getPriorityLow() {return priorityLow;}


    // Login
    bool login(string u, string p) {
        return (username == u && password == p);
    }


    // Add Task
    void addTask(string t, string d, int s, string a, int ddd, int dmd, int dyd, string pr, int pH, int pM, int pL) {
        title = t;
        description = d;
        status = s;
        assignedTo = a;

        dueDayDate = ddd;
        dueMonthDate = dmd;
        dueYearDate = dyd;

        priority = pr;
        priorityHigh = pH;
        priorityMid = pM;
        priorityLow = pL;
    }

    // Edit Task
    void editTask(string t, string d, int s, string a, int ddd, int dmd, int dyd, int pH, int pM, int pL) {
        title = t;
        description = d;
        status = s;
        assignedTo = a;
        dueDayDate = ddd;
        dueMonthDate = dmd;
        dueYearDate = dyd;
        priorityHigh = pH;
    }

    // Delete Task
    void deleteTask() {
        title = "";
        description = "";
        status = 0;
        assignedTo = "";
        dueDayDate = 0;
        dueMonthDate = 0;
        dueYearDate = 0;
        priorityHigh = 0;
        priorityMid = 0;
        priorityLow = 0;
    }

    // Operator
    friend ostream& operator<<(ostream& os, const TaskManager& task) {
        os << "----- Task Details -----" << endl;
        os << "Title: " << task.title << endl;
        os << "Description: " << task.description << endl;
        os << "Status: " << task.status << endl;
        os << "Assigned To: " << task.assignedTo << endl;
        os << "Due Date: " << task.dueDayDate << "/" << task.dueMonthDate << "/" << task.dueYearDate << endl;
        os << "Priority High: " << task.priority << endl;
        os << "-------------------------" << endl;
        return os;
    }
    
    // Display Task Details
    void printTask() {
        cout << "----- Task Details -----" << endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Status: " << status << endl;
        cout << "Assigned To: " << assignedTo << endl;
        cout << "Due Date: " << dueDayDate << "/" << dueMonthDate << "/" << dueYearDate << endl;
        cout << "Priority: " << priority << endl;
        cout << "------------------------" << endl;
    }        
};

// Utility Functions for Task Input

// Function to get title with go back support
bool getTitle(string& title) {
    cout << "\nEnter Task Title: ";
    getline(cin, title);
    if(title == "0") return false;
    return true;
}

// Function to get description with go back support
bool getDescription(string& description) {
    cout << "\nEnter Task Description: ";
    getline(cin, description);
    if(description == "0") return false;
    return true;
}

// Function to get assigned to with go back support
bool getAssignedTo(string& assignedTo) {
    cout << "\nEnter Assigned To: ";
    getline(cin, assignedTo);
    if(assignedTo == "0") return false;
    return true;
}

// Function to get status with validation and go back support
bool getStatus(int& status) {
    while(true) {
        cout << "\nEnter Task Status: \n";
        cout << "1) Pending\n";
        cout << "2) In Progress\n";
        cout << "3) Completed\n";
        cout << "0) Go Back\n";
        cout << "Your choice: ";
        cin >> status;
        if(status == 0) return false;
        
        if(status >= 1 && status <= 3) return true;
        
        cout << "\n===================================\n";
        cout << "ERROR: INVALID STATUS.\n";
        cout << "===================================\n";
    }
}

// Function to get valid date with validation and go back support
bool getValidDate(int& day, int& month, int& year) {
    char slash;
    
    while(true) {
        cout << "\nEnter Due Date (DD/MM/YYYY): ";
        cin >> day >> slash >> month >> slash >> year;
        
        // Check for go back
        if(day == 0) return false;
        
        // Validate day range
        if(day < 1 || day > 31) {
            cout << "\n===================================\n";
            cout << "ERROR: INVALID DAY. Please enter a valid day (1-31).\n";
            cout << "===================================\n";
            continue;
        }
        
        // Validate month range
        if(month < 1 || month > 12) {
            cout << "\n===================================\n";
            cout << "ERROR: INVALID MONTH. Please enter a valid month (1-12).\n";
            cout << "===================================\n";
            continue;
        }
        
        // Validate year
        if(year < 2025) {
            cout << "\n===================================\n";
            cout << "ERROR: INVALID YEAR. Must be 2025 or later.\n";
            cout << "===================================\n";
            continue;
        }
        
        // Check if day is valid for the selected month
        bool dayValid = false;
        if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
            dayValid = (day >= 1 && day <= 31);
        }
        else if(month == 4 || month == 6 || month == 9 || month == 11) {
            dayValid = (day >= 1 && day <= 30);
        }
        else if(month == 2) {
            dayValid = (day >= 1 && day <= 28);
        }
        
        if(!dayValid) {
            cout << "\n===================================\n";
            cout << "ERROR: Day " << day << " is invalid for month " << month << ".\n";
            cout << "===================================\n";
            continue;
        }
        
        // All validations passed
        return true;
    }
}

// Function to get priority with validation and go back support
bool getPriority(int& priority) {
    while(true) {
        cout << "\nEnter Priority: \n";
        cout << "1) High\n";
        cout << "2) Mid\n";
        cout << "3) Low\n";
        cout << "0) Go Back\n";
        cout << "Your choice: ";
        cin >> priority;
        if(priority == 0) return false;
        
        if(priority >= 1 && priority <= 3) return true;
        
        cout << "\n===================================\n";
        cout << "ERROR: INVALID PRIORITY.\n";
        cout << "===================================\n";
    }
}

// Function to display task
void displayTask(const string& title, const string& description, const string& assignedTo,
                 int status, int day, int month, int year, int priority) {
    cout << "\n=====================================\n";
    cout << "----- Task Created Successfully -----\n";
    cout << "=====================================\n";
    cout << "\nTask Title: " << title << endl;
    cout << "Task Description: " << description << endl;
    cout << "Task Status: ";
    if(status == 1) cout << "Pending" << endl;
    else if(status == 2) cout << "In Progress" << endl;
    else if(status == 3) cout << "Completed" << endl;
    cout << "Assigned To: " << assignedTo << endl;
    cout << "Due Date: " << day << "/" << month << "/" << year << endl;
    cout << "Task Priority: ";
    if(priority == 1) cout << "High priority" << endl;
    else if(priority == 2) cout << "Mid priority" << endl;
    else if(priority == 3) cout << "Low priority" << endl;
    cout << "\n===================================\n";
}

// Function to create a task
bool createTask(string& title, string& description, string& assignedTo,
                int& status, int& day, int& month, int& year, int& priority) {
    cin.ignore();
    
    // Get title
    if(!getTitle(title)) return false;
    
    // Get description
    if(!getDescription(description)) {
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    // Get assigned to
    if(!getAssignedTo(assignedTo)) {
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    // Get status
    if(!getStatus(status)) {
        cin.ignore();
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    // Get date
    if(!getValidDate(day, month, year)) {
        cin.ignore();
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    // Get priority
    if(!getPriority(priority)) {
        cin.ignore();
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    return true;
}

// Function to edit task
bool editTask(string& title, string& description, string& assignedTo,
              int& status, int& day, int& month, int& year, int& priority) {
    while(true) {
        cout << "\nWhat would you like to edit?\n";
        cout << "1) Title\n";
        cout << "2) Description\n";
        cout << "3) Assigned To\n";
        cout << "4) Status\n";
        cout << "5) Due Date\n";
        cout << "6) Priority\n";
        cout << "0) Return to Main Menu\n";
        cout << "Your choice: ";
        
        int choice;
        cin >> choice;
        cin.ignore();
        
        cout << "\n===========================\n";
        
        switch(choice) {
            case 1:
                getTitle(title);
                displayTask(title, description, assignedTo, status, day, month, year, priority);
                break;
            case 2:
                getDescription(description);
                displayTask(title, description, assignedTo, status, day, month, year, priority);
                break;
            case 3:
                getAssignedTo(assignedTo);
                displayTask(title, description, assignedTo, status, day, month, year, priority);
                break;
            case 4:
                getStatus(status);
                displayTask(title, description, assignedTo, status, day, month, year, priority);
                break;
            case 5:
                getValidDate(day, month, year);
                displayTask(title, description, assignedTo, status, day, month, year, priority);
                break;
            case 6:
                getPriority(priority);
                displayTask(title, description, assignedTo, status, day, month, year, priority);
                break;
            case 0:
                return true;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }
}