#include "PassBall.h"
#include <cmath>
#include <iostream>

PassBall::PassBall(Master* pMaster, Robot* pTargetRobot) :
    Command(pMaster)
{
    m_pTargetRobot = pTargetRobot;
}

void PassBall::update(double deltaTime)
{
    QVector2D robotPos = m_pRobot->getPosition();
    QVector2D targetRobotPos = m_pTargetRobot->getPosition();

    float targetOrientation = std::atan2(targetRobotPos.y() - robotPos.y(), targetRobotPos.x() - robotPos.x());
    m_pRobot->setTargetOrientation(targetOrientation);

    QVector2D ballPos = m_pMaster->getBall()->getPosition();

    m_pRobot->setTargetSpeed(std::min(std::max((float)((robotPos - ballPos).length() - PASS_TARGET_DISTANCE) * PASS_VELOCITY_THRESHOLD, 0.0f), 1.0f));

    float targetDirection = -std::atan2(ballPos.y() - robotPos.y(), ballPos.x() - robotPos.x());
    m_pRobot->setTargetDirection(targetDirection);
}

bool PassBall::isFinished()
{
    return (m_pRobot->getPosition() - m_pMaster->getBall()->getPosition()).length() < PASS_MAXIMUM_DISTANCE;
}

void PassBall::end()
{
    m_pRobot->setTargetSpeed(0.0f);
}
