#include "PassBall.h"
#include "../MathHelper.h"
#include <cmath>
#include <iostream>

PassBall::PassBall(Master* pMaster, Robot* pTargetRobot) :
    Command(pMaster),
    m_targetOrientation(0.0f),
    m_targetDirection(0.0f)
{
    m_pTargetRobot = pTargetRobot;
}

void PassBall::update(double deltaTime)
{
    QVector2D robotPos = m_pRobot->getPosition();
    QVector2D targetRobotPos = m_pTargetRobot->getPosition();

    m_targetOrientation = MathHelper::getLineAngle(robotPos, targetRobotPos);
    m_pRobot->setTargetOrientation(m_targetOrientation);

    QVector2D ballPos = m_pMaster->getBall()->getPosition();

    m_pRobot->setTargetSpeed(std::min(std::max((float)((robotPos - ballPos).length() - PASS_TARGET_DISTANCE) * PASS_VELOCITY_THRESHOLD, 0.0f), 1.0f));

    m_targetDirection = -MathHelper::getLineAngle(robotPos, ballPos);

    m_pRobot->setTargetDirection(m_targetDirection);
}

bool PassBall::isFinished()
{
    return (m_pRobot->getPosition() - m_pMaster->getBall()->getPosition()).length() < PASS_MAXIMUM_DISTANCE ||
            std::abs(std::abs(m_targetOrientation) - std::abs(m_targetDirection)) > PASS_MAXIMUM_ANGLE;
}

void PassBall::end()
{
    m_pRobot->setTargetSpeed(0.0f);
}
