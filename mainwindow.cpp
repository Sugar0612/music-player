#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QFileDialog>
#include <QSqlQuery>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QMessageBox>
#include <QFont>
#include <deque>
#include <QVariant>
#include <algorithm>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Player = new QMediaPlayer();   // 实体化播放列表
    Playlist = new QMediaPlaylist();

    int x = 1025, y = 700;  //记录初始的宽和高
    this ->resize(x, y);   // 设置主界面的宽高
    setWindowFlag(Qt::FramelessWindowHint);  // 删除以前的 最大化 最小化 关闭自己写
    this ->setMinimumSize(QSize(x, y)); // 窗口最小 size

    this ->X = 63; // 初始化 X
    this ->V = 50; // 初始化 V

    this ->setWindowTitle("糖糖音乐");  //主窗口的运行文件名称
    this ->setWindowIcon(QIcon(":/coin/mymusic.png"));  // 主窗口的图标设置!

    // 固定大小
    this ->setFixedSize(x, y);

    time = new QTimer(this);  // 初始化定时器

    //关于tablewidget 上面的名字
    list_col_table = QStringList() << "歌曲" << "作者" << "专辑" << "操作" << "时间";

    initMysql();
    // 以上关于mysql的初始化

    //关于字体
    QFont font, font_L;
    font.setFamily("幼圆");
    font.setPointSize(12);
    font_L.setFamily("楷体");
    font_L.setPointSize(15);

     // musicTab init
     musicTab = new QWidget;


     // lyricsTab init
      lyricsTab = new QWidget;

     // 初始化主界面
     mainmusic = new mytabwidget(this);
     mainmusic ->addTab(musicTab, "歌曲");
     mainmusic ->addTab(lyricsTab, "歌词");

     // 本地音乐的播放列表
     local_w = new mylistwidget(musicTab);

     //窗口上方按钮的封装
     btnL = new QLabel(this);
     btnL ->setGeometry(0, 0, 1025, 70);
     btnL ->setStyleSheet("QLabel{background-color: rgb(174, 205, 210); border: solid;}");
     btnL ->setFont(font_L);
     btnL ->setText("     糖糖音乐");


     search_line = new QLineEdit(btnL); // 搜索框
     search_line ->setGeometry(180, 18, 180, 40);

    //搜索按钮
     btn_search = new mybtn(":/coin/search.png", ":/coin/search.png");
     btn_search ->setParent(btnL);
     btn_search ->move(360, 20);

    // 主窗口 按钮图标
     winicon = new mybtn(":/coin/mymusic.png", ":/coin/mymusic.png");
     winicon ->setParent(this);
     winicon ->move(12, 12);

    // 播放按钮的创建
    playbt = new startbtn(":/coin/start.png", ":/coin/start_c.png", ":/coin/pause.png", ":/coin/pause_c.png");
    playbt->setParent(this);
    playbt ->move(478, 620);

    // 下一首 功能按钮的创建
    nextbt = new mybtn(":/coin/next.png", ":/coin/next_c.png");
    nextbt ->setParent(this);
    nextbt ->move(545, 623);

    // 上一首 功能的按钮的创建
    prevbt = new mybtn(":/coin/prev.png", ":/coin/prev_c.png");
    prevbt ->setParent(this);
    prevbt ->move(415, 623);

    // 音量功能 的按钮创建
    volbt = new startbtn (":/coin/vol.png", ":/coin/vol_c.png", ":/coin/unvol.png", ":/coin/unvol_c.png");
    volbt ->setParent(this);
    volbt ->move(640, 625);

    // 播放列表 按钮
    listbtn = new mybtn(":/coin/list.png", ":/coin/list_c.png");
    listbtn ->setParent(this);
    listbtn ->move(940, 625);

    //minb init
    minb =new mybtn(":/coin/min.png", ":/coin/min_1.png");
    minb ->setParent(this);
    minb ->move(this ->width() - 118, 10);

    // maxb init
    maxb = new mybtn(":/coin/max.png", ":/coin/max_1.png");
    maxb ->move(this ->width() - 78, 10);
    maxb ->setParent(this);

    // clsb init
    clsb = new mybtn(":/coin/cls.png", ":/coin/cls_1.png");
    clsb ->setParent(this);
    clsb ->move(this ->width() - 38, 10);

    //将minb maxb clsb 加入到水平布局中.
    QHBoxLayout * hlay = new QHBoxLayout();    //设置minb maxb clsb 的水平布局让其对于窗口的相对位置不会改变
    hlay ->addWidget(minb);
    hlay ->addWidget(maxb);
    hlay ->addWidget(clsb);

    // "我的音乐"  标签
    mymusic = new mylab("我的音乐", this);
    mymusic ->setGeometry(0, 70, 160, 40);

    // 我的歌单标签
    mylist = new mylab("我的歌单", this);
    mylist ->setGeometry(0, 210, 160, 40);

    // 用来显示当前播放歌曲
    musicL = new QLabel(this);
    musicL ->setGeometry(30, 620,150, 50);
    musicL ->setFont(font);


    // 我的音乐 的列表 窗口
    musiclist = new mylistwidget(this);
    musiclist ->setGeometry(0, 110, 160, 100);
    musiclist ->setFocusPolicy(Qt::NoFocus); // 去掉虚线框
     // 歌单列表
    songlist = new mylistwidget(this);
    songlist ->setGeometry(0, 250, 160, 350);

    //本地音乐列表
    mylocalmusic = new QListWidgetItem(musiclist);
    mylocalmusic ->setText("本地音乐");
    mylocalmusic ->setFont(font);

    // 歌曲的队列
    songqueue = new mylistwidget(this);
    songqueue ->setGeometry(1053, 110, 250, 485);
    songqueue ->setStyleSheet("QListWidget::Item{height: 100px;}");

    // 喜欢的音乐列表
    likemusiclist = new QListWidgetItem(musiclist);
    likemusiclist ->setText("喜爱的音乐");
    likemusiclist ->setFont(font);

    // 显示搜索音乐的窗口
    tab_search = new QTableWidget();
    tab_search ->setColumnCount(5);  // 设置列数
    tab_search ->setHorizontalHeaderLabels(list_col_table);// 设置列数的 名字


    //获得屏幕的分辨率
    QDesktopWidget* desk = QApplication::desktop();
    QRect apprect = desk ->screenGeometry();

    // http init
    net_manager = new QNetworkAccessManager();
    net_request = new QNetworkRequest();
    network_manager2 = new QNetworkAccessManager();
    network_request2 = new QNetworkRequest();

    connect(minb, &QPushButton::clicked, [=](){
        showMinimized();
    });   // 点击 minb 按钮 最小化

    // 最大化的 按钮
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
    });

    // 关闭窗口按钮
    connect(clsb, &QPushButton::clicked, [=](){
       this ->close();
    });


    // 当点击playbt 时 开始 播放 或者 暂停音乐
    connect(playbt, &QPushButton::clicked, [=] () {
        static int i = 0;
        i++;
        if (!Playlist ->isEmpty()) {
            if (1 == i) emit beginplay();
            int idx = Playlist ->currentIndex();
            QString textL =  nowlist[idx];
            musicL ->setText(getMName(textL) + "<br>" + getPName(textL)); //用来显示当前播放歌曲
            this ->setWindowTitle(textL); // 用来 改变窗口的 名称
            if (playf == false && nowlist.size() != 0) {
                Player ->play();
                this ->druntime = Player ->duration();  // 获得总时长
                time ->start();
                playf = true;
            } else {
                Player ->pause();
                time ->stop();
                playf = false;
            }
        } else {
            QMessageBox::information(this, "warning", "请录入音乐", QMessageBox::Ok);  // 提示用户应该录入 音乐
        }
    });


    // 当点击nextbt 时 播放下一首 音乐
    connect(nextbt, &QPushButton::clicked, [=](){
        if (!Playlist ->isEmpty()) {
            int idx = Playlist ->currentIndex();
            if(idx + 1 < nowlist.size()) {
                Player ->pause();   // 暂停
                Playlist ->next();  // 切换
                Player ->play();  // 播放
                initPlayer(); // 初始化播放
                reinit(); // 初始化
            }
            else {
                Playlist ->setCurrentIndex(0);
                Player ->play();
                reinit(); // 初始化
            }
        }
    });


    // 当点击prevbt 时 播放上一首 音乐
    connect(prevbt, &QPushButton::clicked, [=](){
        if (!Playlist ->isEmpty()) {
            int idx = Playlist ->currentIndex();
            if(idx - 1 >= 0) {
                Playlist ->previous();
                initPlayer(); // init 播放btn
                reinit(); // 初始化
            }
            else {
                Playlist ->setCurrentIndex(nowplaylist.size() - 1);
                Player ->play();
                reinit(); // 初始化
            }
        }
    });


    // 当 点击 音量按钮时 volF = false 时 静音    volF = true 时 返回当时 的 音量
    connect(volbt, &QPushButton::clicked, [=] () {
        if (!volF) {
            volF = true;
            bufferVol = this -> V;   // 用来 记录还没有静音时 V 的值
            this ->V = 0;
            Player ->setVolume(V); // 音量变为 0;
            update(); // 重绘 painter
        } else  {
            volF =  false;
            this ->V= bufferVol;  // 将静音前 V 的值还给V
            Player ->setVolume(2 * V);
            update();
        }
    });


    //点击 listbtn 出现 播放列表
    connect(listbtn, &QPushButton::clicked, [=] () {
        if (!is_open) {       // 打开 播放列表
            is_open = true;
            QPropertyAnimation *an  = new QPropertyAnimation(songqueue, "geometry");
            an ->setDuration(200);
            an ->setStartValue(QRect(1053, 108, 253, 488));
            an ->setEndValue(QRect(780, 108, 253, 488));
            an ->setEasingCurve(QEasingCurve::Linear);
            an ->start();
        } else {    // 关闭播放列表
            is_open = false;
            QPropertyAnimation* an = new QPropertyAnimation(songqueue, "geometry");
            an ->setDuration(200);
            an ->setStartValue(QRect(780, 108, 253, 488));
            an ->setEndValue(QRect(1053, 108, 253, 488));
            an ->setEasingCurve(QEasingCurve::Linear);
            an ->start();
        }
    });


    // 当点击 本地音乐item 时显示本地音乐
    connect(musiclist, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showlocal(QListWidgetItem*)));

    //当点击btn_search 开始搜索
    connect(btn_search, &mybtn::clicked, this, [=] () {
        v_hash.clear();
        v_id.clear();
        index = 0;
        for(int i = 1; i <= 10; ++i) {
            search(search_line ->text(), i);
        }
        tab_search ->setParent(mainmusic);
        tab_search ->setGeometry(0, 30, mainmusic ->width(), mainmusic ->height() - 30);
        for(int i = 0; i < 5; ++i) {
            tab_search ->setColumnWidth(i, mainmusic ->width() / 5 - 12);
        }
        tab_search ->show();  // 显示搜索的结果
    });

    connect(net_manager, &QNetworkAccessManager::finished, this, &MainWindow::reply);
    connect(network_manager2, &QNetworkAccessManager::finished, this, &MainWindow::reply2);
    connect(tab_search, &QTableWidget::cellDoubleClicked, this, &MainWindow::play_net_Music);



    // 开始初始化进度条
    initPro();

    //封装box
    innowplay();

}

