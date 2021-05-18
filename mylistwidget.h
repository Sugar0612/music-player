#ifndef MYLISTWIDGET_H
#define MYLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
class mylistwidget : public QListWidget
{
    Q_OBJECT
public:
    explicit mylistwidget(QWidget *parent = nullptr);

signals:

};

#endif // MYLISTWIDGET_H
