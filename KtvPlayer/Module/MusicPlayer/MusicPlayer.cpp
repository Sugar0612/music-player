#include "MusicPlayer.h"
#include <algorithm>

MusicPlayer::MusicPlayer()
{
    Player = new QMediaPlayer();   // 实体化播放列表
    timer = new QTimer(this);

    connect(this, &MusicPlayer::ChangedPlayerState, this, &MusicPlayer::ChangeTimer);
    connect(timer, &QTimer::timeout, this, &MusicPlayer::RecordCurrTime);
}

bool MusicPlayer::SetLoadMusic(mst path) {
    if (!checkMst(path)) return false;

    int PathIndex = Find(path);
    if (PathIndex != PlayList.size()) {
        return false;
    }

    emit InsertMscInfoInSql(path);
    PlayList.push_back(path);
    currMediaIdx = PlayList.size() - 1;
    Player->setMedia(QUrl(PlayList[currMediaIdx].url));
    currTime = 0;
    Play();
    return true;
}

bool MusicPlayer::PlayTheNextSong(mst path) {
    if (!checkMst(path)) return false;

    int PathIndex = Find(path);
    if (PlayList.size() != PathIndex) return false;

    emit InsertMscInfoInSql(path);
    DeleteMusic(PathIndex);

    if (currMediaIdx > PathIndex) currMediaIdx--;
    PlayList.insert(currMediaIdx + 1, path);
    return true;
}

void MusicPlayer::Play() {
    if (!SongListEmpty()) return;
    if(currMediaIdx == -1) {
        Next();
    }

    qDebug() << "Play() -> " << currMediaIdx;
    Player->play();
    IsPlay = true;
    emit PlzAnlzLrcStr(PlayList[currMediaIdx].lrcStr);
    emit GetMusicNetImg(PlayList[currMediaIdx].img);
    emit ChangedPlayerState(IsPlay);
    emit GetMusicName(PlayList[currMediaIdx].name);
    emit IsThisLikeMusic(PlayList[currMediaIdx]);
}

void MusicPlayer::Pause() {
    Player->pause();
    IsPlay = false;
    emit ChangedPlayerState(IsPlay);
}

void MusicPlayer::Next() {
    if (currMediaIdx == PlayList.size() - 1 || !SongListEmpty()) return;
     currMediaIdx++;
     currTime = 0;
     Player->setMedia(QUrl(PlayList[currMediaIdx].url));
     Play();
}

void MusicPlayer::Prev() {
    if (currMediaIdx == 0 || !SongListEmpty()) return;
    currMediaIdx--;
    currTime = 0;
    Player->setMedia(QUrl(PlayList[currMediaIdx].url));
    Play();
}

void MusicPlayer::Fastward() {
    if (!SongListEmpty()) return;
    currTime += (currTime + 300 < GetMusicDuration() / 10) ? 300 : 0;
    Player->setPosition(currTime * 10);
}

void MusicPlayer::Rewind() {
    if (!SongListEmpty()) return;
    currTime -= (currTime - 300 > 0) ? 300 : 0;
    Player->setPosition(currTime * 10);
}

void MusicPlayer::NotMute() {
    Player->setVolume(volumeVal);
    IsVolume = true;
    emit ChangedVolumeState(!IsVolume);
}

void MusicPlayer::Mute() {
    volumeVal = Player->volume();
    Player->setVolume(0);
    IsVolume = false;
    emit ChangedVolumeState(!IsVolume);
}

void MusicPlayer::Like() {
    IsLike = true;
    emit ChangedLikeThisMusic(IsLike);
}

void MusicPlayer::NotLike() {
    IsLike = false;
    emit ChangedLikeThisMusic(IsLike);
}

void MusicPlayer::SwitchPlayerStatue() {
    IsPlay == false ? (Play()) : (Pause());
}

void MusicPlayer::SwitchVolumeState() {
    IsVolume == false ? (NotMute()) : (Mute());
}

