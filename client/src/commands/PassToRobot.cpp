#include "PassToRobot.h"
#include "AimAtRobot.h"

PassToRobot::PassToRobot(Master* pMaster, Robot* pTargetRobot) :
    CommandSeries(pMaster)
{
    addCommand(new AimAtRobot(pMaster, pTargetRobot));
}
