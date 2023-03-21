#ifndef NEWBUTTON_H
#define NEWBUTTON_H

#include <QWidget>
#include<QString>
#include <QMouseEvent>
#include <QPushButton>

class NewButton : public QPushButton
{
    Q_OBJECT

private:
        QString enter, back, enter2, back2;  // 点击状态显示的两种图片 enter back
        bool isEnter = false;
        bool bStart = false, bPlay = false;

        void mousePressEvent(QMouseEvent*);  // 当点击按钮时变换图片
        void mouseReleaseEvent(QMouseEvent*); // 当松开按钮图片返回到 enter 状态
public:
    NewButton(const QString _Enter, const QString _Back = "");   // 重新写NewButton的构造函数
    NewButton(const QString Enter, const QString Back, const QString Enter2, const QString Back2);   // 重新写NewButton的构造函数

    void SetEnter(bool benter) { isEnter = benter; }

public slots:
    void SwitchButtonIcon(bool);
};

#endif // NEWBUTTON_H
