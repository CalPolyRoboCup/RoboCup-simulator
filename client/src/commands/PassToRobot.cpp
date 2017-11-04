#include "PassToRobot.h"
#include "AimAtRobot.h"
#include "PassBall.h"
#include "SetKicker.h"
#include "Delay.h"
#include "CatchBall.h"
#include "OneTimerPass.h"

PassToRobot::PassToRobot(Master* pMaster, Robot* pTargetRobot) :
    CommandSeries(pMaster)
{
    m_pTargetRobot = pTargetRobot;

    addCommand(new AimAtRobot(pMaster, pTargetRobot));
    addCommand(new PassBall(pMaster, pTargetRobot));
    addCommand(new SetKicker(pMaster, 4.0f));
    addCommand(new Delay(pMaster, 0.05f));
    addCommand(new SetKicker(pMaster, 0.0f));
}

void PassToRobot::end()
{
    m_pTargetRobot->runCommmand(new OneTimerPass(m_pMaster, m_pMaster->getTeamBot((m_pTargetRobot->getId() + 1) % 6))/*CatchBall(m_pMaster)*/);
    destroy();
}
