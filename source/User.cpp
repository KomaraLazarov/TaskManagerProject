#include "User.h"
#include "Utility.h"
#include "PolimorphicPtr.hpp"
#include "PersonalTask.h"
#include "CollaborationTask.h"

User::User(const String& username, const String& password)
	: username(username), password(password)
{
}

const String& User::getUsername() const
{
    return username;
}

bool User::checkPassword(const String& password) const
{
    return this->password == password;
}

void User::addTask(Task* task)
{
    if (!task)
    {
        throw std::invalid_argument("Submitted task must be non-null.");
    }
    tasks.push_back(task);
}

const Vector<Polymorphic_Ptr<Task>>& User::getTasks()
{
    return tasks;
}

const Dashboard& User::getDashboard()
{
    return dashboard;
}

Vector<Polymorphic_Ptr<Task>>& User::getTasksInstance()
{
    return tasks;
}

Dashboard& User::getDashboardInstance()
{
    return dashboard;
}

void User::save(std::ofstream& ofs) const
{
    size_t usernameSize = username.getSize();
    ofs.write(reinterpret_cast<const char*>(&usernameSize), sizeof(usernameSize));
    ofs.write(username.c_str(), usernameSize + 1);

    size_t passwordSize = password.getSize();
    ofs.write(reinterpret_cast<const char*>(&passwordSize), sizeof(passwordSize));
    ofs.write(password.c_str(), passwordSize + 1);

    size_t tasksSize = tasks.getSize();
    ofs.write(reinterpret_cast<const char*>(&tasksSize), sizeof(tasksSize));
    for (size_t i = 0; i < tasksSize; i++)
    {
        tasks[i]->save(ofs);
    }

    //ofs.write(reinterpret_cast<const char*>(&tasks), sizeof(Vector<Polymorphic_Ptr<Task>>));

    /*ofs.write(reinterpret_cast<const char*>(&dashboard), sizeof(Dashboard));*/
}

void User::load(std::ifstream& ifs)
{
    Utility::loadStringFromFile(ifs, username);
    Utility::loadStringFromFile(ifs, password);

    size_t tasksSize;
    ifs.read(reinterpret_cast<char*>(&tasksSize), sizeof(tasksSize));
    for (size_t i = 0; i < tasksSize; i++)
    {
        char taskType;
        ifs.read(&taskType, 1);
        Polymorphic_Ptr<Task> task;

        if (taskType == 'P')
        {
            task = new PersonalTask();
        }
        else if (taskType == 'C')
        {
            task = new CollaborationTask();
        }
        else {
            std::cout << "Unknown task type in file!" << std::endl;
            continue;
        }

        task->load(ifs);
        tasks.push_back(task);
    }

    /*in.read(reinterpret_cast<char*>(&tasks), sizeof(Vector<Polymorphic_Ptr<Task>>));

    in.read(reinterpret_cast<char*>(&dashboard), sizeof(Dashboard));*/
}

void User::printTasks() const 
{
    for (size_t i = 0; i < tasks.getSize(); i++) 
    {
        tasks[i]->printTask();
    }
}
