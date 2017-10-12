#include "Robot.h"
#include <cmath>
#include <iostream>

Robot::Robot(Team team, unsigned char id) :
    m_x(0),
    m_y(0),
    m_orientation(0),
    m_speed(0),
    m_direction(0),
    m_angularVelocity(0),
    m_targetSpeed(0),
    m_targetDirection(0),
    m_targetAngularVelocity(0),
    m_team(team),
    m_id(id)
{
}

void Robot::refresh(SSL_DetectionRobot& robot)
{
    m_x = robot.x();
    m_y = robot.y();
    m_orientation = robot.orientation();
}

void Robot::update(grSim_Robot_Command* pCommand, double deltaTime)
{
    // TODO: Implement velocity tracking

    pCommand->set_id(m_id);

    pCommand->set_wheelsspeed(false);
    pCommand->set_wheel1(0.0f);
    pCommand->set_wheel2(0.0f);
    pCommand->set_wheel3(0.0f);
    pCommand->set_wheel4(0.0f);
    pCommand->set_veltangent(m_targetSpeed * std::cos(m_targetDirection + m_orientation));
    pCommand->set_velnormal(m_targetSpeed * -std::sin(m_targetDirection + m_orientation));
    pCommand->set_velangular(m_targetAngularVelocity);

    pCommand->set_kickspeedx(0.0f);
    pCommand->set_kickspeedz(0.0f);
    pCommand->set_spinner(false);
}

void Robot::setTargetSpeed(float speed)
{
    m_targetSpeed = speed;
}

void Robot::setTargetDirection(float angle)
{
    m_targetDirection = angle;
}

void Robot::setTargetAngularVelocity(float velocity)
{
    m_targetAngularVelocity = velocity;
}
