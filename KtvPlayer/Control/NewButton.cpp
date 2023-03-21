#include "NewButton.h"
#include<QPixmap>
#include <QMessageBox>
#include <QDebug>

NewButton::NewButton(const QString _Enter, const QString _Back) {
    this ->enter = _Enter;
    this ->back = _Back; // 录入enter back

    QPixmap ap;    //录入第一张图片
    bool ok = ap.load(enter);
    if (!ok && enter.size() != 0) {
        QMessageBox::information(this, "Warning", enter + " 录入图片错误!", QMessageBox::Ok);
        return;
    }   // 如果录入失败 那么 停止程序

    this -> setIcon(ap);                //设置图标
    this ->setFixedSize(ap.width(), ap.height()); //设置按钮大小
    this ->setStyleSheet("QPushButton{border:0px;}"); // 设置按钮风格
    this ->setIconSize(QSize(ap.width(), ap.height())); // 设置图标大小
}

NewButton::NewButton(const QString Enter, const QString Back, const QString Enter2, const QString Back2) {
    bStart = true;

    this ->enter = Enter;
    this ->enter2 = Back;
    this ->back = Enter2;
    this ->back2 = Back2;

    QPixmap ep; // 载入图标1
    bool ok = ep.load(enter);
    if (!ok && enter.size() != 0){
         QMessageBox::information(this, "Warning",  enter + " 录入图片错误!", QMessageBox::Ok);
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

void NewButton::mousePressEvent(QMouseEvent * e) {
    if (!bStart) {
        QPixmap bp; // 开始录入 被点击时的图片
        bool ok = bp.load(back);
        if (ok == false && back.size() != 0) {
            QMessageBox::information(this, "Warning", back + " 录入图片错误!", QMessageBox::Ok);
            return ;
        }
        this ->setIcon(bp);
    }
    else {
        QPixmap p_c;  // 载入当鼠标按下时 的 图标
        if(!isEnter) {
            p_c.load(this ->enter2);
            this->setIcon(QIcon(p_c));

        } else {
            p_c.load(this ->back2);
            this->setIcon(QIcon(p_c));
        }

    }

    QPushButton::mousePressEvent(e);
} // 点击事件转换为新的图片

void NewButton::mouseReleaseEvent(QMouseEvent *e) {
    if (!bStart) {
        QPixmap ap;
        bool ok = ap.load(enter);
        if (ok == false && enter.size() != 0) {
            QMessageBox::information(this, "Warning", enter + " 录入图片错误!", QMessageBox::Ok);
            return ;
        }
        this ->setIcon(ap);
    }
    QPushButton::mouseReleaseEvent(e);
}

void NewButton::SwitchButtonIcon(bool state) {
     QPixmap p;
    if (state) {
        p.load(this->back);
        this->setIcon(QIcon(p));
        isEnter = true; // Enter
    } else {
        p.load(this->enter);
        this->setIcon(QIcon(p));
        isEnter = false; // Back
    }
}
