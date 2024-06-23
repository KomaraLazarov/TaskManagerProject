#include <iostream>
#include <iomanip>
#include "TaskManager.h"
#include "ConcreteCommand.h"
#include "Utility.h"

int main()
{
	TaskManager taskManager;
	String command;
	String username, password, name, description, collaborationName, due_date;
	unsigned id;

	while (true)
	{
		std::cout << "> ";
		std::cin >> command;

		if (command == "register")
		{
			std::cin >> username >> password;
			RegisterCommand registerCmd(&taskManager, username, password);
			registerCmd.execute();
		}
		else if (command == "login")
		{
			User user;

			std::cin >> username >> password;
			LoginCommand loginCmd(&taskManager, username, password);
			loginCmd.execute();
		}
		else if (command == "add-task")
		{
			char data[Utility::MAX_BUFF_LENGTH];
			std::cin >> name >> due_date;
			std::cin.ignore(1);
			std::cin.getline(data, Utility::MAX_BUFF_LENGTH);
			description = data;

			AddTaskCommand addTaskCmd(&taskManager, name, due_date, description);
			addTaskCmd.execute();
		}
		else if (command == "get-task")
		{
			char data[Utility::MAX_BUFF_LENGTH];
			std::cin.ignore(1);
			std::cin.getline(data, Utility::MAX_BUFF_LENGTH);


			if (Utility::isNumber(data))
			{
				id = Utility::convertStrToUnsigned(data);
				GetTaskByIdCommand getTaskByIdCmd(&taskManager, id);
				getTaskByIdCmd.execute();
			}
			else
			{
				name = data;
				GetTaskByNameCommand getTaskByNameCmd(&taskManager, name);
				getTaskByNameCmd.execute();
			}
		}
		else if (command == "update-task-name")
		{
			std::cin >> id >> name;
			UpdateTaskNameCommand updateTaskNameCmd(&taskManager, id, name);
			updateTaskNameCmd.execute();
		}
		else if (command == "update-task-description")
		{
			char data[Utility::MAX_BUFF_LENGTH];
			std::cin >> id;
			std::cin.ignore(1);
			std::cin.getline(data, Utility::MAX_BUFF_LENGTH);
			description = data;

			UpdateTaskDescriptionCommand updateTaskDescCmd(&taskManager, id, description);
			updateTaskDescCmd.execute();
		}
		else if (command == "start-task")
		{
			std::cin >> id;
			StartTaskCommand startTaskCmd(&taskManager, id);
			startTaskCmd.execute();
		}
		else if (command == "add-collaboration")
		{
			std::cin >> collaborationName;
			AddCollaborationCommand addCollabCmd(&taskManager, collaborationName);
			addCollabCmd.execute();
		}
		else if (command == "delete-collaboration")
		{
			std::cin >> collaborationName;
			DeleteCollaborationCommand deleteCollabCmd(&taskManager, collaborationName);
			deleteCollabCmd.execute();
		}
		else if (command == "add-user")
		{
			std::cin >> collaborationName >> username;
			AddUserToCollaborationCommand addUserCmd(&taskManager, collaborationName, username);
			addUserCmd.execute();
		}
		else if (command == "assign-task")
		{
			char data[Utility::MAX_BUFF_LENGTH];
			std::cin >> collaborationName >> username >> name >> due_date;
			std::cin.ignore(1);
			std::cin.getline(data, Utility::MAX_BUFF_LENGTH);
			description = data;
			AssignTaskToCollaborationCommand assignTaskCmd(&taskManager, collaborationName, username, name, due_date, description);
			assignTaskCmd.execute();
		}
		else if (command == "list-tasks")
		{
			if (std::cin.get() == '\n')
			{
				ListTasksCommand listTasksCmd(&taskManager);
				listTasksCmd.execute();
			}
			else
			{
				String arg;
				std::cin >> arg;

				if (Utility::isDate(arg))
				{
					ListTasksByDateCommand listTasksByDateCmd(&taskManager, arg);
					listTasksByDateCmd.execute();
				}
				else
				{
					ListTasksInCollaborationCommand listTasksInCollaborationCmd(&taskManager, arg);
					listTasksInCollaborationCmd.execute();
				}
			}
		}
		else if (command == "list-completed-tasks")
		{
			ListCompletedTasksCommand listCompletedTasksCmd(&taskManager);
			listCompletedTasksCmd.execute();
		}
		else if (command == "list-collaborations")
		{
			ListCollaborationsCommand listCollabsCmd(&taskManager);
			listCollabsCmd.execute();
		}
		else if (command == "add-task-to-dashboard")
		{
			std::cin >> id;
			AddTaskToDashboardCommand addTaskToDashboardCmd(&taskManager, id);
			addTaskToDashboardCmd.execute();
		}
		else if (command == "remove-task-from-dashboard")
		{
			std::cin >> id;
			RemoveTaskFromDashboardCommand removeTaskFromDashboardCmd(&taskManager, id);
			removeTaskFromDashboardCmd.execute();
		}
		else if (command == "list-dashboard")
		{
			ListDashboardCommand listDashboardCmd(&taskManager);
			listDashboardCmd.execute();
		}
		else if (command == "finish-task")
		{
			std::cin >> id;
			FinishTaskCommand finishTaskCmd(&taskManager, id);
			finishTaskCmd.execute();
		}
		else if (command == "delete-task")
		{
			std::cin >> id;
			DeleteTaskCommand deleteTaskCmd(&taskManager, id);
			deleteTaskCmd.execute();
		}
		else if (command == "logout")
		{
			LogoutCommand logoutCmd(&taskManager);
			logoutCmd.execute();
		}
		else if (command == "exit")
		{
			ExitCommand exitCmd(&taskManager);
			exitCmd.execute();
			break;
		}
		else
		{
			std::cout << "Invalid command!" << std::endl;
		}
	}

	return 0;
}