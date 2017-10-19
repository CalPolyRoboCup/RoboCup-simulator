#ifndef BALL_H
#define BALL_H

#include <QVector2D>
#include "messages_robocup_ssl_wrapper.pb.h"

/**
 * @brief The Ball class is used for accessing ball information, like position, direction, and speed
 */
class Ball
{
private:
    bool m_initialized;

    // Transform information
    QVector2D m_position;
    QVector2D m_lastPosition;

    // Velocity information
    float m_speed;
    float m_direction;

public:
    Ball();

    /**
     * @brief Used for accessing the position of the ball
     * @return The position of the ball as a @see QVector2D
     */
    QVector2D getPosition() const { return m_position; }

    /**
     * @brief Used for accessing the speed of the ball
     * @return The speed of the ball in m/s as a float
     */
    float getSpeed() const { return m_speed; }

    /**
     * @brief Used for accessing the direction of the ball
     * @return The direction of the ball in radians
     */
    float getDirection() const { return m_direction; }

    /**
     * @brief Updates the positional information of the ball
     * @param ball The @see SSL_DetectionBall used to update the Ball's information
     */
    void refresh(SSL_DetectionBall& ball);

    /**
     * @brief Updates the velocity information of the ball with the given delta time
     * @param deltaTime The time passed in seconds since the last update call
     */
    void updateStats(double deltaTime);
};

#endif // BALL_H
