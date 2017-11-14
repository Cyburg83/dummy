#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>

#include "ca_base.h"

class GameWidget : public QFrame
{
    Q_OBJECT

public:
    GameWidget(QWidget *parent = 0);


protected:
//    void paintGrid(QPaintEvent *event);
//    void paintUniverse(QPaintEvent *event);
//    void mousePressEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
//    void timerEvent(QTimerEvent *event) override;

private:
//    void setTimeIntervall();
    void setUniverseSize(); //resize
//    void clearBoard();
//    int timeoutTime();

    QBasicTimer timer;

};


#endif // GAMEWIDGET_H
