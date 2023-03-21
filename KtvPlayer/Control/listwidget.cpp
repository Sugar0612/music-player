#include "listwidget.h"

ListWidget::ListWidget(QWidget *parent, QStringList itemList) : QWidget(parent)
{
    QFont font, font_L;
    font.setFamily("幼圆");
    font.setPointSize(10);
    font_L.setFamily("楷体");
    font_L.setPointSize(15);

    this->resize(150, 530);

    MainWin = new QListWidget(this);
    MainWin->setGeometry(0, 0, this->width(), this->height());

    for (int i = 0; i < itemList.size(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(MainWin);
        items.push_back(item);
        item->setText(itemList[i]);
        item->setFont(font);
    }
}
