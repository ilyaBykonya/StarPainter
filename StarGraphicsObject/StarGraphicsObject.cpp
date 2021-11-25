#include "StarGraphicsObject.h"
#include <QPolygon>
#include <QPainter>

StarGraphicsObject::StarGraphicsObject(QObject* parent)
    :QObject{ parent },
     QAbstractGraphicsShapeItem{},
     _dialog{}
    {
        connect(&_dialog, &QColorDialog::currentColorChanged, this, &StarGraphicsObject::colorUpdated);
    }

void StarGraphicsObject::setRadius(qreal radius)
{
    _radius = radius;
}
qreal StarGraphicsObject::radius() const
{
    return _radius;
}
void StarGraphicsObject::setAngle(qreal angle)
{
    _angle = angle;
}
qreal StarGraphicsObject::angle() const
{
    return _angle;
}


QRectF StarGraphicsObject::boundingRect() const
{
    return { -_radius, -_radius, 2 * _radius, 2 * _radius };
}
QPainterPath StarGraphicsObject::opaqueArea() const
{
    QPainterPath path;
    QPolygonF polygon;
    polygon.append(QPointF{ 0.0, -_radius });
    polygon.append(QPointF{ _radius * 0.951, -_radius * 0.309 });
    polygon.append(QPointF{ _radius * 0.588, _radius * 0.809 });
    polygon.append(QPointF{ -_radius * 0.588, _radius * 0.809 });
    polygon.append(QPointF{ -_radius * 0.951, -_radius * 0.309 });
    path.addPolygon(polygon);
    return path;
}


void StarGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->save();
    painter->setPen(pen());
    painter->rotate(_angle);
    painter->setRenderHint(QPainter::RenderHint::Antialiasing);

    QPolygonF polygon;
    polygon.append(QPointF{ 0.0, -_radius });
    polygon.append(QPointF{ -_radius * 0.588, _radius * 0.809 });
    polygon.append(QPointF{ _radius * 0.951, -_radius * 0.309 });
    polygon.append(QPointF{ -_radius * 0.951, -_radius * 0.309 });
    polygon.append(QPointF{ _radius * 0.588, _radius * 0.809 });

    painter->drawPolygon(polygon);
    painter->restore();
}
void StarGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _dialog.show();
}
void StarGraphicsObject::colorUpdated(const QColor& color)
{
    setPen(QPen(color));
}
