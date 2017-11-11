#include "QuickPass.h"
#include "OneTimerPass.h"
#include "PassToRobot.h".h"
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
    m_ballDirectionVector = QVector2D(std::cos(ballDirection), -std::sin(ballDirection));
    ballDirection = std::atan2(m_ballDirectionVector.y(), m_ballDirectionVector.x()) + M_PI;

    QVector2D ballPos = m_pMaster->getBall()->getPosition();
    QVector2D pointOfContact = MathHelper::getClosestPoint(ballPos, ballPos + m_ballDirectionVector, m_startPosition);

    float robotAngle = MathHelper::getLineAngle(pointOfContact, m_pTargetRobot->getPosition());
    ballDirection = MathHelper::adjustAngleValue(robotAngle, ballDirection);

    float targetAngle = MathHelper::biasAngle(ballDirection, robotAngle, QUICKPASS_ANGLE_BIAS / m_pMaster->getBall()->getSpeed());
    m_pRobot->setTargetOrientation(targetAngle);

    QVector2D targetPos = pointOfContact - QVector2D(std::cos(targetAngle), std::sin(targetAngle)) * 90.0f;
    QVector2D robotPos = m_pRobot->getPosition();

    float targetDirection = -MathHelper::getLineAngle(robotPos, targetPos);
    m_pRobot->setTargetDirection(targetDirection);
    m_pRobot->setTargetSpeed(std::min((float)(robotPos - targetPos).length() * QUICKPASS_VELOCITY_THRESHOLD, 1.0f));
}

bool QuickPass::isFinished()
{
    return (m_pMaster->getBall()->getPosition() - m_pRobot->getPosition()).length() < QUICKPASS_MAXIMUM_DISTANCE ||
            (m_pMaster->getBall()->getPosition() + m_ballDirectionVector * 0.001 - m_pRobot->getPosition()).length() >
            (m_pMaster->getBall()->getPosition() - m_pRobot->getPosition()).length() ||
            (m_pMaster->getBall()->getSpeed() < QUICKPASS_BALL_VElOCITY_THRESHOLD);
}

void QuickPass::end()
{
    m_pRobot->setKickerSpeed(4);
}
