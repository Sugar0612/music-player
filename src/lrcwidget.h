#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QLabel>

class lrcwidget : public QWidget
{
    Q_OBJECT
public:
    QLabel *l;  // 用来绘制歌曲专辑图片
    explicit lrcwidget(QWidget *parent = nullptr);

signals:

};

#endif // MYWIDGET_H
