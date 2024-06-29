#pragma once
#include "String.h"
#include "Task.h"

class PersonalTask : public Task
{
public:
	PersonalTask();
	PersonalTask(const String& name, const String& description, const String& due_date_str = "");

	void printTask() const override;

	Task* clone() const override;

	void save(std::ofstream& ofs) const override;
	void load(std::ifstream& ifs) override;
};

