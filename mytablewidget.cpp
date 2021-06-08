#include "mytablewidget.h"
#include <QHeaderView>
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
    this ->setStyleSheet("QTableWidget::Item::selected{background: white;}");
}
