#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <QVector2D>

namespace MathHelper
{
    /**
     * @brief Returns the point along the given line closes to the point provided
     * @param lineStart The start of the line
     * @param lineEnd The end of the line
     * @param point The point to compare with the line
     * @return A @see QVector2D describing the point along the line closest to the point provided
     */
    QVector2D getClosestPoint(QVector2D lineStart, QVector2D lineEnd, QVector2D point);

    /**
     * @brief Returns the angle in radians of the line drawn from point A to point B
     * @param pointA The first point in the line
     * @param pointB The second point in the line
     * @return A float representing the radians of the line drawn from point A to point B
     */
    float getLineAngle(QVector2D pointA, QVector2D pointB);

    /**
     * @brief Returns the angle in radians that results in the lowest difference between the two given angles
     * @param baseAngle The angle used to adjust the other angle
     * @param otherAngle The angle to be adjusted
     * @return The value of the adjusted angle
     */
    float adjustAngleValue(float baseAngle, float otherAngle);

    /**
     * @brief Returns the angle that represents a bisection of the two given angles, but biased toward the outgoing angle from the given bias
     * @param incoming The incoming angle
     * @param outgoing The outgoing angle (the bias controls how influential this is)
     * @param outoingBias The outgoing angle bias constant
     * @return The baised angle
     */
    float biasAngle(float incoming, float outgoing, float outgoingBias);
}

#endif // MATHHELPER_H
