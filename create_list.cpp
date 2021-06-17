#include "create_list.h"
#include <QFont>
create_list::create_list(QWidget *parent) : QWidget(parent)
{

    QFont font;
    font.setFamily("幼圆");

    this ->resize(350, 200);
    this ->setWindowTitle("歌单创建窗口");
    this ->setWindowIcon(QIcon(":/coin/mymusic.png"));  // 主窗口的图标设置!

    name = new QLineEdit(this);
    name ->setGeometry(80, 40, 200, 40);

    list_name = new QLabel("歌单名", this);
    list_name->setFont(font);
    list_name ->setGeometry(10, 40, 60, 40);

    ok = new QPushButton(this);
    ok ->setText("确定");
    ok ->setGeometry(80, 100, 60, 30);

    cancel = new QPushButton(this);
    cancel ->setText("取消");
    cancel ->setGeometry(210, 100, 60, 30);

    connect(ok, &QPushButton::clicked, [=] () {
        this ->hide();
        emit create_ok(name ->text());
    });

    connect(cancel, &QPushButton::clicked, [=] () {
        this ->hide();
    });
}
