#ifndef SETKICKER_H
#define SETKICKER_H

#include "../Command.h"

class SetKicker : public Command
{
public:
    /**
     * @brief Creates a new SetKicker instance
     * @param pMaster The master instance associated with the SetKicker command
     * @param speed The speed to set the kicker to
     */
    SetKicker(Master* pMaster, float speed);

    virtual void start();

    virtual bool isFinished();

private:
    float m_speed;
};

#endif // SETKICKER_H
