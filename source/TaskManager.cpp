#include "TaskManager.h"
#include <iostream>
#include <fstream>
#include "TaskStatus.h"
#include <iomanip>
#include "Utility.h"


TaskManager::TaskManager() : loggedInUser(nullptr)
{
	//loadUsersData();
	//loadCollaborationsData();
}

void TaskManager::registerUser(const String& username, const String& password)
{
	if (loggedInUser)
	{
		std::cout << "You are already logged in and you can not register until you log out!";
	}
	unsigned usersSize = users.getSize();
	for (size_t i = 0; i < usersSize; i++)
	{
		if (users[i].getUsername() == username)
		{
			std::cout << "User already exists.\n";
			return;
		}
	}

	User newUser(username, password);
	users.push_back(newUser);

	std::cout << "Registered successfully!\n";
}

void TaskManager::loginUser(const String& username, const String& password)
{
	if (loggedInUser)
	{
		std::cout << "You are already logged in!\n";
		return;
	}
	unsigned usersSize = users.getSize();
	for (size_t i = 0; i < usersSize; i++)
	{
		if (users[i].getUsername() == username && users[i].checkPassword(password))
		{
			loggedInUser = &users[i];
			loggedInUser->getDashboardInstance().update(loggedInUser->getTasks());
			std::cout << "Welcome back, " << username << "!\n";
			return;
		}
	}
	std::cout << "Invalid username or password.\n";
}

