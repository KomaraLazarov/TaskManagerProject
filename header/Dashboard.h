#pragma once
#include "Vector.hpp"
#include "Task.h"
#include "PolimorphicPtr.hpp"

class Dashboard
{
private:
    Vector<int> taskIds;

public:
    void addTask(unsigned taskId);
    void removeTask(unsigned taskId);
    void update(const Vector<Polymorphic_Ptr<Task>>& allTasks);
    void listTasks(const Vector<Polymorphic_Ptr<Task>>& allTasks) const;
};

