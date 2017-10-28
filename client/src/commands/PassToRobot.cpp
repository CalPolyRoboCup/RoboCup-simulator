#include "PassToRobot.h"
#include "AimAtRobot.h"
#include "PassBall.h"
#include "SetKicker.h"
#include "Delay.h"

PassToRobot::PassToRobot(Master* pMaster, Robot* pTargetRobot) :
    CommandSeries(pMaster)
{
    addCommand(new AimAtRobot(pMaster, pTargetRobot));
    addCommand(new PassBall(pMaster, pTargetRobot));
    addCommand(new SetKicker(pMaster, 3.0f));
    addCommand(new Delay(pMaster, 0.25f));
    addCommand(new SetKicker(pMaster, 0.0f));
}
