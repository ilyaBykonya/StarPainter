#include "StarPainterApplication.h"

StarPainterApplication::StarPainterApplication(QWidget *parent)
    :QWidget{ parent }
    {
        _view->setScene(_scene);
        StarBuilder::create(_scene);
        connect(_screenButton, &QPushButton::clicked, this, &StarPainterApplication::makeScreen);
        connect(_quitButton, &QPushButton::clicked, qApp, &QApplication::quit);
        _view->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        _view->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        QHBoxLayout* controlsLayout = new QHBoxLayout;
            controlsLayout->addWidget(_screenButton, 1);
            controlsLayout->addStretch(1);
            controlsLayout->addWidget(_quitButton, 1);
        QVBoxLayout* windowLayout = new QVBoxLayout;
            windowLayout->addWidget(_view, 1);
            windowLayout->addLayout(controlsLayout);
        this->setLayout(windowLayout);
    }

void StarPainterApplication::makeScreen()
{
    QString saveFileName = QFileDialog::getSaveFileName(this, {}, {}, "*.jpg *.png");
    if(saveFileName.isEmpty())
        return;

    _view->grab().save(saveFileName, "jpg");
}
void StarPainterApplication::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    _scene->setSceneRect(QRectF{ { 0.0, 0.0 }, _view->size() });
}
