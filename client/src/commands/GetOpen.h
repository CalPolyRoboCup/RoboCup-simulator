#ifndef GETOPEN_H
#define GETOPEN_H

#include "../Command.h"

class GetOpen : public Command
{
public:
    /**
     * @brief Creates a new GetOpen instance
     * @param pMaster The Master instance associated with the GetOpen command
     */
    GetOpen(Master* pMaster);

    virtual void update(double deltaTime);

    virtual bool isFinished();
};

#endif // GETOPEN_H
