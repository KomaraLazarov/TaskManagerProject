#pragma once
#include <ctime>
#include "String.h"
#include "TaskStatus.h"

class Task
{
protected:
    std::tm due_date;
    String name;
    String description;
    Status status = ON_HOLD;
    unsigned id;

    static int nextId;

public:
    Task() = default;
    Task(const String& name, const String& description, const String& due_date_str = "");

    unsigned getId() const;
    const String& getName() const;
    const std::tm& getDueDate() const;
    const Status& getStatus() const;
    
    void setName(const String& newName);
    void setDueDate(const String& due_date_str);
    void setStatus(Status newStatus);
    void setDescription(const String& newDescription);

    virtual Task* clone() const = 0;
    virtual void printTask() const = 0;

    virtual ~Task() = default;
};