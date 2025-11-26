#include <iostream>
#include "Task.h"


int main(){
    // Create a Task object
    Task myTask("Project", "Create a task management app ", "In Progress", "Alice", "2024-12-31", "High");
    
    // Set additional details
    // myTask.setStatus("In Progress");
    
    // Display task details
    myTask.displayTask();
    std::cout << "End of Program" << std::endl;
    
    return 0;
    return 0;
}