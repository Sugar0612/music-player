#ifndef SONGLISTWIDGET_H
#define SONGLISTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QListWidget>
#include <QListWidgetItem>

#include <QPaintEvent>
#include <QPainter>

#include "Control/NewButton.h"
#include "Tool/MusicStruct.h"

#include <QVector>
#include <QDebug>
#include <utility>

using namespace std;

class SongListWidget : public QWidget
{
    Q_OBJECT
public:
    SongListWidget(QWidget *parent);

public slots:

    void InsertSongListWgt(QString name, int idx);

    void ClickItem(QListWidgetItem*);

    void BuildSongListInit(QVector<mst> info);

private:
    QLabel *MusicListLab;
    QFont LabFont, ItemFont;
    QListWidget *SongList;
    QVector<NewButton*> Btns;

    int currIdx = -1;
    const QString ResPath = ":/Resources/Texture/";

    void BtnConnect();

    void paintEvent(QPaintEvent * event);
signals:

    void RequestPlayMusic(int);
    void DeleteListMusic(int);
};

#endif // SONGLISTWIDGET_H