void TaskManager::addTask(const String& name, const String& due_date, const String& description)
{
	if (loggedInUser)
	{
		const Vector<Polymorphic_Ptr<Task>>& userTasks = loggedInUser->getTasks();
		unsigned userTasksSize = userTasks.getSize();
		std::tm formatedDate = {};
		Utility::formatTmTypeDate(due_date, formatedDate);
		for (size_t i = 0; i < userTasksSize; i++)
		{
			std::tm dueDate = userTasks[i]->getDueDate();
			if (userTasks[i]->getName() == name &&
				!std::difftime(std::mktime(&dueDate), std::mktime(&formatedDate)))
			{
				std::cout << "A task with the same name and the same due date already exists!\n";
				return;
			}
		}
		loggedInUser->addTask(new PersonalTask(name, description, due_date));
		std::cout << "Task added successfully!\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::updateTaskName(unsigned id, const String& name)
{
	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			if (loggedInUser->getTasks()[i]->getId() == id)
			{
				loggedInUser->getTasksInstance()[i]->setName(name);
				std::cout << "Task name updated successfully.\n";
				return;
			}
		}
		std::cout << "Task not found.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::startTask(unsigned id)
{
	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			if (loggedInUser->getTasks()[i]->getId() == id)
			{
				loggedInUser->getTasksInstance()[i]->setStatus(Status::IN_PROCESS);
				std::cout << "Task started.\n";
				return;
			}
		}
		std::cout << "Task not found.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::updateTaskDescription(unsigned id, const String& description)
{
	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			if (loggedInUser->getTasks()[i]->getId() == id)
			{
				loggedInUser->getTasksInstance()[i]->setDescription(description);
				std::cout << "Task description updated successfully.\n";
				return;
			}
		}
		std::cout << "Task not found.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::addTaskToDashboard(unsigned id)
{
	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			if (loggedInUser->getTasks()[i]->getId() == id && loggedInUser->getTasks()[i]->getStatus() != Status::OVERDUE)
			{
				loggedInUser->getDashboardInstance().addTask(id);
				std::cout << "Task added to dashboard successfully!\n";
				return;
			}
		}
		std::cout << "Task not found.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::removeTaskFromDashboard(unsigned id)
{
	if (loggedInUser)
	{
		loggedInUser->getDashboardInstance().removeTask(id);
		std::cout << "Task removed from dashboard successfully!\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::deleteTask(unsigned id)
{
	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			if (loggedInUser->getTasks()[i]->getId() == id)
			{
				loggedInUser->getTasksInstance().remove(i);
				std::cout << "Task deleted successfully!\n";
				return;
			}
		}
		std::cout << "Task not found.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::getTask(const String& name)
{
	if (loggedInUser)
	{
		Polymorphic_Ptr<Task> foundTask = nullptr;
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			if (loggedInUser->getTasks()[i]->getName() == name)
			{
				if (!foundTask || loggedInUser->getTasks()[i]->getId() < foundTask->getId())
				{
					foundTask = loggedInUser->getTasks()[i];
				}
			}
		}
		if (foundTask)
		{
			foundTask->printTask();
		}
		else
		{
			std::cout << "Task not found.\n";
		}
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::getTask(unsigned id)
{
	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			if (loggedInUser->getTasks()[i]->getId() == id)
			{
				loggedInUser->getTasks()[i]->printTask();
				return;
			}
		}
		std::cout << "Task not found.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::listTasks(const String& date)
{
	std::tm formatedDate = {};
	Utility::formatTmTypeDate(date, formatedDate);

	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			std::tm dueDate = loggedInUser->getTasks()[i]->getDueDate();
			if (!std::difftime(std::mktime(&dueDate), std::mktime(&formatedDate)))
			{
				loggedInUser->getTasks()[i]->printTask();
			}
		}
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::listTasks()
{
	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			loggedInUser->getTasks()[i]->printTask();
		}
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::listCompletedTasks()
{
	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			if (loggedInUser->getTasks()[i]->getStatus() == Status::DONE)
			{
				loggedInUser->getTasks()[i]->printTask();
			}
		}
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::listDashboard()
{
	if (loggedInUser)
	{
		loggedInUser->getDashboard().listTasks(loggedInUser->getTasks());
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::finishTask(unsigned id)
{
	if (loggedInUser)
	{
		unsigned tasksSize = loggedInUser->getTasks().getSize();
		for (size_t i = 0; i < tasksSize; i++)
		{
			if (loggedInUser->getTasks()[i]->getId() == id)
			{
				loggedInUser->getTasksInstance()[i]->setStatus(Status::DONE);
				std::cout << "Task finished.\n";
				return;
			}
		}
		std::cout << "Task not found.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::logout()
{
	if (loggedInUser)
	{
		loggedInUser = nullptr;
		std::cout << "User logged out successfully.\n";
	}
	else
	{
		std::cout << "No user is currently logged in.\n";
	}
}

void TaskManager::exit()
{
	//saveUsersData();
	//saveCollaborationsData();
	std::cout << "Exited successfully!\n";
}

void TaskManager::addCollaboration(const String& name)
{
	if (loggedInUser)
	{
		Collaboration newCollaboration(name, loggedInUser);
		collaborations.push_back(newCollaboration);
		std::cout << "Collaboration added successfully!\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::deleteCollaboration(const String& name)
{
	if (loggedInUser)
	{
		unsigned collabsSize = collaborations.getSize();
		for (size_t i = 0; i < collabsSize; i++)
		{
			if (collaborations[i].getName() == name && collaborations[i].getCreator() == loggedInUser)
			{
				Vector<CollaborationTask*> collabTasks = collaborations[i].getTasksCollab();
				unsigned collabTasksSize = collabTasks.getSize();
				for (size_t j = 0; j < collabTasksSize; j++)
				{
					collaborations[i].removeCollabTasksFromUsers(collabTasks[j]);
				}
				collaborations.remove(i);
				std::cout << "Collaboration deleted successfully!\n";
				return;
			}
		}
		std::cout << "Collaboration not found or user not authorized.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::listCollaborations()
{
	if (loggedInUser)
	{
		unsigned collabsSize = collaborations.getSize();
		for (size_t i = 0; i < collabsSize; i++)
		{
			if (collaborations[i].getCreator() == loggedInUser ||
				collaborations[i].isUserInCollaboration(loggedInUser->getUsername()))
			{
				std::cout << "Collaboration: " << collaborations[i].getName() << "\n";
			}
		}
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::addUserToCollaboration(const String& collaborationName, const String& username)
{
	if (loggedInUser)
	{
		unsigned collabsSize = collaborations.getSize();
		unsigned usersSize = users.getSize();
		for (size_t i = 0; i < collabsSize; i++)
		{
			if (collaborations[i].getName() == collaborationName && collaborations[i].getCreator() == loggedInUser)
			{
				for (size_t j = 0; j < usersSize; j++)
				{
					if (users[j].getUsername() == username)
					{
						collaborations[i].addUser(&users[j]);
						std::cout << "User added successfully to collaboration!\n";
						return;
					}
				}
				std::cout << "User not found.\n";
				return;
			}
		}
		std::cout << "Collaboration not found or user not authorized.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::assignTaskToCollaboration(const String& collaborationName, const String& username, const String& taskName,
	const String& due_date, const String& description)
{
	if (loggedInUser)
	{
		unsigned collabsSize = collaborations.getSize();
		unsigned usersSize = users.getSize();
		for (size_t i = 0; i < collabsSize; i++)
		{
			if (collaborations[i].getName() == collaborationName && collaborations[i].getCreator() == loggedInUser)
			{
				if (!collaborations[i].isUserInCollaboration(username) && collaborations[i].getCreator()->getUsername() != username)
				{
					std::cout << "The user " << username << " is not part of this collaboration.\n";
					return;
				}
				Vector<CollaborationTask*>& collabTasks = collaborations[i].getTasksCollab();
				unsigned collabTasksSize = collabTasks.getSize();
				std::tm formatedDate = {};
				Utility::formatTmTypeDate(due_date, formatedDate);
				for (size_t k = 0; k < collabTasksSize; k++)
				{
					std::tm dueDate = collabTasks[k]->getDueDate();
					if (collabTasks[k]->getName() == taskName &&
						!std::difftime(std::mktime(&dueDate), std::mktime(&formatedDate)))
					{
						std::cout << "A task with the same name and the same due date already exists!\n";
						return;
					}
				}
				for (size_t j = 0; j < usersSize; j++)
				{
					if (users[j].getUsername() == username)
					{
						CollaborationTask* newTask = new CollaborationTask(taskName, description, users[j], due_date);
						collaborations[i].addTask(newTask);
						users[j].getTasksInstance().push_back(newTask);
						std::cout << "Task assigned successfully to collaboration!\n";
						return;
					}
				}
				std::cout << "User not found.\n";
				return;
			}
		}
		std::cout << "Collaboration not found or user not authorized.\n";
		return;
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::listCollaborationTasks(const String& collaborationName)
{
	if (loggedInUser)
	{
		unsigned collabsSize = collaborations.getSize();
		for (size_t i = 0; i < collabsSize; i++)
		{
			if (collaborations[i].getName() == collaborationName)
			{
				if (collaborations[i].getCreator() == loggedInUser ||
					collaborations[i].isUserInCollaboration(loggedInUser->getUsername()))
				{
					unsigned taskInCollabSize = collaborations[i].getTasksCollab().getSize();
					for (size_t j = 0; j < taskInCollabSize; j++)
					{
						collaborations[i].getTasksCollab()[j]->printTask();
					}
					return;
				}
				std::cout << "User not authorized.\n";
				return;
			}
		}
		std::cout << "Collaboration not found.\n";
	}
	else
	{
		std::cout << "User not logged in.\n";
	}
}

void TaskManager::saveUsersData()
{
	std::ofstream outFile("users.dat", std::ios::binary);

	if (!outFile.is_open()) {
		throw std::runtime_error("Failed to open file for saving");
	}

	size_t userCount = users.getSize();
	outFile.write(reinterpret_cast<const char*>(&userCount), sizeof(userCount));
	for (size_t i = 0; i < userCount; i++)
	{
		users[i].save(outFile);
	}
}

void TaskManager::loadUsersData()
{
	std::ifstream inFile("users.dat", std::ios::binary);

	if (!inFile.is_open()) {
		throw std::runtime_error("Failed to open file for loading");
	}

	size_t userCount;
	inFile.read(reinterpret_cast<char*>(&userCount), sizeof(userCount));

	for (size_t i = 0; i < userCount; i++)
	{
		User user;
		user.load(inFile);
		users.push_back(user);
	}
}
