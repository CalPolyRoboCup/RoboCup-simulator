#include "GetOpen.h"
#include <cmath>

GetOpen::GetOpen(Master* pMaster) :
    Command(pMaster)
{
}

void GetOpen::update(double deltaTime)
{
    QVector2D robotPos = m_pRobot->getPosition();
    QVector2D ballPos = m_pMaster->getBall()->getPosition();

    float targetOrientation = std::atan2(ballPos.y() - robotPos.y(), ballPos.x() - robotPos.x());
    m_pRobot->setTargetOrientation(targetOrientation);
}

bool GetOpen::isFinished()
{
    return false;
}
