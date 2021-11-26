#include "StarBuilder.h"
#include <QMouseEvent>
#include <QEvent>
#include <QtMath>

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
    case QEvent::Type::GraphicsSceneMousePress: return buttonClicked(mouseEvent);
    case QEvent::Type::GraphicsSceneMouseMove: return buttonMoved(mouseEvent);
    case QEvent::Type::GraphicsSceneMouseRelease: return buttonReleased(mouseEvent);
    default: return false;
    }
}

bool StarBuilder::buttonClicked(QGraphicsSceneMouseEvent* event)
{
    if((event->button() & Qt::MouseButton::LeftButton) == 0)
        return false;

    if(_bufferStar)
        _bufferStar->deleteLater();

    _bufferStar = new StarGraphicsObject(this);
    _owner->addItem(_bufferStar);
    _bufferStar->setPos(event->scenePos());
    _owner->update();
    return true;
}
bool StarBuilder::buttonMoved(QGraphicsSceneMouseEvent* event)
{
    if((event->buttons() & Qt::MouseButton::LeftButton) == 0)
        return false;

    if(_bufferStar == nullptr)
        return false;;

    updateStarState(event->scenePos());
    _owner->update();
    return true;
}
bool StarBuilder::buttonReleased(QGraphicsSceneMouseEvent* event)
{
    if((event->button() & Qt::MouseButton::LeftButton) == 0)
        return false;

    if(_bufferStar == nullptr)
        return false;

    if(_bufferStar->radius() <= 5.0) {
        _bufferStar->deleteLater();
        _bufferStar = nullptr;
        _owner->update();
        return false;
    }

    updateStarState(event->scenePos());
    _bufferStar = nullptr;
    _owner->update();
    return true;
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
