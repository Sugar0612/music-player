#include "Lrcwgt.h"

LrcWgt::LrcWgt(QWidget *parent) : QWidget(parent)
{
    QFont font;
    font.setFamily("幼圆");
    font.setPointSize(23);
    font.setWeight(30);
    setWindowFlags(Qt::FramelessWindowHint);  // 删除以前的 最大化 最小化 关闭自己写

    this->setWindowTitle("歌词窗口");
    this->setWindowIcon(QIcon(":/Resources/Texture/mymusic.png"));  // 主窗口的图标设置!
    this->resize(500, 80);

    this->setWindowFlags(Qt::FramelessWindowHint); //使得窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true); // 透明显示

    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint); //窗口最前面 不会因为点击而隐藏

    LrcLab = new QLabel(this);
    LrcLab->setGeometry(0, 0, this ->width(), this ->height());
    LrcLab->setFont(font);
    LrcLab->setStyleSheet("QLabel{color: rgb(238, 201, 0);}");
    LrcLab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    LrcLab->setText("暂无歌词");
}

void LrcWgt::mouseMoveEvent(QMouseEvent *e) {
    // 移动窗口
    if(leftflag && e->pos().y() >= 0 && e->pos().y() <= this->height()) {
        win_p = e->globalPos();
        this->move(win_p - glbal_p);
    }
}

void LrcWgt::mousePressEvent(QMouseEvent *e) {
    // 点击窗口
    if(e->button() == Qt::LeftButton && e->pos().y() >= 0 && e->pos().y() <= this->height()) {
        leftflag = true;
        glbal_p = e->globalPos() - this->pos();
    }
}

//透明设置 可以点击窗口了
void LrcWgt::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(0, 0, 0, 100));
    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(0, 0, 0, 100)));

    painter.drawRect(this->rect());

    return QWidget::paintEvent(event);
}

void LrcWgt::SetLrc(QString Lrc) {
    LrcLab->setText(Lrc);
}
