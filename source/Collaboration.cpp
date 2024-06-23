#include "Collaboration.h"
#include "Vector.hpp"


int Collaboration::nextId = 1;

Collaboration::Collaboration(const String& name, User* creator)
	: id(nextId++), name(name), creator(creator)
{
}

const String& Collaboration::getName() const
{
	return name;
}

unsigned Collaboration::getId() const
{
	return id;
}

User* Collaboration::getCreator() const
{
	return creator;
}

void Collaboration::addUser(User* user)
{
	workingGroup.push_back(user);
}

void Collaboration::addTask(CollaborationTask* task)
{
	if (!task)
	{
		throw std::invalid_argument("Nullptr has given!");
	}
	collabTasks.push_back(task);
}

Vector<CollaborationTask*>& Collaboration::getTasksCollab() 
{
	return collabTasks;
}

bool Collaboration::isUserInCollaboration(const String& username) const
{
	unsigned workingGroupSize = workingGroup.getSize();
	for (size_t i = 0; i < workingGroupSize; i++)
	{
		if (workingGroup[i]->getUsername() == username) 
		{
			return true;
		}
	}

	return false;
}

void Collaboration::removeTaskFromUser(Task* removeTask, User* user)
{
	if (!removeTask || !user)
	{
		throw std::invalid_argument("Nullptr has given!");
	}

	Vector<Polymorphic_Ptr<Task>>& userTasks = user->getTasksInstance();
	unsigned userTasksSize = userTasks.getSize();
	for (size_t j = 0; j < userTasksSize; j++)
	{
		if (userTasks[j]->getId() == removeTask->getId())
		{
			userTasks.remove(j);
			Dashboard& userDashboard = user->getDashboardInstance();
			userDashboard.removeTask(removeTask->getId());
			return;
		}
	}
}

void Collaboration::removeCollabTasksFromUsers(Task* removeTask)
{
	if (!removeTask)
	{
		throw std::invalid_argument("Nullptr has given!");
	}

	unsigned workingGroupSize = workingGroup.getSize();
	for (size_t i = 0; i < workingGroupSize; i++)
	{
		removeTaskFromUser(removeTask, workingGroup[i]);
	}

	removeTaskFromUser(removeTask, creator);
}
