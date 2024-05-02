#ifndef LOGINW_H
#define LOGINW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>

#include <QJsonDocument>   // json
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include <Control/NewButton.h>
#include "Tool/MD5.h"

#include <QFont>
#include <QDebug>

class LoginW : public QWidget
{
        Q_OBJECT
public:
    LoginW(QWidget *p, int x, int y, int width, int height);
    void ClearLineEditText();
    bool CheckUserinfo();
    QJsonObject JsonReadOnlyInFile();

    bool IsRememberMe() { return rememberMe->isChecked(); }
    void JsonWriteInFile(QString account, QString pwd);

private:
    const QString ResPath = ":/Resources/Texture/";
    const QString path = "E:\\Qt\\pro\\KtvPlayer\\localData\\userinfo.json";

    QFont NorFont, Radfont;
    QLabel *AccountLab, *PassLab{};
    QLineEdit *account, *password;
    QRadioButton *Manager{}, *User{};
    QCheckBox *rememberMe{};

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
