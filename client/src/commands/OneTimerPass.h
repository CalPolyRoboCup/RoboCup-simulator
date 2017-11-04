#ifndef ONETIMERPASS_H
#define ONETIMERPASS_H

#include "../CommandSeries.h"

class OneTimerPass : public CommandSeries
{
public:
    OneTimerPass(Master* pMaster, Robot* pTargetRobot);

    virtual void end();
};

#endif // ONETIMERPASS_H
