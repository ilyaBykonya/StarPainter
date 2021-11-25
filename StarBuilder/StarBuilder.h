#pragma once
#include "../StarGraphicsObject/StarGraphicsObject.h"
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
    void updateStarState(const QPointF& mousePos);
};


