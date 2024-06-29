#pragma once
#include "Task.h"
#include "User.h"

class CollaborationTask: public Task
{
private:
	String assigneeUsername;

public :
    CollaborationTask();
    CollaborationTask(const String& name, const String& description, const String& assigneeUsername, const String& due_date_str = "");

    const String& getAssignee() const;
    void setAssignee(const String& assigneeUsername);
    void printTask() const override;

    void save(std::ofstream& ofs) const override;
    void load(std::ifstream& ifs) override;

    Task* clone() const override;
};

