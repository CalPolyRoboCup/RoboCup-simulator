#include "OneTimerPass.h"
#include "QuickPass.h"
#include "Delay.h"
#include "SetKicker.h"

OneTimerPass::OneTimerPass(Master* pMaster, Robot* pTargetRobot)
    : CommandSeries(pMaster)
{
    addCommand(new QuickPass(pMaster, pTargetRobot));
    addCommand(new Delay(pMaster, 0.05));
    addCommand(new SetKicker(pMaster, 0.0f));
}

void OneTimerPass::end()
{
    destroy();
}
