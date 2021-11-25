#pragma once
#include "StarGraphicsObject/StarGraphicsObject.h"
#include "StarBuilder/StarBuilder.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QApplication>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QScreen>
#include <QTimer>

class StarPainterApplication : public QWidget
{
    Q_OBJECT
private:
    QGraphicsScene* _scene = new QGraphicsScene(this);
    QGraphicsView* _view = new QGraphicsView;
    QPushButton* _screenButton = new QPushButton("Screen");
    QPushButton* _quitButton = new QPushButton("Quit");

public:
    explicit StarPainterApplication(QWidget *parent = nullptr);
public slots:
    void makeScreen();

protected slots:
    virtual void resizeEvent(QResizeEvent *event) override;
};


