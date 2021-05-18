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

    time = new QTimer(this);  // 初始化定时器

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

    //获得屏幕的分辨率
    QDesktopWidget* desk = QApplication::desktop();
    QRect apprect = desk ->screenGeometry();

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
        if (!Playlist ->isEmpty()) {
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
                qDebug() << "IN" << endl;
                Player ->pause();   // 暂停
                Playlist ->next();  // 切换
                Player ->play();  // 播放
                initPlayer(); // 初始化播放
                reinit(); // 初始化
            }
            else {
                qDebug() << "IN" << endl;
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
                Playlist ->setCurrentIndex(filemlist.size() - 1);
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
            an ->setEndValue(QRect(800, 108, 253, 488));
            an ->setEasingCurve(QEasingCurve::Linear);
            an ->start();
        } else {    // 关闭播放列表
            is_open = false;
            QPropertyAnimation* an = new QPropertyAnimation(songqueue, "geometry");
            an ->setDuration(200);
            an ->setStartValue(QRect(800, 108, 253, 488));
            an ->setEndValue(QRect(1053, 108, 253, 488));
            an ->setEasingCurve(QEasingCurve::Linear);
            an ->start();
        }
    });

    // 当点击 本地音乐item 时显示本地音乐
    connect(musiclist, SIGNAL(itemClicked(QListWidgetItem*)),this, SLOT(showlocal(QListWidgetItem*)));


    // 开始初始化进度条
    initPro();

    //封装box
    innowplay();

}

//####################################################################################

