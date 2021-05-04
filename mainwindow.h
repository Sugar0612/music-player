#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include <QSqlDatabase>
#include <QPushButton>
#include <QMouseEvent>
#include<QEvent>
#include "mybtn.h"
#include"mylab.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     int flag = 0; // 当flag = 0 时 maxb 让窗口变大  flag = 1 时让窗口变成原来的样子
    QSqlDatabase db;   // 用来连接数据库 来调用歌曲
    mybtn *minb, *maxb, *clsb;  // 窗口的最大化 最小化 以及 关闭

    //实现窗口的 任意拖动
    QPoint glbal_p, win_p;   // 用win_p - glabel_p 就是 偏移量
    void mouseMoveEvent(QMouseEvent*);   // 鼠标移动事件
    void mousePressEvent(QMouseEvent*);  // 鼠标点击事件


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
