#include "register.h"

Register::Register(QWidget *p, int x, int y, int width, int height)
{
    this->setParent(p);
    setWindowFlags(Qt::FramelessWindowHint);
    setGeometry(x, y, width, height);

    NorFont.setFamily("宋体");
    NorFont.setPointSize(15);

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

    OkBtn = new NewButton(ResPath + "OK.png", ResPath + "OK_c.png");
    OkBtn->setParent(this);
    OkBtn->move(PassLab->x(), PassLab->y() + 50);

    CancelBtn = new NewButton(ResPath + "Cancel.png", ResPath + "Cancel_c.png");
    CancelBtn->setParent(this);
    CancelBtn->move(OkBtn->x() + 180, OkBtn->y());

    connect(OkBtn, &QPushButton::clicked, this, [=] () {
        QString name = account->text();
        QString pwd = password->text();
        emit RequestRegister(name, pwd);
    });

    connect(CancelBtn, &NewButton::clicked, this, [=] () {
        emit CloseRegister();
    });
}


void Register::ClearLineEditText() {
    account->setText("");
    password->setText("");
}
