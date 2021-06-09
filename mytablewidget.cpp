#include "mytablewidget.h"
#include <QHeaderView>
#include <QDebug>


mytablewidget::mytablewidget(QWidget *parent) : QTableWidget(parent)
{
    this ->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不可编辑
    this ->setShowGrid(false); // 关闭网格
    this ->setFocusPolicy(Qt::NoFocus); //去掉虚线格
    this ->verticalHeader() ->setHidden(true); // 去掉表头行号

    //设置 列宽 和 列count
    this ->setColumnCount(5);


    this ->setColumnWidth(0, 40);  // 爱心
    this ->setColumnWidth(1, 100); // 名字
    this ->setColumnWidth(2, 30);  // 播放
    this ->setColumnWidth(3, 30);  // 删除
    this ->setColumnWidth(4, 30); // 增添
    this ->setMouseTracking(true); //开启捕获鼠标功能
    this ->setSelectionBehavior(QAbstractItemView::SelectRows);   //设置整行选择
    this ->setStyleSheet("QTableWidget::Item::selected{background: rgb(228, 228, 228);}");
    connect(this, &QTableWidget::cellEntered, this, &mytablewidget::changeColor);  // 当鼠标hover itme 这一行 使一整行 都变色
}


void mytablewidget::changeColor(int row, int col) {
    QTableWidgetItem *item = this ->item(pre_row, 0);
    if (item) {
        qDebug() << "pre row is:  "  << pre_row << endl;
        this ->hover_row_color(pre_row, QColor(255, 255, 255));
    }

    this ->hover_row_color(row, QColor(228, 228, 228));
    pre_row = row;
    return;
}


void mytablewidget::hover_row_color(int row, QColor color) {
    for(int i = 0; i < 5; ++i) {
        this ->item(row, i) ->setBackgroundColor(color);
    }
    return;
}



