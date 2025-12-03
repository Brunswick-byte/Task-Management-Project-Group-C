#ifndef TASKID_H
#define TASKID_H

#include <iostream>
#include <string>

using namespace std;

class TaskID {
public:
    int taskID;
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

    // Default Constructor
    TaskID() {
        taskID = 0;
        title = "";
        description = "";
        status = 0;
        assignedTo = "";
        dueDayDate = dueMonthDate = dueYearDate = 0;
        priority = "";
        priorityHigh = priorityMid = priorityLow = 0;
    }

    // Setters
    void setTitle(string t) { title = t; }
    void setDescription(string d) { description = d; }
    void setStatus(int s) { status = s; }
    void setAssignedTo(string a) { assignedTo = a; }
    void setDueDay(int d) { dueDayDate = d; }
    void setDueMonth(int m) { dueMonthDate = m; }
    void setDueYear(int y) { dueYearDate = y; }
    void setPriority(string pr, int pH, int pM, int pL) {
        priority = pr;
        priorityHigh = pH;
        priorityMid = pM;
        priorityLow = pL;
    }

    // Getters
    string getTitle() { return title; }
    string getDescription() { return description; }
    int getStatus() { return status; }
    string getAssignedTo() { return assignedTo; }
    int getDueDay() { return dueDayDate; }
    int getDueMonth() { return dueMonthDate; }
    int getDueYear() { return dueYearDate; }
    string getPriority() { return priority; }
};

// Operator to print a Task
ostream& operator<<(ostream& os, const TaskID& t) {
    os << "\n----- Task Details -----\n";
    os << "Task ID: " << t.taskID << endl;
    os << "Title: " << t.title << endl;
    os << "Description: " << t.description << endl;
    os << "Priority: " << t.priority << endl;
    os << "Status: ";
    if(t.status == 1) os << "Pending" << endl;
    else if(t.status == 2) os << "In Progress" << endl;
    else if(t.status == 3) os << "Completed" << endl;
    os << "Assigned To: " << t.assignedTo << endl;
    os << "Due Date: " << t.dueDayDate << "/" << t.dueMonthDate << "/" << t.dueYearDate << endl;
    os << "-------------------------\n";
    return os;
}

#endif 
