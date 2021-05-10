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

    this ->X = 63; // 初始化 X
    this ->V = 50; // 初始化 V
    time = new QTimer(this);  // 初始化定时器

    //窗口上方按钮的封装
    btnL = new QLabel(this);
    btnL ->setGeometry(0, 0, 1025, 50);
    btnL ->setStyleSheet("QLabel{background-color: rgb(174, 205, 210); border: solid;}");

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
        if (playf == false) {
            Player ->play();
            this ->druntime = Player ->duration();  // 获得总时长
            time->start();
            playf = true;
        } else {
            Player ->pause();
            time ->stop();
            playf = false;
        }
    });


    // 当点击nextbt 时 播放下一首 音乐
    connect(nextbt, &QPushButton::clicked, [=](){
        int idx = Playlist ->currentIndex();
        if(idx + 1 < filemlist.size()) {
            Playlist ->next();
            reinit(); // 初始化
        }
        else {
            Playlist ->setCurrentIndex(0);
            Player ->play();
            reinit(); // 初始化
        }
    });


    // 当点击prevbt 时 播放上一首 音乐
    connect(prevbt, &QPushButton::clicked, [=](){
        int idx = Playlist ->currentIndex();
        if(idx - 1 >= 0) {
            Playlist ->previous();
            reinit(); // 初始化
        }
        else {
            Playlist ->setCurrentIndex(filemlist.size() - 1);
            Player ->play();
            reinit(); // 初始化
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

    // 开始初始化音乐播放
     init();
     // 开始初始化进度条
     initPro();
}

//##########################################
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
    time -> setInterval(1000); // 1000 毫秒触发一次
    connect(time, &QTimer::timeout, this, [=]() {
        updatepos();
    });  // 1秒 触发一次 updatepos();

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

     Player ->setPlaylist(Playlist);
    // 将歌曲从 playlist中加载 到player中 !!!!

    // 当改变了多媒体 (换歌曲), label ->settext  改变播放的歌曲的名字 以及初始化
    connect(Player, &QMediaPlayer::currentMediaChanged, this, [=]() {
        MainWindow::showPlayMedia();
    });
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
    ui -> tbw ->setItem(count, 0, witem);                            // 用item 载入歌曲
} // TableWidght  addItem


void MainWindow::showPlayMedia() {
    reinit();  //初始化
    int idx = Playlist ->currentIndex();
    QString textL =  filemlist[idx];
    musicL ->setText(textL);
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

