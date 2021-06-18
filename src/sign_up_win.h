#ifndef SIGN_UP_WIN_H
#define SIGN_UP_WIN_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class sign_up_win : public QWidget
{
    Q_OBJECT
public:
    explicit sign_up_win(QWidget *parent = nullptr);


    QSqlDatabase db; // mysql
    QLabel *user_name_l, *user_password_l;
    QLineEdit *login_user_name, *login_user_password;
    QPushButton *ok, *cancel;

    void _initMysql();
    void user_sign_up();  // 注册响应

signals:

};

#endif // SIGN_UP_WIN_H
