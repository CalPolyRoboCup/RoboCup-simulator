#ifndef PASSTOROBOT_H
#define PASSTOROBOT_H

#include "../CommandSeries.h"

class PassToRobot : public CommandSeries
{
public:
    /**
     * @brief Initializes a new PassToRobot command
     * @param pMaster The Master instance the PassToRobot Command is associated with
     * @param pTargetRobot The robot to pass the ball to
     */
    PassToRobot(Master* pMaster, Robot* pTargetRobot);
};

#endif // PASSTOROBOT_H