//###################################################################################################################################

// 初始化进度条
void MainWindow::initPro() {
    QPalette pal; //  调色板
    pal.setColor(QPalette::WindowText,QColor(0,0,0)); // 调颜色
    QFont font("Courier",10); // 设置字体

    liftLabel=new QLabel(this);
    rightLabel=new QLabel(this);
    // 创建 标签

    liftLabel->setAlignment(Qt::AlignCenter);
    rightLabel->setAlignment(Qt::AlignCenter);
    // text 居中

    liftLabel->setGeometry(160, 643,50,50);
    rightLabel->setGeometry(815,643, 50,50);
    // 设置位置 和 大小

    rightLabel->setFont(font);
    liftLabel->setFont(font);
    // 设置 字体

    liftLabel->setPalette(pal);
    rightLabel->setPalette(pal);
    liftLabel ->setText("00:00");
    rightLabel ->setText("00:00");
    // 设置 颜色


    // 定时器
    connect(this, &MainWindow::beginplay, [=] () {
        if(!Playlist ->isEmpty()) {
            time -> setInterval(1000); // 1000 毫秒触发一次
            connect(time, &QTimer::timeout, this, [=]() {
                updatepos();

                // 当Player 播放完最后一首时 让palylist 的index 变成0, Qt的QPlayMedia 真是博大精深
                if (Playlist ->currentIndex() == Playlist ->mediaCount() - 1 && Player ->duration() / 1000 == this ->positontime / 1000) {
                    Playlist ->setCurrentIndex(0);
                }
            });  // 1秒 触发一次 updatepos();
        }
    });
}


