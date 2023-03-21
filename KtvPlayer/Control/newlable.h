#ifndef NEWLABLE_H
#define NEWLABLE_H


#include <QLabel>
#include <QString>
class NewLable : public QLabel
{
    Q_OBJECT
public:
    explicit NewLable (QString text, QWidget *parent = nullptr);

signals:

};


#endif // NEWLABLE_H
