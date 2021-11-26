#pragma once
#include "../StarGraphicsObject/StarGraphicsObject.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QObject>

class StarBuilder: public QObject
{
    Q_OBJECT
private:
    StarGraphicsObject* _bufferStar = nullptr;
    QGraphicsScene* _owner = nullptr;

private:
    explicit StarBuilder(QObject *parent = nullptr);
public:
    static StarBuilder* create(QGraphicsScene* owner);

protected:
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private:
    bool buttonClicked(QGraphicsSceneMouseEvent* event);
    bool buttonMoved(QGraphicsSceneMouseEvent* event);
    bool buttonReleased(QGraphicsSceneMouseEvent* event);

    void updateStarState(const QPointF& mousePos);
};


