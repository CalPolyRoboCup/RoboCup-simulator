#include "Delay.h"

Delay::Delay(Master* pMaster, double seconds) :
    Command(pMaster),
    m_delayTime(seconds)
{
}

void Delay::start()
{
    m_secondsPassed = 0;
}

void Delay::update(double deltaTime)
{
    m_secondsPassed += deltaTime;
}

bool Delay::isFinished()
{
    return m_secondsPassed >= m_delayTime;
}
