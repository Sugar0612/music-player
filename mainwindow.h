#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include <QSqlDatabase>
#include <QPushButton>
#include <QMouseEvent>
#include<QEvent>
#include<QMediaPlayer>      // 实现多媒体的 应用
#include<QMediaPlaylist>
#include<QTableWidget>
#include <QLabel> // 用来显示当前播放歌曲
#include<QDir>
#include "mybtn.h"
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

    mybtn *minb, *maxb, *clsb;  // 窗口的最大化 最小化 以及 关闭
    QSqlDatabase db;   // 用来连接数据库 来调用歌曲
    QMediaPlayer *Player;    // 实现多媒体操控
    QMediaPlaylist *Playlist;  // 多媒体列表
    QString filem = "F:\\qq音乐\\Music";           // 音乐文件路径
    QStringList filemlist;
//    QTableWidget* tbw;  // 建立播放列表样式
    QLabel* musicL;     // 用来显示当前播放歌曲

    //实现窗口的 任意拖动
    QPoint glbal_p, win_p;   // 用win_p - glabel_p 就是 偏移量
    void mouseMoveEvent(QMouseEvent*);   // 鼠标移动事件
    void mousePressEvent(QMouseEvent*);  // 鼠标点击事件

private slots:
    void init();    // 初始化播放器
    QStringList getfileName(const QString& file);
    void showPlayMedia();
    void addItem(QString& file);   // 添加到TableWeight中


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
