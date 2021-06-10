#include "show_list.h"



show_list::show_list(int id, QWidget *parent) : QWidget(parent), user_id(id)
{
    this ->setFixedSize(200, 350);

    // connect mysql
    initMysql();

    // 显示所有的 歌单
    show_song_list();

    connect(list, &mylistwidget::itemDoubleClicked, this, &show_list::item_show);  // 当点击 list 时, 开始返回item
}


void show_list::initMysql() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("musicbase");
    db.setUserName("root");
    db.setPassword("tsy20010612");
    db.open();
}


void show_list::show_song_list() {
    list = new mylistwidget(this);
    list ->setGeometry(0, 0, this ->width(), this ->height());
    QString user_id_s = QString("%0").arg(user_id);

    QSqlQuery sql_l(db);
    sql_l.exec("select name from listname where id = " + user_id_s + ";");
    while(sql_l.next()) {
        list ->addItem(sql_l.value(0).value<QString>());
    }
}

// 当点击 list 时, 开始返回item
void show_list::item_show(QListWidgetItem *item) {
    emit return_item(item);
    this ->hide();
}
