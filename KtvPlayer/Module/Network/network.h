#ifndef NETWORK_H
#define NETWORK_H


#include <QNetworkAccessManager>  // network
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QVariant>
#include<QUrl>
#include<QByteArray>
#include <QNetworkCookie>
#include <QBitmap>

#include <QJsonDocument>   // json
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>

#include <QObject>
#include <QWidget>
#include <QPixmap>

#include <Tool/MusicStruct.h>

class Network : public QWidget
{
    Q_OBJECT
public:
    explicit  Network();

private:
    int idx = 0;

    QString MusicUrl;
private slots:
    void reply(QNetworkReply *re);  // 如果net_messager finish  判断是否载入 然后进行js
    void reply2(QNetworkReply *reply);  // 如果net_messageer finish  判断是否载入 然后进行js
    void reply3(QNetworkReply *re);  //图片
    void RankReply(QNetworkReply*); //rank songs.

private:
    //Http. Network.
    QNetworkAccessManager *net_manager, *network_manager2, *network_manager3, *network_manager4;
    QNetworkRequest *net_request, *network_request2, *network_request3, *net_request4;
    QPixmap imgPix;

private:
    void parseJson(QString, int);  // 将歌曲放入 tableWidget
    void parseJson2(QString json);  //播放音乐解析Json
    void New_parseJson2(QString json);  //播放音乐解析Json
    void parseJson3(QString, int);  //播放音乐解析Json
    void RankParseJson(QString, int);
    void ParseSingerAndSong(QString&, QString&, QString); // 解析歌曲名和歌手名
public:
    QVector<mst> infoArray;
    void search(QString, int);  // 连接http 搜索歌曲
    void SearchRank(); // rank歌曲排名
    void ClearNetworkVector();
    void SelectNetworkMusic(int row);
    mst GetMusicStruct() { return infoArray[TargetRow]; };
    std::map<int, QString> BuildLrc(QString lrc);
    QPixmap GetImgPix() { return imgPix; }
    void StartRequestNetImg(QString url);
    QString ImageUrlProcessing(QString imgurl, QString size);
    int TargetRow = 0;
public slots:
    void AnlzLrcStr(QString lrcStr);

signals:
    void SearchIsFinished(QVector<mst>);
    void GetMusicFinished();
    void GetNetworkImgFinished();
    void AnlzLrcStrFinished(std::map<int, QString> mapinfo);
};

#endif // NETWORK_H
