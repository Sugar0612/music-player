#ifndef CREATE_LIST_H
#define CREATE_LIST_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "mybtn.h"

class create_list : public QWidget
{
    Q_OBJECT
public:
    void initmysql();

    QPushButton *ok, *cancel;
    QLineEdit *name;
    explicit create_list(QWidget *parent = nullptr);

signals:
    void create_ok(QString);
};

#endif // CREATE_LIST_H
