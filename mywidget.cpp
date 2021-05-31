#include "mywidget.h"
#include <QPainter>

mywidget::mywidget(QWidget *parent) : QWidget(parent)
{
    l = new QLabel(this);
    l ->setGeometry(50, 50, 400, 400);
    l ->setStyleSheet("broder-radius: 30px;}");
}
