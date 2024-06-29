#include "Task.h"
#include <sstream>
#include <iomanip>
#include "Utility.h"
#include <fstream>
#include "User.h"

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

void Task::save(std::ofstream& ofs) const
{
	ofs.write(reinterpret_cast<const char*>(&id), sizeof(id));

	int statusInt = static_cast<int>(status);
	ofs.write(reinterpret_cast<const char*>(&statusInt), sizeof(statusInt));

	ofs.write(reinterpret_cast<const char*>(&due_date), sizeof(due_date));

	size_t nameSize = name.getSize();
	ofs.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
	ofs.write(name.c_str(), nameSize + 1);

	size_t descriptionSize = description.getSize();
	ofs.write(reinterpret_cast<const char*>(&descriptionSize), sizeof(descriptionSize));
	ofs.write(description.c_str(), descriptionSize + 1);
}

void Task::load(std::ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*>(&id), sizeof(id));

	int statusInt;
	ifs.read(reinterpret_cast<char*>(&statusInt), sizeof(statusInt));
	status = static_cast<Status>(statusInt);

	ifs.read(reinterpret_cast<char*>(&due_date), sizeof(due_date));

	Utility::loadStringFromFile(ifs, name);
	Utility::loadStringFromFile(ifs, description);
}