void MainWindow::initMysql() {
    db = QSqlDatabase::addDatabase("QMYSQL");    // 加载mysql 驱动
    db.setHostName("localhost");  // 主机名
    db.setDatabaseName("musicbase"); // 库名
    db.setUserName("root"); //用户名
    db.setPassword("tsy20010612"); // 密码
    db.open();  //打开数据库
}

// 用来 单独封装控制 播放
void MainWindow::initPlayer() {
    int _idx = Playlist ->isEmpty() ? 0 : Playlist ->currentIndex();  //获取 播放位置
    QString textL =  nowlist[_idx];
    musicL ->setText(getMName(textL) + "<br>" + getPName(textL)); //用来显示当前播放歌曲
    this ->setWindowTitle(textL); // 用来 改变窗口的 名称

    if (playf == false && filemlist.size() != 0) {
        playbt ->is_play = true;
        playbt ->setIcon(QIcon(":/coin/pause.png"));  // 改变图标
        this ->druntime = Player ->duration();  // 获得总时长
        playf = true;
    }
}

//让QstringList 获得所有选中的歌曲文件路径
QStringList MainWindow::getfileName(const QString& file) {
       QDir dir(file);
       QStringList filelist;
       filelist << "*.mp3";
       QStringList res = dir.entryList(filelist, QDir::Files | QDir::Readable, QDir::Name);
       return res;
}


void MainWindow::showPlayMedia() {
    reinit();  //初始化
    int idx = Playlist ->currentIndex();
    QString textL =  nowlist[idx];
    musicL ->setText(getMName(textL) + "<br>" + getPName(textL));
    this ->setWindowTitle(textL);  // 用来 改变窗口的 名称
}  // 改变label 显示新的 歌曲名字




void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);  // 避免编译器警告
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);  // 使用平滑的pixmap变换算法
    painter.setRenderHint(QPainter::Antialiasing, true);   // 反走样

    QColor baseColor(0,20,20);  // 进度条基底颜色
    QColor inColor(255,0,0);      // 显示播放了多少的红色进度条
    QColor outColor(174, 205, 210);  // 小球

