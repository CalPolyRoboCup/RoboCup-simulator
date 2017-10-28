#ifndef SETKICKER_H
#define SETKICKER_H

#include "../Command.h"

class SetKicker : public Command
{
public:
    SetKicker(Master* pMaster, float speed);

    virtual void start();

    virtual bool isFinished();

private:
    float m_speed;
};

#endif // SETKICKER_H
