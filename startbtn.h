#ifndef STARTBTN_H
#define STARTBTN_H

#include <QPushButton>
#include <QString>
#include <QMouseEvent>
class startbtn : public QPushButton
{
    Q_OBJECT
public:
//    explicit startbtn(QPushButton *parent = nullptr);
    explicit startbtn(const QString a, const QString b, const QString c, const QString d); // startbtn 构造函数
    QString enter, enter_c, back, back_c;   // enter 初始图标, enter_c 当鼠标点击btn上时 改变其图标, back 当鼠标放开时改变图标, back_c 当鼠标点击btn上时改变
    bool is_play = false;  //当 is_play = false时, 为播放图标, is_play = true 时为暂停图标

   void mousePressEvent(QMouseEvent*);     // 点击事件
   void mouseReleaseEvent(QMouseEvent*);   // 鼠标松开事件
signals:

};

#endif // STARTBTN_H
