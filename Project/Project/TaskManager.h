#include <string>
#include <iostream>

using namespace std;

class TaskManager {
private:
    string username;
    string password;

    string title;
    string description;
    int status;
    string assignedTo;

    int dueDayDate;
    int dueMonthDate;
    int dueYearDate;

    string priority;
    int priorityHigh;
    int priorityMid;
    int priorityLow;

public:
    // Constructor
    TaskManager(string u, string p, string t, string d, int s, string a, int ddd, int dmd, int dyd, string pr ,int pH = 1, int pM = 2, int pL =3) {
        username = u;
        password = p;

        title = t;
        description = d;
        status = s;
        assignedTo = a;

        dueDayDate = ddd;
        dueMonthDate = dmd;
        dueYearDate = dyd;

        priority = pr;
        priorityHigh = pH;
        priorityMid = pM;
        priorityLow = pL;
    }
    
    // Destructor
    ~TaskManager() {}


    // Setters   
    void setUsername(string u) {username = u;}
    void setPassword(string p) {password = p;}

    void setTitle(string t) {title = t;}
    void setDescription(string d) {description = d;}
    void setStatus(int s) {status = s;}
    void setAssignedTo(string a) {assignedTo = a;}

    void setDueDate(int ddd) {dueDayDate = ddd;}
    void setDueMonthDate(int dmd) {dueMonthDate = dmd;}
    void setDueYearDate(int dyd) {dueYearDate = dyd;}

    void setPriority(string pr, int pH, int pM, int pL) {
        priority = pr;
        priorityHigh = pH;
        priorityMid = pM;
        priorityLow = pL;
    }

    // Getters

    string getUsername() {return username;}
    string getPassword() {return password;}
    
    string getTitle() {return title;}
    string getDescription() {return description;}   
    int getStatus() {return status;}
    string getAssignedTo() {return assignedTo;}
    int getDueDayDate() {return dueDayDate;}
    int getDueMonthDate() {return dueMonthDate;}
    int getDueYearDate() {return dueYearDate;}
    string getPriority() {return priority;}
    int getPriorityHigh() {return priorityHigh;}
    int getPriorityMid() {return priorityMid;}
    int getPriorityLow() {return priorityLow;}


    // Login
    bool login(string u, string p) {
        return (username == u && password == p);
    }


    // Add Task
    void addTask(string t, string d, int s, string a, int ddd, int dmd, int dyd, string pr, int pH, int pM, int pL) {
        title = t;
        description = d;
        status = s;
        assignedTo = a;

        dueDayDate = ddd;
        dueMonthDate = dmd;
        dueYearDate = dyd;

        priority = pr;
        priorityHigh = pH;
        priorityMid = pM;
        priorityLow = pL;
    }

    // Edit Task
    void editTask(string t, string d, int s, string a, int ddd, int dmd, int dyd, int pH, int pM, int pL) {
        title = t;
        description = d;
        status = s;
        assignedTo = a;
        dueDayDate = ddd;
        dueMonthDate = dmd;
        dueYearDate = dyd;
        priorityHigh = pH;
    }

    // Delete Task
    void deleteTask() {
        title = "";
        description = "";
        status = 0;
        assignedTo = "";
        dueDayDate = 0;
        dueMonthDate = 0;
        dueYearDate = 0;
        priorityHigh = 0;
        priorityMid = 0;
        priorityLow = 0;
    }

    // Operator
    friend ostream& operator<<(ostream& os, const TaskManager& task) {
        os << "----- Task Details -----" << endl;
        os << "Title: " << task.title << endl;
        os << "Description: " << task.description << endl;
        os << "Status: " << task.status << endl;
        os << "Assigned To: " << task.assignedTo << endl;
        os << "Due Date: " << task.dueDayDate << "/" << task.dueMonthDate << "/" << task.dueYearDate << endl;
        os << "Priority High: " << task.priority << endl;
        os << "-------------------------" << endl;
        return os;
    }
    
    // Display Task Details
    void printTask() {
        cout << "----- Task Details -----" << endl;
        cout << "Title: " << title << endl;
        cout << "Description: " << description << endl;
        cout << "Status: " << status << endl;
        cout << "Assigned To: " << assignedTo << endl;
        cout << "Due Date: " << dueDayDate << "/" << dueMonthDate << "/" << dueYearDate << endl;
        cout << "Priority: " << priority << endl;
        cout << "------------------------" << endl;
    }        
};
