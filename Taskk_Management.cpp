#ifndef TASKID_H
#define TASKID_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class TaskID {
public:
    int taskID;
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
    string ownerUsername;  // NEW: Track which user owns this task

    // Default Constructor
    TaskID() {
        taskID = 0;
        title = "";
        description = "";
        status = 0;
        assignedTo = "";
        dueDayDate = dueMonthDate = dueYearDate = 0;
        priority = "";
        priorityHigh = priorityMid = priorityLow = 0;
        ownerUsername = "";
    }

    // Setters
    void setTitle(string t) { title = t; }
    void setDescription(string d) { description = d; }
    void setStatus(int s) { status = s; }
    void setAssignedTo(string a) { assignedTo = a; }
    void setDueDay(int d) { dueDayDate = d; }
    void setDueMonth(int m) { dueMonthDate = m; }
    void setDueYear(int y) { dueYearDate = y; }
    void setOwner(string owner) { ownerUsername = owner; }  // NEW
    void setPriority(string pr, int pH, int pM, int pL) {
        priority = pr;
        priorityHigh = pH;
        priorityMid = pM;
        priorityLow = pL;
    }

    // Getters
    string getTitle() { return title; }
    string getDescription() { return description; }
    int getStatus() { return status; }
    string getAssignedTo() { return assignedTo; }
    int getDueDay() { return dueDayDate; }
    int getDueMonth() { return dueMonthDate; }
    int getDueYear() { return dueYearDate; }
    string getPriority() { return priority; }
    string getOwner() { return ownerUsername; }  // NEW

    // NEW: Serialization methods
    void serialize(ofstream& out) {
        out << taskID << endl;
        out << title << endl;
        out << description << endl;
        out << status << endl;
        out << assignedTo << endl;
        out << dueDayDate << endl;
        out << dueMonthDate << endl;
        out << dueYearDate << endl;
        out << priority << endl;
        out << priorityHigh << endl;
        out << priorityMid << endl;
        out << priorityLow << endl;
        out << ownerUsername << endl;
    }

    void deserialize(ifstream& in) {
        in >> taskID;
        in.ignore();
        getline(in, title);
        getline(in, description);
        in >> status;
        in.ignore();
        getline(in, assignedTo);
        in >> dueDayDate >> dueMonthDate >> dueYearDate;
        in.ignore();
        getline(in, priority);
        in >> priorityHigh >> priorityMid >> priorityLow;
        in.ignore();
        getline(in, ownerUsername);
    }
};

// NEW: prettier Task details card
ostream& operator<<(ostream& os, const TaskID& t) {
    string statusText;
    switch (t.status) {
        case 1: statusText = "Pending";     break;
        case 2: statusText = "In Progress"; break;
        case 3: statusText = "Completed";   break;
        default: statusText = "Unknown";    break;
    }

    os << "\n========================================\n";
    os << "              TASK DETAILS              \n";
    os << "========================================\n";

    os << "Task ID     : " << t.taskID << '\n';
    os << "Title       : " << t.title << '\n';
    os << "Description : " << t.description << '\n';
    os << "Assigned To : " << t.assignedTo << '\n';
    os << "Status      : " << statusText << '\n';
    os << "Due Date    : " << t.dueDayDate << "/"
       << t.dueMonthDate << "/" << t.dueYearDate << '\n';
    os << "Priority    : " << t.priority << '\n';
    os << "Owner       : " << t.ownerUsername << '\n';  // NEW: Show owner

    os << "----------------------------------------\n";
    return os;
}

#endif

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;


// Forward declarations of utility functions
bool getTitle(string& title);
bool getDescription(string& description);
bool getAssignedTo(string& assignedTo);
bool getStatus(int& status);
bool getValidDate(int& day, int& month, int& year);
bool getPriority(int& priority);
    
class TaskManager {
private:
    string username;
    string password;
    static const int MAX_TASKS = 100;
    TaskID tasks[MAX_TASKS];
    int taskCount = 0;

public:
    TaskManager(string u, string p) {
        username = u;
        password = p;
        loadTasks();  // NEW: Load tasks for this user when manager is created
    }

    ~TaskManager() {
        saveTasks();  // NEW: Save tasks when manager is destroyed
    }

    bool signup(string u, string p) {
        username = u;
        password = p;
        return true;
    }
    
    bool login(string u, string p) {
        return (username == u && password == p);
    }

