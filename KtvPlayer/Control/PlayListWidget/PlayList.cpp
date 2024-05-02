#include "PlayList.h"

PlayList::PlayList(QWidget *parent)
{
    this->setParent(parent);
    this->resize(200, 200);
    setWindowFlags(Qt::FramelessWindowHint);  // 删除以前的 最大化 最小化 关闭自己写
    this->raise();
    this->hide();
    this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint); //窗口最前面 不会因为点击而隐藏

    listofsong = new NewListWidget(this, QStringList());
    listofsong->setGeometry(0, 0, 150, 200);

    font.setFamily("幼圆");
    font.setPointSize(10);

    connect(listofsong, &NewListWidget::itemClicked, this, &PlayList::listofSongItemClicked);
}

void PlayList::Move(int x, int y) {
    emit RequestSqlBuildList();
    this->move(x, y);
    this->show();
}

QVector4D PlayList::GetPlayListRange() {
    int x = this->x();
    int y = this->y();
    return QVector4D(x, y, x + this->width(), y + this->height());
}

void PlayList::AddItem(QString name) {
    QListWidgetItem *item = new QListWidgetItem(listofsong);
    item->setText(name);
    item->setFont(font);
}

void PlayList::mousePressEvent(QMouseEvent *e) {
    // 点击窗口
    if(e->pos().y() >= 0 && e->pos().y() <= this->height() && e->pos().x() >= 0 && e->pos().x() <= this->width()) {

    }
    QWidget::mousePressEvent(e);
}


void PlayList::GetListofSong(QVector<QString> list) {
    listofsong->clear();
    listofsong->setCurrentRow(0);
    for (int i = 0; i < list.size(); ++i) {
        AddItem(list[i]);
    }
}

void PlayList::listofSongItemClicked(QListWidgetItem *item) {
    TargetName = item->text();
    emit cellClickedItem();
}
