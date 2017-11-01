#ifndef PASSBALL_H
#define PASSBALL_H

#include "../Command.h"

#define PASS_VELOCITY_THRESHOLD 0.005f
#define PASS_TARGET_DISTANCE 90
#define PASS_MAXIMUM_DISTANCE 110
#define PASS_MAXIMUM_ANGLE M_PI*0.25f

class PassBall : public Command
{
public:
    /**
     * @brief Creates a new PassBall instance
     * @param pMaster The Master instance associated with the command
     * @param pTargetRobot The @see Robot to pass the ball to
     */
    PassBall(Master* pMaster, Robot* pTargetRobot);

    virtual void update(double deltaTime);

    virtual bool isFinished();

    virtual void end();

private:
    Robot* m_pTargetRobot;

    float m_targetOrientation;
    float m_targetDirection;
};

#endif // PASSBALL_H
