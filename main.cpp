#include <iostream>
#include <string>
#include "TaskManager.h"
#include "TaskID.h"

using namespace std;

int main(){
    // User input
    string title = "", username = "", password = "", description = "", assignedTo = "";
    int status = 0, dueDayDate = 0, dueMonthDate = 0, dueYearDate = 0, priority = 0, choice = 0;

    // Input

    cout << "============================\n";
    cout << "------- Task Manager -------\n";
    cout << "============================\n";
    cout << "\nWelcome to the Task Manager!\n";
    cout << "Please login to continue.\n";
    cout << "\nEnter 0 to exit.\n";

    
    // Username input
    cout << "\nEnter Username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    getline(cin, password);
    cout << "\n===========================\n";
    cout << "\nLogin Successful!\n";
    cout << "\nWelcome, " << username << "!\n";


    // Main menu
    TaskManager tm(username, password);
    tm.mainMenu();
    cout << "0) Exit\n";
    cout << "Your choice: ";
    cin >> choice;
    if(choice == 0) return 0;
    else if (choice == 1) {
        cout << "\n===========================\n";
        cout << "Redirecting to Add Task...\n";
        cout << "===========================\n";
        
    } else if(choice == 2) {
        cout << "\n===========================\n";
        cout << "Redirecting to View Tasks...\n";
        cout << "===========================\n";
        TaskManager tm(username, password);
        tm.viewTasks();
        return 0;
    } else if(choice == 3) {
        int editID;
        cout << "\n===========================\n";
        cout << "Enter Task ID to edit: ";
        cin >> editID;
        cout << "Redirecting to Edit Task...\n";
        cout << "===========================\n";
        TaskManager tm(username, password);
        tm.editTask(editID);
        return 0;
    } else if(choice == 4) {
        int deleteID;
        cout << "\n===========================\n";
        cout << "Enter Task ID to delete: ";
        cin >> deleteID;
        cout << "Redirecting to Delete Task...\n";
        cout << "===========================\n";
        TaskManager tm(username, password);
        tm.deleteTask(deleteID);
        return 0;
    } else {
        cout << "Invalid choice. Exiting.\n";
        return 0;
    }
        
    
    // Add Task
    cout << "\n===========================\n";
    cout << "----- Create New Task -----\n";
    cout << "===========================\n";
    
    // Create task using functions
    if(!createTask(title, description, assignedTo, status, dueDayDate, dueMonthDate, dueYearDate, priority)) {
        return 0;
    }
    
    // Display the created task
    displayTask(title, description, assignedTo, status, dueDayDate, dueMonthDate, dueYearDate, priority);
    
    // Post-creation menu
    cout << "\nWhat would you like to do?\n";
    cout << "1) Edit This Task\n";
    cout << "2) Return to Main Menu\n";
    cout << "0) Exit\n";
    cout << "Your choice: ";
    cin >> choice;
    
    if(choice == 1) {
        cout << "\n===========================\n";
        cout << "Redirecting to Edit Task...\n";
        cout << "===========================\n";
        editTask(title, description, assignedTo, status, dueDayDate, dueMonthDate, dueYearDate, priority);
    } else if(choice == 2) {
        cout << "\n===========================\n";
        cout << "Returning to Main Menu...\n";
        cout << "===========================\n";

    } else {
        cout << "Exiting...\n";
    }
    
    return 0;    
}
