#include "PersonalTask.h"
#include "Utility.h"
#include <iomanip>
#include <fstream>
#include "User.h"

PersonalTask::PersonalTask() : Task()
{
}

PersonalTask::PersonalTask(const String& name, const String& description, const String& due_date_str)
	:Task(name, description, due_date_str)
{
}

void PersonalTask::printTask() const
{
    std::cout << "Task ID: " << id << "\n"
        << "Name: " << name << "\n"
        << "Due Date: " << std::put_time(&due_date, "%a %b %d %H:%M:%S %Y") << "\n"
        << "Status: " << Utility::getStatus(status) << "\n"
        << "Description: " << description << "\n";
}

Task* PersonalTask::clone() const
{
	return new PersonalTask(*this);
}

void PersonalTask::save(std::ofstream& ofs) const 
{
    ofs.write("P", 1);

    Task::save(ofs);
}

void PersonalTask::load(std::ifstream& ifs)
{
    Task::load(ifs);
}