//     qDebug() << "X is : " << this ->X << endl;
    // 进度条的基底
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(baseColor);
    QRectF rect=QRectF(220,665,580,6);
    painter.drawRoundedRect(rect,3,3);
    painter.restore();

    // 在基底上 加入红色进度条
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(inColor);
    QRectF playrect = QRectF(220,665, X - 63, 6);
    painter.drawRoundedRect(playrect,0,3);
    painter.restore();

    // 加入进度条上的 圆形
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(outColor);
    painter.drawEllipse(X + 150, 658,20,20);
    painter.restore();

    // 在圆形上加入红点
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(inColor);
    painter.drawEllipse(X + 157, 665, 6, 6);
    painter.restore();


    // 构造 声音进度条
    QPainter volumeP(this);
    volumeP.setRenderHint(QPainter::SmoothPixmapTransform);  // 使用平滑的pixmap变换算法
    volumeP.setRenderHint(QPainter::Antialiasing, true);   // 反走样

    // 同绘制 进度条一样
    volumeP.save();
    volumeP.setPen(Qt::NoPen);
    volumeP.setBrush(baseColor);
    QRectF baserect = QRectF(670, 635, 50, 4);
    volumeP.drawRoundedRect(baserect, 3, 3);
    volumeP.restore();

    volumeP.save();
    volumeP.setPen(Qt::NoPen);
    volumeP.setBrush(inColor);
    QRectF inrect = QRectF(670, 635, V, 4);
    volumeP.drawRoundedRect(inrect, 0, 3);
    volumeP.restore();

    volumeP.save();
    volumeP.setPen(Qt::NoPen);
    volumeP.setBrush(inColor);
    volumeP.drawEllipse(V + 670, 633, 8, 8);
    volumeP.restore();
}

void MainWindow::updatepos() {
    // druntime: 总进度 positontime: 当前进度
    this ->positontime += 1000; // 每过一秒 加一秒
    float a;
    a = (float)positontime / (float)Player ->duration();
     X = a * 580 + 58;
    if (X > 635) X = 635;

    qint64 time = Player ->duration();  // 毫秒单位
    double secondDouble = time / 1000;  // 转化成秒
    int minint = secondDouble / 60;      // 总分钟
    int secondint = secondDouble - minint * 60;  // 总秒

    double secondtime1 = positontime / 1000;    // 当前播放的总秒数
    int minint1 = secondtime1 / 60;                // 当前播放的分钟
    int secondint1 = secondtime1 - minint1 * 60; // 当前播放的秒

    int curra = minint1 / 10;
    int currb = minint1 % 10;
    int currc = secondint1 / 10;
    int currd = secondint1 % 10;

    int alla = minint / 10;
    int allb = minint % 10;
    int allc = secondint / 10;
    int alld = secondint % 10;
    current = QString("%0%1:%2%3").arg(curra) .arg(currb).arg(currc). arg(currd);
    all = QString("%0%1:%2%3").arg(alla) .arg(allb) .arg(allc) .arg(alld);
    rightLabel->setText(all);
    liftLabel->setText(current);
    update();
}

// 初始化X
void MainWindow::reinit() {
    time ->stop();
    this ->druntime = Player ->duration();   // 获得总时长
    this ->positontime = 0; // 初始化
    this -> X = 63;
    time -> start();
}

// 初始化 listwidgetitem
void MainWindow::boxitem(int i, QString text, QString file, QString file_c, QListWidget* lw, QVector<mybtn*>& b, QVector<QListWidgetItem*>& _i) {
     if(text == "") {
        qDebug() << "null filename!" << endl;
        return;
     }
     QFont font;
     font.setFamily("幼圆");
     font.setPointSize(10);

    QListWidgetItem *item = new QListWidgetItem();  // 新的一首歌
//    lw ->addItem(item);
    lw ->insertItem(i, item);


    QWidget *iwt = new QWidget(lw);      //new widget
    iwt ->resize(253, 100);

    mybtn* tbtn = new mybtn(file, file_c);  // 按钮用来删除
    tbtn ->move(70, 5);

    QLabel* l = new QLabel(iwt);             //显示 歌曲名称
    l ->setGeometry(0, 0, iwt ->width() - 200,  iwt ->height());
    l ->setFont(font);
    l ->setText(getMName(text) + "<br>" + getPName(text));
    tbtn ->setParent(l);

    iwt ->setStyleSheet("QWidget {background: white; border-left: 2px;}");

    QHBoxLayout *layout = new QHBoxLayout;     // 布局
    layout ->addWidget(l);
    layout ->addWidget(tbtn);
    iwt ->setLayout(layout);

    iwt ->setStyleSheet("QWidget::hover{background:rgb(228, 228, 228);}"
                         "QWidget::selected{background:rgb(228,228,228);}");
    lw ->setItemWidget(item, iwt);   // 实现item 和 widget1的结合(显示 控件)

    // 存储 插入
    b.insert(b.begin() + i, tbtn);
    _i.insert(_i.begin() + i, item);
}


// 加入到歌曲队列
void MainWindow::queuefun(QListWidget* lw, QString file, QString m_name) {
    bool is_http = is_net_music(file);
    int idx = Playlist ->isEmpty() ? -1 : Playlist ->currentIndex();
    if(file != "") {
        if(!is_http) Playlist ->insertMedia(idx + 1, QUrl::fromLocalFile(file));// 加入到多媒体 插入到下一首歌后面
        else Playlist ->insertMedia(idx + 1, QUrl(file));
        Player ->setPlaylist(Playlist);
        Playlist ->setCurrentIndex(idx + 1);  // 重新设置 多媒体位置
        time ->setInterval(1000);
        reinit(); // 初始化
        Player ->play();
    }

    boxitem(idx + 1, m_name, ":/coin/delete.png", ":/coin/delete_c.png", lw, vb, vi);  // 加入队列 增加 item

     // 当点击vb[i] 时 删除此时的音乐 在音乐队列 和 mysql中
    if(is_delete) {
        for(int i = 0; i < vb.size(); ++i) {
            connect(vb[i], &QPushButton::clicked, [=] () {
                qDebug() << "new in!" << endl;
                qDebug() << nowplaylist[i] << endl;
                qDebug() << "vb size is:  " << vb.size() << "    row is :  " << i << endl;
                deletenowplay(nowplaylist[i], i);
                return;
            });
            break;
        }
    }
}

