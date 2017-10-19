#include "TestCommand.h"
#include <iostream>

TestCommand::TestCommand(Master* pMaster, std::string name, int lifetime) :
    Command(pMaster),
    m_name(name),
    m_lifetime(lifetime),
    m_numFrames(0)
{
}

void TestCommand::start()
{
    m_numFrames = 0;
    std::cout << m_name << " has started!\n";
}

void TestCommand::update(double deltaTime)
{
    std::cout << m_name << " has updated!\n";
    m_numFrames++;
}

bool TestCommand::isFinished()
{
    return m_numFrames == m_lifetime;
}

void TestCommand::end()
{
    std::cout << m_name << " has ended!\n";
}