    // NEW: Save tasks to file
    void saveTasks() {
        string filename = username + "_tasks.txt";
        ofstream outFile(filename);
        
        if (!outFile) {
            cout << "\n===================================\n";
            cout << "Error: Could not save tasks to file!\n";
            cout << "===================================\n";
            return;
        }
        
        outFile << taskCount << endl;
        for (int i = 0; i < taskCount; i++) {
            tasks[i].serialize(outFile);
        }
        
        outFile.close();
    }

    // NEW: Load tasks from file
    void loadTasks() {
        string filename = username + "_tasks.txt";
        ifstream inFile(filename);
        
        if (!inFile) {
            // File doesn't exist yet, that's OK
            taskCount = 0;
            return;
        }
        
        inFile >> taskCount;
        inFile.ignore();
        
        for (int i = 0; i < taskCount && i < MAX_TASKS; i++) {
            tasks[i].deserialize(inFile);
        }
        
        inFile.close();
    }

    // Main menu
    void mainMenu() {
        int choice;
        while (true) {
            // Better main menu header
            cout << "\n========================================\n";
            cout << "        TASK MANAGER - MAIN MENU        \n";
            cout << "========================================\n";
            cout << "Logged in as: " << username << "\n";
            cout << "Task Count: " << taskCount << "\n";
            cout << "----------------------------------------\n";
            cout << " 1) Add Task\n";
            cout << " 2) View Tasks\n";
            cout << " 3) Edit Task\n";
            cout << " 4) Delete Task\n";
            cout << " 5) Save Tasks (Manual Save)\n";  // NEW: Manual save option
            cout << " 0) Logout\n";
            cout << "----------------------------------------\n";
            cout << "Your choice: ";
            cin >> choice;

            if (choice == 0) {
                saveTasks();  // Auto-save on logout
                cout << "\n===========================\n";
                cout << "Logging out...\n";
                cout << "===========================\n";
                break;
            }
            else if (choice == 1) {
                addTaskMenu();
            }
            else if (choice == 2) {
                viewTasks();
            }
            else if (choice == 3) {
                int editID;
                cout << "\nEnter Task ID to edit: ";
                cin >> editID;
                editTask(editID);
            }
            else if (choice == 4) {
                int deleteID;
                cout << "\nEnter Task ID to delete: ";
                cin >> deleteID;
                deleteTask(deleteID);
            }
            else if (choice == 5) {
                saveTasks();
                cout << "\n===================================\n";
                cout << "Tasks saved successfully!\n";
                cout << "===================================\n";
            }
            else {
                cout << "\n===========================\n";
                cout << "Invalid choice. Please try again.\n";
                cout << "===========================\n";
            }
        }
    }

