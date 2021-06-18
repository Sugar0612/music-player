#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
class mytablewidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit mytablewidget(QWidget *parent = nullptr);
    void hover_row_color(int, QColor);  // 改变相应行的颜色
    void changeColor(int, int); // 获取需要改变颜色的 item 的行数

    int pre_row; // 上一行的颜色

};

#endif // MYTABLEWIDGET_H
