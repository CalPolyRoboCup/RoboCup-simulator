#ifndef AIMATROBOT_H
#define AIMATROBOT_H

#include "../Command.h"

/**
 * @brief The AimAtRobot @see Command is used for positioning the robot so the ball lies between this robot and the target robot
 */
class AimAtRobot : public Command
{
public:
    /**
     * @brief Initializes a new AimAtRobot instance
     * @param pMaster The Master instance the AimAtRobot Command is associated with
     * @param pTargetRobot The robot to aim at
     */
    AimAtRobot(Master* pMaster, Robot* pTargetRobot);

    virtual void update(double deltaTime);

    virtual bool isFinished();

private:
    Robot* m_pTargetRobot;
};

#endif // AIMATROBOT_H
