#ifndef PID_H
#define PID_H

/**
 * @brief The PID class is used for performing PID calculations given PID constasnts, min and max values, an input, and a delta time
 */
class PID
{
public:
    /**
     * @brief Creates a new PID instance
     * @param p The P (proportional) constant
     * @param i The I (integral) constant
     * @param d The D (derivative) constant
     * @param min The minimum output value
     * @param max The maximum output value
     */
    PID(float p, float i, float d, float min, float max);

    /**
     * @brief Calculates the output from the given delta time and input
     * @param deltaTime The time passed since the last calculate call
     * @param input The input to the PID calculation
     * @return The output of the PID calculations
     */
    float calculate(float deltaTime, float input);

    /**
     * @brief Used for accessing the P constant
     * @return The P constant
     */
    float getP() const { return m_p; }

    /**
     * @brief Used for accessing the I constant
     * @return The I constant
     */
    float getI() const { return m_i; }

    /**
     * @brief Used for accessing the D constant
     * @return The D constant
     */
    float getD() const { return m_d; }

    /**
     * @brief Used for accessing the minimum output limit
     * @return The mimimum output limit
     */
    float getMin() const { return m_min; }

    /**
     * @brief Used for accessing the maximum output limit
     * @return The maximum output limit
     */
    float getMax() const { return m_max; }

    /**
     * @brief Used for accessing the setpoint
     * @return The setpoint
     */
    float getSetpoint() const { return m_setpoint; }

    /**
     * @brief Used for setting the P constant
     */
    void setP(float p) { m_p = p; }

    /**
     * @brief Used for setting the I constant
     */
    void setI(float i) { m_i = i; }

    /**
     * @brief Used for setting the D constant
     */
    void setD(float d) { m_d = d; }

    /**
     * @brief Used for setting the setpoint
     */
    void setSetpoint(float setpoint) { m_setpoint = setpoint; }

private:
    float m_p;
    float m_i;
    float m_d;

    float m_min;
    float m_max;

    float m_setpoint;

    float m_lastError;
    float m_integral;
};

#endif // PID_H