// 歌手名字
QString MainWindow::getPName(QString file) {
    bool is_ok = false;
    QString res;
    for(int i = 0; i < file.size(); ++i) {
       if(is_ok) res += file[i];
       if(file[i] == '-') is_ok = true;
       if(i + 1 < file.size() && file[i + 1] == '.') break;
    }
    return res;
}

// 音乐名字
QString MainWindow::getMName(QString file) {
    QString res;
    for(int i = 0; i < file.size(); ++i) {
        res += file[i];
        if(i + 1 < file.size() && file[i + 1] == '-') break;
    }
    return res;
}

void MainWindow::showlocal(QListWidgetItem* i) {
    // 将mysql中的音乐路径打印出来
    QSqlQuery selectq;
    selectq.exec("select name from localmusic;");
    selectq.next();

    // 读入文件路径 开始初始化本地音乐库
    if(!selectq.value(0).value<QString>().isNull()) this ->filem = selectq.value(0).value<QString>();

//    qDebug() << "filem is :   "  << this ->filem << endl;
    int idx = musiclist ->row(i);  //点击的是我的音乐的第几行item （共两行）
    if (idx == 0) {  // idx == 0 说明点击的时 本地音乐
        filemlist = getfileName(this ->filem);   // 用来存储载入歌曲的 歌名
        local_w ->setGeometry(0, 0, musicTab->width(), musicTab->height());
        local_w ->setStyleSheet("QListWidget::Item{height: 60px;}");
        localinit(local_w); // init QlistWidget
        local_w ->show();
        tab_search ->hide();
    }
}

// init 本地音乐 当点击item时 播放 那个item 对应的歌曲
void MainWindow::localinit(QListWidget* lw) {
    for(int i = 0; i < filemlist.size(); ++i) {
        boxitem(i, filemlist[i], ":/coin/begin.png", ":/coin/begin.png", lw, l_vb, l_vi);
    }  // 录入本地音乐text

    // 点击播放切换歌曲
    for(int i = 0; i < filemlist.size(); ++i) {
        connect(l_vb[i], &mybtn::clicked, [=] () {
            l_updown(l_vb[i]);  // 按钮跳动
            insert_nowplay(this ->filem + "/" + filemlist[i], filemlist[i]);  // 插入到数据库 音乐队列中
            playf = false; //准备初始化 播放按钮
            initPlayer();   // 初始化播放按钮
        });
    }
}

// 按钮跳动动作
void MainWindow::l_updown(mybtn* btn) {
    // 向下
    QPropertyAnimation *an  = new QPropertyAnimation(btn, "geometry");
    an ->setDuration(200);
    an ->setStartValue(QRect(btn->x(), btn->y(), btn->width(), btn->height()));
    an ->setEndValue(QRect(btn->x(), btn->y() + 5, btn->width(), btn->height()));
    an ->setEasingCurve(QEasingCurve::OutBounce);  // 弹跳方式
    an ->start();

    // 向上复原
    QPropertyAnimation *a  = new QPropertyAnimation(btn, "geometry");
    a ->setDuration(200);
    a ->setStartValue(QRect(btn->x(), btn->y() + 5, btn->width(), btn->height()));
    a ->setEndValue(QRect(btn->x(), btn->y(), btn->width(), btn->height()));
    a ->setEasingCurve(QEasingCurve::OutBounce); // 弹跳方式
    a ->start();
}

// 从数据库读出当前播放音乐的路径
void MainWindow::innowplay() {
    // 将mysql中的音乐路径打印出来
    QSqlQuery selectq;
    selectq.exec("select * from nowplay;");
    // 开始导入 音乐队列(路径 和 歌名)
    while (selectq.next()) {
        this ->nowplaylist.push_back(selectq.value(0).value<QString>());
        this ->nowlist.push_back(selectq.value(1).value<QString>());
        qDebug() << "nowplayinit:   " << selectq.value(0).value<QString>() << "    "  << selectq.value(1).value<QString>() << endl;

    }


    //初始化播放列表
    for(int i = 0; i < nowplaylist.size(); ++i) {
        readmysql(songqueue, nowplaylist[i], nowlist[i]); // 开始将歌曲一个一个的加入播放队列
    }

    // 当音乐改变初始化 进度条 以及 显示音乐标签
    connect(Player, &QMediaPlayer::currentMediaChanged, this, [=]() {
        reinit();
        MainWindow::showPlayMedia();
     });
}

 // 插入到数据库 和 音乐队列中
