#include "AimAtRobot.h"
#include "../MathHelper.h"
#include <cmath>
#include <iostream>

AimAtRobot::AimAtRobot(Master* pMaster, Robot* pTargetRobot) :
    Command(pMaster)
{
    m_pTargetRobot = pTargetRobot;
}

void AimAtRobot::start()
{
    m_targetPos = QVector2D(0, 0);
}

void AimAtRobot::update(double deltaTime)
{
    QVector2D robotPos = m_pRobot->getPosition();
    QVector2D ballPos = m_pMaster->getBall()->getPosition();

    float targetOrientation = MathHelper::getLineAngle(robotPos, ballPos);
    m_pRobot->setTargetOrientation(targetOrientation);

    QVector2D targetRobotPos = m_pTargetRobot->getPosition();
    m_targetPos = ballPos + (ballPos - targetRobotPos).normalized() * AIM_ORBIT_RADIUS;

    m_pRobot->setTargetSpeed(std::min((float)(robotPos - m_targetPos).length() * AIM_VELOCITY_THRESHOLD, 1.0f));

    QVector2D currentTargetPos = m_targetPos;

    if ((robotPos - currentTargetPos).length() > AIM_ORBIT_RADIUS)
        currentTargetPos = ballPos - (ballPos - MathHelper::getClosestPoint(robotPos, currentTargetPos, ballPos)).normalized() * AIM_ORBIT_RADIUS;

    float targetDirection = -MathHelper::getLineAngle(robotPos, currentTargetPos);
    m_pRobot->setTargetDirection(targetDirection);
}

bool AimAtRobot::isFinished()
{
    return (m_pRobot->getPosition() - m_targetPos).length() < AIM_MAXIMUM_DISTANCE;
}

void AimAtRobot::end()
{
    m_pRobot->setTargetSpeed(0.0f);
}
