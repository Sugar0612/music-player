#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QFont>

class ListWidget : public QWidget
{
    Q_OBJECT
public:
    ListWidget(QWidget *parent, QStringList itemList);

private:

    QListWidget *MainWin = nullptr;
    QVector<QListWidgetItem*> items;
};

#endif // LISTWIDGET_H
