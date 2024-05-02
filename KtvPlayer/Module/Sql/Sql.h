#ifndef SQL_H
#define SQL_H
#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>

#include <QDebug>
#include <QDate>
#include <set>

#include "Tool/MusicStruct.h"
#include "Tool/MD5.h"

class Sql : public QWidget
{
    Q_OBJECT
public:
    Sql(QString name, QString Password, QString Host, QString DataBaseName);
    Sql();
    ~Sql();

    QMap<QString, int> like_map;

public slots:
    bool LoginManager(QString name, QString password);
    bool LoginUser(QString name, QString password);

    QVector<mst> GetMusicInfo() { return MscInfo; };
    QString GetUserName() { return UserName; }
    bool InsertUser(QString id, QString name, QString password);
    int GetUserCount();

    QVector<QVector<QString>> GetUserInfo();
    bool DeleteUserInfo(QString name);
    void GetUserMscList(QString username);
    void GetUserSongGroups(QString name);

    void InsertMscInfo(mst info);
    void DeleteMusicInfo(mst info);

    bool InsertNewSongGroup(QString name);
    void DeleteSongGroup(QString name);

    void GetPlaysongList();
    bool InsertListOfSong(mst info, QString ListName);

    QVector<mst> GetMusicInThisList(QString listname);
    void DeleteMusicInThisList(QString listname, mst info);

    QPair<bool, QString> GetUserPassword(QString account, QString pwd_md5);

    void RequestLikeList(mst info);
    void RequestCancleLikeList(mst info);

    void checkLikeMusic(mst info);

    QVector<mst> SelectLikeMusic(QString Type);

private:
    QSqlDatabase db;
    QSqlQuery sql;
    QString UserName = "";
    QVector<mst> MscInfo;

    bool CheckSongGroup(QString name);
    bool CheckListofSong(mst data, QString listname);
    QString MD5Encryption(QString pwd);
    QString AnalyzeDate(QString Str, QString Type);
signals:
    void GetSqlMscListFinished(QVector<mst>);
    void GetSqlSongGroupsFinished(QVector<QString>);
    void GetSqlSongListFinished(QVector<QString>);
    void ThisIsLikeMusic();
    void ThisNotLikeMusic();
};

#endif // SQL_H