    // NEW: Separate method for adding tasks
    void addTaskMenu() {
        cout << "\n========================================\n";
        cout << "               ADD NEW TASK             \n";
        cout << "========================================\n";
        cout << "Please enter the following details:\n";
        cout << "----------------------------------------\n";

        TaskID newTask;
        string title, description, assignedTo;
        int status, day, month, year, priority;
        
        cin.ignore();
        
        // Get title
        if(!getTitle(title)) return;
        
        // Get description
        if(!getDescription(description)) return;
        
        // Get assigned to
        if(!getAssignedTo(assignedTo)) return;
        
        // Get status
        if(!getStatus(status)) {
            cin.ignore();
            return;
        }
        
        // Get date
        if(!getValidDate(day, month, year)) {
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        
        // Get priority
        if(!getPriority(priority)) {
            cin.ignore();
            return;
        }
        
        // Populate TaskID object
        newTask.setTitle(title);
        newTask.setDescription(description);
        newTask.setAssignedTo(assignedTo);
        newTask.setStatus(status);
        newTask.setDueDay(day);
        newTask.setDueMonth(month);
        newTask.setDueYear(year);
        newTask.setOwner(username);  // Set the owner
        
        // Set priority string based on priority value
        string priorityStr;
        if(priority == 1)      priorityStr = "High";
        else if(priority == 2) priorityStr = "Mid";
        else if(priority == 3) priorityStr = "Low";
        newTask.setPriority(
            priorityStr,
            priority == 1 ? 1 : 0,
            priority == 2 ? 1 : 0,
            priority == 3 ? 1 : 0
        );
        
        addTask(newTask);
    }

    // Add Task
    void addTask(const TaskID& t) {
        if (taskCount >= MAX_TASKS) {
            cout << "\n=============================\n";
            cout << "Task list full!\n";
            cout << "=============================\n";
            return;
        }

        tasks[taskCount] = t;
        tasks[taskCount].taskID = taskCount + 1;
        taskCount++;

        cout << "\n=============================\n";
        cout << "Task added successfully!\n";
        cout << "Task ID: " << tasks[taskCount-1].taskID << "\n";
        cout << "=============================\n";
    }

    // Edit Task
    void editTask(int id) {
        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].taskID == id) {
                // Check if task belongs to current user
                if (tasks[i].getOwner() != username) {
                    cout << "\n===================================\n";
                    cout << "ERROR: You can only edit your own tasks!\n";
                    cout << "===================================\n";
                    return;
                }
                
                // New edit header
                cout << "\n========================================\n";
                cout << "                 EDIT TASK              \n";
                cout << "========================================\n";
                cout << "Task ID: " << id << "\n";
                cout << "Current Task Details:\n";
                cout << tasks[i];
                cout << "----------------------------------------\n";
                
                while(true) {
                    cout << "\nWhat would you like to edit?\n";
                    cout << "1) Title\n";
                    cout << "2) Description\n";
                    cout << "3) Assigned To\n";
                    cout << "4) Status\n";
                    cout << "5) Due Date\n";
                    cout << "6) Priority\n";
                    cout << "0) Return\n";
                    cout << "Your choice: ";
                    
                    int choice;
                    cin >> choice;
                    cin.ignore();
                    
                    if(choice == 0) {
                        return;
                    }
                    
                    cout << "\n===========================\n";
                    
                    switch(choice) {
                        case 1:
                            cout << "Enter new title: ";
                            getline(cin, tasks[i].title);
                            cout << "\n===========================\n";
                            cout << "\nTitle updated successfully!\n";
                            cout << "===========================\n";
                            break;
                        case 2:
                            cout << "Enter new description: ";
                            getline(cin, tasks[i].description);
                            cout << "\n===========================\n";
                            cout << "\nDescription updated successfully!\n";
                            cout << "===========================\n";
                            break;
                        case 3:
                            cout << "Enter new assigned to: ";
                            getline(cin, tasks[i].assignedTo);
                            cout << "\n===========================\n";
                            cout << "\nAssigned To updated successfully!\n";
                            cout << "===========================\n";
                            break;
                        case 4:
                            cout << "\nEnter new status: \n";
                            cout << "1) Pending\n";
                            cout << "2) In Progress\n";
                            cout << "3) Completed\n";
                            cout << "Your choice: ";
                            cin >> tasks[i].status;
                            cin.ignore();
                            cout << "\n===========================\n";
                            cout << "\nStatus updated successfully!\n";
                            cout << "===========================\n";
                            break;
                        case 5: {
                            char slash;
                            cout << "\nEnter new due date (DD/MM/YYYY): ";
                            cin >> tasks[i].dueDayDate >> slash >> tasks[i].dueMonthDate >> slash >> tasks[i].dueYearDate;
                            cin.ignore();
                            cout << "\n===========================\n";
                            cout << "\nDue Date updated successfully!\n";
                            cout << "===========================\n";
                            break;
                        }
                        case 6: {
                            int priority;
                            cout << "\nEnter new priority: \n";
                            cout << "1) High\n";
                            cout << "2) Mid\n";
                            cout << "3) Low\n";
                            cout << "Your choice: ";
                            cin >> priority;
                            cin.ignore();
                            
                            string priorityStr;
                            if(priority == 1)      priorityStr = "High";
                            else if(priority == 2) priorityStr = "Mid";
                            else if(priority == 3) priorityStr = "Low";
                            tasks[i].setPriority(
                                priorityStr,
                                priority == 1 ? 1 : 0,
                                priority == 2 ? 1 : 0,
                                priority == 3 ? 1 : 0
                            );
                            cout << "\n===========================\n";
                            cout << "\nPriority updated successfully!\n";
                            cout << "===========================\n";
                            break;
                        }
                        default:
                            cout << "\n===========================\n";
                            cout << "Invalid choice. Please try again.\n";
                            cout << "===========================\n";
                            break;
                    }
                }
                return;
            }
        }
        cout << "\n===========================\n";
        cout << "Task ID not found!\n";
        cout << "===========================\n";
    }

    // Delete Task
    void deleteTask(int id) {
        // New delete header
        cout << "\n========================================\n";
        cout << "               DELETE TASK              \n";
        cout << "========================================\n";
        cout << "Task ID: " << id << "\n";
        cout << "----------------------------------------\n";

        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].taskID == id) {
                // Check if task belongs to current user
                if (tasks[i].getOwner() != username) {
                    cout << "\n===================================\n";
                    cout << "ERROR: You can only delete your own tasks!\n";
                    cout << "===================================\n";
                    return;
                }

                for (int j = i; j < taskCount - 1; j++) {
                    tasks[j] = tasks[j + 1];
                    tasks[j].taskID = j + 1;  // Update task IDs
                }

                taskCount--;
                cout << "\n===========================\n";
                cout << "Task deleted successfully!\n";
                cout << "===========================\n";
                return;
            }
        }
        cout << "\n===========================\n";
        cout << "Task ID not found!\n";
        cout << "===========================\n";
    }

    // View Tasks
    void viewTasks() {
        if (taskCount == 0) {
            cout << "\n===========================\n";
            cout << "No tasks available.\n";
            cout << "===========================\n";
            cout << "\nPress Enter to return";
            cin.ignore();
            cin.get();
            return;
        }

        // New Header for the view menu
        cout << "\n========================================\n";
        cout << "               VIEW TASKS                 \n";
        cout << "========================================\n";

        cout << "\n1) View All Tasks\n";
        cout << "2) View Tasks by Priority\n";
        cout << "3) View Tasks by Status\n";
        cout << "4) View Tasks by Assigned User\n";
        cout << "5) View Tasks by Deadline\n";
        cout << "0) Return to Main Menu\n";
        cout << "Your choice: ";
        int choice;
        cin >> choice;
        cin.ignore();
        cout << "\n========================================\n";

        switch(choice) {
            case 0:
                return;

            case 1: {
                //Adapted UI table layout for viewing all tasks
                cout << "\n================================== TASK LIST ===================================\n\n";
                cout << left
                     << setw(5)  << "ID"
                     << setw(20) << "Title"
                     << setw(15) << "Status"
                     << setw(15) << "Due Date"
                     << setw(15) << "Assigned To"
                     << setw(10) << "Priority" << '\n';
                cout << string(80, '-') << '\n';

                for (int i = 0; i < taskCount; i++) {
                    string statusText;
                    switch (tasks[i].status) {
                        case 1: statusText = "Pending";     break;
                        case 2: statusText = "In Progress"; break;
                        case 3: statusText = "Completed";   break;
                        default: statusText = "Unknown";    break;
                    }

                    string dueDate = to_string(tasks[i].dueDayDate) + "/" +
                                     to_string(tasks[i].dueMonthDate) + "/" +
                                     to_string(tasks[i].dueYearDate);

                    cout << left
                         << setw(5)  << tasks[i].taskID
                         << setw(20) << tasks[i].title
                         << setw(15) << statusText
                         << setw(15) << dueDate
                         << setw(15) << tasks[i].assignedTo
                         << setw(10) << tasks[i].priority
                         << '\n';
                }

                cout << "\n================================================================================\n";
                cout << "\nPress Enter to return";
                cin.get();
                break;
            }

            case 2: {
                int priorityChoice;
                cout << "Select Priority to filter:\n";
                cout << "1) High\n";
                cout << "2) Mid\n";
                cout << "3) Low\n";
                cout << "Your choice: ";
                cin >> priorityChoice;
                cin.ignore();
                
                string priorityFilter;
                if(priorityChoice == 1) priorityFilter = "High";
                else if(priorityChoice == 2) priorityFilter = "Mid";
                else if(priorityChoice == 3) priorityFilter = "Low";
                else {
                    cout << "Invalid choice.\n";
                    break;
                }
                
                int foundCount = 0;
                for (int i = 0; i < taskCount; i++) {
                    if (tasks[i].getPriority() == priorityFilter) {
                        cout << tasks[i];   // uses NEW detailed operator<<
                        foundCount++;
                    }
                }
                
                if(foundCount == 0) {
                    cout << "\nNo tasks found with priority: " << priorityFilter << endl;
                }
                
                cout << "\nPress Enter to return";
                cin.get();
                break;
            }

            case 3: {
                int statusFilter;
                cout << "Enter Status to filter:\n";
                cout << "1) Pending\n";
                cout << "2) In Progress\n";
                cout << "3) Completed\n";
                cout << "Your choice: ";
                cin >> statusFilter;
                cin.ignore();
                
                int foundCount = 0;
                for (int i = 0; i < taskCount; i++) {
                    if (tasks[i].getStatus() == statusFilter) {
                        cout << tasks[i];
                        foundCount++;
                    }
                }
                
                if(foundCount == 0) {
                    string statusName = (statusFilter == 1) ? "Pending" :
                                        (statusFilter == 2) ? "In Progress" : "Completed";
                    cout << "\nNo tasks found with status: " << statusName << endl;
                }
                
                cout << "\nPress Enter to return";
                cin.get();
                break;
            }

            case 4: {
                string userFilter;
                cout << "Enter Assigned User to filter: ";
                getline(cin, userFilter);
                
                int foundCount = 0;
                for (int i = 0; i < taskCount; i++) {
                    if (tasks[i].getAssignedTo() == userFilter) {
                        cout << tasks[i];
                        foundCount++;
                    }
                }
                
                if(foundCount == 0) {
                    cout << "\nNo tasks found assigned to: " << userFilter << endl;
                }
                
                cout << "\nPress Enter to return";
                cin.get();
                break;
            }

            case 5: {
                int day, month, year;
                char slash;
                cout << "Enter Deadline to filter (DD/MM/YYYY): ";
                cin >> day >> slash >> month >> slash >> year;
                cin.ignore();
                
                int foundCount = 0;
                for (int i = 0; i < taskCount; i++) {
                    if (tasks[i].getDueDay() == day &&
                        tasks[i].getDueMonth() == month &&
                        tasks[i].getDueYear() == year) {
                        cout << tasks[i];
                        foundCount++;
                    }
                }
                
                if(foundCount == 0) {
                    cout << "\nNo tasks found with deadline: "
                         << day << "/" << month << "/" << year << endl;
                }
                
                cout << "\nPress Enter to return";
                cin.get();
                break;
            }

            default:
                cout << "Invalid choice. Returning to main menu.\n";
                break;
        }
    }
};


