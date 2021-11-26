#pragma once
#include <QAbstractGraphicsShapeItem>
#include <QColorDialog>
#include <QObject>

class StarGraphicsObject: public QObject, public QAbstractGraphicsShapeItem
{
    Q_OBJECT
private:
    QPolygonF _currentStarPolygon;//Создание полигона - операция недешёвая. Не будем пересоздавать одно и тоже миллиарды раз
    QColorDialog _dialog;
    qreal _radius = 0.0;
    qreal _angle = 0.0;

public:
    StarGraphicsObject(QObject* parent = nullptr);

    void setRadius(qreal radius);
    qreal radius() const;
    void setAngle(qreal radius);
    qreal angle() const;

public:
    virtual QRectF boundingRect() const override;
    virtual QPainterPath opaqueArea() const override;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private slots:
    void colorUpdated(const QColor& color);
private:
    QPolygonF createStarPolygon() const;
};




