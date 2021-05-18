#include "mytabwidget.h"
#include <QFont>
mytabwidget::mytabwidget(QWidget *parent) : QTabWidget(parent)
{
         // 位置以及大小
        this->setGeometry(160, 80, 865, 520);

        // 设置风格
        this ->setStyleSheet("QTabBar::tab {background: #00000000;border: none; min-width: 10px; margin-right: 20px; border-left: 50px;"
                             "padding-left:20px; padding-right:20px;padding-top:5px;padding-bottom:5px;color:#686a6e; margin-left: 200px;}"
                             "QTabBar::tab:hover {background: rgb(228, 228, 228); color: rgb(0, 0, 0); border-bottom: 2px solid #3c3e42; }"
                             "QTabBar::tab:selected {border-color: #3a3a3f;color:rgb(0, 0, 0); border-bottom-color: #dcdde4; border-bottom: 2px solid #3c3e42;}");

    QFont font;
    font.setFamily("幼圆");
    font.setPointSize(13);  // 设置字号
    this -> setFont(font); // 设置tab 字体
}
