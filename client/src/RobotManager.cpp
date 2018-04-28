#include "RobotManager.h"
#include "Team.h"

RobotManager::RobotManager()
{

}

Robot* RobotManager::get(int index)
{
    std::map<int, Robot*>::iterator item = m_robots.find(index);

    if (item != m_robots.end())
        return item->second;

    Robot* robot = new Robot(YELLOW, index);
    m_robots.insert(std::pair<int, Robot*>(index, robot));
    return robot;
}
