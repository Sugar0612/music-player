#include "sign_up_win.h"
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
sign_up_win::sign_up_win(QWidget *parent) : QWidget(parent)
{
    // 初始化
    _initMysql();

    this ->setWindowTitle("注册窗口");
    this ->setWindowIcon(QIcon(":/coin/mymusic.png"));  // 主窗口的图标设置!


    this ->setFixedSize(350, 200);
    login_user_name = new QLineEdit(this);
    login_user_password = new QLineEdit(this);

    login_user_name ->setGeometry(80, 30, 200, 30);
    login_user_password ->setGeometry(80, 80, 200, 30);

    ok = new QPushButton("确定", this);
    cancel = new QPushButton("取消", this);
    ok ->setGeometry(80, 120, 90, 30);
    cancel ->setGeometry(190, 120, 90, 30);

    user_name_l = new QLabel("用户名" ,this);
    user_password_l = new QLabel("密码", this);

    user_name_l ->setGeometry(30, 35, 40, 20);
    user_password_l ->setGeometry(35, 85, 40, 20);

    connect(ok, &QPushButton::clicked, this, &sign_up_win::user_sign_up);
    connect(cancel, &QPushButton::clicked, this, [=] () {
        this ->hide();
    });
}

// 注册响应
void sign_up_win::user_sign_up() {
    QSqlQuery selectq = QSqlQuery(db);
    selectq.exec("select count(*) from user");
    selectq.next();
    QString count = QString("%1").arg(selectq.value(0).value<int>());

    QString _user_name = login_user_name ->text();
    QString _user_password = login_user_password ->text();
    QString cnt_list = QString("%0").arg(0);
    QString exec = QString("insert into user values(" + count + ",\"" + _user_name + "\"," + "\"" + _user_password + "\", " + cnt_list + ");");

    bool ok = selectq.exec(exec);
    if(ok) QMessageBox::information(this, "提示", "注册成功!", QMessageBox::Ok);
    else QMessageBox::information(this, "提示", "注册失败(可能是用户名重复)!", QMessageBox::Ok);
    this ->hide();
}

void sign_up_win::_initMysql() {
    db = QSqlDatabase::addDatabase("QMYSQL");    // 加载mysql 驱动
    db.setHostName("rm-uf6to17061qpnj06goo.mysql.rds.aliyuncs.com");  // 主机名
    db.setPort(3306); // 端口
    db.setDatabaseName("musicbase"); // 库名
    db.setUserName("user"); //用户名
    db.setPassword("Tsy20010612"); // 密码
    bool ok = db.open();  //打开数据库
    if (ok) qDebug() << "connect aliyun ok!" << endl;
}
