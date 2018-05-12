#include "RobotManager.h"
#include <QPainter>
#include <qmath.h>
#include "Team.h"

RobotManager::RobotManager(Team team, QPixmap* pixmap) : m_team(team), m_pixmap(pixmap), m_numRobots(0)
{
}

RobotManager::~RobotManager()
{
}

void RobotManager::updateStats(double deltaTime)
{
    for (std::map<int, Robot*>::iterator it = m_robots.begin(); it != m_robots.end(); it++)
        it->second->updateStats(deltaTime);
}

void RobotManager::updateCommand(double deltaTime)
{
    for (std::map<int, Robot*>::iterator it = m_robots.begin(); it != m_robots.end(); it++)
        it->second->updateCommand(deltaTime);
}

void RobotManager::paint(Master *pMaster, QPainter& painter)
{
    for (std::map<int, Robot*>::iterator it = m_robots.begin(); it != m_robots.end(); it++)
    {
        Robot* robot = it->second;
        QPoint robotPoint = pMaster->convertToScreenPoint(robot->getPosition());

        painter.translate(robotPoint.x(), robotPoint.y());
        painter.rotate(-robot->getOrientation() * (180.0 / M_PI));

        painter.drawPixmap(-9, -9, 18, 18, *m_pixmap);

        painter.resetTransform();
    }
}

void RobotManager::paintIDs(Master *pMaster, QPainter& painter)
{
    int i = 0;
    for (std::map<int, Robot*>::iterator it = m_robots.begin(); it != m_robots.end(); it++)
    {
        Robot* robot = it->second;
        QPoint robotPoint = pMaster->convertToScreenPoint(robot->getPosition());
        painter.drawText(robotPoint.x() + 9, robotPoint.y() - 9, QString::number(i));
        i++;
    }
}

Robot* RobotManager::get(int index)
{
    std::map<int, Robot*>::iterator item = m_robots.find(index);

    if (item != m_robots.end())
        return item->second;

    Robot* robot = new Robot(m_team, index);
    m_robots.insert(std::pair<int, Robot*>(index, robot));
    m_numRobots++;

    return robot;
}
