#include "Command.h"

Command::Command(Master *pMaster) :
    m_pMaster(pMaster)
{
    m_pRobot = 0;
}

bool Command::setRobot(Robot *pRobot)
{
    if (m_pRobot != 0)
        return false;

    m_pRobot = pRobot;
    return true;
}
