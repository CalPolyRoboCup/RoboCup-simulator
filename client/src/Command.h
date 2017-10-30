#ifndef COMMAND_H
#define COMMAND_H

#include "Master.h"
#include "Robot.h"

class Master;
class Robot;

/**
 * @brief The Command class provides a means of assigning actions to Robots.
 * Commands are designed to allow reuseability, so any given Command should be designed
 * to be initialized, updated, and ended multiple times.
 */
class Command
{
public:
    Command(Master* pMaster);

    /**
     * @brief Defines the robot that this Command is attached to
     * @note Once the robot is defined, it cannot be changed
     * @param pRobot The robot to assign the Command to
     * @return true if the robot was properly assigned, otherwise false
     */
    bool setRobot(Robot* pRobot);

    /**
     * @brief Used for deallocating a Command instance.
     */
    void destroy() { delete this; }

    /**
     * @brief Called when the Command is first started
     */
    virtual void start() { }

    /**
     * @brief Called when the Command is updated
     * @param deltaTime The time passed since the last update
     */
    virtual void update(double deltaTime) { }

    /**
     * @brief Should return true when the command has finished
     * @return True if the command has finished
     */
    virtual bool isFinished() { return false; }

    /**
     * @brief Called when the command has been interrupted with another incoming command
     */
    virtual void interrupted() { }

    /**
     * @brief Called when the command ends
     */
    virtual void end() { }

    /**
     * @brief Returns the @see Robot associated with this Command
     * @return The @see Robot associated with this Comand
     */
    Robot* getRobot() const { return m_pRobot; }

protected:
    Master* m_pMaster;
    Robot* m_pRobot;

    /**
     * @brief The virtual destructor
     * @note The destructor is protected to prevent allocation of Commands on the stack
     */
    virtual ~Command() { }

    /**
     * @brief Called when the Command is first assigned to a robot
     */
    virtual void init() { }

};

#endif // COMMAND_H
