#pragma once
#include "User.h"
#include "String.h"
#include "Vector.hpp"
#include "CollaborationTask.h"

class Collaboration
{
private:
	Vector<User*> workingGroup;
	Vector<CollaborationTask*> collabTasks;
	String name;
	User* creator;
	unsigned id;
	static int nextId;

	void removeTaskFromUser(Task* removeTask, User* user);

public:
	Collaboration() = default;
	Collaboration(const String& name, User* creator);

	const String& getName() const;
	unsigned getId() const;
	User* getCreator() const;
	void addUser(User* user);
	void addTask(CollaborationTask* task);
	Vector<CollaborationTask*>& getTasksCollab();
	bool isUserInCollaboration(const String& username) const;
	void removeCollabTasksFromUsers(Task* removeTask);
};
