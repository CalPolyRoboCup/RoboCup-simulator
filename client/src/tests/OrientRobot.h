#ifndef ORIENTROBOT_H
#define ORIENTROBOT_H

#include "../Command.h"

class OrientRobot : public Command
{
public:
    OrientRobot(Master* pMaster);

    virtual void update(double deltaTime);
};

#endif // ORIENTROBOT_H
