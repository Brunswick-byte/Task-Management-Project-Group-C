#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// User class stores login details for a single user
class User {
private:
    string username;
    string password;
    
public:
    // Default constructor
    User() : username(""), password("") {}
    
    // Overloaded constructor
    User(string n, string p){
        username = n;
        password = p;
    }

    // Get username
    string getUsername(){return username;}
    // Get password
    string getPassword(){return password;}

    // Set username
    void setUsername(string n){username = n;}
    // Set password
    void setPassword(string p){password = p;}

    // Save this user to file
    void serialize(ofstream& out) {
        out << username << endl;
        out << password << endl;
    }

    // Load this user from file
    void deserialize(ifstream& in) {
        getline(in, username);
        getline(in, password);
    }

    // Example account creation message (not used for logic)
    void createAccount(){
        cout << "Creating account for " << username << endl;
    }

    // Check login credentials
    bool login(string n, string p){
        return (n == username && p == password);
    }
};

// Save all users to users.txt
inline void saveUsers(User** users, int userCount) {
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

// Load all users from users.txt
inline int loadUsers(User** users) {
    ifstream inFile("users.txt");
    if (!inFile) {
        return 0;
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

#endif
