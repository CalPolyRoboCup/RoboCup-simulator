#ifndef ROBOTMANAGER_H
#define ROBOTMANAGER_H

#include <map>
#include "Robot.h"
#include "Master.h"

class Robot;
class Master;

class RobotManager
{
public:
    RobotManager(Team team, QPixmap* pixmap);
    ~RobotManager();

    Robot* get(int index);
    void updateStats(double deltaTime);
    void updateCommand(double deltaTime);
    void paint(Master *pMaster, QPainter& painter);
    void paintIDs(Master *pMaster, QPainter& painter);

    int getNumRobots() const { return m_numRobots; }

private:
    Team m_team;
    QPixmap* m_pixmap;
    std::map<int, Robot*> m_robots;
    int m_numRobots;
};

#endif // ROBOTMANAGER_H
