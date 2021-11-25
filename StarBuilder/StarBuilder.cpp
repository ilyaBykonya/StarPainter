#include "StarBuilder.h"
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QLineF>
#include <QtMath>
#include <QDebug>

StarBuilder::StarBuilder(QObject *parent)
    :QObject{ parent }
    {
    }


StarBuilder* StarBuilder::create(QGraphicsScene* owner)
{
    StarBuilder* result = new StarBuilder(owner);
    owner->installEventFilter(result);
    result->_owner = owner;
    return result;
}
bool StarBuilder::eventFilter(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched)
    QGraphicsSceneMouseEvent* mouseEvent = dynamic_cast<QGraphicsSceneMouseEvent*>(event);
    if(mouseEvent == nullptr)
        return false;

    switch (event->type())
    {
    case QEvent::Type::GraphicsSceneMousePress:
    {
        if(_bufferStar)
            _bufferStar->deleteLater();

        _bufferStar = new StarGraphicsObject(this);
        _owner->addItem(_bufferStar);
        _bufferStar->setPos(mouseEvent->scenePos());
        _owner->update();

        return false;
    }
    case QEvent::Type::GraphicsSceneMouseMove:
    {
        if(_bufferStar == nullptr)
            return false;

        updateStarState(mouseEvent->scenePos());
        _owner->update();
        return false;
    }
    case QEvent::Type::GraphicsSceneMouseRelease:
    {
        if(_bufferStar == nullptr)
            return false;
        if(_bufferStar->radius() == 5.0) {
            _bufferStar->deleteLater();
            _bufferStar = nullptr;
            _owner->update();
            return false;;
        }

        updateStarState(mouseEvent->scenePos());
        _bufferStar = nullptr;
        _owner->update();
        return false;
    }
    default:
    {
        return false;
    }
    }
}
void StarBuilder::updateStarState(const QPointF& mousePos)
{
    qreal newRadius = QLineF(mousePos, _bufferStar->pos()).length();
    qreal newAngleCos = qAcos((mousePos.x() -  _bufferStar->pos().x()) / newRadius);
    qreal newAngleSin = qAsin((mousePos.y() -  _bufferStar->pos().y()) / newRadius);
    qreal resultAngle = newAngleCos * 180.0 / 3.14 * (newAngleSin > 0 ? 1:-1);

    _bufferStar->setAngle(resultAngle + 18.0);
    _bufferStar->setRadius(newRadius);
}
