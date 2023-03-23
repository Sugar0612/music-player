#include "loginw.h"

LoginW::LoginW(QWidget *p, int x, int y, int width, int height)
{
    this->setParent(p);
    setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(x, y, width, height);

    NorFont.setFamily("宋体");
    NorFont.setPointSize(15);

    Radfont.setFamily("幼圆");
    Radfont.setPointSize(10);

    account = new QLineEdit(this);
    account->setFont(NorFont);
    account->setGeometry(this->width() / 2 - 150, this->height() / 2 - 100, 200, 40);
    account->setStyleSheet("QLineEdit{height: 20px;border-style:none; padding:6px; border-radius: 20px;background:rgba(100, 205, 210, 100); }");

    password = new QLineEdit(this);
    password->setFont(NorFont);
    password->setGeometry(this->width() / 2 - 150, this->height() / 2 - 50, 200, 40);
    password->setStyleSheet("QLineEdit{height: 20px;border-style:none; padding:6px; border-radius: 20px;background:rgba(100, 205, 210, 100); }");
    password->setEchoMode(QLineEdit::Password);

    AccountLab = new QLabel(this);
    AccountLab->setGeometry(account->x() - 65, account->y(), 100, 40);
    AccountLab->setFont(NorFont);
    AccountLab->setText("用户名");

    PassLab = new QLabel(this);
    PassLab->setGeometry(password->x() - 65, password->y(), 100, 40);
    PassLab->setFont(NorFont);
    PassLab->setText("密码");

    RegisterBtn = new NewButton(ResPath + "register.png", ResPath + "register_c.png");
    RegisterBtn->setParent(this);
    RegisterBtn->move(PassLab->x(), PassLab->y() + 80);

    LoginBtn = new NewButton(ResPath + "Login.png", ResPath + "Login_c.png");
    LoginBtn->setParent(this);
    LoginBtn->move(RegisterBtn->x() + 180, RegisterBtn->y());

    Manager = new QRadioButton(this);
    Manager->setText("我是管理员");
    Manager->setFont(Radfont);
    Manager->move(PassLab->x() - 20, PassLab->y() + 50);

    User = new QRadioButton(this);
    User->setChecked(true);
    User->setText("我是用户");
    User->setFont(Radfont);
    User->move(Manager->x() + 180, Manager->y());

    rememberMe = new QCheckBox(this);
    rememberMe->setText("记住密码");
    rememberMe->setFont(Radfont);
    rememberMe->move(User->x() + 180, User->y());

    connect(Manager, &QRadioButton::clicked, this, &LoginW::ClickedManger);
    connect(User, &QRadioButton::clicked, this, &LoginW::ClickedUser);
    connect(RegisterBtn, &QPushButton::clicked, this, [=] () {
        emit ShowRegister();
    });

    connect(LoginBtn, &QPushButton::clicked, this, [=] () {
        QString name = account->text();
        QString pwd = password->text();
        if (Type == 1) {
            emit RequestLogin(name, pwd);
            if (rememberMe->isChecked()) {
                JsonWriteInFile(name, pwd);
            }
        }
        else emit RequestLoginManager(name, pwd);
    });
}

void LoginW::ClickedUser() {
    Type = (User->isChecked()) ? 1 : 0;
}

void LoginW::ClickedManger() {
    Type = (Manager->isChecked()) ? 0 : 1;
}


void LoginW::ClearLineEditText() {
    account->setText("");
    password->setText("");
}

void LoginW::JsonWriteInFile(QString account, QString pwd) {
    QJsonObject json;
    Md5 md5;
    QString md5_pwd = md5.MD5Encryption(pwd);
    json["account"] = account;
    json["password"] = md5_pwd;
    QString jsonStr = QString(QJsonDocument(json).toJson());

    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream txtOutput(&file);
    txtOutput << jsonStr;
    file.close();
}

QJsonObject LoginW::JsonReadOnlyInFile() {
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) return QJsonObject();

    QByteArray jsonByteData = file.readAll();
    QJsonParseError jsonError;
    QJsonDocument jsonDcm(QJsonDocument::fromJson(jsonByteData, &jsonError));

    if(jsonError.error != QJsonParseError::NoError) return QJsonObject();

    file.close();
    return jsonDcm.object();
}

bool LoginW::CheckUserinfo() {
    QFile file(path);
    return file.exists();
}