// Utility Functions for Task Input

bool getTitle(string& title) {
    cout << "\nEnter Task Title: ";
    getline(cin, title);
    if(title == "0") return false;
    return true;
}

bool getDescription(string& description) {
    cout << "\nEnter Task Description: ";
    getline(cin, description);
    if(description == "0") return false;
    return true;
}

bool getAssignedTo(string& assignedTo) {
    cout << "\nEnter Assigned To: ";
    getline(cin, assignedTo);
    if(assignedTo == "0") return false;
    return true;
}

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

bool getValidDate(int& day, int& month, int& year) {
    char slash;
    
    while(true) {
        cout << "\nEnter Due Date (DD/MM/YYYY): ";
        cin >> day >> slash >> month >> slash >> year;
        
        if(day == 0) return false;
        
        if(day < 1 || day > 31) {
            cout << "\n===================================\n";
            cout << "ERROR: INVALID DAY. Please enter a valid day (1-31).\n";
            cout << "===================================\n";
            continue;
        }
        
        if(month < 1 || month > 12) {
            cout << "\n===================================\n";
            cout << "ERROR: INVALID MONTH. Please enter a valid month (1-12).\n";
            cout << "===================================\n";
            continue;
        }
        
        if(year < 2025) {
            cout << "\n===================================\n";
            cout << "ERROR: INVALID YEAR. Must be 2025 or later.\n";
            cout << "===================================\n";
            continue;
        }
        
        bool dayValid = false;
        if(month == 1 || month == 3 || month == 5 || month == 7 ||
           month == 8 || month == 10 || month == 12) {
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
            cout << "ERROR: Day "<< day << " is invalid for month " << month << ".\n";
            cout << "===================================\n";
            continue;
        }
        
        return true;
    }   
}

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
                cout << "\n===========================\n";
                cout << "Invalid choice.\n";
                cout << "===========================\n";
                break;
        }
    }
}

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class User {
private:
    string username;
    string password;
    
public:
    User() : username(""), password("") {}
    
    User(string n, string p){
        username = n;
        password = p;
    }

    // Getters
    string getUsername(){return username;}
    string getPassword(){return password;}

    // Setters
    void setUsername(string n){username = n;}
    void setPassword(string p){password = p;}

    // NEW: Serialization methods
    void serialize(ofstream& out) {
        out << username << endl;
        out << password << endl;
    }

    void deserialize(ifstream& in) {
        getline(in, username);
        getline(in, password);
    }

    // Create account
    void createAccount(){
        cout << "Creating account for " << username << endl;
    }

    // Login
    bool login(string n, string p){
        return (n == username && p == password);
    }
};

