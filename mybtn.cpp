#include "mybtn.h"
#include<QPixmap>
#include <QMessageBox>
mybtn::mybtn(const QString a, const QString b){
    this ->enter = a;
    this ->back = b; // 录入enter back
    QPixmap ap;    //录入第一张图片
    bool ok = ap .load(enter);
    if(!ok) {
        QMessageBox::information(this, "Warning", "录入图片错误!", QMessageBox::Ok);
        return;
    }   // 如果录入失败 那么 停止程序

    this -> setIcon(ap);                //设置图标
    this ->setFixedSize(ap.width(), ap.height()); //设置按钮大小
    this ->setStyleSheet("QPushButton{border:0px}"); // 设置按钮风格
    this ->setIconSize(QSize(ap.width(), ap.height())); // 设置图标大小
}

void mybtn::mousePressEvent(QMouseEvent * e) {
    QPixmap bp; // 开始录入 被点击时的图片
    bool ok = bp.load(back);
    if(ok == false) {
        QMessageBox::information(this, "Warning", "录入图片错误!", QMessageBox::Ok);
        return ;
    }

    this ->setIcon(bp);
    QPushButton::mousePressEvent(e);
} // 点击事件转换为新的图片

void mybtn::mouseReleaseEvent(QMouseEvent *e) {
    QPixmap ap;
    ap.load(enter);
    this ->setIcon(ap);
    QPushButton::mouseReleaseEvent(e);
}  // 重新录入一开始的图片
