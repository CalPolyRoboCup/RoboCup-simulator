#ifndef DELAY_H
#define DELAY_H

#include "../Command.h"

class Delay : public Command
{
public:
    Delay(Master* pMaster, double seconds);

    virtual void start();

    virtual void update(double deltaTime);

    virtual bool isFinished();

    virtual void end();

private:
    double m_delayTime;
    double m_secondsPassed;
};

#endif // DELAY_H
