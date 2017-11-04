#include "GetOpen.h"
#include "../MathHelper.h"
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

    float targetDirection = -MathHelper::getLineAngle(robotPos, m_startPosition);
    m_pRobot->setTargetDirection(targetDirection);

    QVector2D ballPos = m_pMaster->getBall()->getPosition();

    float targetOrientation = MathHelper::getLineAngle(robotPos, ballPos);
    m_pRobot->setTargetOrientation(targetOrientation);
}

bool GetOpen::isFinished()
{
    return false;
}
