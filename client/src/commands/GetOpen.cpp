#include "GetOpen.h"
#include <cmath>

GetOpen::GetOpen(Master* pMaster) :
    Command(pMaster)
{
}

void GetOpen::start()
{
    if (m_startPosition.isNull())
        m_startPosition = m_pRobot->getPosition();
}

void GetOpen::update(double deltaTime)
{
    QVector2D robotPos = m_pRobot->getPosition();

    m_pRobot->setTargetSpeed(std::min((float)(robotPos - m_startPosition).length() * GETOPEN_VELOCITY_THRESHOLD, 1.0f));

    float targetDirection = -std::atan2(m_startPosition.y() - robotPos.y(), m_startPosition.x() - robotPos.x());
    m_pRobot->setTargetDirection(targetDirection);

    QVector2D ballPos = m_pMaster->getBall()->getPosition();

    float targetOrientation = std::atan2(ballPos.y() - robotPos.y(), ballPos.x() - robotPos.x());
    m_pRobot->setTargetOrientation(targetOrientation);
}

bool GetOpen::isFinished()
{
    return false;
}
