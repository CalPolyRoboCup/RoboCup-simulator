#include "QuickPass.h"
#include "OneTimerPass.h"
#include "../MathHelper.h"
#include <cmath>
#include <iostream>

QuickPass::QuickPass(Master* pMaster, Robot* pTargetRobot) :
    Command(pMaster)
{
    m_pTargetRobot = pTargetRobot;
}

void QuickPass::start()
{
    m_startPosition = m_pRobot->getPosition();
}

void QuickPass::update(double deltaTime)
{
    float ballDirection = m_pMaster->getBall()->getDirection();
    QVector2D ballVector = QVector2D(std::cos(ballDirection), -std::sin(ballDirection));
    ballDirection = std::atan2(ballVector.y(), ballVector.x()) + M_PI;

    QVector2D ballPos = m_pMaster->getBall()->getPosition();
    QVector2D pointOfContact = MathHelper::getClosestPoint(ballPos, ballPos + ballVector, m_startPosition);

    float robotAngle = MathHelper::getLineAngle(pointOfContact, m_pTargetRobot->getPosition());

    while (robotAngle < 0)
        robotAngle += M_PI * 2;

    while (robotAngle - ballDirection > M_PI)
        ballDirection += M_PI * 2;

    float targetAngle = (robotAngle * 3 + ballDirection) * 0.25;
    m_pRobot->setTargetOrientation(targetAngle);

    QVector2D targetPos = pointOfContact - QVector2D(std::cos(targetAngle), std::sin(targetAngle)) * 90.0f;
    QVector2D robotPos = m_pRobot->getPosition();

    float targetDirection = -MathHelper::getLineAngle(robotPos, targetPos);
    m_pRobot->setTargetDirection(targetDirection);
    m_pRobot->setTargetSpeed(std::min((float)(robotPos - targetPos).length() * QUICKPASS_VELOCITY_THRESHOLD, 1.0f));
}

bool QuickPass::isFinished()
{
    return (m_pMaster->getBall()->getPosition() - m_pRobot->getPosition()).length() < QUICKPASS_MAXIMUM_DISTANCE;
}

void QuickPass::end()
{
    m_pRobot->setKickerSpeed(4);
    m_pMaster->getTeamBot((m_pRobot->getId() + 1) % 6)->runCommmand(new OneTimerPass(m_pMaster, m_pMaster->getTeamBot((m_pRobot->getId() + 2) % 6)));
}
