#include "newtablewidget.h"

NewTableWidget::NewTableWidget()
{
    this->setShowGrid(false); // 关闭网格
    this->setFocusPolicy(Qt::NoFocus); //去掉虚线格
    this->verticalHeader()->setHidden(true); // 去掉表头行号
    this->setStyleSheet("QTableWidget::Item::selected{background: white;}"
                               "QHeaderView::section{border: 0px solid white};"
                               "QTableWidget::Item::hover{background: black;}");
}

void NewTableWidget::mousePressEvent(QMouseEvent *e) {
    e_x = e->pos().x();
    e_y = e->pos().y();
    emit ClickedMouse(e_x, e_y);
    QTableWidget::mousePressEvent(e);
}