void MainWindow::insert_nowplay(QString name, QString m_name) {
    bool is_http = is_net_music(name);
    // 如果播放列表已经存在这首歌 那么只需要完成相对应的插入操作
    if (nowlist.count(m_name) != 0) {
        int idx = std::find(nowlist.begin(), nowlist.end(), m_name) - nowlist.begin(); // 找到这首歌的索引
        int c_idx = Playlist ->currentIndex() > idx ? Playlist ->currentIndex() - 1 : Playlist ->currentIndex(); // 当前播放的索引

        if(Playlist ->currentIndex() == idx) return; // 如果你想插入的歌就是 现在的歌 那么不需要插入

        // 重新插入歌曲
        if(idx == 0 && c_idx == Playlist ->mediaCount() - 2) {
            Playlist ->setCurrentIndex(Playlist ->currentIndex() - 1);
            if(!is_http) Playlist ->addMedia(QUrl::fromLocalFile(nowplaylist[idx]));
            else Playlist ->addMedia(QUrl(nowplaylist[idx]));
            Playlist ->removeMedia(0);
            Player ->play();    // 就是 qt player 这个机制过于博大精深 我吐了真的.......不得不这样写了
        } else {
            Playlist ->removeMedia(idx);
            if(!is_http) Playlist ->insertMedia(c_idx + 1, QUrl::fromLocalFile(nowplaylist[idx]));
            else Playlist ->insertMedia(idx + 1, QUrl(nowplaylist[idx]));
            Playlist ->setCurrentIndex(c_idx + 1);
            Player ->play();
        }

        // 重新插入 item
        songqueue ->takeItem(idx);
        vb.erase(vb.begin() + idx, vb.begin() + idx + 1);
        vi.erase(vi.begin() + idx, vi.begin() + idx + 1);
        boxitem(c_idx + 1, nowlist[idx], ":/coin/delete.png", ":/coin/delete_c.png", songqueue, vb, vi);  // 加入队列 增加 item

        //重新插入nowlist nowplaylist
        QString nowlist_s = nowlist[idx];
        QString nowplaylist_s = nowplaylist[idx];
        nowlist.erase(nowlist.begin() + idx, nowlist.begin() + idx + 1);
        nowplaylist.erase(nowplaylist.begin() + idx, nowplaylist.begin() + idx + 1);

        nowlist.insert(nowlist.begin() + c_idx + 1, nowlist_s);
        nowplaylist.insert(nowplaylist.begin() + c_idx + 1, nowplaylist_s);
        return;
    }

    // 如果is_delete = false 那么调用readmysql 里面的deletenowplay 否则调用queuefun里面的deletenowplay
    is_delete = true;
    // 插入到数据库中
    QSqlQuery sql;
    QString sfile = QString("insert into nowplay values (\"" + name + "\",\"" + m_name + "\");"); // 插入从本地音乐目录路径
    sql.exec(sfile); // 执行
    if(nowlist.count(m_name) == 0) {
        int idx = Playlist ->currentIndex(); // 插入到此时播放音乐的后面
        nowplaylist.insert(nowplaylist.begin() + idx + 1, name);
        nowlist.insert(nowlist.begin() + idx + 1, m_name);
        queuefun(songqueue, name, m_name); //插入新的歌曲
    }
}

// 获取当前音乐文件的文件名
QString MainWindow::getname(QString file) {
    QString ans;
    for(int i = file.size() - 1; i >= 0; --i) {
        if(file[i] != '\\' && file[i] != '/') ans.push_front(file[i]);
        else break;
    }
    return ans;
}

// 初始化音乐队列 (仅在开启播放器的调用)
void MainWindow::readmysql(QListWidget* lw, QString file, QString name) {
    int idx = Playlist ->isEmpty() ? 0 : Playlist ->mediaCount();
    is_net = is_net_music(file); // 判断是不是 网络音乐
    if(file != "") {
        if(!is_net) Playlist ->addMedia(QUrl::fromLocalFile(file));// 加入到多媒体 插入到下一首歌后面
        else Playlist ->addMedia(QUrl(file));
        Playlist ->setCurrentIndex(0);  // 重新设置 多媒体位置
        Player ->setPlaylist(Playlist);
        reinit(); // 初始化
    }

    boxitem(idx, name, ":/coin/delete.png", ":/coin/delete_c.png", lw, vb, vi);  // 加入队列 增加 item

     // 当点击vb[i] 时 删除此时的音乐 在音乐队列 和 mysql中
    if(!is_delete) {
        for(int i = 0; i < vb.size(); ++i) {
            connect(vb[i], &QPushButton::clicked, [=] () {
                qDebug() << "old in!" << endl;
                qDebug() << "vb size is:  " << vb.size() << "    row is :  " << i << endl;
                qDebug() << nowplaylist[i] << endl;
                deletenowplay(nowplaylist[i], i);
                return;
            });
        }
    }
}


void MainWindow::deletenowplay(QString file, int row) {
    if (vb.size() <= row) {
        return;
    }
    Playlist ->removeMedia(row);
    nowplaylist.erase(nowplaylist.begin() + row, nowplaylist.begin() + row + 1);
    nowlist.erase(nowlist.begin() + row, nowlist.begin() + row + 1);

    vb[row] = nullptr;
    vb.erase(vb.begin() + row, vb.begin() + row + 1);
    vi.erase(vi.begin() + row, vi.begin() + row + 1);

    this ->songqueue ->takeItem(row);

    QSqlQuery sql;
    sql.exec("delete from nowplay where music = '" + file + "'; ");
    return;
}

// 判断是否是网络音乐
bool MainWindow::is_net_music(QString file) {
    QString buf;
    for(int i = 0; i < file.size(); ++i) {
         buf += file[i];
        if(buf == "http") return true;
    }
    return false;
}


// 搜索 text 通过 http网络, 给予finish 相应
void MainWindow::search(QString text, int idx) {
    QString net_search = QString("http://mobilecdn.kugou.com/api/v3/search/song?format=json&keyword=%1&page=%2&pagesize=18a").arg(text).arg(idx);
    net_request ->setUrl(QUrl(net_search));
    net_manager ->get(*net_request);
}

