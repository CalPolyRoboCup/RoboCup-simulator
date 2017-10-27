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
}

#endif // MATHHELPER_H
