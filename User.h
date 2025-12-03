#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
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

    string getUsername(){return username;}
    string getPassword(){return password;}

    void setUsername(string n){username = n;}
    void setPassword(string p){password = p;}

    void serialize(ofstream& out) {
        out << username << endl;
        out << password << endl;
    }

    void deserialize(ifstream& in) {
        getline(in, username);
        getline(in, password);
    }

    void createAccount(){
        cout << "Creating account for " << username << endl;
    }

    bool login(string n, string p){
        return (n == username && p == password);
    }
};

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
