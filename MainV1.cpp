#include <iostream>
#include <string>
#include "TaskManagerV1.h"
#include "TaskIDV1.h"
#include "UserV1.h"

using namespace std;

int main(){
    // Array to store registered users
    User* users[100];
    int userCount = 0;
    
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
                cin >> username;
                
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
                cin >> password;
                
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
    
    // Clean up dynamic memory
    for(int i = 0; i < userCount; i++) {
        delete users[i];
    }
    
    cout << "\nThank you for using Task Manager!\n";
    return 0;    
}