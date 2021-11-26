#include "StarPainterApplication.h"
#include <QApplication>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QScreen>
#include <QTimer>


StarPainterApplication::StarPainterApplication(QWidget *parent)
    :QWidget{ parent }
    {
        //========================================

        _view->setScene(_scene);
        StarBuilder::create(_scene);
        _view->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        _view->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);

        //========================================

        QMenuBar* mainMenu = new QMenuBar;

        QMenu* actionsMenu = mainMenu->addMenu("Actions");
        actionsMenu->addAction("Screen...", this, &StarPainterApplication::makeScreen);
        actionsMenu->addAction("Canvas color...", this, &StarPainterApplication::changeColor);
        actionsMenu->addAction("Exit", qApp, &QApplication::quit);

        QMenu* aboutMenu = mainMenu->addMenu("About");
        aboutMenu->addAction("About app", this, &StarPainterApplication::aboutApp);
        aboutMenu->addAction("About Qt", qApp, &QApplication::aboutQt);

        //========================================

        QVBoxLayout* windowLayout = new QVBoxLayout;
        windowLayout->setMenuBar(mainMenu);
        windowLayout->addWidget(_view, 1);
        this->setLayout(windowLayout);

        //========================================
    }

void StarPainterApplication::makeScreen()
{
    QString saveFileName = QFileDialog::getSaveFileName(this, {}, {}, "*.jpg *.png");
    if(saveFileName.isEmpty())
        return;

    _view->grab().save(saveFileName, "jpg");
}
void StarPainterApplication::changeColor()
{
    QColorDialog dialog(QColor(255, 255, 255));
    if(dialog.exec() == QDialog::Accepted)
        _view->setBackgroundBrush(QBrush(dialog.selectedColor()));
}
void StarPainterApplication::aboutApp()
{
    QMessageBox::about(this, "Star painter", "Version: 2.0.0");
}

void StarPainterApplication::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    _scene->setSceneRect(QRectF{ { 0.0, 0.0 }, _view->size() });
}
