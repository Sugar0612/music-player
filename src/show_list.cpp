#include "show_list.h"



show_list::show_list(int id, QWidget *parent) : QWidget(parent), user_id(id)
{

    setWindowFlag(Qt::FramelessWindowHint);  // 删除以前的 最大化 最小化 关闭自己写
    this ->setFixedSize(200, 350);

    // connect mysql
    initMysql();

    // 显示所有的 歌单
    show_song_list();

    connect(list, &mylistwidget::itemDoubleClicked, this, &show_list::item_show);  // 当点击 list 时, 开始返回item
}


void show_list::initMysql() {
    db = QSqlDatabase::addDatabase("QMYSQL");    // 加载mysql 驱动
    db.setHostName("rm-uf6to17061qpnj06goo.mysql.rds.aliyuncs.com");  // 主机名
    db.setPort(3306); // 端口
    db.setDatabaseName("musicbase"); // 库名
    db.setUserName("user"); //用户名
    db.setPassword("Tsy20010612"); // 密码
    bool ok = db.open();  //打开数据库
    if (ok) qDebug() << "connect aliyun ok!" << endl;
}


void show_list::show_song_list() {
    QFont font;
    font.setFamily("幼圆");
    font.setPointSize(12);

    list = new mylistwidget(this);
    list ->setFont(font);
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
