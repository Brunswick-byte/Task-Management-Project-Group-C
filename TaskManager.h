#include <iostream>
#include <string>
using namespace std;

#include "TaskID.h"

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

    TaskID tasks[100];
    int taskCount = 0;

public:
    TaskManager(string u, string p) {
        username = u;
        password = p;
    }

    bool login(string u, string p) {
        return (username == u && password == p);
    }

    // Main menu
    void mainMenu() {
        int choice;
        while (true) {
            cout << "\n1) Add Task\n";
            cout << "2) View Tasks\n";
            cout << "3) Edit Task\n";
            cout << "4) Delete Task\n";
            cout << "0) Exit\n";
            cout << "Your choice: ";
            cin >> choice;

            if (choice == 0) break;
            else if (choice == 1) {
                TaskID newTask;
                string title, description, assignedTo;
                int status, day, month, year, priority;
                
                cin.ignore();
                
                // Get title
                if(!getTitle(title)) continue;
                
                // Get description
                if(!getDescription(description)) continue;
                
                // Get assigned to
                if(!getAssignedTo(assignedTo)) continue;
                
                // Get status
                if(!getStatus(status)) {
                    cin.ignore();
                    continue;
                }
                
                // Get date
                if(!getValidDate(day, month, year)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    continue;
                }
                
                // Get priority
                if(!getPriority(priority)) {
                    cin.ignore();
                    continue;
                }
                
                // Populate TaskID object
                newTask.setTitle(title);
                newTask.setDescription(description);
                newTask.setAssignedTo(assignedTo);
                newTask.setStatus(status);
                newTask.setDueDay(day);
                newTask.setDueMonth(month);
                newTask.setDueYear(year);
                
                // Set priority string based on priority value
                string priorityStr;
                if(priority == 1) priorityStr = "High";
                else if(priority == 2) priorityStr = "Mid";
                else if(priority == 3) priorityStr = "Low";
                newTask.setPriority(priorityStr, priority == 1 ? 1 : 0, priority == 2 ? 1 : 0, priority == 3 ? 1 : 0);
                
                addTask(newTask);
            }
            else if (choice == 2) {
                viewTasks();
            }
            else if (choice == 3) {
                int editID;
                cout << "Enter Task ID to edit: ";
                cin >> editID;
                editTask(editID);
            }
            else if (choice == 4) {
                int deleteID;
                cout << "Enter Task ID to delete: ";
                cin >> deleteID;
                deleteTask(deleteID);
            }
            else {
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
    // Add Task
    void addTask(const TaskID& t) {
        if (taskCount >= 100) {
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
        cout << "=============================\n";
    }

    // Edit Task
    void editTask(int id) {
        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].taskID == id) {
                cout << "\n===========================\n";
                cout << "\nEditing Task ID: " << id << endl;
                cout << "===========================\n";
                
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
                            if(priority == 1) priorityStr = "High";
                            else if(priority == 2) priorityStr = "Mid";
                            else if(priority == 3) priorityStr = "Low";
                            tasks[i].setPriority(priorityStr, priority == 1 ? 1 : 0, priority == 2 ? 1 : 0, priority == 3 ? 1 : 0);
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

    // Delete Task
    void deleteTask(int id) {
        for (int i = 0; i < taskCount; i++) {
            if (tasks[i].taskID == id) {

                for (int j = i; j < taskCount - 1; j++) {
                    tasks[j] = tasks[j + 1];
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

        cout << "\n======= ALL TASKS =======\n";
        for (int i = 0; i < taskCount; i++) {
            cout << tasks[i];
        }
        cout << "=========================\n";
        cout << "\nPress Enter to return";
        cin.ignore();
        cin.get();
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
            cout << "ERROR: Day "<< day << " is invalid for month " << month << ".\n";
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
                cout << "\n===========================\n";
                cout << "Invalid choice.\n";
                cout << "===========================\n";
                break;
        }
    }
}
