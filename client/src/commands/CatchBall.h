#ifndef CATCHBALL_H
#define CATCHBALL_H

#include "../Command.h"

#define CATCH_BALL_VElOCITY_THRESHOLD 0.01f
#define CATCH_VELOCITY_THRESHOLD 0.005f
#define CATCH_MAXIMUM_DISTANCE 130

class CatchBall : public Command
{
public:
    /**
     * @brief Initializes a new CatchBall instance
     * @param pMaster The Master instance associated with the CatchBall command
     */
    CatchBall(Master* pMaster);

    virtual void update(double deltaTime);

    virtual bool isFinished();

    virtual void end();

private:
    QVector2D m_ballDirectionVector;
};

#endif // CATCHBALL_H
