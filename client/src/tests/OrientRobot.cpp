#include "OrientRobot.h"
#include <qmath.h>

OrientRobot::OrientRobot(Master* pMaster) :
    Command(pMaster)
{
}

void OrientRobot::update(double deltaTime)
{
    if (m_pRobot->getSpeed() < 0.1)
        return;

    float direction = m_pRobot->getDirection();
    if (direction < 0)
        direction += M_PI * 2;

    m_pRobot->setTargetOrientation(direction);
}
