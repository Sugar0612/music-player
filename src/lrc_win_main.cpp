#include "lrc_win_main.h"
#include <QLabel>
#include <QPainter>
#include <QFont>
#include <QIcon>


lrc_win_main::lrc_win_main(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setFamily("幼圆");
    font.setPointSize(20);
    font.setWeight(25);
    setWindowFlag(Qt::FramelessWindowHint);  // 删除以前的 最大化 最小化 关闭自己写

    this ->setWindowTitle("歌词窗口");
    this ->setWindowIcon(QIcon(":/coin/mymusic.png"));  // 主窗口的图标设置!
    this ->resize(500, 80);

    this->setWindowFlags(Qt::FramelessWindowHint); //使得窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true); // 透明显示

    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint); //窗口最前面 不会因为点击而隐藏

    l = new QLabel(this);
    l ->setGeometry(0, 0, this ->width(), this ->height());
    l ->setFont(font);
    l ->setStyleSheet("QLabel{color: rgb(128, 0, 128);}");
    l ->setText("糖糖音乐");
}

void lrc_win_main::mouseMoveEvent(QMouseEvent *e) {
    // 移动窗口
    if(leftflag && e ->pos().y() >= 0 && e ->pos().y() <= this ->height()) {
        win_p = e ->globalPos();
        this ->move(win_p - glbal_p);
    }
}

void lrc_win_main::mousePressEvent(QMouseEvent *e) {
    // 点击窗口
    if(e ->button() == Qt::LeftButton && e ->pos().y() >= 0 && e ->pos().y() <= this ->height()) {
        leftflag = true;
        glbal_p = e ->globalPos() - this ->pos();
    }
}

//透明设置 可以点击窗口了
void lrc_win_main::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(0, 0, 0, 1));
    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(0, 0, 0, 1)));

    painter.drawRect(QRect(0, 0, this ->width(), this ->height()));

    return QWidget::paintEvent(event);
}
