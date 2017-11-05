#include "OneTimerPass.h"
#include "QuickPass.h"
#include "Delay.h"
#include "SetKicker.h"

OneTimerPass::OneTimerPass(Master* pMaster, Robot* pTargetRobot)
    : CommandSeries(pMaster)
{
    m_pTargetRobot = pTargetRobot;
    addCommand(new QuickPass(pMaster, pTargetRobot));
    addCommand(new Delay(pMaster, 0.05));
    addCommand(new SetKicker(pMaster, 0.0f));
}

void OneTimerPass::end()
{
    m_pTargetRobot->runCommmand(new OneTimerPass(m_pMaster, m_pMaster->getTeamBot((m_pTargetRobot->getId() + 1) % 6)));
    destroy();
}
