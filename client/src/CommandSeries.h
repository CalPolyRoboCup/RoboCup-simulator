#ifndef COMMANDSERIES_H
#define COMMANDSERIES_H

#include <vector>
#include "Command.h"

/**
 * @brief The CommandSeries class is used to group multiple Commands into one
 */
class CommandSeries : public Command
{
public:
    /**
     * @brief Initializes a new CommandSeries instance
     * @param pMaster The Master instance
     */
    CommandSeries(Master* pMaster);

    virtual void start();

    virtual void update(double deltaTime);

    virtual bool isFinished();

protected:
    /**
     * @brief Adds a @see Command to the CommandSeries
     * @param pCommand The @see Command to add
     */
    void addCommand(Command* pCommand);

    virtual void init();

private:
    std::vector<Command*> m_commands;
    Command* m_pCommand;

    int m_commandIndex;
    bool m_isFinished;
};

#endif // COMMANDSERIES_H
