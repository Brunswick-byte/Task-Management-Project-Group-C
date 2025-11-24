#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <iomanip>  // for setw, left

// =============================
// Task data structures
// =============================

enum class TaskStatus {
    Pending,
    Completed
};

struct Task {
    int id;
    std::string title;
    std::string description;
    std::string deadline;
    TaskStatus status;
};

// Global task list
std::vector<Task> tasks;
int nextTaskId = 1;

// Current logged-in user
std::string currentUser;

// =============================
// Utility input functions (UI)
// =============================

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

std::string getStringInput(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void pressEnterToContinue() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// =============================
// Forward declarations
// =============================

// UI
bool showLoginScreen();
int showMainMenu();
void handleViewTasksMenu();
void uiAddTask();
void uiEditTask();
void uiDeleteTask();
void viewTasksByStatus(int status);

// Logic
void addTask(const std::string& title,
             const std::string& description,
             const std::string& deadline);

bool editTask(int id);
bool deleteTask(int id);
void printTasksByStatus(int status);

// File I/O (placeholders)
void loadTasksFromFile(const std::string& filename);
void saveTasksToFile(const std::string& filename);

// =============================
// Main
// =============================

int main() {
    const std::string FILENAME = "tasks.txt";

    loadTasksFromFile(FILENAME);

    if (!showLoginScreen()) {
        std::cout << "Exiting program...\n";
        return 0;
    }

    bool running = true;
    while (running) {
        int choice = showMainMenu();
        switch (choice) {
            case 1: uiAddTask(); break;
            case 2: handleViewTasksMenu(); break;
            case 3: uiEditTask(); break;
            case 4: uiDeleteTask(); break;
            case 5:
                std::cout << "Logging out...\n";
                running = false;
                break;
            default:
                std::cout << "Invalid selection.\n";
        }
    }

    saveTasksToFile(FILENAME);

    std::cout << "Goodbye, " << currentUser << "!\n";
    return 0;
}

// =============================
// UI IMPLEMENTATION
// =============================

bool showLoginScreen() {
    std::cout << "=====================================\n";
    std::cout << "      Task Management System\n";
    std::cout << "=====================================\n";
    std::cout << "1. Login\n";
    std::cout << "2. Exit\n";

    int choice = getIntInput("Enter choice: ");

    if (choice == 1) {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\n=== Login ===\n";
        std::cout << "Username: ";
        std::getline(std::cin, currentUser);

        if (currentUser.empty()) {
            std::cout << "Username cannot be empty.\n";
            return false;
        }

        std::cout << "Welcome, " << currentUser << "!\n\n";
        return true;
    }

    return false;
}

int showMainMenu() {
    std::cout << "\n=====================================\n";
    std::cout << "Logged in as: " << currentUser << "\n";
    std::cout << "=====================================\n";
    std::cout << "1. Add Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Edit Task\n";
    std::cout << "4. Delete Task\n";
    std::cout << "5. Logout / Exit\n";

    return getIntInput("Enter your choice: ");
}

void handleViewTasksMenu() {
    std::cout << "\n=== View Tasks ===\n";
    std::cout << "1. View all\n";
    std::cout << "2. View pending\n";
    std::cout << "3. View completed\n";

    int choice = getIntInput("Select option: ");

    switch (choice) {
        case 1: viewTasksByStatus(0); break;
        case 2: viewTasksByStatus(1); break;
        case 3: viewTasksByStatus(2); break;
        default: std::cout << "Invalid option.\n";
    }

    pressEnterToContinue();
}

void uiAddTask() {
    std::cout << "\n=== Add Task ===\n";

    std::string title = getStringInput("Title: ");
    std::string desc = getStringInput("Description: ");
    std::string deadline = getStringInput("Deadline (DD/MM/YYYY): ");

    addTask(title, desc, deadline);

    std::cout << "Task added successfully.\n";
    pressEnterToContinue();
}

void uiEditTask() {
    std::cout << "\n=== Edit Task ===\n";
    int id = getIntInput("Enter task ID: ");

    if (!editTask(id)) {
        std::cout << "Task not found.\n";
    }

    pressEnterToContinue();
}

void uiDeleteTask() {
    std::cout << "\n=== Delete Task ===\n";
    int id = getIntInput("Task ID to delete: ");

    std::cout << "Are you sure? (Y/N): ";
    char c;
    std::cin >> c;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (c == 'Y' || c == 'y') {
        if (deleteTask(id))
            std::cout << "Task deleted.\n";
        else
            std::cout << "Task not found.\n";
    } else {
        std::cout << "Cancelled.\n";
    }

    pressEnterToContinue();
}

void viewTasksByStatus(int status) {
    std::cout << "\n=== Tasks ===\n";
    printTasksByStatus(status);
}

// =============================
// TASK LOGIC IMPLEMENTATION
// =============================

void addTask(const std::string& title,
             const std::string& description,
             const std::string& deadline)
{
    Task t;
    t.id = nextTaskId++;
    t.title = title;
    t.description = description;
    t.deadline = deadline;
    t.status = TaskStatus::Pending;

    tasks.push_back(t);
}

bool editTask(int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            std::cout << "Editing task: " << task.title << "\n";

            std::string newTitle = getStringInput("New title (blank = no change): ");
            std::string newDesc  = getStringInput("New description (blank = no change): ");
            std::string newDeadline = getStringInput("New deadline (blank = no change): ");

            std::string statusIn = getStringInput("Status (P = pending, C = completed, blank = no change): ");

            if (!newTitle.empty()) task.title = newTitle;
            if (!newDesc.empty()) task.description = newDesc;
            if (!newDeadline.empty()) task.deadline = newDeadline;

            if (!statusIn.empty()) {
                char c = std::toupper(statusIn[0]);
                if (c == 'P') task.status = TaskStatus::Pending;
                else if (c == 'C') task.status = TaskStatus::Completed;
            }

            std::cout << "Updated.\n";
            return true;
        }
    }
    return false;
}

bool deleteTask(int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            return true;
        }
    }
    return false;
}

void printTasksByStatus(int status) {
    if (tasks.empty()) {
        std::cout << "No tasks available.\n";
        return;
    }

    std::cout << std::left
              << std::setw(5) << "ID"
              << std::setw(20) << "Title"
              << std::setw(15) << "Deadline"
              << std::setw(12) << "Status"
              << "Description\n";

    std::cout << std::string(70, '-') << "\n";

    bool printed = false;

    for (const auto& task : tasks) {
        bool match =
            (status == 0) ||
            (status == 1 && task.status == TaskStatus::Pending) ||
            (status == 2 && task.status == TaskStatus::Completed);

        if (!match) continue;

        printed = true;

        std::cout << std::left
                  << std::setw(5) << task.id
                  << std::setw(20) << task.title.substr(0, 18)
                  << std::setw(15) << task.deadline
                  << std::setw(12) << (task.status == TaskStatus::Pending ? "Pending" : "Completed")
                  << task.description << "\n";
    }

    if (!printed)
        std::cout << "No tasks match this filter.\n";
}

// =============================
// FILE I/O (placeholder)
// =============================

void loadTasksFromFile(const std::string& filename) {
    std::cout << "[DEBUG] loadTasksFromFile called.\n";
}

void saveTasksToFile(const std::string& filename) {
    std::cout << "[DEBUG] saveTasksToFile called.\n";
}
