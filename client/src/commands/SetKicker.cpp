#include "SetKicker.h"

SetKicker::SetKicker(Master* pMaster, float speed):
    Command(pMaster),
    m_speed(speed)
{
}

void SetKicker::start()
{
    m_pRobot->setKickerSpeed(m_speed);
}

bool SetKicker::isFinished()
{
    return true;
}

void SetKicker::end()
{
    destroy();
}
