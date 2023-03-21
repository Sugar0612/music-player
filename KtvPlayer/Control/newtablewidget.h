#ifndef NEWTABLEWIDGET_H
#define NEWTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>

#include <QMouseEvent>
#include <QDebug>

class NewTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    QString GetClickItemText() { return itemText; };
    void SetClickedItemText(QString name) { itemText = name; }
    NewTableWidget();
    QVector2D GetMousePos() {
        return QVector2D(e_x, e_y);
    }

private:
    int e_x = 0, e_y = 0;
    QString itemText = "";
    void mousePressEvent(QMouseEvent *);

signals:
    void ClickedMouse(int, int);
};

#endif // NEWTABLEWIDGET_H