void MusicPlayer::SwitchLikeState() {
    IsLike == false ? (Like()) : (NotLike());
    if(currMediaIdx >= 0) {
        IsLike == false ? (emit CancleLike(PlayList[currMediaIdx])) :
                (emit AddLike(PlayList[currMediaIdx]));
    }
}

int MusicPlayer::GetMusicDuration() {
    return Player->duration();
}

void MusicPlayer::ChangeTimer(bool isPlay) {
    if (isPlay) {
        timer->setInterval(10);
        timer->start();
    }
    else {
        timer->stop();
    }
}

void MusicPlayer::RecordCurrTime() {
    if (Player->state() == QMediaPlayer::State::StoppedState && currMediaIdx + 1 < PlayList.size()) {
        currMediaIdx++;
        Player->setMedia(QUrl(PlayList[currMediaIdx].url));
        currTime = 0;
        Play();
    }
    else if (Player->state() == QMediaPlayer::State::StoppedState && currMediaIdx + 1 >= PlayList.size()) {
        currTime = 0;
        Pause();
    }

    if (GetMusicDuration() != 0) currTime++;
    emit MusicTimeout();
    if (PlayList[currMediaIdx].lrc[currTime].size() != 0) emit SetLrcTxt(PlayList[currMediaIdx].lrc[currTime]);
}

void MusicPlayer::SetCurrVol(int vol) {
    if(vol < 0 || vol > 100) return;
    if (vol == 0) Mute();
    else {
        NotMute();
        Player->setVolume(vol);
    }
}

void MusicPlayer::SetMusicPosition(int pos) {
    int Pos = (float)(1.0f * pos / 100) * Player->duration();
    Player->setPosition(Pos);
    currTime = Pos / 10;
}

void MusicPlayer::DeleteMusic(int idx) {
    if (idx == PlayList.size()) return;
    PlayList.erase(PlayList.begin() + idx, PlayList.begin() + idx + 1);
}

void MusicPlayer::InitPlayList(QVector<mst> info) {
    if (info.size() != 0) {
        currMediaIdx = 0;
        for (auto val: info) {
            PlayList.push_back(val);
        }
        Player->setMedia(QUrl(PlayList[currMediaIdx].url));
    }
}

void MusicPlayer::GetAnlzLrcMap(std::map<int, QString> lrcMap)  {
    PlayList[currMediaIdx].lrc = lrcMap;
}

void MusicPlayer::DeleteMusicInMediaPlayer(int i) {
    if (i >= PlayList.size()) return;
    emit RequestSqlDeleteMusic(PlayList[i]);
    PlayList.erase(PlayList.begin() + i, PlayList.begin() + i + 1);
    if (currMediaIdx > i) currMediaIdx = currMediaIdx - 1;
    else if (currMediaIdx == i && SongListEmpty()) {
        currMediaIdx = i;
        currTime = 0;
        Player->setMedia(QUrl(PlayList[currMediaIdx].url));
        Play();
    }
}

void MusicPlayer::PlayerMusic(int idx) {
    if(idx == currMediaIdx || !SongListEmpty()) return;
    qDebug() << "PlayerMusic() -> " << currMediaIdx;
    currMediaIdx = idx;
    currTime = 0;
    Player->setMedia(QUrl(PlayList[currMediaIdx].url));
    Play();
}

bool MusicPlayer::SongListEmpty() {
    if (PlayList.size() == 0) {
        emit PlayerIsEmpty();
        currTime = 0;
        currMediaIdx = -1;
        Pause();
        return false;
    }
    return true;
}

bool MusicPlayer::checkMst(mst target) {
    return !target.url.isEmpty() && !target.name.isEmpty();
}

int MusicPlayer::Find(mst buf) {
    int i = 0;
    while(i < PlayList.size()) {
        if (buf.url == PlayList[i].url && buf.name == PlayList[i].name) return i;
        i++;
    }
    return PlayList.size();
}
