#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QMouseEvent>
#include <QEvent>
#include <QPalette>
#include <QTimer>
#include <QMediaPlayer>      // 实现多媒体的 应用
#include <QMediaPlaylist>
#include <QTableWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QMap>
#include <QPainter>
#include <QPaintEvent>
#include <QLabel> // 用来显示当前播放歌曲
#include <QDir>
#include <QListWidgetItem>
#include <QSlider>  // 音量进度条
#include <QLineEdit>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPaintEvent>
#include "mybtn.h"
#include"startbtn.h"
#include "mylab.h"
#include "mylistwidget.h"
#include "sign_in_win.h"
#include "lrcwidget.h"
#include "mytablewidget.h"
#include "create_list.h"
#include "show_list.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    bool f;
    QVector<mybtn*> l_vb = QVector<mybtn*>(10000, nullptr);  // 用来存储 音乐item 里的按钮vb
    QVector<QListWidgetItem*> l_vi = QVector<QListWidgetItem*>(10000, nullptr), lrc_itm; // 用来存储 一首歌的item
    QVector<QString> v_hash, v_id; // 保存 hash 和 id 用来 播放歌曲
    QMap<int, QString> lrcMap; // 歌词保存
    QMap<int, int> lrc_idx; // 存储 itme idx
    QMap<int, QString>::iterator p_lrcit; // 歌词上一个保存的it

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
     QString current="00:00";   // 目前播放的时间
     QString all="00:00";   // 该歌曲的 时间
     int bufferVol;   // 用来 在 valbt 的点击事件中 记录 还未变成 0 的THIS ->V 也会在之后的 点击中 将 V 的值 重新 赋值给V
     bool playf = false;   // 当点击playf 时 如果是false 则为 播放音乐 否则为 停止音乐
     bool leftflag = false; // 如果 leftflag == true 那么开始移动屏幕
     bool volF = false;     //volF = false 时 静音    volF = true 时 返回当时 的 音量
     bool is_open = false; // 当为false 时 点击 打开列表 否则关闭列表
     bool is_delete = false; // 如果is_delete = false 那么调用readmysql 里面的deletenowplay 否则调用queuefun里面的deletenowplay
     bool is_net = false; // 根据 is_net 的不同判断是否时 网络音乐 从而实现不同的操作
     bool sign_in = false; // 只有登录成功才可以听歌
     bool lrc_open = false;  // 如果false 则显示lrc_win 如果true 则关闭
     int flag = 0; // 当flag = 0 时 maxb 让窗口变大  flag = 1 时让窗口变成原来的样子
     int index = 0;  // 用来在tablewidget 中显示歌曲
     int is_insert = 1; // 是否真的插入net_music  如果为 0 no , 1 yes!
     int emit_i = 0; // 如何 初始化完成 则为1 否则如果使用 本地音乐初始化 则为 0 可以调用 beginplay信号
     int roll, roll_cnt; // roll 代表真实歌词下滚行数, 而 roll_cnt 代表歌词读取次数 当达到4次时 才允许歌词下滚
     int idd; // 歌词item idx
     int user_id = -1; // 用户的id
     int song_list_id = 0; // 用户歌单号 或者是 歌单数量
     int is_change = 0; // 当等于 1 时 说明是 改变了歌曲那么 要singleshot
     QString list_id; // 记录 list_id
     int g_row = -1;



    sign_in_win* sign; // 登录界面
    mybtn *minb, *maxb, *clsb, *nextbt, *prevbt, *winicon, *listbtn, *btn_search, *sign_in_btn, *local_btn;  // 窗口的最大化 最小化  关闭 下一首 上一首 的按钮 主窗口图标  音乐列表图标, 搜索按钮
    //登录按钮  本地音乐添加窗口
    mybtn *add_songlist; // 添加歌单按钮
    QSqlDatabase db;   // 用来连接数据库 来调用歌曲
    QMediaPlayer *Player;    // 实现多媒体操控
    QMediaPlaylist *Playlist;  // 多媒体列表
    QString filem;           // 音乐文件路径  "F:\\qq音乐\\Music";
    QString pname, mname; // 歌手名字 和 歌曲名字
    QString net_file, net_name, net_image, net_lrc; // 记录http 的路径  歌曲名字 歌曲图片 歌词
    QStringList filemlist, nowplaylist, nowlist, nowlist_im, list_col_table, nowlist_lrc, song_col_name, likelist;  // 本地音乐文件路径, 当前播放音乐路径  歌词   当前的播放音乐名字（当放入songqueue 后可以clear）
    startbtn* playbt ,*volbt;                  // 音乐的播放按钮  音量按钮
    QLabel* musicL, *btnL ,*liftLabel ,*rightLabel, *PlayL, *sign_L;     // 用来显示当前播放歌曲  窗口按钮的封装 左时间显示 右边时间显示 播放控件的封装 登录标签
