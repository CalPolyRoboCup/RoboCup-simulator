#include "TestCommand.h"
#include <iostream>

TestCommand::TestCommand(Master* pMaster) :
    Command(pMaster),
    m_numFrames(0)
{
}

void TestCommand::start()
{
    m_numFrames = 0;
    std::cout << "I've started!\n";
}

void TestCommand::update(double deltaTime)
{
    std::cout << "I've been updated!\n";
    m_numFrames++;
}

bool TestCommand::isFinished()
{
    return m_numFrames == 10;
}

void TestCommand::end()
{
    std::cout << "I've been ended!\n";
}
