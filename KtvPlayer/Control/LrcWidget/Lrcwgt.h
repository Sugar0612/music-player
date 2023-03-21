#ifndef LRCWGT_H
#define LRCWGT_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QFont>

#include <QMoveEvent>
#include <QPaintEvent>
#include <QIcon>

class LrcWgt : public QWidget
{
    Q_OBJECT
public:
    LrcWgt(QWidget *p);

public slots:
    void SetLrc(QString Lrc);

private:

    bool leftflag = false;
    QLabel *LrcLab = nullptr;
    QPoint glbal_p, win_p;   // 用win_p - glabel_p 就是 偏移量

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent * event);
};

#endif // LRCWGT_H