//    mytabwidget *mainmusic; // 设置音乐播放器 主窗口!
    mylab* mymusic, *mylist;   // 我的音乐的标签  我的歌单标签
    mylistwidget *musiclist ,*songlist;  // 喜爱歌单 和 本地音乐的创建
    mytablewidget *songqueue;   //播放队列列表
    QTableWidget *local_w, *like_w, *list_w;       //本地音乐列表 喜爱音乐窗口 自定义歌单窗口
    QListWidgetItem* likemusiclist, *mylocalmusic;  // 喜爱的歌单 和 本地音乐
    QLineEdit* search_line;   // 搜索框
    QTableWidget *tab_search;  //用来显示歌曲
    QTabWidget *lrcwin; //  歌词显示窗口
    QPushButton *music_map;  //当前播放音乐的图标
    lrcwidget* lrc_w; // 歌词窗口(地基)
    QListWidget* lrc_l; // 歌词显示
    create_list *n_list; // 显示窗口输入歌单的名字然后创建
    show_list *show_w; // 当点击收藏时 显示所有的自定义歌单


    //http
    QNetworkAccessManager *net_manager, *network_manager2, *network_manager3;
    QNetworkRequest *net_request, *network_request2, *network_request3;


    //实现窗口的 任意拖动
    QPoint glbal_p, win_p;   // 用win_p - glabel_p 就是 偏移量
    void changePro();  // 通过拖动进度条  改变歌曲进度
    void mouseMoveEvent(QMouseEvent*);   // 鼠标移动事件
    void mousePressEvent(QMouseEvent*);  // 鼠标点击事件

private slots:
//    QPushButton  *localbnt;  // 点击录入本地音乐
    void initMysql();
    void initPlayer(); // 用来根据 playf 来改变播放器图标
    void initPro(); // 初始化进度条
    void showPlayMedia();                                  //  将 当前播放歌的名称 在label 的 text 中显示
    void  readmysql(mytablewidget*, QString, QString);   // 初始化音乐队列 (仅在开启播放器的调用)
    QStringList getfileName(const QString& file);  // 将所有的 歌的文件路径都记录到 QstrinList中
    void reinit(int);  // x 初始化
    void boxitem(int i, QString text, QTableWidget*); // 去在音乐列表里(QListWidget) 中实现一个item
    void queuefun(mytablewidget*, QString, QString); // 封装 boxitem
    QString getPName(QString filename); // 歌手名字
    QString getMName(QString filename); // 音乐名字
    QString getname(QString); // 获取当前音乐文件的文件名
    void showlocal(QListWidgetItem*);  // 显示本地音乐
    void localinit(QTableWidget*); // 初始化本地音乐列表
    void insert_nowplay(QString, QString, QString, QString); // 插入到音乐队列中
    void innowplay();   // 将当前播放音乐路径录入
    void songqueue_fun(int, int); // songqueue功能
    void local_fun(int, int);  // local 功能
    void reply(QNetworkReply*);  // 如果net_messager finish  判断是否载入 然后进行js
    void search(QString, int);  // 连接http 搜索歌曲
    void parseJson(QString, int);  // 将歌曲放入 tableWidget
    void reply2(QNetworkReply *reply);  // 如果net_messageer finish  判断是否载入 然后进行js
    void parseJson2(QString json);  //播放音乐解析Json
    void reply3(QNetworkReply *);
    void local_img(QString);     // 同上 只不过是本地的音乐图片 处理
    void play_net_Music(int, int); //点击歌曲tableWidget item 播放音乐
    bool is_net_music(QString); // 判断是不是 net_music
    void initlrc_win(); // 初始化歌词播放窗口
    void buildlrc(QString);
    QPixmap PixmapToRound(QPixmap&, int); // 将图片变成圆角
    QString is_like(QString); // 判断是不是喜欢音乐
    void fun_like(QString, int);  // like_w的显示
    void fun_like_w(int, int); // 关于like_w的点击
    void init_local();  // 本地init
    void init_like();  // 喜爱init
    void songlist_add(QString); // 添加 自定义歌单
    void initsonglist(); //初始化歌单
    void show_List_music(QListWidgetItem *);  // 展示自定义歌单音乐
    void this_songlist(QListWidgetItem *); // 获得 点击的歌单 并存储歌曲
    void show_list_music(QListWidgetItem *); // 显示 该自定义歌单的歌曲


public slots:
    void updatepos();   // 更新 播放时间

signals:
    void beginplay(); // 开始重新构造 进度条
    void file_null(); // 当mfile为空时 触发
    void is_sign_in(); //当登录成功 更新列表

private:
    int X;    // 进度条总长度  防止出现越界情况
    int V;    //音量总长度  防止出现越界情况
    qint64 druntime;//总进度
    qint64  positontime = 0;//当前进度
    QTimer *time; //刷新

    void paintEvent(QPaintEvent* event); // 绘制 进度条
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
