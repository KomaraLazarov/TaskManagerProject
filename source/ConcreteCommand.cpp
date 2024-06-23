#include "ConcreteCommand.h"

RegisterCommand::RegisterCommand(TaskManager* tm, const String& user, const String& pass)
    : taskManager(tm), username(user), password(pass) 
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void RegisterCommand::execute() 
{
    taskManager->registerUser(username, password);
}

LoginCommand::LoginCommand(TaskManager* tm, const String& user, const String& pass)
    : taskManager(tm), username(user), password(pass) 
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void LoginCommand::execute()
{
    taskManager->loginUser(username, password);
}

AddTaskCommand::AddTaskCommand(TaskManager* tm, const String& taskName, const String& dueDate, const String& taskDesc)
    : taskManager(tm), name(taskName), due_date(dueDate), description(taskDesc)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void AddTaskCommand::execute()
{
    taskManager->addTask(name, due_date, description);
}

UpdateTaskNameCommand::UpdateTaskNameCommand(TaskManager* tm, unsigned taskId, const String& newTaskName)
    : taskManager(tm), id(taskId), newName(newTaskName)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void UpdateTaskNameCommand::execute() 
{
    taskManager->updateTaskName(id, newName);

}

StartTaskCommand::StartTaskCommand(TaskManager* tm, unsigned taskId)
    : taskManager(tm), id(taskId)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void StartTaskCommand::execute() 
{
    taskManager->startTask(id);
}

UpdateTaskDescriptionCommand::UpdateTaskDescriptionCommand(TaskManager* tm, unsigned taskId, const String& desc)
    : taskManager(tm), id(taskId), description(desc)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void UpdateTaskDescriptionCommand::execute()
{
    taskManager->updateTaskDescription(id, description);
}

RemoveTaskFromDashboardCommand::RemoveTaskFromDashboardCommand(TaskManager* tm, unsigned taskId)
    : taskManager(tm), id(taskId)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void RemoveTaskFromDashboardCommand::execute()
{
    taskManager->removeTaskFromDashboard(id);
}

AddTaskToDashboardCommand::AddTaskToDashboardCommand(TaskManager* tm, unsigned taskId)
    : taskManager(tm), id(taskId)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void AddTaskToDashboardCommand::execute() 
{
    taskManager->addTaskToDashboard(id);
}

DeleteTaskCommand::DeleteTaskCommand(TaskManager* tm, unsigned taskId)
    : taskManager(tm), id(taskId)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void DeleteTaskCommand::execute() 
{
    taskManager->deleteTask(id);
}

GetTaskByNameCommand::GetTaskByNameCommand(TaskManager* tm, const String& taskName)
    : taskManager(tm), name(taskName)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void GetTaskByNameCommand::execute() 
{
    taskManager->getTask(name);
}

GetTaskByIdCommand::GetTaskByIdCommand(TaskManager* tm, unsigned taskId)
    : taskManager(tm), id(taskId)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void GetTaskByIdCommand::execute() 
{
    taskManager->getTask(id);
}

ListTasksCommand::ListTasksCommand(TaskManager* tm)
    : taskManager(tm)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void ListTasksCommand::execute()
{
    taskManager->listTasks();
}

ListTasksByDateCommand::ListTasksByDateCommand(TaskManager* tm, const String& taskDate)
    : taskManager(tm), date(taskDate)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void ListTasksByDateCommand::execute()
{
    taskManager->listTasks(date);
}

ListCompletedTasksCommand::ListCompletedTasksCommand(TaskManager* tm)
    : taskManager(tm)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void ListCompletedTasksCommand::execute()
{
    taskManager->listCompletedTasks();
}

ListDashboardCommand::ListDashboardCommand(TaskManager* tm)
    : taskManager(tm)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void ListDashboardCommand::execute() 
{
    taskManager->listDashboard();
}

FinishTaskCommand::FinishTaskCommand(TaskManager* tm, unsigned taskId)
    : taskManager(tm), id(taskId)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void FinishTaskCommand::execute() 
{
    taskManager->finishTask(id);
}

AddCollaborationCommand::AddCollaborationCommand(TaskManager* tm, const String& collabName)
    : taskManager(tm), name(collabName)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void AddCollaborationCommand::execute()
{
    taskManager->addCollaboration(name);
}

DeleteCollaborationCommand::DeleteCollaborationCommand(TaskManager* tm, const String& collabName)
    : taskManager(tm), name(collabName)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void DeleteCollaborationCommand::execute()
{
    taskManager->deleteCollaboration(name);
}

ListCollaborationsCommand::ListCollaborationsCommand(TaskManager* tm)
    : taskManager(tm)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void ListCollaborationsCommand::execute()
{
    taskManager->listCollaborations();
}

AddUserToCollaborationCommand::AddUserToCollaborationCommand(TaskManager* tm, const String& collab, const String& user)
    : taskManager(tm), collabName(collab), username(user)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void AddUserToCollaborationCommand::execute()
{
    taskManager->addUserToCollaboration(collabName, username);
}

AssignTaskToCollaborationCommand::AssignTaskToCollaborationCommand(TaskManager* tm, const String& collab, const String& user,
    const String& taskName, const String& dueDate, const String& desc)
    : taskManager(tm), collabName(collab), username(user), taskName(taskName), due_date(dueDate), description(desc)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void AssignTaskToCollaborationCommand::execute() 
{
    taskManager->assignTaskToCollaboration(collabName, username, taskName, due_date, description);
}

ListTasksInCollaborationCommand::ListTasksInCollaborationCommand(TaskManager* tm, const String& collab)
    : taskManager(tm), collabName(collab)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}
    

void ListTasksInCollaborationCommand::execute() 
{
    taskManager->listCollaborationTasks(collabName);
}

LogoutCommand::LogoutCommand(TaskManager* tm)
    : taskManager(tm)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void LogoutCommand::execute()
{
    taskManager->logout();
}

ExitCommand::ExitCommand(TaskManager* tm)
    : taskManager(tm)
{
    if (!tm)
    {
        throw std::invalid_argument("Nullptr has given!");
    }
}

void ExitCommand::execute() 
{
    taskManager->exit();
}