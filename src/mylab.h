#ifndef MYLAB_H
#define MYLAB_H

#include <QLabel>
#include <QString>
class mylab : public QLabel
{
    Q_OBJECT
public:
    explicit mylab(QString text, QWidget *parent = nullptr);

signals:

};

#endif // MYLAB_H
