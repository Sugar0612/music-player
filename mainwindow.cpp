#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QHBoxLayout>
#include <QDesktopWidget>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

   this ->setWindowTitle("Sugar music");  //主窗口的运行文件名称

    db = QSqlDatabase::addDatabase("QMYSQL");    // 加载mysql 驱动
    db.setHostName("localhost");  // 主机名
    db.setDatabaseName("mysql"); // 库名
    db.setUserName("root"); //用户名
    db.setPassword("tsy20010612"); // 密码
    db.open();  //打开数据库
    // 以上关于mysql的初始化

    int x = 1025, y = 700;  //记录初始的宽和高
    this ->resize(x, y);   // 设置主界面的宽高
    setWindowFlag(Qt::FramelessWindowHint);  // 删除以前的 最大化 最小化 关闭自己写
    this ->setMinimumSize(QSize(x, y)); // 窗口最小 size



    //播放 框架
    musicW = new PlayWidget(this);
    musicW ->setGeometry(0, 620, 1025, 80);
//    musicW ->setStyleSheet("QWidget{background-color: rgb(248, 248, 255)}");


    //窗口上方按钮的封装
    btnL = new QLabel(this);
    btnL ->setGeometry(0, 0, 1025, 50);
    btnL ->setStyleSheet("QLabel{background-color: rgb(174, 205, 210); border: solid;}");

    // 播放按钮的创建
    playbt = new startbtn(":/coin/start.png", ":/coin/start_c.png", ":/coin/pause.png", ":/coin/pause_c.png");
    playbt->setParent(this);
    playbt ->move(480, 640);

    // 下一首 功能按钮的创建
    nextbt = new mybtn(":/coin/next.png", ":/coin/next_c.png");
    nextbt ->setParent(this);
    nextbt ->move(560, 640);

    // 上一首 功能的按钮的创建
    prevbt = new mybtn(":/coin/prev.png", ":/coin/prev_c.png");
    prevbt ->setParent(this);
    prevbt ->move(400, 640);

    // 音量功能 的按钮创建
    volbt = new startbtn (":/coin/vol.png", ":/coin/vol_c.png", ":/coin/unvol.png", ":/coin/unvol_c.png");
    volbt ->setParent(this);
    volbt ->move(640, 645);


    //minb init
    minb =new mybtn(":/coin/min.png", ":/coin/min_1.png");
    minb ->setParent(this);
    minb ->move(this ->width() - 118, 2);

    // maxb init
    maxb = new mybtn(":/coin/max.png", ":/coin/max_1.png");
    maxb ->move(this ->width() - 78, 2);
    maxb ->setParent(this);

    // clsb init
    clsb = new mybtn(":/coin/cls.png", ":/coin/cls_1.png");
    clsb ->setParent(this);
    clsb ->move(this ->width() - 38, 2);

    //将minb maxb clsb 加入到水平布局中.
    QHBoxLayout * hlay = new QHBoxLayout();    //设置minb maxb clsb 的水平布局让其对于窗口的相对位置不会改变
    hlay ->addWidget(minb);
    hlay ->addWidget(maxb);
    hlay ->addWidget(clsb);


    // 用来显示当前播放歌曲
    musicL = new QLabel(this);
    musicL ->move(200, 500);


    //获得屏幕的分辨率
    QDesktopWidget* desk = QApplication::desktop();
    QRect apprect = desk ->screenGeometry();

    connect(minb, &QPushButton::clicked, [=](){
        showMinimized();
    });   // 点击 minb 按钮 最小化

    connect(maxb, &QPushButton::clicked, [=](){
        if(flag == 0) {
            this ->resize(apprect.width(),apprect.height());
            minb ->move(this ->width() - 115, 0);
            maxb ->move(this ->width() - 75, 0);
            clsb ->move(this ->width() - 35, 0);
            flag = 1;
        } else {
            this ->resize(x, y);
            minb ->move(this ->width() - 115, 0);
            maxb ->move(this ->width() - 75, 0);
            clsb ->move(this ->width() - 35, 0);
            flag = 0;
        }
    });  // 最大化的 按钮

    connect(clsb, &QPushButton::clicked, [=](){
       this ->close();
    }); // 关闭窗口按钮


    // 当点击playbt 时 开始 播放 或者 暂停音乐
    connect(playbt, &QPushButton::clicked, [=] () {
        if (playf == false) {
            Player ->play();
            playf = true;
        } else {
            Player ->pause();
            playf = false;
        }
    });


    // 当点击nextbt 时 播放下一首 音乐
    connect(nextbt, &QPushButton::clicked, [=](){
        int idx = Playlist ->currentIndex();
        if(idx + 1 < filemlist.size()) Playlist ->next();
        else {
            Playlist ->setCurrentIndex(0);
            Player ->play();
        }
    });


    // 当点击prevbt 时 播放上一首 音乐
    connect(prevbt, &QPushButton::clicked, [=](){
        int idx = Playlist ->currentIndex();
        if(idx - 1 >= 0) Playlist ->previous();
        else {
            Playlist ->setCurrentIndex(filemlist.size() - 1);
            Player ->play();
        }
    });

    // 开始初始化音乐播放
     init();
}

