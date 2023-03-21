#ifndef LOGINW_H
#define LOGINW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>

#include <Control/NewButton.h>

#include <QFont>
#include <QDebug>

class LoginW : public QWidget
{
        Q_OBJECT
public:
    LoginW(QWidget *p, int x, int y, int width, int height);
    void ClearLineEditText();

private:
    const QString ResPath = ":/Resources/Texture/";

    QFont NorFont, Radfont;
    QLabel *AccountLab, *PassLab{};
    QLineEdit *account, *password;
    QRadioButton *Manager{}, *User{};

    NewButton *LoginBtn{}, *RegisterBtn{};

    int Type = 1; // 0 -> Manager, 1 -> User;

private slots:
    void ClickedManger();
    void ClickedUser();

signals:
    void ShowRegister();
    void RequestLogin(QString, QString);
    void RequestLoginManager(QString, QString);
};

#endif // LOGINW_H
