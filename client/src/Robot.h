#ifndef ROBOT_H
#define ROBOT_H

#include <QVector2D>
#include "messages_robocup_ssl_wrapper.pb.h"
#include "grSim_Packet.pb.h"

/**
 * @brief The Team enum is used for describing which team a robot is on
 */
enum Team
{
    YELLOW,
    BLUE
};

/**
 * @brief The Robot class is used for accessing robot information and controlling a robot's outputs
 */
class Robot
{
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
    float m_targetAngularVelocity;

    // Metadata
    Team m_team;
    unsigned char m_id;
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
    void update(grSim_Robot_Command* pCommand, double deltaTime);

    // Velocity setters

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
     * @brief Sets the target angular velocity of the robot
     * @param velocity The target velocity in rad/s
     */
    void setTargetAngularVelocity(float velocity);
};

#endif // ROBOT_H