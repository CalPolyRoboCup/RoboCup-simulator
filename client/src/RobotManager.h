#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <map>
#include "Robot.h"

class RobotManager
{
public:
    RobotManager();
    ~RobotManager();

    Robot* get(int index);

private:
    std::map<int, Robot*> m_robots;
};

#endif // ROBOTMANAGER_H
