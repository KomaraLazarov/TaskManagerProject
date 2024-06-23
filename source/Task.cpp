#include "Task.h"
#include <sstream>
#include <iomanip>
#include "Utility.h"


int Task::nextId = 1;


Task::Task(const String& name, const String& description, const String& due_date_str)
	: id(nextId++), name(name), description(description)
{
	if (due_date_str != "")
	{
		Utility::formatTmTypeDate(due_date_str, due_date);
	}
}

unsigned Task::getId() const
{
	return id;
}

const String& Task::getName() const
{
	return name;
}

const std::tm& Task::getDueDate() const 
{
	return due_date;
}

const Status& Task::getStatus() const 
{
	return status; 
}

void Task::setName(const String& newName) 
{
	name = newName; 
}
void Task::setDueDate(const String& due_date_str) 
{
	std::stringstream ss(due_date_str.c_str());
	ss >> std::get_time(&due_date, "%Y-%m-%d");
}

void Task::setStatus(Status newStatus) 
{
	status = newStatus; 
}

void Task::setDescription(const String& newDescription) 
{
	description = newDescription; 
}