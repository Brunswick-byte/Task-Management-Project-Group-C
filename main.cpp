#include <iostream>
#include <string>
#include "TaskManager.h"
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


    // Choice to add task
    cout << "\n";
    cout << "\n1) Add Task\n";
    cout << "0) Exit\n";
    cout << "Your choice: ";
    cin >> choice;
    if(choice == 0) return 0;
    
    if(choice != 1) {
        cout << "\nInvalid choice. Exiting Task Manager. Goodbye!\n";
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
    cout << "0) Exit\n";
    cout << "Your choice: ";
    cin >> choice;
    
    if(choice == 1) {
        cout << "\n===========================\n";
        cout << "Redirecting to Edit Task...\n";
        cout << "===========================\n";
        editTask(title, description, assignedTo, status, dueDayDate, dueMonthDate, dueYearDate, priority);
    }
    
    return 0;    
}