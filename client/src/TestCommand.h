#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "Command.h"

class TestCommand : public Command
{
public:
    TestCommand(Master* pMaster);

    virtual void start();
    virtual void update(double deltaTime);
    virtual bool isFinished();
    virtual void end();

private:
    int m_numFrames;
};

#endif // TESTCOMMAND_H
