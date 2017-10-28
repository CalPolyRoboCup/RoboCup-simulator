#include "CommandSeries.h"
#include <iostream>

CommandSeries::CommandSeries(Master* pMaster) :
    Command(pMaster)
{
    m_pCommand = 0;
}

void CommandSeries::addCommand(Command* pCommand)
{
    m_commands.push_back(pCommand);
}

void CommandSeries::init()
{
    if (!m_commands.empty())
    {
        for (int i = 0; i < m_commands.size(); i++)
            if (!m_commands[i]->setRobot(m_pRobot))
                std::cout << "Warning: cannot add Commands to a CommandSeries that have already been added to another robot!\n";
    }
}

void CommandSeries::start()
{
    m_commandIndex = 0;
    m_isFinished = false;

    m_pCommand = m_commands.front();
    m_pCommand->start();
}

void CommandSeries::update(double deltaTime)
{
    if (m_pCommand != 0)
    {
        if (m_pCommand->isFinished())
        {
            m_pCommand->end();

            if (m_commandIndex < m_commands.size() - 1)
            {
                m_pCommand = m_commands[++m_commandIndex];
                m_pCommand->start();
            }
            else
            {
                m_isFinished = true;
                return;
            }
        }

        m_pCommand->update(deltaTime);
    }
    else
    {
        m_isFinished = true;
    }
}

bool CommandSeries::isFinished()
{
    return m_isFinished;
}
