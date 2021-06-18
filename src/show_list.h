#ifndef SHOW_LIST_H
#define SHOW_LIST_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QString>
#include <QtDebug>
#include "sign_in_win.h"
#include "mylistwidget.h"

class show_list : public QWidget
{
    Q_OBJECT
public:
    explicit show_list(int id, QWidget *parent = nullptr);


    int user_id; // 用户id
    QSqlDatabase db; // connect sql db
    mylistwidget *list;


    void initMysql();
    void show_song_list(); // 展示 所有的歌单
    void item_show(QListWidgetItem *); // 传递item
signals:
    void return_item(QListWidgetItem *);
};

#endif // SHOW_LIST_H
