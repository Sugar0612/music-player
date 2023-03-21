#ifndef NEWLISTWIDGET_H
#define NEWLISTWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFont>
#include <QLabel>
#include <QDebug>

#include "Control/NewButton.h"

class NewListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit NewListWidget(QWidget *parent, QStringList itemList);
    void AddItem(QString name);
    void AddItem_(QString name);
private:
    const QString ResPath = ":/Resources/Texture/";
    QFont font, font_L;
    QVector<QListWidgetItem*> items;
    QVector<NewButton*> Btns;

    void BtnConnect();

signals:
    void DeleteSongGroup(QString);
};



#endif // NEWLISTWIDGET_H
