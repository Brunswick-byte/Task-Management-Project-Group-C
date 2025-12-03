#ifndef TASKID_H
#define TASKID_H

#include <iostream>
#include <string>
#include <fstream>

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
    string ownerUsername;

    TaskID() {
        taskID = 0;
        title = "";
        description = "";
        status = 0;
        assignedTo = "";
        dueDayDate = dueMonthDate = dueYearDate = 0;
        priority = "";
        priorityHigh = priorityMid = priorityLow = 0;
        ownerUsername = "";
    }

    void setTitle(string t) { title = t; }
    void setDescription(string d) { description = d; }
    void setStatus(int s) { status = s; }
    void setAssignedTo(string a) { assignedTo = a; }
    void setDueDay(int d) { dueDayDate = d; }
    void setDueMonth(int m) { dueMonthDate = m; }
    void setDueYear(int y) { dueYearDate = y; }
    void setOwner(string owner) { ownerUsername = owner; }
    void setPriority(string pr, int pH, int pM, int pL) {
        priority = pr;
        priorityHigh = pH;
        priorityMid = pM;
        priorityLow = pL;
    }

    string getTitle() { return title; }
    string getDescription() { return description; }
    int getStatus() { return status; }
    string getAssignedTo() { return assignedTo; }
    int getDueDay() { return dueDayDate; }
    int getDueMonth() { return dueMonthDate; }
    int getDueYear() { return dueYearDate; }
    string getPriority() { return priority; }
    string getOwner() { return ownerUsername; }

    void serialize(ofstream& out) {
        out << taskID << endl;
        out << title << endl;
        out << description << endl;
        out << status << endl;
        out << assignedTo << endl;
        out << dueDayDate << endl;
        out << dueMonthDate << endl;
        out << dueYearDate << endl;
        out << priority << endl;
        out << priorityHigh << endl;
        out << priorityMid << endl;
        out << priorityLow << endl;
        out << ownerUsername << endl;
    }

    void deserialize(ifstream& in) {
        in >> taskID;
        in.ignore();
        getline(in, title);
        getline(in, description);
        in >> status;
        in.ignore();
        getline(in, assignedTo);
        in >> dueDayDate >> dueMonthDate >> dueYearDate;
        in.ignore();
        getline(in, priority);
        in >> priorityHigh >> priorityMid >> priorityLow;
        in.ignore();
        getline(in, ownerUsername);
    }
};

inline ostream& operator<<(ostream& os, const TaskID& t) {
    string statusText;
    switch (t.status) {
        case 1: statusText = "Pending"; break;
        case 2: statusText = "In Progress"; break;
        case 3: statusText = "Completed"; break;
        default: statusText = "Unknown"; break;
    }

    os << "\n========================================\n";
    os << "              TASK DETAILS              \n";
    os << "========================================\n";

    os << "Task ID     : " << t.taskID << '\n';
    os << "Title       : " << t.title << '\n';
    os << "Description : " << t.description << '\n';
    os << "Assigned To : " << t.assignedTo << '\n';
    os << "Status      : " << statusText << '\n';
    os << "Due Date    : " << t.dueDayDate << "/"
       << t.dueMonthDate << "/" << t.dueYearDate << '\n';
    os << "Priority    : " << t.priority << '\n';
    os << "Owner       : " << t.ownerUsername << '\n';

    os << "----------------------------------------\n";
    return os;
}

#endif
