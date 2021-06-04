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
    int w = 250 / 7;
    this ->setColumnWidth(0, w);
    this ->setColumnWidth(1, w * 3);

    for(int i = 2; i <= 4; ++i) this ->setColumnWidth(i, w);
    this ->setStyleSheet("QTableWidget::Item::selected{background: white;}");
}
