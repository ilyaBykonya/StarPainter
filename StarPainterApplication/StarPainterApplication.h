#pragma once
#include "StarGraphicsObject/StarGraphicsObject.h"
#include "StarBuilder/StarBuilder.h"
#include <QGraphicsScene>
#include <QGraphicsView>

class StarPainterApplication : public QWidget
{
    Q_OBJECT
private:
    QGraphicsScene* _scene = new QGraphicsScene(this);
    QGraphicsView* _view = new QGraphicsView;

public:
    explicit StarPainterApplication(QWidget *parent = nullptr);

public slots:
    void makeScreen();
    void changeColor();
    void aboutApp();

protected slots:
    virtual void resizeEvent(QResizeEvent *event) override;
};


