#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include <QString>
#include <QPainter>
#include <QMouseEvent>
#include <QPalette>
#include <QLabel>
#include <QTimer>
#include <QPaintEvent>

class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayWidget(QWidget *parent = nullptr);

    int X = 63; // 进度条总长度  防止出现越界情况
    qint64 tcurr, tall; // 当前播放的时间, 该歌曲总共时间 (毫秒)
    QString currt = "0:0", allt = "0: 0";    // currt: 目前播放的时间  allt:  该歌曲的 时间
    QLabel *currL, *allL;   // 用来 呈现 currt , allt
    QTimer *time;   //刷新

    void ChangeCurrT(int t); // 用来改变 当前播放时间 this ->tcurr = t;
    void updatecurr();    // 用来改变 当前播放时间


    // 防越界
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent* event); // 绘制 进度条

signals:
    void changem(); // 通过触发 信号changm  来改变当前歌曲进度
};

#endif // PLAYWIDGET_H
