#include "Ball.h"
#include <cmath>

Ball::Ball() :
    m_initialized(false),
    m_position(0, 0),
    m_lastPosition(0, 0),
    m_speed(0),
    m_direction(0)
{
}

void Ball::refresh(SSL_DetectionBall& ball)
{
    m_position.setX(ball.x());
    m_position.setY(ball.y());

    if (!m_initialized)
    {
        m_initialized = true;
        m_lastPosition = m_position;
    }asdf
}

void Ball::updateStats(double deltaTime)
{
    // Update the speed of the ball
    if (m_position != m_lastPosition)
    {
        m_speed = (m_position - m_lastPosition).length() / deltaTime * 0.001;

        if (m_speed > 0)
            m_direction = std::atan2(-(m_position.y() - m_lastPosition.y()), m_position.x() - m_lastPosition.x());

        m_lastPosition = m_position;
    }
}
