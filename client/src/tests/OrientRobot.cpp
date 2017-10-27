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

    m_pRobot->setTargetOrientation(m_pRobot->getDirection());
}
