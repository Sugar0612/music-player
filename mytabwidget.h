#ifndef MYTABWIDGET_H
#define MYTABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QFont>
class mytabwidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit mytabwidget(QWidget *parent = nullptr);

signals:

};

#endif // MYTABWIDGET_H
