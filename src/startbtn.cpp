#include "startbtn.h"
#include <QPixmap>
#include<QMessageBox>
startbtn::startbtn(const QString a, const QString b, const QString c, const QString d) {
    // 关于 enter, enter_c, back, back_c 查看startbtn.h
    this ->enter = a;
    this ->enter_c = b;
    this ->back = c;
    this ->back_c = d;

    QPixmap ep; // 载入图标1
    bool ok = ep.load(this ->enter);
    if (!ok){
         QMessageBox::information(this, "Warning", "图片为载入!", QMessageBox::Ok);
         return;
    }

    // 将图片载入到按钮中
    this ->setIcon(ep);

    // 设置图标大小
    this -> setIconSize(QSize(ep.width(), ep.height()));

    // 设置图标大小
    this ->setFixedSize(ep.width(), ep.height());

    //设置按钮风格
    this ->setStyleSheet("QPushButton{border: 0px;}");

}


// 点击事件
void startbtn::mousePressEvent(QMouseEvent * ev) {
        QPixmap p_c;  // 载入当鼠标按下时 的 图标
        if(!is_play) {
            p_c.load(this ->enter_c);
            this ->setIcon(QIcon(p_c));

        } else {
            p_c.load(this ->back_c);
            this ->setIcon(QIcon(p_c));
        }

        QPushButton::mousePressEvent(ev);
}


// 鼠标松开事件
void startbtn::mouseReleaseEvent(QMouseEvent *ev) {
    QPixmap p;
    if(!is_play) {
        p.load(this ->back);

        this ->setIcon(QIcon(p));
        is_play = true; // 播放器现在处于暂停状态
    } else {
        p.load(this ->enter);

        this ->setIcon(QIcon(p));
        is_play = false; // 播放器现在处于播放状态
    }
    QPushButton::mouseReleaseEvent(ev);
}
