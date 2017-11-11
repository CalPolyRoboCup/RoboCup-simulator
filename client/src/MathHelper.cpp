#include "MathHelper.h"
#include <cmath>

namespace MathHelper
{
    QVector2D getClosestPoint(QVector2D lineStart, QVector2D lineEnd, QVector2D point)
    {
        QVector2D dir = (lineEnd - lineStart).normalized();

        float t = dir.x() * (point.x() - lineStart.x()) + dir.y() * (point.y() - lineStart.y());

        return QVector2D(t * dir.x() + lineStart.x(), t * dir.y() + lineStart.y());
    }

    float getLineAngle(QVector2D pointA, QVector2D pointB)
    {
        return std::atan2(pointB.y() - pointA.y(), pointB.x() - pointA.x());
    }

    float adjustAngleValue(float baseAngle, float otherAngle)
    {
        while (baseAngle - otherAngle > M_PI)
            otherAngle += M_PI * 2;

        while (otherAngle - baseAngle > M_PI)
            otherAngle -= M_PI * 2;

        return otherAngle;
    }

    float biasAngle(float incoming, float outgoing, float outgoingBias)
    {
        return (incoming + outgoing * outgoingBias) / (1 + outgoingBias);
    }
}
