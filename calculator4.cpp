#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class Task {
public:
    std::string name;
    bool is_done;

    Task(const std::string& n) : name(n), is_done(false) {}

    void markDone() {
        is_done = true;
    }
};

class TaskList {
public:
    std::vector<std::shared_ptr<Task>> tasks;

    void addTask(const std::shared_ptr<Task>& task) {
        tasks.push_back(task);
    }

    void removeTask(const std::string& taskName) {
        auto it = std::find_if(tasks.begin(), tasks.end(),
        [&taskName](const std::shared_ptr<Task>& task) {
            return task->name == taskName;
        });

        if (it != tasks.end()) {
            tasks.erase(it);
        }
    }

    std::shared_ptr<Task> findTask(const std::string& taskName) {
        auto it = std::find_if(tasks.begin(), tasks.end(),
        [&taskName](const std::shared_ptr<Task>& task) {
            return task->name == taskName;
        });

        return (it != tasks.end()) ? *it : nullptr;
    }
};

int main() {
    TaskList taskList;

    auto task1 = std::make_shared<Task>("Task1");
    auto task2 = std::make_shared<Task>("Task2");

    taskList.addTask(task1);
    taskList.addTask(task2);

    auto foundTask = taskList.findTask("Task1");
    if (foundTask) {
        foundTask->markDone();
        std::cout << "Task1 is done.\n";
    }

    taskList.removeTask("Task2");

    foundTask = taskList.findTask("Task2");
    if (!foundTask) {
        std::cout << "Task2 is removed from the task list.\n";
    }

    return 0;
}