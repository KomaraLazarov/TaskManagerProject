#pragma once
#include "String.h"
#include "Command.h"
#include "TaskManager.h"

class RegisterCommand : public Command
{
    TaskManager* taskManager;
    String username;
    String password;
public:
    RegisterCommand(TaskManager* tm, const String& user, const String& pass);
    void execute() override;
};

class LoginCommand : public Command 
{
    TaskManager* taskManager;
    String username;
    String password;
public:
    LoginCommand(TaskManager* tm, const String& user, const String& pass);
    void execute() override;
};

class AddTaskCommand : public Command 
{
    TaskManager* taskManager;
    String name;
    String due_date;
    String description;
public:
    AddTaskCommand(TaskManager* tm, const String& taskName, const String& taskDesc, const String& dueDate);
    void execute() override;
};

class UpdateTaskNameCommand : public Command 
{
    TaskManager* taskManager;
    unsigned id;
    String newName;
public:
    UpdateTaskNameCommand(TaskManager* tm, unsigned taskId, const String& newTaskName);
    void execute() override;
};

class StartTaskCommand : public Command
{
    TaskManager* taskManager;
    unsigned id;
public:
    StartTaskCommand(TaskManager* tm, unsigned taskId);
    void execute() override;
};

class UpdateTaskDescriptionCommand : public Command 
{
    TaskManager* taskManager;
    unsigned id;
    String description;
public:
    UpdateTaskDescriptionCommand(TaskManager* tm, unsigned taskId, const String& desc);
    void execute() override;
};

class RemoveTaskFromDashboardCommand : public Command
{
    TaskManager* taskManager;
    unsigned id;
public:
    RemoveTaskFromDashboardCommand(TaskManager* tm, unsigned taskId);
    void execute() override;
};

class AddTaskToDashboardCommand : public Command
{
    TaskManager* taskManager;
    unsigned id;
public:
    AddTaskToDashboardCommand(TaskManager* tm, unsigned taskId);
    void execute() override;
};

class DeleteTaskCommand : public Command 
{
    TaskManager* taskManager;
    unsigned id;
public:
    DeleteTaskCommand(TaskManager* tm, unsigned taskId);
    void execute() override;
};

class GetTaskByNameCommand : public Command
{
    TaskManager* taskManager;
    String name;
public:
    GetTaskByNameCommand(TaskManager* tm, const String& taskName);
    void execute() override;
};

class GetTaskByIdCommand : public Command 
{
    TaskManager* taskManager;
    unsigned id;
public:
    GetTaskByIdCommand(TaskManager* tm, unsigned taskId);
    void execute() override;
};

class ListTasksCommand : public Command
{
    TaskManager* taskManager;
public:
    ListTasksCommand(TaskManager* tm);
    void execute() override;
};

class ListTasksByDateCommand : public Command
{
    TaskManager* taskManager;
    String date;
public:
    ListTasksByDateCommand(TaskManager* tm, const String& taskDate);
    void execute() override;
};

class ListCompletedTasksCommand : public Command
{
    TaskManager* taskManager;
public:
    ListCompletedTasksCommand(TaskManager* tm);
    void execute() override;
};

class ListDashboardCommand : public Command
{
    TaskManager* taskManager;
public:
    ListDashboardCommand(TaskManager* tm);
    void execute() override;
};

class FinishTaskCommand : public Command
{
    TaskManager* taskManager;
    unsigned id;
public:
    FinishTaskCommand(TaskManager* tm, unsigned taskId);
    void execute() override;
};

class AddCollaborationCommand : public Command
{
    TaskManager* taskManager;
    String name;
public:
    AddCollaborationCommand(TaskManager* tm, const String& collabName);
    void execute() override;
};

class DeleteCollaborationCommand : public Command
{
    TaskManager* taskManager;
    String name;
public:
    DeleteCollaborationCommand(TaskManager* tm, const String& collabName);
    void execute() override;
};

class ListCollaborationsCommand : public Command 
{
    TaskManager* taskManager;
public:
    ListCollaborationsCommand(TaskManager* tm);
    void execute() override;
};

class AddUserToCollaborationCommand : public Command 
{
    TaskManager* taskManager;
    String collabName;
    String username;
public:
    AddUserToCollaborationCommand(TaskManager* tm, const String& collab, const String& user);
    void execute() override;
};

class AssignTaskToCollaborationCommand : public Command 
{
    TaskManager* taskManager;
    String collabName;
    String username;
    String taskName;
    String due_date;
    String description;
public:
    AssignTaskToCollaborationCommand(TaskManager* tm, const String& collab, const String& user, const String& taskName,
        const String& dueDate, const String& desc);
    void execute() override;
};

class ListTasksInCollaborationCommand : public Command 
{
    TaskManager* taskManager;
    String collabName;
public:
    ListTasksInCollaborationCommand(TaskManager* tm, const String& collab);
    void execute() override;
};

class LogoutCommand : public Command 
{
    TaskManager* taskManager;
public:
    LogoutCommand(TaskManager* tm);
    void execute() override;
};

class ExitCommand : public Command 
{
    TaskManager* taskManager;
public:
    ExitCommand(TaskManager* tm);
    void execute() override;
};