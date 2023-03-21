#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <Tool/MusicStruct.h>
#include <QMediaPlayer>      // 实现多媒体的 应用
#include <QMediaPlaylist>
#include <QWidget>
#include <QTimer>
#include <QMap>
#include <QQueue>
#include <qmediaplayer.h>

class MusicPlayer : public QWidget
{
    Q_OBJECT
public:
    MusicPlayer();

private:
    QMediaPlayer *Player;    // 实现多媒体操控

    bool IsPlay = false, IsVolume = true;
    QTimer *timer;

    int currTime = 0;
    int volumeVal = 100;
    int currMediaIdx = -1;
    QList<mst> PlayList;
    int Find(mst buf);

public slots:
    bool SetLoadMusic(mst path);
    void SwitchPlayerStatue();
    void SwitchVolumeState();

    void Next();

    void Prev();

    void Fastward(); //快进

    void Rewind(); // 快退

    int GetMusicDuration();

    void ChangeTimer(bool);

    void RecordCurrTime();

    int GetCurrTime() { return currTime; }

    void SetCurrVol(int vol);

    void SetMusicPosition(int pos);

    void DeleteMusic(int idx);

    void InitPlayList(QVector<mst> info);

    void GetAnlzLrcMap(std::map<int, QString> lrcMap);

    // SongList Signals.
    void DeleteMusicInMediaPlayer(int idx);

    void PlayerMusic(int idx);

    bool SongListEmpty();

public:

    void Play();

    void Pause();

    void NotMute(); //不静音

    void Mute(); // 静音.

    bool PlayTheNextSong(mst path);

    int GetCurrMediaIdx() { return currMediaIdx; }

    bool checkMst(mst target);

signals:
    void ChangedPlayerState(bool);
    void ChangedVolumeState(bool);
    void MusicTimeout();
    void GetMusicNetImg(QString);
    void GetMusicName(QString);
    void SetLrcTxt(QString);
    void GetInitMusicList(QString);
    void PlzAnlzLrcStr(QString lrcstr);
    void InsertMscInfoInSql(mst info);

    void RequestSqlDeleteMusic(mst);
    void PlayerIsEmpty();
};

#endif // MUSICPLAYER_H
