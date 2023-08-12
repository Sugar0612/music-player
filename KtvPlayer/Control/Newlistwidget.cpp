#include "Newlistwidget.h"

NewListWidget::NewListWidget(QWidget *parent, QStringList itemList) : QListWidget(parent)
{
    // 关于 mylistwidget的 风格 (qss)
    this -> setStyleSheet("QListWidget{color:rgb(0, 0, 0); background:rgb(232,232,232);border:0px solid black; border-radius: 10px;}"
                                           "QListWidget::Item{height:45px; border: 0px solid white; border-radius: 10px;padding-left:10px;}"
                                           "QListWidget::Item:hover{color:rgb(0, 0, 0);background: rgb(185,211,238); border: 0px solid white;}"
                                           "QListWidget::Item:selected{color:rgb(0, 0, 0); background: rgb(185,211,238); border: 0px solid white;}");
    this ->setFocusPolicy(Qt::NoFocus);


    font.setFamily("幼圆");
    font.setPointSize(12);
    font_L.setFamily("楷体");
    font_L.setPointSize(15);

    this->resize(150, 530);

    for (int i = 0; i < itemList.size(); ++i) {
        AddItem(itemList[i]);
    }
}

void NewListWidget::AddItem(QString name) {
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setText(name);
    item->setFont(font);
}

void NewListWidget::AddItem_(QString name) {
    QListWidgetItem *item = new QListWidgetItem(this);
    item->setText(name);
    item->setFont(font);

    QWidget *BtnWgt = new QWidget();

    NewButton *DeleteBtn = new NewButton(ResPath + "cls.png", ResPath + "cls.png");
    Btns.push_back(DeleteBtn);
    DeleteBtn->setParent(BtnWgt);
    DeleteBtn->move(100, 10);

    this->setItemWidget(item, BtnWgt);
    BtnConnect();
}

void NewListWidget::BtnConnect() {
    for (int i = 0; i < Btns.size(); ++i) {
        disconnect(Btns[i], 0, 0, 0);

        connect(Btns[i], &QPushButton::clicked, this, [=] () {
            QString songname = this->item(i)->text();
            emit DeleteSongGroup(songname);
            this->removeItemWidget(this->item(i));
            this->takeItem(i);
            Btns.erase(Btns.begin() + i, Btns.begin() + i + 1);
            BtnConnect();
        });
    }
}
