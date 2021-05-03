#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QMYSQL");    // 加载mysql 驱动
    db.setHostName("localhost");  // 主机名
    db.setDatabaseName("mysql"); // 库名
    db.setUserName("root"); //用户名
    db.setPassword("tsy20010612"); // 密码
    db.open();  //打开数据库
    // 以上关于mysql的初始化


    QHBoxLayout * hlay = new QHBoxLayout();    //设置minb maxb clsb 的水平布局让其对于窗口的相对位置不会改变
    int x = 1300, y = 850;  //记录初始的宽和高
    this ->resize(x, y);   // 设置主界面的宽高
    setWindowFlag(Qt::FramelessWindowHint);  // 删除以前的 最大化 最小化 关闭自己写

    minb =new mybtn(":/coin/min.png", ":/coin/min_1.png");
    minb ->setParent(this);
    minb ->move(this ->width() - 115, 0);

    maxb = new mybtn(":/coin/max.png", ":/coin/max_1.png");
    maxb ->move(this ->width() - 75, 0);
    maxb ->setParent(this);

    clsb = new mybtn(":/coin/cls.png", ":/coin/cls_1.png");
    clsb ->setParent(this);
    clsb ->move(this ->width() - 35, 0);

    //将minb maxb clsb 加入到水平布局中
    hlay ->addWidget(minb);
    hlay ->addWidget(maxb);
    hlay ->addWidget(clsb);

    connect(minb, &QPushButton::clicked, [=](){
        showMinimized();
    });

    connect(maxb, &QPushButton::clicked, [=](){
        if(flag == 0) {
            showFullScreen();
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

    connect(clsb, &QPushButton::clicked, [=](){
       this ->close();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

