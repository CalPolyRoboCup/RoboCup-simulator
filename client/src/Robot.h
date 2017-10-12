#ifndef ROBOT_H
#define ROBOT_H

#include "messages_robocup_ssl_wrapper.pb.h"
#include "grSim_Packet.pb.h"

enum Team
{
    YELLOW,
    BLUE
};

class Robot
{
private:
    // Transform information
    float m_x;
    float m_y;
    float m_orientation;

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
    Robot(Team team, unsigned char id);

    // Transformational getters
    float getX() const { return m_x; }
    float getY() const { return m_y; }
    float getOrientation() const { return m_orientation; }

    // Velocity getters
    float getSpeed() const { return m_speed; }
    float getDirection() const { return m_direction; }
    float getAngularVelocity() const { return m_angularVelocity; }

    // Metadata getters
    Team getTeam() const { return m_team; }
    unsigned char getId() const { return m_id; }

    // Updating robot information
    void refresh(SSL_DetectionRobot& robot);
    void update(grSim_Robot_Command* pCommand, double deltaTime);

    // Velocity setters
    void setTargetSpeed(float speed);
    void setTargetDirection(float angle);
    void setTargetAngularVelocity(float velocity);
};

#endif // ROBOT_H
