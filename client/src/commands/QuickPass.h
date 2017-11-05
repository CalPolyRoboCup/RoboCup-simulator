#ifndef QUICKPASS_H
#define QUICKPASS_H

#include "../Command.h"

#define QUICKPASS_VELOCITY_THRESHOLD 0.005f
#define QUICKPASS_MAXIMUM_DISTANCE 130
#define QUICKPASS_ANGLE_BIAS 4.25f
#define QUICKPASS_BALL_VElOCITY_THRESHOLD 0.01f

class QuickPass : public Command
{
public:
    QuickPass(Master* pMaster, Robot* pTargetRobot);

    virtual void start();

    virtual void update(double deltaTime);

    virtual bool isFinished();

    virtual void end();

private:
    Robot* m_pTargetRobot;

    QVector2D m_startPosition;
    QVector2D m_ballDirectionVector;

    float biasAngle(float incoming, float outgoing, float outgoingBias);
};

#endif // QUICKPASS_H
