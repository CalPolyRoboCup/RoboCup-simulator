#include "CatchBall.h"
#include "../MathHelper.h"
#include "PassToRobot.h"
#include <cmath>

CatchBall::CatchBall(Master* pMaster) :
    Command(pMaster)
{
}

void CatchBall::update(double deltaTime)
{
    float ballSpeed = m_pMaster->getBall()->getSpeed();
    QVector2D robotPos = m_pRobot->getPosition();
    QVector2D ballPos = m_pMaster->getBall()->getPosition();

    float ballDirection = m_pMaster->getBall()->getDirection();
    m_ballDirectionVector = QVector2D(std::cos(ballDirection), -std::sin(ballDirection));
    m_pRobot->setTargetOrientation(std::atan2(m_ballDirectionVector.y(), m_ballDirectionVector.x()) + M_PI);

    QVector2D targetPos = MathHelper::getClosestPoint(ballPos, ballPos + m_ballDirectionVector, robotPos);

    float targetDirection = -MathHelper::getLineAngle(robotPos, targetPos);

    m_pRobot->setTargetDirection(targetDirection);
    m_pRobot->setTargetSpeed(std::min((float)(robotPos - targetPos).length() * CATCH_VELOCITY_THRESHOLD, 1.0f));
}

bool CatchBall::isFinished()
{
    return (m_pMaster->getBall()->getSpeed() < CATCH_BALL_VElOCITY_THRESHOLD) ||
            (m_pRobot->getPosition() - m_pMaster->getBall()->getPosition()).length() < CATCH_MAXIMUM_DISTANCE ||
            (m_pMaster->getBall()->getPosition() + m_ballDirectionVector * 0.001 - m_pRobot->getPosition()).length() >
            (m_pMaster->getBall()->getPosition() - m_pRobot->getPosition()).length();
}

void CatchBall::end()
{
    // vvv This is just for testing
    m_pRobot->setTargetSpeed(0.0f);

    int nextIndex = (m_pRobot->getId() + 1) % m_pMaster->getNumTeamBots();
    m_pRobot->runCommmand(new PassToRobot(m_pMaster, m_pMaster->getTeamBot(nextIndex)));
    // ^^^

    destroy();
}
