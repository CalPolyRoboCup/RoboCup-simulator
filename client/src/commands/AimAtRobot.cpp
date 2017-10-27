#include "AimAtRobot.h"
#include "../MathHelper.h"
#include <cmath>
#include <iostream>

AimAtRobot::AimAtRobot(Master* pMaster, Robot* pTargetRobot) :
    Command(pMaster)
{
    m_pTargetRobot = pTargetRobot;
}

void AimAtRobot::update(double deltaTime)
{
    QVector2D robotPos = m_pRobot->getPosition();
    QVector2D ballPos = m_pMaster->getBall()->getPosition();

    float targetOrientation = std::atan2(ballPos.y() - robotPos.y(), ballPos.x() - robotPos.x());
    m_pRobot->setTargetOrientation(targetOrientation);

    QVector2D targetRobotPos = m_pTargetRobot->getPosition();
    QVector2D targetPos = ballPos + (ballPos - targetRobotPos).normalized() * 240;

    m_pRobot->setTargetSpeed(std::min((robotPos - targetPos).length() * 0.005, 1.0));

    if ((robotPos - ballPos).length() < (robotPos - targetPos).length())
        targetPos = ballPos - (ballPos - MathHelper::getClosestPoint(robotPos, targetPos, ballPos)).normalized() * 240;

    float targetDirection = -std::atan2(targetPos.y() - robotPos.y(), targetPos.x() - robotPos.x());
    m_pRobot->setTargetDirection(targetDirection);
}

bool AimAtRobot::isFinished()
{
    return false;
}
