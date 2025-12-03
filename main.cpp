#include <iostream>
#include <string>
using namespace std;

#include "TaskID.h"
#include "User.h"
#include "TaskManager.h"

// Program entry point
int main(){
    // Array of pointers to store registered users in memory
    User* users[100];
    int userCount = 0;
    
    // Load existing users from file at startup
    userCount = loadUsers(users);
    if (userCount > 0) {
        cout << "Loaded " << userCount << " user(s) from file.\n";
    }
    
    string username = "", password = "";
    int choice = 0;
    bool exitProgram = false;

    // Welcome banner
    cout << "============================\n";
    cout << "------- Task Manager -------\n";
    cout << "============================\n";
    cout << "\nWelcome to the Task Manager!\n";

    // Outer loop: runs until user chooses to exit program
    while (!exitProgram) {
        bool loggedIn = false;
        
        // Login / Signup loop
        while (!loggedIn && !exitProgram) {
            cout << "\nPlease select an option:\n";
            cout << "1) Login\n";
            cout << "2) Signup\n";
            cout << "0) Exit\n";
            cout << "Your choice: ";
            cin >> choice;
            cin.ignore();
            
            if(choice == 0) {
                // Exit entire program
                exitProgram = true;
                break;
            }
            else if(choice == 2) {
                // Signup workflow
                cout << "\n===========================\n";
                cout << "--------- Sign Up ---------\n";
                cout << "===========================\n";
                
                cout << "\nEnter New Username: ";
                getline(cin, username);
                
                // Check if username is already taken
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
                
                // Basic password length check
                if(password.length() < 4) {
                    cout << "\n===========================\n";
                    cout << "ERROR: Password must be at least 4 characters!\n";
                    cout << "===========================\n";
                    continue;
                }
                
                // Create and store new user
                users[userCount] = new User(username, password);
                userCount++;
                
                // Save users after signup
                saveUsers(users, userCount);
                
                cout << "\n===========================\n";
                cout << "Signup Successful!\n";
                cout << "Welcome, " << username << "!\n";
                cout << "===========================\n";
                loggedIn = true;
            }
            else if(choice == 1) {
                // Login workflow
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
                
                // Check username/password against stored users
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
                // Invalid option in login/signup menu
                cout << "\n===========================\n";
                cout << "Invalid choice. Please try again.\n";
                cout << "===========================\n";
            }
        }
        
        // If user is logged in, create a TaskManager and show task menu
        if(loggedIn) {
            TaskManager tm(username, password);
            tm.mainMenu();
        }
    }
    
    // Save users one last time before program exits
    saveUsers(users, userCount);
    
    // Free dynamically allocated user objects
    for(int i = 0; i < userCount; i++) {
        delete users[i];
    }
    
    cout << "\nThank you for using Task Manager!\n";
    cout << "All data has been saved.\n";
    return 0;    
}
