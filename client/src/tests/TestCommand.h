#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "../Command.h"

class TestCommand : public Command
{
public:
    TestCommand(Master* pMaster, std::string name, int lifetime);

    virtual void start();
    virtual void update(double deltaTime);
    virtual bool isFinished();
    virtual void end();

private:
    std::string m_name;
    int m_lifetime;
    int m_numFrames;
};

#endif // TESTCOMMAND_H
