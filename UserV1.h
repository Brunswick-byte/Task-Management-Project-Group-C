#include <iostream>
using namespace std;

class User {
    private:
        string username;
        string password;
    public:
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

        // Create account
        void createAccount(){
            cout << "Creating account for " << username << endl;
            // Additional logic for account creation
        }

        // Login
        bool login(string n, string p){
            return (n == username && p == password);
        }
};