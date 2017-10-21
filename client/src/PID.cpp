#include "PID.h"

PID::PID(float p, float i, float d, float min, float max) :
    m_p(p),
    m_i(i),
    m_d(d),
    m_min(min),
    m_max(max),
    m_setpoint(0),
    m_lastError(0),
    m_integral(0)
{
}

float PID::calculate(float deltaTime, float input)
{
    float error = m_setpoint - input;

    float pOut = m_p * error;

    m_integral += error * deltaTime;
    float iOut = m_i * m_integral;

    float derivative = (error - m_lastError) / deltaTime;
    float dOut = m_d * derivative;

    float output = pOut + iOut + dOut;

    if (output > m_max)
        output = m_max;
    else if (output < m_min)
        output = m_min;

    m_lastError = error;

    return output;
}
