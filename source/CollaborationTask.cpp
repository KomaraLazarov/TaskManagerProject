#include "CollaborationTask.h"
#include "Utility.h"
#include "User.h"
#include <iomanip>

CollaborationTask::CollaborationTask() : Task()
{
}

CollaborationTask::CollaborationTask(const String& name, const String& description, const String& assigneeUsername, const String& due_date_str)
	:Task(name, description, due_date_str), assigneeUsername(assigneeUsername)
{
}

const String& CollaborationTask::getAssignee() const
{
	return assigneeUsername;
}

void CollaborationTask::setAssignee(const String& assigneeUsername)
{
	this->assigneeUsername = assigneeUsername;
}

void CollaborationTask::printTask() const
{
	std::cout << "Task ID: " << id << "\n"
		<< "Name: " << name << "\n"
		<< "Due Date: " << std::put_time(&due_date, "%a %b %d %H:%M:%S %Y") << "\n"
		<< "Status: " << Utility::getStatus(status) << "\n"
		<< "Description: " << description << "\n"
		<< "Assignee: " << assigneeUsername.c_str() << "\n";
}

void CollaborationTask::save(std::ofstream& ofs) const
{
	ofs.write("C", 1);

	size_t nameSize = assigneeUsername.getSize();
	ofs.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
	ofs.write(assigneeUsername.c_str(), nameSize + 1);

	Task::save(ofs);
}

void CollaborationTask::load(std::ifstream& ifs)
{
	Utility::loadStringFromFile(ifs, assigneeUsername);
	Task::load(ifs);
}

Task* CollaborationTask::clone() const
{
	return new CollaborationTask(*this);
}

