#ifndef PASSBALL_H
#define PASSBALL_H

#include "../Command.h"

#define PASS_VELOCITY_THRESHOLD 0.005f
#define PASS_TARGET_DISTANCE 90
#define PASS_MAXIMUM_DISTANCE 110

class PassBall : public Command
{
public:
    PassBall(Master* pMaster, Robot* pTargetRobot);

    virtual void update(double deltaTime);

    virtual bool isFinished();

    virtual void end();

private:
    Robot* m_pTargetRobot;
};

#endif // PASSBALL_H
