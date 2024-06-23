#pragma once
#include "String.h"
#include "Vector.hpp"
#include "User.h"
#include "Task.h"
#include "PersonalTask.h"
#include "CollaborationTask.h"
#include "Collaboration.h"
#include "PolimorphicPtr.hpp"

class TaskManager
{
private:
    Vector<User> users;
    Vector<Collaboration> collaborations;
    User* loggedInUser;
    void saveUsersData();
    void loadUsersData();

public:
    TaskManager();
    void registerUser(const String& username, const String& password);
    void loginUser(const String& username, const String& password);
    void addTask(const String& name, const String& due_date, const String& description);
    void updateTaskName(unsigned id, const String& name);
    void startTask(unsigned id);
    void updateTaskDescription(unsigned id, const String& description);
    void removeTaskFromDashboard(unsigned id);
    void addTaskToDashboard(unsigned id);
    void deleteTask(unsigned id);
    void getTask(const String& name);
    void getTask(unsigned id);
    void listTasks(const String& date);
    void listTasks();
    void listCompletedTasks();
    void listDashboard();
    void finishTask(unsigned id);
    void logout();
    void exit();

    void addCollaboration(const String& name);
    void deleteCollaboration(const String& name);
    void listCollaborations();
    void addUserToCollaboration(const String& collaborationName, const String& username);
    void assignTaskToCollaboration(const String& collaborationName, const String& username, const String& taskName,
        const String& due_date, const String& description);
    void listCollaborationTasks(const String& collaborationName);
};
