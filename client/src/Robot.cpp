#include "Robot.h"
#include "MathHelper.h"
#include <cmath>
#include <iostream>

Robot::Robot(Team team, unsigned char id) :
    m_initialized(false),
    m_position(0, 0),
    m_orientation(0),
    m_lastPosition(0, 0),
    m_lastOrientation(0),
    m_speed(0),
    m_direction(0),
    m_angularVelocity(0),
    m_targetSpeed(0),
    m_targetDirection(0),
    m_targetAngularVelocity(0),
    m_kickerSpeed(0),
    m_team(team),
    m_id(id)
{
    m_orientationPid = new PID(10.0, 0.0, 0.25, -M_PI * 4, M_PI * 4);

    m_pDefaultCommand = 0;
    m_pWaitingCommand = 0;
    m_pCommand = 0;
}

void Robot::refresh(SSL_DetectionRobot& robot)
{
    // Update positional information
    m_position.setX(robot.x());
    m_position.setY(robot.y());
    m_orientation = robot.orientation();

    // If this is the first frame, set the last position and orientation to the current position and orientation
    if (!m_initialized)
    {
        m_initialized = true;
        m_lastPosition = m_position;
        m_lastOrientation = m_orientation;
    }
}

void Robot::updateStats(double deltaTime)
{
    // Update the speed of the robot
    if (m_position != m_lastPosition)
    {
        m_speed = (m_position - m_lastPosition).length() / deltaTime * 0.001;

        if (m_speed > 0)
            m_direction = std::atan2(m_position.y() - m_lastPosition.y(), m_position.x() - m_lastPosition.x());

        m_lastPosition = m_position;
    }

    // Update the angular velocity of the robot
    if (m_orientation != m_lastOrientation)
    {
        m_angularVelocity = (m_orientation - m_lastOrientation) / deltaTime;
        m_lastOrientation = m_orientation;
    }
}

void Robot::updateCommand(double deltaTime)
{
    if (m_pWaitingCommand != 0)
    {
        if (m_pCommand != 0)
        {
            m_pCommand->interrupted();
            m_pCommand->end();
        }

        m_pCommand = m_pWaitingCommand;
        m_pWaitingCommand = 0;
        m_pCommand->start();
    }

    if (m_pCommand != 0)
    {
        if (m_pCommand->isFinished())
        {
            m_pCommand->end();
            m_pCommand = 0;
        }
        else
        {
            m_pCommand->update(deltaTime);
        }
    }

    if (m_pCommand == 0 && m_pWaitingCommand == 0 && m_pDefaultCommand != 0)
    {
        m_pCommand = m_pDefaultCommand;
        m_pCommand->start();
    }

    m_targetAngularVelocity = m_orientationPid->calculate(deltaTime, MathHelper::adjustAngleValue(m_orientationPid->getSetpoint(), m_orientation));
}

void Robot::writeOutput(grSim_Robot_Command *pCommand)
{
    // Define the ID of the robot
    pCommand->set_id(m_id);

    // Make sure we're defining x and y speed, not individual wheel speeds
    pCommand->set_wheelsspeed(false);
    pCommand->set_wheel1(0.0f);
    pCommand->set_wheel2(0.0f);
    pCommand->set_wheel3(0.0f);
    pCommand->set_wheel4(0.0f);

    // Calculate the horizontal speed from the target speed, target direction, and orientation
    pCommand->set_veltangent(m_targetSpeed * std::cos(m_targetDirection + m_orientation));

    // Calculate the vertical speed from the target speed, taret direction, and orientation
    pCommand->set_velnormal(-m_targetSpeed * std::sin(m_targetDirection + m_orientation));
    pCommand->set_velangular(m_targetAngularVelocity);

    // Set kicker speeds
    pCommand->set_kickspeedx(m_kickerSpeed);
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

void Robot::setTargetOrientation(float angle)
{
    m_targetOrientation = angle;

    while (angle < 0)
        angle += M_PI * 2;

    while (angle > M_PI * 2)
        angle -= M_PI * 2;

    m_orientationPid->setSetpoint(angle);
}

void Robot::setKickerSpeed(float speed)
{
    m_kickerSpeed = speed;
}

void Robot::setDefaultCommand(Command *pCommand)
{
    if (pCommand->getRobot() == this || pCommand->setRobot(this))
        m_pDefaultCommand = pCommand;
    else
        std::cout << "Cannot set a default Command that's already been assigned to another robot!\n";
}

void Robot::runCommmand(Command *pCommand)
{
    if (pCommand->getRobot() == this || pCommand->setRobot(this))
        m_pWaitingCommand = pCommand;
    else
        std::cout << "Cannot run a Command that's already been assigned to another robot!\n";
}
