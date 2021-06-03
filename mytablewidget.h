#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QWidget>
#include <QTableWidget>
class mytablewidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit mytablewidget(QWidget *parent = nullptr);

signals:

};

#endif // MYTABLEWIDGET_H
