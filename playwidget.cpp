#include "playwidget.h"
#include <QRectF>
PlayWidget::PlayWidget(QWidget *parent) : QWidget(parent)
{

//        this ->setStyleSheet("QWidget{background-color: rgb(128, 128, 128);}");
        setWindowFlag(Qt::FramelessWindowHint);  // 删除以前的 最大化 最小化 关闭自己写
        this ->setFixedSize(1025, 90);

        QPalette Pl; //  调色板
        Pl.setColor(QPalette::WindowText, QColor(0, 0, 0));
        QFont Lf("Courier", 10);


        // 创建 标签
        currL = new QLabel(this);
        allL = new QLabel(this);


        currL ->setAlignment(Qt::AlignCenter);
        allL ->setAlignment(Qt::AlignCenter);
        currL ->setText("00:00");
        allL ->setText("00:00");
        // text 居中

        // 设置 字体
        currL ->setFont(Lf);
        allL ->setFont(Lf);

        // 设置位置 和 大小
        currL ->setGeometry(160, 43,50,50);
        allL ->setGeometry(815,43, 50,50);

        // 设置 颜色
        currL ->setPalette(Pl);
        allL ->setPalette(Pl);

        time = new QTimer(this);
        time ->setInterval(1000);
        connect(time, SIGNAL(timeout), this, SLOT(updatecurr)); // 1秒 触发一次 updatepos();
}

void PlayWidget::paintEvent(QPaintEvent *) {   // 用Qpainter 去绘制进度条
    QPainter Paint(this);
    Paint.setRenderHint(QPainter::SmoothPixmapTransform); // 使用平滑的pixmap变换算法
    Paint.setRenderHint(QPainter::Antialiasing, true);   // 反走样

    QColor baseC(0, 20, 20);    // 进度条基底颜色
    QColor progressC(255,0,0);      // 显示播放了多少的红色进度条
    QColor roundC(255,255,255);  // 白色小球

    // 进度条的基底
    Paint.save();
    Paint.setPen(Qt::NoPen);
    Paint.setBrush(baseC);
    QRectF build = QRectF(220,65,580,6);
    Paint.drawRoundedRect(build, 3, 3);
    Paint.restore();


    // 在基底上 加入红色进度条
    Paint.save();
    Paint.setPen(Qt::NoPen);
    Paint.setBrush(progressC);
    QRectF build_1 = QRectF(220,65, X - 63, 6);
    Paint.drawRoundedRect(build_1, 0, 3);
    Paint.restore();

    // 加入进度条上的 白色圆形
    Paint.save();
    Paint.setPen(Qt::NoPen);
    Paint.setBrush(roundC);
    Paint.drawEllipse(X + 150, 58,20,20);
    Paint.restore();

    // 在`圆形上加入红点
    Paint.save();
    Paint.setPen(Qt::NoPen);
    Paint.setBrush(progressC);
    Paint.drawEllipse(X + 157, 65, 6, 6);
    Paint.restore();
}


// 见头文件
void PlayWidget::mousePressEvent(QMouseEvent *event) {
    if(event->pos().y() > 40 && event->pos().y() < 75 && event ->pos().x() >= 220 && event ->pos().x() < 785)
    {
        int value;
        value = event->pos().x();
        if(value < 220)
        {
            X = 56;
        }
        else if(value > 780)
        {
            X = 635;
        }
        else
        {
            X = value - 150;
        }
        if(X<= 620)
        {
            emit changem();
        }
       update(); // 重绘
       setCursor(Qt::PointingHandCursor);
    }
    else
    {
        event->ignore();  // 忽略鼠标事件
    }
}

// 见头文件
void PlayWidget::mouseMoveEvent(QMouseEvent *event) {
    if (event->pos().y() > 40 && event->pos().y() < 75 && event ->pos().x() >= 220 && event ->pos().x() < 785) {
            int value = event->pos().x();
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
                X =  event->pos().x() - 150;
            }
        }

   emit changem();
   update();
   setCursor(Qt::PointingHandCursor);
}

void PlayWidget::updatecurr() {
    // tcurr, tall  当前播放的时间, 该歌曲总共时间 (毫秒)
    float cnt = (float) tcurr / (float) tall;
    this ->X = cnt * 580 + 56;

    qint64 ctime = this ->tcurr;
    ctime = ctime / 1000;    // 转化成秒
    int cmin = ctime / 60;    // 总分钟
    int csecond = ctime - cmin * 60;  // 总秒

    // 同上
    double atime = tall / 1000;
    int amin = atime / 60;
    int asecond = atime - amin * 60;

    QString current = QString("0%:1%").arg(cmin). arg(csecond);
    QString all = QString("0%:1%").arg(amin) .arg(asecond);

    currL ->setText(current);
    allL ->setText(all);
    update();
}
