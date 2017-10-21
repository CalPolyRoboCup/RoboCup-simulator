#ifndef ROBOT_H
#define ROBOT_H

#include <QVector2D>
#include "Command.h"
#include "Team.h"
#include "PID.h"
#include "messages_robocup_ssl_wrapper.pb.h"
#include "grSim_Packet.pb.h"

class Command;

/**
 * @brief The Robot class is used for accessing robot information and controlling a robot's outputs
 */
class Robot
{
public:
    /**
     * @brief Initailizes a new Robot instance
     * @param team The team the robot is on
     * @param id The ID of the robot
     */
    Robot(Team team, unsigned char id);

    // Transformational getters

    /**
     * @brief Used for accessing the position of the robot
     * @return A copy of the position of the robot
     */
    QVector2D getPosition() const { return m_position; }

    /**
     * @brief Used for accessing the orientation of the robot
     * @return The orientation of the robot in radians
     */
    float getOrientation() const { return m_orientation; }

    // Velocity getters

    /**
     * @brief Used for accessing the speed of the robot
     * @return The speed of the robot in m/s
     */
    float getSpeed() const { return m_speed; }

    /**
     * @brief Used for accessing the direction of the robot
     * @return The direction of the robot in radians
     */
    float getDirection() const { return m_direction; }

    /**
     * @brief Used for accessing the angular velocity of the robot
     * @return The angular velocity of the robot in rad/s
     */
    float getAngularVelocity() const { return m_angularVelocity; }

    // Target value getters

    /**
     * @brief Used for accessing the target speed of the robot
     * @return The target speed of the robot in m/s
     */
    float getTargetSpeed() const { return m_targetSpeed; }

    /**
     * @brief Used for accessing the target direction of the robot
     * @return The target direction of the robot in radians
     */
    float getTargetDirection() const { return m_targetDirection; }

    /**
     * @brief Used for accessing the target orientation of the robot
     * @return The target orientation of the robot in radians
     */
    float getTargetOrientation() const { return m_orientationPid->getSetpoint(); }

    // Metadata getters

    /**
     * @brief Used for determining which team the robot is on
     * @return The @see Team the robot is on
     */
    Team getTeam() const { return m_team; }

    /**
     * @brief Used for determining the ID of the robot
     * @return The ID of the robot as a byte
     */
    unsigned char getId() const { return m_id; }

    // Updating robot information

    /**
     * @brief Updates positional information of the robot
     * @param robot The @see SSL_DetectionRobot from which to refresh
     */
    void refresh(SSL_DetectionRobot& robot);

    /**
     * @brief Updates the robot's motor outputs and writes them to the given @see grSim_Robot_Command
     * @param pCommand The command to which the function will write the outputs
     * @param deltaTime The time passed since the last update call
     */
    void updateStats(double deltaTime);

    /**
     * @brief Performs an update call for the Robot's current Command
     * @param deltaTime The time passed since the last update call
     */
    void updateCommand(double deltaTime);

    /**
     * @brief Generates the @see grSim_Robot_Command information to be sent to GrSim
     * @param pCommand The command to be populated
     */
    void writeOutput(grSim_Robot_Command* pCommand);

    // Target value setters

    /**
     * @brief Sets the target speed of the robot
     * @param speed The target speeed in m/s
     */
    void setTargetSpeed(float speed);

    /**
     * @brief Sets the target direction of the robot
     * @param angle The target direction angle in radians
     */
    void setTargetDirection(float angle);

    /**
     * @brief Sets the target orientation of the robot
     * @param angle The angle in radians
     */
    void setTargetOrientation(float angle);

    /**
     * @brief Sets the command to be executed before one is assigned or after a command ends
     * @param pCommand The default command
     */
    void setDefaultCommand(Command* pCommand);

    /**
     * @brief Runs the given command
     * @note Robot does NOT assume ownership of the command passed; eventual deallocation is the responsibility of the caller
     * @param pCommand The @see Command to run
     */
    void runCommmand(Command* pCommand);

private:
    bool m_initialized;

    // Transform information
    QVector2D m_position;
    float m_orientation;

    // Transform information from the last frame for calculating velocity
    QVector2D m_lastPosition;
    float m_lastOrientation;

    // Velocity information
    float m_speed;
    float m_direction;
    float m_angularVelocity;

    // Target velocity information
    float m_targetSpeed;
    float m_targetDirection;
    float m_targetOrientation;
    float m_targetAngularVelocity;

    // PID information
    PID* m_orientationPid;

    // Command information
    Command* m_pDefaultCommand;
    Command* m_pWaitingCommand;
    Command* m_pCommand;

    // Metadata
    Team m_team;
    unsigned char m_id;
};

#endif // ROBOT_H
