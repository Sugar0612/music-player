#ifndef STARTBTN_H
#define STARTBTN_H

#include <QPushButton>
#include <QString>
class startbtn : public QPushButton
{
    Q_OBJECT
public:
//    explicit startbtn(QPushButton *parent = nullptr);
    explicit startbtn(const QString a, const QString b, const QString c, const QString d);

signals:

};

#endif // STARTBTN_H
