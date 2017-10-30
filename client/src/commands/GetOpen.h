#ifndef GETOPEN_H
#define GETOPEN_H

#include "../Command.h"

#define GETOPEN_VELOCITY_THRESHOLD 0.005f

class GetOpen : public Command
{
public:
    /**
     * @brief Creates a new GetOpen instance
     * @param pMaster The Master instance associated with the GetOpen command
     */
    GetOpen(Master* pMaster);

    virtual void start();

    virtual void update(double deltaTime);

    virtual bool isFinished();

private:
    QVector2D m_startPosition;

};

#endif // GETOPEN_H
