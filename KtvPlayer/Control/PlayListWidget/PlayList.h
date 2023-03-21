#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QVector4D>
#include <QFont>
#include <QListWidgetItem>

#include "Control/Newlistwidget.h"

#include <QDebug>

class PlayList : public QWidget
{
    Q_OBJECT
public:
    QString TargetName = "";
    PlayList(QWidget *parent);
    void Move(int x, int y);
    QVector4D GetPlayListRange();
    QFont font;
    void SetTargetRow(int row) { targetRow = row; }
    int GetTargetRow() { return targetRow; }
public slots:
    void GetListofSong(QVector<QString> list);
    void AddItem(QString name);

private slots:
    void listofSongItemClicked(QListWidgetItem *);

private:
    NewListWidget *listofsong{};
    int targetRow = 0;
private:
    void mousePressEvent(QMouseEvent *);

signals:
    void RequestSqlBuildList();
    void cellClickedItem();
};

#endif // PLAYLIST_H
