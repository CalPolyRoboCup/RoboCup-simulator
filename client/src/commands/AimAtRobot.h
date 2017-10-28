#ifndef AIMATROBOT_H
#define AIMATROBOT_H

#include "../Command.h"

#define AIM_ORBIT_RADIUS 240.0f
#define AIM_VELOCITY_THRESHOLD 0.005f
#define AIM_MAXIMUM_DISTANCE 5.0f

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

    virtual void start();

    virtual void update(double deltaTime);

    virtual bool isFinished();

    virtual void end();

private:
    Robot* m_pTargetRobot;

    QVector2D m_targetPos;
};

#endif // AIMATROBOT_H