// net_manager finish 响应reply 开始在tableWidget 上显示
void MainWindow::reply(QNetworkReply* re) {
    QVariant status_code = re ->attribute(QNetworkRequest::HttpStatusCodeAttribute);

    if (re ->error() == QNetworkReply::NoError) {
        QByteArray bytes = re ->readAll();
        QString res(bytes);
        parseJson(res, index);
        index += 20;
    } else {
        qDebug() << "error!" << endl;
    }
}

// 解析 json 显示到 tablewidget上
void MainWindow::parseJson(QString json, int idx) {
        QString songname_original; //歌曲名
            QString singername;        //歌手
            QString hashStr;           //hash
            QString album_name;        //专辑
            int duration;          	   //时间
            QByteArray byte_array;
            QJsonParseError json_error;
            QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json), &json_error);
            if (json_error.error == QJsonParseError::NoError)
            {
                if (parse_doucment.isObject())
                {
                    QJsonObject rootObj = parse_doucment.object();
                    if (rootObj.contains("data"))
                    {
                        QJsonValue valuedata = rootObj.value("data");
                        if (valuedata.isObject())
                        {
                            QJsonObject valuedataObject = valuedata.toObject();
                            if (valuedataObject.contains("info"))
                            {
                                QJsonValue valueArray = valuedataObject.value("info");
                                if (valueArray.isArray())
                                {
                                    QJsonArray array = valueArray.toArray();
                                    int size = array.size();
                                    for (int i = idx, j = 0; i < size + idx && j < size; i++, ++j)
                                    {
                                        QJsonValue value = array.at(j);
                                       if (value.isObject())
                                       {
                                            QJsonObject object = value.toObject();
                                            if (object.contains("songname_original"))//歌曲名
                                            {
                                                QJsonValue AlbumID_value = object.take("songname_original");
                                                if (AlbumID_value.isString())
                                                {
                                                    songname_original = AlbumID_value.toString();
                                                }
                                            }
                                            if (object.contains("singername"))//歌手
                                            {
                                                QJsonValue AlbumID_value = object.take("singername");
                                                if (AlbumID_value.isString())
                                                {
                                                    singername = AlbumID_value.toString();
                                                }
                                            }
                                            if (object.contains("album_name"))//专辑
                                            {
                                                QJsonValue AlbumID_value = object.take("album_name");
                                                if (AlbumID_value.isString())
                                                {
                                                    album_name = AlbumID_value.toString();
                                                }
                                            }
                                            if (object.contains("hash")) //hash
                                            {
                                                QJsonValue FileHash_value = object.take("hash");
                                                if (FileHash_value.isString())
                                                {
                                                    hashStr = FileHash_value.toString();
                                                    //用Vector保存每首歌曲的hash
                                                    v_hash.push_back(FileHash_value.toString());
                                                }
                                            }
                                            if (object.contains("album_id"))
                                            {
                                                QJsonValue FileHash_value = object.take("album_id");
                                                if (FileHash_value.isString())
                                                {
                                                    //用Vector保存每首歌曲的album_id
                                                    v_id.push_back(FileHash_value.toString());
                                                }
                                            }
                                            if (object.contains("duration"))//时长
                                            {
                                               QJsonValue AlbumID_value = object.take("duration").toInt();
                                               duration = AlbumID_value.toInt();
                                            }
                                            //将解析出的内容放到列表中
                                            tab_search ->setRowCount(i + 1);
                                            tab_search ->setItem(i,0,new QTableWidgetItem(songname_original));
                                            //文字居中
                                            tab_search->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);


                                            tab_search ->setItem(i,1,new QTableWidgetItem(singername));
                                            tab_search ->item(i,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                                            tab_search ->setItem(i,2,new QTableWidgetItem(album_name));
                                            tab_search ->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

                                            QString time = QString("%1:%2").arg(duration/60).arg(duration%60);
                                            tab_search ->setItem(i,4,new QTableWidgetItem(time));
                                            tab_search ->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                                      }
                                 }
                            }
                        }
                    }
                }
            }
        }
}

// 播放歌曲发出信号
void MainWindow::play_net_Music(int row, int col) {
    //歌曲请求 row 是行号
    QString KGAPISTR1 =QString("http://www.kugou.com/yy/index.php?r=play/getdata"
    "&hash=%1&album_id=%2&_=1497972864535").arg(v_hash.at(row)) .arg(v_id.at(row));
    network_request2->setUrl(QUrl(KGAPISTR1));
    //这句话很重要，我们手动复制url放到浏览器可以获取json，但是通过代码不行，必须加上下面这句才可以
    network_request2->setRawHeader("Cookie","kg_mid=2333");
    network_request2->setHeader(QNetworkRequest::CookieHeader, 2333);
    network_manager2->get(*network_request2);
}


void MainWindow::reply2(QNetworkReply *re)  // 如果net_messageer finish  判断是否载入 然后进行js
{
    //获取响应的信息，状态码为200表示正常
         QVariant status_code = re->attribute(QNetworkRequest::HttpStatusCodeAttribute);

        //无错误返回
        if(re->error() == QNetworkReply::NoError)
        {
            QByteArray bytes = re->readAll();  //获取字节
            QString result(bytes);  //转化为字符串
            parseJson2(result);//解析json
        }
        else
        {
            //处理错误
            qDebug()<<"歌曲播放失败";
        }
}


