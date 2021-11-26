#include "StarGraphicsObject.h"
#include <QGraphicsSceneMouseEvent>
#include <QPolygon>
#include <QPainter>

StarGraphicsObject::StarGraphicsObject(QObject* parent)
    :QObject{ parent },
     QAbstractGraphicsShapeItem{}
    {
        connect(&_dialog, &QColorDialog::currentColorChanged, this, &StarGraphicsObject::colorUpdated);
    }

void StarGraphicsObject::setRadius(qreal radius)
{
    _radius = radius;
    _currentStarPolygon = createStarPolygon();
}
qreal StarGraphicsObject::radius() const
{
    return _radius;
}
void StarGraphicsObject::setAngle(qreal angle)
{
    _angle = angle;
    _currentStarPolygon = createStarPolygon();
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
    path.addPolygon(_currentStarPolygon);
    return path;
}


void StarGraphicsObject::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->save();
    painter->setPen(pen());
    painter->setRenderHint(QPainter::RenderHint::Antialiasing);
    painter->drawPolygon(_currentStarPolygon);
    painter->restore();
}
void StarGraphicsObject::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(_currentStarPolygon.containsPoint(event->scenePos() - this->pos(), Qt::FillRule::OddEvenFill)) {
        _dialog.show();

        //Если юзер зажал Ctrl, откроются окна настройки
        //цвета для всех звёзд на этой координате, а не
        //только для самой высокой (последней добавленной
        if(event->modifiers() & Qt::Modifier::CTRL)
            event->ignore();
    } else {
        event->ignore();
    }
}
void StarGraphicsObject::colorUpdated(const QColor& color)
{
    setPen(QPen(color));
}
QPolygonF StarGraphicsObject::createStarPolygon() const
{
    QPolygonF polygon;
    polygon << QPointF{ 0.0, -_radius }
            << QPointF{ _radius * 0.225, -_radius * 0.313 }
            << QPointF{ _radius * 0.951, -_radius * 0.309 }
            << QPointF{ _radius * 0.362, _radius * 0.119 }
            << QPointF{ _radius * 0.588, _radius * 0.809 }
            << QPointF{ 0, _radius * 0.384 }
            << QPointF{ -_radius * 0.588, _radius * 0.809 }
            << QPointF{ -_radius * 0.362, _radius * 0.119 }
            << QPointF{ -_radius * 0.951, -_radius * 0.309 }
            << QPointF{ -_radius * 0.225, -_radius * 0.313 }
            << QPointF{ 0.0, -_radius };

    //Thanks: Yury. Идея с QTransform его
    polygon = QTransform().rotate(_angle).map(polygon);
    return polygon;
}