// NEW: Global functions for user persistence
void saveUsers(User** users, int userCount) {
    ofstream outFile("users.txt");
    if (!outFile) {
        cout << "Error: Could not save users to file!\n";
        return;
    }
    
    outFile << userCount << endl;
    for (int i = 0; i < userCount; i++) {
        users[i]->serialize(outFile);
    }
    outFile.close();
}

int loadUsers(User** users) {
    ifstream inFile("users.txt");
    if (!inFile) {
        return 0;  // No users file yet
    }
    
    int userCount;
    inFile >> userCount;
    inFile.ignore();
    
    for (int i = 0; i < userCount; i++) {
        users[i] = new User();
        users[i]->deserialize(inFile);
    }
    
    inFile.close();
    return userCount;
}

#include <iostream>
#include <string>
using namespace std;

int main(){
    // Array to store registered users
    User* users[100];
    int userCount = 0;
    
    // NEW: Load users from file at startup
    userCount = loadUsers(users);
    if (userCount > 0) {
        cout << "Loaded " << userCount << " user(s) from file.\n";
    }
    
    string username = "", password = "";
    int choice = 0;
    bool exitProgram = false;

    cout << "============================\n";
    cout << "------- Task Manager -------\n";
    cout << "============================\n";
    cout << "\nWelcome to the Task Manager!\n";

    // Main program loop
    while (!exitProgram) {
        bool loggedIn = false;
        
        // Login/Signup loop
        while (!loggedIn && !exitProgram) {
            cout << "\nPlease select an option:\n";
            cout << "1) Login\n";
            cout << "2) Signup\n";
            cout << "0) Exit\n";
            cout << "Your choice: ";
            cin >> choice;
            cin.ignore();
            
            if(choice == 0) {
                exitProgram = true;
                break;
            }
            else if(choice == 2) {
                // Signup
                cout << "\n===========================\n";
                cout << "--------- Sign Up ---------\n";
                cout << "===========================\n";
                
                cout << "\nEnter New Username: ";
                getline(cin, username);
                
                // Check if username already exists
                bool userExists = false;
                for(int i = 0; i < userCount; i++) {
                    if(users[i]->getUsername() == username) {
                        userExists = true;
                        break;
                    }
                }
                
                if(userExists) {
                    cout << "\n===========================\n";
                    cout << "ERROR: Username already exists!\n";
                    cout << "===========================\n";
                    continue;
                }
                
                cout << "Enter New Password: ";
                getline(cin, password);
                
                // Validate password (minimum 4 characters)
                if(password.length() < 4) {
                    cout << "\n===========================\n";
                    cout << "ERROR: Password must be at least 4 characters!\n";
                    cout << "===========================\n";
                    continue;
                }
                
                // Create new user
                users[userCount] = new User(username, password);
                userCount++;
                
                // NEW: Save users after signup
                saveUsers(users, userCount);
                
                cout << "\n===========================\n";
                cout << "Signup Successful!\n";
                cout << "Welcome, " << username << "!\n";
                cout << "===========================\n";
                loggedIn = true;
            }
            else if(choice == 1) {
                // Login
                cout << "\n===========================\n";
                cout << "---------- Login ----------\n";
                cout << "===========================\n";
                
                if(userCount == 0) {
                    cout << "\n===========================\n";
                    cout << "No users registered. Please sign up first.\n";
                    cout << "===========================\n";
                    continue;
                }
                
                cout << "\nEnter Username: ";
                getline(cin, username);
                cout << "Enter Password: ";
                getline(cin, password);
                
                // Check credentials
                bool validLogin = false;
                for(int i = 0; i < userCount; i++) {
                    if(users[i]->login(username, password)) {
                        validLogin = true;
                        break;
                    }
                }
                
                if(validLogin) {
                    cout << "\n===========================\n";
                    cout << "Login Successful!\n";
                    cout << "Welcome back, " << username << "!\n";
                    cout << "===========================\n";
                    loggedIn = true;
                } else {
                    cout << "\n===========================\n";
                    cout << "ERROR: Invalid username or password!\n";
                    cout << "===========================\n";
                }
            }
            else {
                cout << "\n===========================\n";
                cout << "Invalid choice. Please try again.\n";
                cout << "===========================\n";
            }
        }
        
        // Main menu - only run if logged in
        if(loggedIn) {
            TaskManager tm(username, password);
            tm.mainMenu();
            // After logout, loop back to login screen
        }
    }
    
    // NEW: Save users before exiting
    saveUsers(users, userCount);
    
    // Clean up dynamic memory
    for(int i = 0; i < userCount; i++) {
        delete users[i];
    }
    
    cout << "\nThank you for using Task Manager!\n";
    cout << "All data has been saved.\n";
    return 0;    
}