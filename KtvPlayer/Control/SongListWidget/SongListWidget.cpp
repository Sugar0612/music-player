#include "SongListWidget.h"

SongListWidget::SongListWidget(QWidget *parent)
{
    this->setParent(parent);

    this->setWindowFlags(Qt::FramelessWindowHint); //使得窗体透明
    this->setAttribute(Qt::WA_TranslucentBackground, true); // 透明显示
    //this->setFixedSize(300, )

    LabFont.setFamily("幼圆");
    LabFont.setPointSize(15);
    ItemFont.setFamily("幼圆");
    ItemFont.setPointSize(11);

    MusicListLab = new QLabel(this);
    MusicListLab->setFont(LabFont);
    //MusicListLab->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    MusicListLab->setText("播放列表");
    MusicListLab->setStyleSheet("QLabel{ background:rgba(238, 233, 233, 180);}");
    MusicListLab->setGeometry(30, 0, 250, 60);

    SongList = new QListWidget(this);
    SongList->setStyleSheet("QListWidget{color:rgba(238, 233, 233, 180); background:rgba(238, 233, 233, 180);border:0px solid black;}"
                                           "QListWidget::Item{height:50px; border: 0px solid white; padding-left:10px;}"
                                           "QListWidget::Item:hover{background: rgba(255, 235, 205, 180); border: 0px solid white;}"
                                           "QListWidget::Item:selected{background: rgba(84, 255, 159, 180); border: 0px solid white;}");
    SongList->setFocusPolicy(Qt::NoFocus);
    SongList->setGeometry(0, MusicListLab->height(), 250, height());

    connect(SongList, &QListWidget::itemDoubleClicked, this, &SongListWidget::ClickItem);
}

void SongListWidget::InsertSongListWgt(QString name, int idx) {
    QListWidgetItem *item = new QListWidgetItem();
    item->setFont(ItemFont);
    SongList->insertItem(idx, item);

    QWidget *BtnWgt = new QWidget();

    NewButton *DeleteBtn = new NewButton(ResPath + "cls.png", ResPath + "cls.png");
    DeleteBtn->setParent(BtnWgt);
    DeleteBtn->move(190, 13);

    QLabel *TxtLab = new QLabel(BtnWgt);
    TxtLab->setFont(ItemFont);
    TxtLab->setText(name);
    TxtLab->setGeometry(0, 0, 140, 40);

    Btns.insert(idx, DeleteBtn);
    BtnConnect();
    SongList->setItemWidget(item, BtnWgt);
}

void SongListWidget::ClickItem(QListWidgetItem *item) {
    int row = SongList->row(item);
    emit RequestPlayMusic(row);
}

void SongListWidget::BtnConnect() {
    for (int i = 0; i < Btns.size(); ++i) {
        disconnect(Btns[i], 0, 0, 0);

        connect(Btns[i], &QPushButton::clicked, this, [=] () {
            emit DeleteListMusic(i);
            SongList->removeItemWidget(SongList->item(i));
            SongList->takeItem(i);
            Btns.erase(Btns.begin() + i, Btns.begin() + i + 1);
            BtnConnect();
        });
    }
}

void SongListWidget::BuildSongListInit(QVector<mst> info) {
    qDebug() << "build list init.";
    for (int i = 0; i < info.size(); ++i) {
        InsertSongListWgt(info[i].name, i);
    }
}

//透明设置 可以点击窗口了
void SongListWidget::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(238, 233, 233, 180));
    painter.setPen(pen);
    painter.setBrush(QBrush(QColor(238, 233, 233, 180)));

    painter.drawRect(this->rect());

    return QWidget::paintEvent(event);
}
