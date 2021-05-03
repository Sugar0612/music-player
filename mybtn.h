#ifndef MYBTN_H
#define MYBTN_H

#include <QWidget>
#include<QString>
#include <QMouseEvent>
#include <QPushButton>
class mybtn : public QPushButton
{
    Q_OBJECT
public:
//    explicit mybtn(QObject *parent = nullptr);
    QString enter, back;  // 点击状态显示的两种图片 enter back
    mybtn(const QString a, const QString b = "");   // 重新写 mybtn的构造函数

    void mousePressEvent(QMouseEvent*);  // 当点击按钮时变换图片
    void mouseReleaseEvent(QMouseEvent*); // 当松开按钮图片返回到 enter 状态

signals:

};

#endif // MYBTN_H