// 初始化整个播放列表
void MainWindow::init() {
    Player = new QMediaPlayer();   // 实体化播放列表
    Playlist = new QMediaPlaylist();

    filemlist = getfileName(this ->filem);   // 用来存储载入歌曲的 歌名

    for(int i = 0; i < filemlist.size(); ++i) {
        QString file_ = filemlist[i];   //  获取文件路径的字符串
        addItem(file_);
        Playlist ->addMedia(QUrl::fromLocalFile(this ->filem + "//" + file_));  //  加入到 playmedia 实体播放音乐列表
    }

    Playlist ->setCurrentIndex(0);   // 让playlist 的索引为0开始
//    Player ->setVolume();

    Player ->setPlaylist(Playlist);
    // 将歌曲从 playlist中加载 到player中 ~!!!!

    // 当改变了多媒体 (换歌曲), label ->settext  改变播放的歌曲的名字
    connect(Player, &QMediaPlayer::currentMediaChanged, this, &MainWindow::showPlayMedia);
}

//让QstringList 获得所有选中的歌曲文件路径
QStringList MainWindow::getfileName(const QString& file) {
       QDir dir(file);
       QStringList filelist;
       filelist << "*.mp3";
       QStringList res = dir.entryList(filelist, QDir::Files | QDir::Readable, QDir::Name);
       return res;
}

void MainWindow::addItem(QString& file) {
    int count = ui -> tbw ->rowCount();                                // count 音乐列表的行数
    ui -> tbw ->setRowCount(count + 1);                           // count + 1行 因为要载入新的 歌曲
    QTableWidgetItem* witem = new QTableWidgetItem(file);  // 创建 item
    ui -> tbw ->setItem(count, 0, witem);                              // 用item 载入歌曲
} // TableWidght  addItem

void MainWindow::showPlayMedia() {
    int idx = Playlist ->currentIndex();
    QString textL =  filemlist[idx];
    musicL ->setText(textL);
}  // 改变label 显示新的 歌曲名字







///////////////////////////////////////////////////////////////////////////////////////////////////////////
bool leftflag = false; // 如果 leftflag == true 那么开始移动屏幕
void MainWindow::mousePressEvent(QMouseEvent * e) {
    if(e ->button() == Qt::LeftButton) {
        leftflag = true;
    }
    glbal_p = e ->globalPos() - this ->pos();
} // init mousePressEvent

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    if(leftflag) {
        win_p = e ->globalPos();
        this ->move(win_p - glbal_p);
    }
} // init mouseMoveEvent

MainWindow::~MainWindow()
{
    delete ui;
}

