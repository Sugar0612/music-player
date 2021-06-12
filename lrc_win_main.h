#ifndef LRC_WIN_MAIN_H
#define LRC_WIN_MAIN_H

#include <QWidget>
#include <QMoveEvent>
#include <QLabel>
#include <QPaintEvent>

class lrc_win_main : public QWidget
{
    Q_OBJECT
public:
    explicit lrc_win_main(QWidget *parent = nullptr);


    QLabel *l = nullptr;

    bool leftflag = false;
    QPoint glbal_p, win_p;   // 用win_p - glabel_p 就是 偏移量
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent * event);

signals:

};

#endif // LRC_WIN_MAIN_H
