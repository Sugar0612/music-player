#ifndef SIGN_IN_WIN_H
#define SIGN_IN_WIN_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "sign_up_win.h"

class sign_in_win : public QWidget
{
    Q_OBJECT
public:
    explicit sign_in_win(QWidget *parent = nullptr);

    QSqlDatabase db;  // mysql
    int user_id = -1; // 用户登录的id
    int song_list_cnt = 0; // 用户歌单号 或者是 歌单数量
    QLabel *user_name_l, *user_password_l;
    QLineEdit *user_name, *user_password;
    QPushButton *sign_in_btn, *sign_up_btn; // 登录 和 注册 界面

    sign_up_win* login_win = nullptr;  // 注册界面

    void initMysql();   // 连接mysql
    void user_sign_in(); // 登录响应

signals:
    void sign_in_success();  //登录成功触发信号
};

#endif // SIGN_IN_WIN_H
