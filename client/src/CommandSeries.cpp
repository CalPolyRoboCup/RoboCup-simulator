#include "CommandSeries.h"

CommandSeries::CommandSeries(Master* pMaster) :
    Command(pMaster),
    m_commandIndex(0),
    m_isFinished(false)
{
    m_pCommand = 0;
}

void CommandSeries::addCommand(Command* pCommand)
{
    m_commands.push_back(pCommand);
}

void CommandSeries::start()
{
    if (!m_commands.empty())
    {
        m_pCommand = m_commands.front();
        m_pCommand->start();
    }
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
