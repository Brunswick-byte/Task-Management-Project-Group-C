#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

#include "TaskID.h"

// Input helper function prototypes
bool getTitle(string& title);
bool getDescription(string& description);
bool getAssignedTo(string& assignedTo);
bool getStatus(int& status);
bool getValidDate(int& day, int& month, int& year);
bool getPriority(int& priority);
void displayTask(const string& title, const string& description, const string& assignedTo,
                 int status, int day, int month, int year, int priority);
bool createTask(string& title, string& description, string& assignedTo,
                int& status, int& day, int& month, int& year, int& priority);
bool editTask(string& title, string& description, string& assignedTo,
              int& status, int& day, int& month, int& year, int& priority);

// TaskManager class controls all task operations for one user
class TaskManager {
private:
    string username;
    string password;
    static const int MAX_TASKS = 100;
    TaskID tasks[MAX_TASKS];
    int taskCount = 0;

public:
    // Constructor sets user credentials and loads their tasks
    TaskManager(string u, string p) {
        username = u;
        password = p;
        loadTasks();
    }

    // Destructor saves tasks automatically
    ~TaskManager() {
        saveTasks();
    }

    // Simple signup method (stores username and password)
    bool signup(string u, string p) {
        username = u;
        password = p;
        return true;
    }
    
    // Simple login check against stored username/password
    bool login(string u, string p) {
        return (username == u && password == p);
    }

    // Save all tasks for this user to username_tasks.txt
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

    // Load all tasks for this user from username_tasks.txt
    void loadTasks() {
        string filename = username + "_tasks.txt";
        ifstream inFile(filename);
        
        if (!inFile) {
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

    // Main menu loop for task operations
    void mainMenu() {
        int choice;
        while (true) {
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
            cout << " 5) Save Tasks (Manual Save)\n";
            cout << " 0) Logout\n";
            cout << "----------------------------------------\n";
            cout << "Your choice: ";
            cin >> choice;

            if (choice == 0) {
                // Logout and autosave
                saveTasks();
                cout << "\n===========================\n";
                cout << "Logging out...\n";
                cout << "===========================\n";
                break;
            }
            else if (choice == 1) {
                // Add new task
                addTaskMenu();
            }
            else if (choice == 2) {
                // View existing tasks
                viewTasks();
            }
            else if (choice == 3) {
                // Edit selected task by ID
                int editID;
                cout << "\nEnter Task ID to edit: ";
                cin >> editID;
                editTask(editID);
            }
            else if (choice == 4) {
                // Delete selected task by ID
                int deleteID;
                cout << "\nEnter Task ID to delete: ";
                cin >> deleteID;
                deleteTask(deleteID);
            }
            else if (choice == 5) {
                // Manual save to file
                saveTasks();
                cout << "\n===================================\n";
                cout << "Tasks saved successfully!\n";
                cout << "===================================\n";
            }
            else {
                // Invalid menu choice
                cout << "\n===========================\n";
                cout << "Invalid choice. Please try again.\n";
                cout << "===========================\n";
            }
        }
    }

    // Menu to collect details and create a new task
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
        
        if(!getTitle(title)) return;
        if(!getDescription(description)) return;
        if(!getAssignedTo(assignedTo)) return;
        if(!getStatus(status)) {
            cin.ignore();
            return;
        }
        if(!getValidDate(day, month, year)) {
            cin.clear();
            cin.ignore(10000, '\n');
            return;
        }
        if(!getPriority(priority)) {
            cin.ignore();
            return;
        }
        
        newTask.setTitle(title);
        newTask.setDescription(description);
        newTask.setAssignedTo(assignedTo);
        newTask.setStatus(status);
        newTask.setDueDay(day);
        newTask.setDueMonth(month);
        newTask.setDueYear(year);
        newTask.setOwner(username);
        
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

    // Add a task object to the internal array
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

    // Edit an existing task by ID
    void editTask(int id) {
        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].taskID == id) {
                // Only allow editing own tasks
                if (tasks[i].getOwner() != username) {
                    cout << "\n===================================\n";
                    cout << "ERROR: You can only edit your own tasks!\n";
                    cout << "===================================\n";
                    return;
                }
                
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
            }
        }
        cout << "\n===========================\n";
        cout << "Task ID not found!\n";
        cout << "===========================\n";
    }

    // Delete a task by ID
    void deleteTask(int id) {
        cout << "\n========================================\n";
        cout << "               DELETE TASK              \n";
        cout << "========================================\n";
        cout << "Task ID: " << id << "\n";
        cout << "----------------------------------------\n";

        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].taskID == id) {
                // Only allow deleting own tasks
                if (tasks[i].getOwner() != username) {
                    cout << "\n===================================\n";
                    cout << "ERROR: You can only delete your own tasks!\n";
                    cout << "===================================\n";
                    return;
                }

                for (int j = i; j < taskCount - 1; j++) {
                    tasks[j] = tasks[j + 1];
                    tasks[j].taskID = j + 1;
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

    // View tasks with different filter options
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
                // View all tasks in table format
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
                // Filter tasks by priority
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
                        cout << tasks[i];
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
                // Filter tasks by status
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
                // Filter tasks by assigned user
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
                // Filter tasks by deadline date
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
                // Invalid view option
                cout << "Invalid choice. Returning to main menu.\n";
                break;
        }
    }
};

// Below are helper functions for reading task input from the user

// Get task title from user
inline bool getTitle(string& title) {
    cout << "\nEnter Task Title: ";
    getline(cin, title);
    if(title == "0") return false;
    return true;
}

// Get task description from user
inline bool getDescription(string& description) {
    cout << "\nEnter Task Description: ";
    getline(cin, description);
    if(description == "0") return false;
    return true;
}

// Get person assigned to task
inline bool getAssignedTo(string& assignedTo) {
    cout << "\nEnter Assigned To: ";
    getline(cin, assignedTo);
    if(assignedTo == "0") return false;
    return true;
}

// Get task status choice
inline bool getStatus(int& status) {
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

// Get a valid due date from user
inline bool getValidDate(int& day, int& month, int& year) {
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

// Get priority choice from user
inline bool getPriority(int& priority) {
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

// Display a summary of a task based on parameters
inline void displayTask(const string& title, const string& description, const string& assignedTo,
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

// Helper to create a task by repeatedly prompting the user
inline bool createTask(string& title, string& description, string& assignedTo,
                int& status, int& day, int& month, int& year, int& priority) {
    cin.ignore();
    
    if(!getTitle(title)) return false;
    
    if(!getDescription(description)) {
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    if(!getAssignedTo(assignedTo)) {
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    if(!getStatus(status)) {
        cin.ignore();
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    if(!getValidDate(day, month, year)) {
        cin.ignore();
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    if(!getPriority(priority)) {
        cin.ignore();
        return createTask(title, description, assignedTo, status, day, month, year, priority);
    }
    
    return true;
}

// Helper to edit fields of an existing task (not used by TaskManager methods)
inline bool editTask(string& title, string& description, string& assignedTo,
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

#endif