// 初始化进度条
void MainWindow::initPro() {
    qDebug() << "pro" << endl;
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


// 初始化整个播放列表
void MainWindow::init() {

//    filemlist = getfileName(this ->filem);   // 用来存储载入歌曲的 歌名
//    innowplay(); // 录入当前播放歌曲的路径

//    for(int i = 0; i < nowplaylist.size(); ++i) {
//        QString file_ = nowplaylist[i];   //  获取文件路径的字符串
//        Playlist ->addMedia(QUrl::fromLocalFile(file_));  //  加入到 playmedia 实体播放音乐列表
//    }

      if(nowplaylist.size() != 0) {
            Playlist ->setCurrentIndex(0);   // 让playlist 的索引为0开始

            Player ->setPlaylist(Playlist);
        // 将歌曲从 playlist中加载 到player中 !!!!

        // 当改变了多媒体 (换歌曲), label ->settext  改变播放的歌曲的名字 以及初始化
        connect(Player, &QMediaPlayer::currentMediaChanged, this, [=]() {
            MainWindow::showPlayMedia();
         });
      }
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
    qDebug() << textL << "  " << getPName(textL) << endl;
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

    /////////////////////////////////////////////
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
void MainWindow::boxitem(int i, QString text, QString file, QString file_c, QListWidget* lw, QMap<int, mybtn*>& b, QMap<int, QListWidgetItem*>& _i) {
     if(text == "") {
        qDebug() << "null filename!" << endl;
        return;
     }
     QFont font;
     font.setFamily("幼圆");
     font.setPointSize(10);

    QListWidgetItem *item = new QListWidgetItem();  // 新的一首歌
    lw ->addItem(item);


    QWidget *iwt = new QWidget(lw);      //new widget
    iwt ->resize(253, 100);

    mybtn* tbtn = new mybtn(file, file_c);  // 按钮用来删除
    tbtn ->move(100, 4);

    QLabel* l = new QLabel(iwt);             //显示 歌曲名称
    l ->setGeometry(0, 0, iwt ->width() - 150,  iwt ->height());
    l ->setFont(font);
    l ->setText(getMName(text) + "<br>" + getPName(text));

    iwt ->setStyleSheet("QWidget {background: white; border-left: 2px;}");

    QHBoxLayout *layout=new QHBoxLayout;     //  布局
    layout ->addWidget(l);
    layout ->addWidget(tbtn);
    iwt ->setLayout(layout);

    iwt ->setStyleSheet("QWidget::hover{background:rgb(228, 228, 228);}"
                         "QWidget::selected{background:rgb(228,228,228);}");
    lw ->setItemWidget(item, iwt);   // 实现item 和 widget1的结合(显示 控件)

    // 存储
    b[i] = tbtn;
    _i[i] = item;
}


// 加入到歌曲队列
void MainWindow::queuefun(QListWidget* lw, QString file) {
    int cnt = lw ->count(); // 获取总行数 也是下一个item 插入的行数
    if(file != "") {
        int idx = Playlist ->isEmpty() ? 0 : Playlist ->mediaCount();
        Playlist ->addMedia(QUrl::fromLocalFile(file)); // 加入到多媒体
        Playlist ->setCurrentIndex(idx);  // 重新设置 多媒体位置
        reinit(); // 初始化
        Player ->play();
        QString mname = getname(file); // 获取歌曲名字
        boxitem(cnt, mname, ":/coin/delete.png", ":/coin/delete_c.png", lw, vb, vi);  // 加入队列 增加 item

    }

    for(int i = 0; i < vb.size(); ++i) {
        connect(vb[i], &QPushButton::clicked, [=] () {
            int idx = lw ->row(vi[i]);
            // 删除item 以及歌曲
            lw ->takeItem(idx);
            Playlist ->removeMedia(idx);
            nowlist.erase(nowlist.begin() + idx, nowlist.begin() + idx + 1);
            if(nowlist.empty()) Player->stop();
            showPlayMedia();
            vi[i] = nullptr;
            vb[i] = nullptr;
        });
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
            Player ->stop(); // 先停止音乐
            l_updown(l_vb[i]);  // 按钮跳动
            insert_nowplay(this ->filem + "/" + filemlist[i]);  // 插入到数据库 音乐队列中
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
    // 开始导入 音乐队列
    while (selectq.next()) {
        this ->nowplaylist.push_back(selectq.value(0).value<QString>());
    }
    //将歌名导入
    for(int i = 0; i < nowplaylist.size(); ++i) {
        QString res = getname(nowplaylist[i]);
        nowlist.push_back(res);
        buflist.push_back(res);
    }

    //初始化播放列表
    for(int i = 0; i < nowplaylist.size(); ++i) {
        readmysql(songqueue, nowplaylist[i]); // 开始将歌曲一个一个的加入播放队列
    }
}

 // 插入到数据库 和 音乐队列中
void MainWindow::insert_nowplay(QString name) {
    // 插入到数据库中
    QSqlQuery sql;
    QString sfile = QString("insert into nowplay values (\"" + name + "\");"); // 插入从本地音乐目录路径
    sql.exec(sfile); // 执行
    QString mname = getname(name); // 获取歌曲名字
    if(nowlist.count(mname) == 0) {
        nowlist .push_back(mname);
        queuefun(songqueue, name); // 插入新的歌曲
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

void MainWindow::readmysql(QListWidget* lw, QString file) {
    static int i = 0; // 防止多次启动time
    i++; // 当i 大于 1 时不启动time
    int cnt = lw ->count(); // 获取总行数 也是下一个item 插入的行数
    if(file != "") {
        int idx = Playlist ->isEmpty() ? 0 : Playlist ->currentIndex();
        Playlist ->addMedia(QUrl::fromLocalFile(file)); // 加入到多媒体
        Playlist ->setCurrentIndex(idx);  // 重新设置 多媒体位置
        Player ->setPlaylist(Playlist);   //  重新载入 Player
        if (i == 1) emit beginplay(); // 发出信号重新 构造进度条
        QString mname = getname(file); // 获取歌曲名字
        boxitem(cnt, mname, ":/coin/delete.png", ":/coin/delete_c.png", lw, vb, vi);  // 加入队列 增加 item

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

