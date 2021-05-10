#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QMainWindow>
#include <QSqlDatabase>
#include <QMouseEvent>
#include<QEvent>
#include<QPalette>
#include<QTimer>
#include <QPaintEvent>
#include<QMediaPlayer>      // 实现多媒体的 应用
#include<QMediaPlaylist>
#include<QPainter>
#include<QTableWidget>
#include <QLabel> // 用来显示当前播放歌曲
#include<QDir>
#include<QSlider>  // 音量进度条
#include "mybtn.h"
#include"startbtn.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString current="00:00";   // 目前播放的时间
    QString all="00:00";   // 该歌曲的 时间
     int bufferVol;   // 用来 在 valbt 的点击事件中 记录 还未变成 0 的THIS ->V 也会在之后的 点击中 将 V 的值 重新 赋值给V
     bool playf = false;   // 当点击playf 时 如果是false 则为 播放音乐 否则为 停止音乐
     bool leftflag = false; // 如果 leftflag == true 那么开始移动屏幕
     bool volF = false;     //volF = false 时 静音    volF = true 时 返回当时 的 音量
     int flag = 0; // 当flag = 0 时 maxb 让窗口变大  flag = 1 时让窗口变成原来的样子

    mybtn *minb, *maxb, *clsb, *nextbt, *prevbt;  // 窗口的最大化 最小化  关闭 下一首 和上一首 的按钮
    QSqlDatabase db;   // 用来连接数据库 来调用歌曲
    QMediaPlayer *Player;    // 实现多媒体操控
    QMediaPlaylist *Playlist;  // 多媒体列表
    QString filem = "F:\\qq音乐\\Music";           // 音乐文件路径
    QStringList filemlist;
    startbtn* playbt ,*volbt;                  // 音乐的播放按钮  音量按钮
    QLabel* musicL, *btnL ,*liftLabel ,*rightLabel, *PlayL;     // 用来显示当前播放歌曲  窗口按钮的封装 左时间显示 右边时间显示 播放控件的封装

    //实现窗口的 任意拖动
    QPoint glbal_p, win_p;   // 用win_p - glabel_p 就是 偏移量
    void changePro();  // 通过拖动进度条  改变歌曲进度
    void mouseMoveEvent(QMouseEvent*);   // 鼠标移动事件
    void mousePressEvent(QMouseEvent*);  // 鼠标点击事件
private slots:
    void init();    // 初始化播放器
    void initPro(); // 初始化进度条
    void showPlayMedia();                                  //  将 当前播放歌的名称 在label 的 text 中显示
    void addItem(QString& file);   // 添加到TableWeight中
    QStringList getfileName(const QString& file);  // 将所有的 歌的文件路径都记录到 QstrinList中
    void reinit();  // x 初始化
public slots:
    void updatepos();   // 更新 播放时间
private:
    int X;    // 进度条总长度  防止出现越界情况
    int V;    //音量总长度  防止出现越界情况
    qint64 druntime;//总进度
    qint64  positontime = 0;//当前进度
    QTimer *time; //刷新
//    QTimer* time1 = new QTimer(this); // 启动后

    void paintEvent(QPaintEvent* event); // 绘制 进度条
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
