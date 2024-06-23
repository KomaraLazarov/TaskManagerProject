#include "CollaborationTask.h"
#include "Utility.h"
#include <iomanip>

CollaborationTask::CollaborationTask() : Task()
{
}

CollaborationTask::CollaborationTask(const String& name, const String& description, const User& assignee, const String& due_date_str)
	:Task(name, description, due_date_str), assignee(assignee)
{
}

User CollaborationTask::getAssignee() const
{
	return assignee;
}

void CollaborationTask::setAssignee(const User& assignee)
{
	this->assignee = assignee;
}

void CollaborationTask::printTask() const
{
	std::cout << "Task ID: " << id << "\n"
		<< "Name: " << name << "\n"
		<< "Due Date: " << std::put_time(&due_date, "%a %b %d %H:%M:%S %Y") << "\n"
		<< "Status: " << Utility::getStatus(status) << "\n"
		<< "Description: " << description << "\n"
		<< "Assignee: " << assignee.getUsername() << "\n";
}

Task* CollaborationTask::clone() const
{
	return new CollaborationTask(*this);
}

