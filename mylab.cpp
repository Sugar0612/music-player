#include "mylab.h"
#include <QFont>
mylab::mylab(QString text, QWidget *parent) : QLabel(parent)
{
    this ->setStyleSheet("QLabel{color: rgb(128, 128, 128); padding-left: 30px;}");  // 改变label 的风格
    this ->setText(text); // 内容
    QFont font; // 修改字体
    font.setFamily("幼圆");
    this ->setFont(font);
}
