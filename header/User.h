#pragma once
#include "String.h"
#include "Vector.hpp"
#include "PolimorphicPtr.hpp"
#include "Task.h"
#include "Dashboard.h"

class User
{
private:
	String username;
	String password;
	Vector<Polymorphic_Ptr<Task>> tasks;
	Dashboard dashboard;

	void loadStringFromFile(std::ifstream& in, String& string);

public:
	User() = default;
	User(const String& username, const String& password);

	const String& getUsername() const;
	bool checkPassword(const String& password) const;

	void addTask(Task* task);

	const Vector<Polymorphic_Ptr<Task>>& getTasks();
	const Dashboard& getDashboard();

	Vector<Polymorphic_Ptr<Task>>& getTasksInstance();
	Dashboard& getDashboardInstance();

	void save(std::ofstream& out) const;
	void load(std::ifstream& in);

	void printTasks() const;
};