//解析 json
void MainWindow::parseJson2(QString json) {
    QString audio_name;//歌手-歌名
    QString play_url;//播放地址
    QString img;
    QByteArray byte_array;
    QJsonParseError json_error;
    QJsonDocument parse_doucment = QJsonDocument::fromJson(byte_array.append(json), &json_error);
    if(json_error.error == QJsonParseError::NoError) {
       if(parse_doucment.isObject())
       {
           QJsonObject rootObj = parse_doucment.object();
           if(rootObj.contains("data"))
           {
               QJsonValue valuedata = rootObj.value("data");
               if(valuedata.isObject())
               {
                   QJsonObject valuedataObject = valuedata.toObject();
                   QString play_urlStr("");
                   if(valuedataObject.contains("play_url"))
                   {
                       QJsonValue play_url_value = valuedataObject.take("play_url");
                       if(play_url_value.isString())
                       {
                           play_urlStr = play_url_value.toString();      //歌曲的url
                           if(play_urlStr!="")
                           {
                               qDebug() << "line 1039: " << play_urlStr << endl;
                               net_file = play_urlStr;
//                               Player ->setMedia(QUrl(play_urlStr));
//                               Player->play();
                           }
                       }
                   }
                   if(valuedataObject.contains("audio_name"))
                   {
                       QJsonValue play_name_value = valuedataObject.take("audio_name");
                       if(play_name_value.isString())
                       {
                           QString audio_name = play_name_value.toString();    //歌曲名字
                           if(audio_name!="")
                           {
                               //显示
                               qDebug()<<audio_name;
                               net_name = audio_name;
                           }
                       }
                   }
                   insert_nowplay(net_file, net_name);  //将网络歌曲插入到队列
               }
                    //下一篇的歌词获取也是在这里添加代码
                    //图片显示代码在这里添加
               else {
                    qDebug()<<"出错";
                }
           }
       }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindow::mousePressEvent(QMouseEvent * e) {
    // 音量进度条
    if (e ->pos().x() >= 670 && e ->pos().x() < 720 && e ->pos().y() >= 635 && e ->pos().y() <= 640)  {
        V = e ->pos().x() - 670;
        Player ->setVolume(V * 2);   // 调整音量
        if (this ->volF) {
           volF = false;
           volbt->is_play = false;
           volbt ->setIcon(QIcon(":/coin/vol.png"));
        }
        update();
    }

    //点击进度条
    if( e->pos().y() > 640 && e->pos().y() < 675 && e ->pos().x() >= 220 && e ->pos().x() < 785)
    {
            int value;
            value = e->pos().x();
            time ->stop();
            if(value < 220)
            {
                X = 56;
            }
            else if (value > 780)
            {
                X = 635;
            }
            else
            {
                X = value - 150;
            }
            if(X <= 620)
            {
                changePro();
            }
           update(); // 重绘
           setCursor(Qt::PointingHandCursor);
           if(playf) time ->start();
    }

    // 点击窗口
    if(e ->button() == Qt::LeftButton && e ->pos().y() >= 0 && e ->pos().y() < 50) {
        leftflag = true;
    }
    glbal_p = e ->globalPos() - this ->pos();
} // init mousePressEvent

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    // 音量进度条
    if (e ->pos().x() >= 670 && e ->pos().x() < 720 && e ->pos().y() >= 635 && e ->pos().y() <= 640)  {
        V = e ->pos().x() - 670;
        Player ->setVolume(V * 2);   // 调整音量
        if (this ->volF) {
           volF = false;
           volbt->is_play = false;
           volbt ->setIcon(QIcon(":/coin/vol.png"));
        }
        update();
    }

    // 移动进度条
    if (e->pos().y() > 640 && e->pos().y() < 675 && e ->pos().x() >= 220 && e ->pos().x() < 785) {
        time ->stop();
        int value = e->pos().x();
        if (value < 220)
        {
            X = 56;
        }
        else if (value > 780)
        {
            X = 635;
        }
        else
        {
            X =  e->pos().x() - 150;
        }

        changePro();
        update();
        setCursor(Qt::PointingHandCursor);
        if(playf) time ->start();
    }

    // 移动窗口
    if(leftflag && e ->pos().y() >= 0 && e ->pos().y() < 50) {
        win_p = e ->globalPos();
        this ->move(win_p - glbal_p);
    }
} // init mouseMoveEvent

// 通过拖动进度条  改变歌曲进度
void MainWindow::changePro() {
    this ->positontime = (float)((X - 56) / (float)580.0) * Player ->duration();  //根据鼠标的坐标 反推出此时 音乐的进度
    Player ->setPosition(this ->positontime);       // 改变音乐的进度
    double secondtime1 = positontime / 1000;    // 当前播放的总秒数
    int minint1 = secondtime1 / 60;                // 当前播放的分钟
    int secondint1 = secondtime1 - minint1 * 60; // 当前播放的秒

    int curra = minint1 / 10;
    int currb = minint1 % 10;
    int currc = secondint1 / 10;
    int currd = secondint1 % 10;
    current = QString("%0%1:%2%3").arg(curra) .arg(currb).arg(currc). arg(currd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

