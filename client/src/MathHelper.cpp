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
}
