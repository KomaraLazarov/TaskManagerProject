#pragma once
#include "Task.h"
#include "User.h"

class CollaborationTask: public Task
{
private:
	User assignee;

public :
    CollaborationTask();
    CollaborationTask(const String& name, const String& description, const User& assignee, const String& due_date_str = "");

    User getAssignee() const;
    void setAssignee(const User& assignee);
    void printTask() const override;

    Task* clone() const override;
};

