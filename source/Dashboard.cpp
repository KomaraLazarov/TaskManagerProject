#include "Dashboard.h"
#include "Utility.h"

void Dashboard::addTask(unsigned taskId)
{
	for (size_t i = 0; i < taskIds.getSize(); i++)
	{
		if (taskIds[i] == taskId)
		{
			std::cout << "Task already in dashboard.\n";
			return;
		}
	}

	taskIds.push_back(taskId);
}

void Dashboard::removeTask(unsigned taskId)
{
	for (size_t i = 0; i < taskIds.getSize(); i++)
	{
		if (taskIds[i] == taskId)
		{
			taskIds.remove(i);
			return;
		}
	}

	std::cout << "Task not found in dashboard.\n";
}

void Dashboard::update(const Vector<Polymorphic_Ptr<Task>>& allTasks)
{
	std::time_t now;
	std::time(&now);
#pragma warning(suppress : 4996)
	std::tm* currentTime = std::localtime(&now);

	size_t tasksSize = allTasks.getSize();

	size_t idsSize = taskIds.getSize();
	for (size_t i = 0; i < tasksSize; i++)
	{
		for (size_t j = 0; j < idsSize; j++)
		{
			if (allTasks[i]->getId() == taskIds[j])
			{
				Polymorphic_Ptr<Task> task = allTasks[i];
				if (Utility::pastDate(currentTime, &task->getDueDate())
					&& task->getStatus() != Status::DONE)
				{
					task->setStatus(Status::OVERDUE);
					taskIds.remove(j);
				}
				break;
			}
		}
	}
	
	for (size_t i = 0; i < tasksSize; i++)
	{
		Polymorphic_Ptr<Task> task = allTasks[i];
		std::tm dueDate = task->getDueDate();
		if (task->getStatus() != Status::DONE && task->getStatus() != Status::OVERDUE && 
			dueDate.tm_year == currentTime->tm_year && dueDate.tm_mon == currentTime->tm_mon && dueDate.tm_mday == currentTime->tm_mday)
		{
			addTask(task->getId());
		}
	}
}

void Dashboard::listTasks(const Vector<Polymorphic_Ptr<Task>>& allTasks) const
{
	for (size_t i = 0; i < taskIds.getSize(); i++)
	{
		for (size_t j = 0; j < allTasks.getSize(); j++)
		{
			if (allTasks[j]->getId() == taskIds[i])
			{
				Polymorphic_Ptr<Task> task = allTasks[j];
				task->printTask();
				break;
			}
		}
	}
}