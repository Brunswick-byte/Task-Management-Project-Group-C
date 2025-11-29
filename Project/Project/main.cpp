#include <iostream>
#include <string>
using namespace std;

int main(){


    // User input
    string title = "", username = "", password = "", description = "", assignedTo = "";
    int status = 0, dueDayDate = 0, dueMonthDate = 0, dueYearDate = 0, priority = 0, addTask = 0, editTask = 0, removeTask = 0;

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


    // Choice to add, edit, or remove task
    cout << "\n";
    cout << "\n";
    cout << "\n1) Add Task\n";
    cout << "2) Edit Task\n";
    cout << "3) Remove Task\n";
    cout << "0) Exit\n";
    cout << "Your choice: ";
    cin >> addTask;
    if(addTask == 0) return 0;


    // Add Task
    cout << "\n===========================\n";
    cout << "----- Create New Task -----\n";
    cout << "===========================\n";

    // Title input
    stepTitle:
    cout << "\nEnter Task Title: ";
    cin.ignore();
    getline(cin, title);
    if(title == "0") return 0;

    // Description input
    stepDescription:
    cout << "Enter Task Description: ";
    getline(cin, description);
    if(description == "0") goto stepTitle;

    // Assigned To input
    stepAssignedTo:
    cout << "Enter Assigned To: ";
    getline(cin, assignedTo);
    if(assignedTo == "0") goto stepDescription;

    // Status input
    stepStatus:
    cout << "Enter Task Status: \n";
    cout << "1) Pending\n";
    cout << "2) In Progress\n";
    cout << "3) Completed\n";
    cin >> status;
    if(status == 0) goto stepAssignedTo;
    while(status < 1 || status > 3){
        cout << "\n===================================\n";
        cout << "ERROR: INVALID STATUS.\n";
        cout << "===================================\n";
        cout << "Please Re-enter Task Status: ";
        cin >> status;
        if(status == 0) goto stepAssignedTo;
    }

    // Due Date input
    stepDueDay:
    cout << "Enter Due Day (In DD): ";
    cin >> dueDayDate;
    if(dueDayDate == 0) goto stepStatus;
    while(dueDayDate < 1 || dueDayDate > 31){
        cout << "\n===================================\n";
        cout << "ERROR: INVALID DATE.\n";
        cout << "===================================\n";
        cout << "Please Re-enter Day: ";
        cin >> dueDayDate;
        if(dueDayDate == 0) goto stepStatus;
    }

    stepDueMonth:
    cout << "Enter Due Month (In MM): ";
    cin >> dueMonthDate;
    if(dueMonthDate == 0) goto stepDueDay;
    while(dueMonthDate < 1 || dueMonthDate > 12){
        cout << "\n===================================\n";
        cout << "ERROR: INVALID DATE.\n";
        cout << "===================================\n";
        cout << "Please Re-enter Month: ";
        cin >> dueMonthDate;
        if(dueMonthDate == 0) goto stepDueDay;
    }
    
    if(dueMonthDate == 1 || dueMonthDate == 3 || dueMonthDate == 5 || dueMonthDate == 7 || dueMonthDate == 8 || dueMonthDate == 10 || dueMonthDate == 12){
        while(dueDayDate < 1 || dueDayDate > 31){
            cout << "\n===================================\n";
            cout << "ERROR: INVALID DATE.\n";
            cout << "===================================\n";
            cout << "Please Re-enter Month: ";
            cin >> dueMonthDate;
            if(dueMonthDate == 0) goto stepDueDay;
        }
    }
    else if(dueMonthDate == 4 || dueMonthDate == 6 || dueMonthDate == 9 || dueMonthDate == 11){
        while(dueDayDate < 1 || dueDayDate > 30){
            cout << "\n===================================\n";
            cout << "ERROR: INVALID DATE.\n";
            cout << "===================================\n";
            cout << "Please Re-enter Month: ";
            cin >> dueMonthDate;
            if(dueMonthDate == 0) goto stepDueDay;
        }
    }
    else if(dueMonthDate == 2){
        while(dueDayDate < 1 || dueDayDate > 28){
            cout << "\n===================================\n";
            cout << "ERROR: INVALID DATE.\n";
            cout << "===================================\n";
            cout << "Please Re-enter Day: ";
            cin >> dueMonthDate;
            if(dueMonthDate == 0) goto stepDueDay;
        }
    }
    
    stepDueYear:
    cout << "\nEnter Due Year (In YYYY): ";
    cin >> dueYearDate;
    if(dueYearDate == 0) goto stepDueMonth;
    while(dueYearDate < 2024){
        cout << "\n===================================\n";
        cout << "ERROR: INVALID YEAR.\n";
        cout << "===================================\n";
        cout << "Please Re-enter Year: ";
        cin >> dueYearDate;
        if(dueYearDate == 0) goto stepDueMonth;
    }
    
    // Priority input
    stepPriority:
    cout << "\nEnter Priority: \n";
    cout << "1) High\n";
    cout << "2) Mid\n";
    cout << "3) Low\n";
    cin >> priority;
    if(priority == 0) goto stepDueYear;
    while(priority < 1 || priority > 3){
        cout << "\n===================================\n";
        cout << "ERROR: INVALID PRIORITY.\n";
        cout << "===================================\n";
        cout << "Please Re-enter Priority: ";
        cin >> priority;
        if(priority == 0) goto stepDueYear;
    }
    
    displayTask:
    cout << "\n=====================================\n";
    cout << "----- Task Created Successfully -----\n";
    cout << "=====================================\n";
    cout << "Task Title: " << title << endl;
    cout << "Task Description: " << description << endl;
    cout << "Task Status: ";
    if(status == 1) cout << "Pending" << endl;
    else if(status == 2) cout << "In Progress" << endl;
    else if(status == 3) cout << "Completed" << endl;
    cout << "Assigned To: " << assignedTo << endl;
    cout << "Due Date: " << dueDayDate << "/" << dueMonthDate << "/" << dueYearDate << endl;
    cout << "Task Priority: ";
    if(priority == 1) cout << "High priority" << endl;
    else if(priority == 2) cout << "Mid priority" << endl;
    else if(priority == 3) cout << "Low priority" << endl;
    cout << "===================================\n";
    
    // Edit menu
    cout << "\nWhat would you like to do?\n";
    cout << "1) Edit This Task\n";
    cout << "2) Add Another Task\n";
    cout << "3) Remove This Task\n";
    cout << "\n0) Exit\n";
    
    int choice;
    cin >> choice;
    cin.ignore();
    
    switch(choice){
        case 1:
        cout << "\nEdit Task feature is under development.\n";
        main();
        break;

        case 2:
        cout << "\nRedirecting to Add Another Task...\n";
        main();
        break;

        case 3:
        cout << "\nRemove Task feature is under development.\n";
        break;

        case 0:
        cout << "\nExiting Task Manager. Goodbye!\n";
        break;

        default:
        cout << "\nInvalid choice. Exiting Task Manager. Goodbye!\n";
        break;
    }
    
    return 0;    
}
