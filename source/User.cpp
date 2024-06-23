#include "User.h"

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

void User::save(std::ofstream& out) const
{
    size_t usernameSize = username.getSize();
    out.write(reinterpret_cast<const char*>(&usernameSize), sizeof(usernameSize));
    out.write(username.c_str(), usernameSize + 1);

    size_t passwordSize = password.getSize();
    out.write(reinterpret_cast<const char*>(&passwordSize), sizeof(passwordSize));
    out.write(password.c_str(), passwordSize + 1);

    //out.write(reinterpret_cast<const char*>(&tasks), sizeof(Vector<Polymorphic_Ptr<Task>>));

    /*out.write(reinterpret_cast<const char*>(&dashboard), sizeof(Dashboard));*/
}

void User::load(std::ifstream& in)
{
    loadStringFromFile(in, username);
    loadStringFromFile(in, password);

    /*in.read(reinterpret_cast<char*>(&tasks), sizeof(Vector<Polymorphic_Ptr<Task>>));

    in.read(reinterpret_cast<char*>(&dashboard), sizeof(Dashboard));*/
}

void User::loadStringFromFile(std::ifstream& in, String& string)
{
    size_t size = 0;
    in.read(reinterpret_cast<char*>(&size), sizeof(size_t));
    char* currentUsername = new char[size + 1];
    in.read((char*)(&*currentUsername), size + 1);
    string = currentUsername;
    delete currentUsername;
}

void User::printTasks() const 
{
    for (size_t i = 0; i < tasks.getSize(); i++) 
    {
        tasks[i]->printTask();
    }
}
