#include <string>
#include <iostream>

using namespace std;

class Task {
private:
    string title;
    string description;
    string status;
    string assignedTo;
    string dueDate;
    string priority;

public:
    // Constructor
    Task(string t, string d, string s, string a, string due, string p) {
        title = t;
        description = d;
        status = s;
        assignedTo = a;
        dueDate = due;
        priority = p;
        cout << "Task " << title << " created." << endl;
    }
    
    // Destructor
    ~Task() {
        cout << "Task " << title << " destroyed." << endl;
    }

    // Setters
    void setTitle(const string& t) {
        title = t;
    }
    void setDescription(const string& d) {
        description = d;
    }
    void setStatus(const string& s) {
        status = s;
    }
    void setAssignedTo(const string& a) {
        assignedTo = a;
    }
    void setDueDate(const string& due) {
        dueDate = due;
    }
    void setPriority(const string& p) {
        priority = p;
    }

    // Getters
    string getTitle() const {
        return title;
    }
    string getDescription() const {
        return description;
    }   
    string getStatus() const {
        return status;
    }
    string getAssignedTo() const {
        return assignedTo;
    }
    string getDueDate() const {
        return dueDate;
    }
    string getPriority() const {
        return priority;
    }

    // Display Task Details
    void displayTask() const {
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Status: " << status << endl;
        cout << "Assigned To: " << assignedTo << endl;
        cout << "Due Date: " << dueDate << endl;
        cout << "Priority: " << priority << endl;
    }

        
};
