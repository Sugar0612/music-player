#ifndef MUSICSTRUCT_H
#define MUSICSTRUCT_H

#include <QString>
#include <map>

//struct mst {
//    QString url;
//    QString name;
//    QString img;
//    QString lrcStr;
//    std::map<int, QString> lrc;

//    bool operator == (const mst a) const {
//        bool res = true;
//        for (auto p: lrc) {
//            std::map<int, QString> a_lrc = a.lrc;
//            if (a_lrc[p.first].size() == 0 && p.second != a_lrc[p.first]) {
//                res = false;
//                break;
//            }
//        }
//        return res && url == a.url && name == a.name && img == a.img;
//    }
//};

struct mst {
    QString name;
    QString singername;
    QString album_name;
    QString time;
    QString hashStr;
    QString id;
    QString url;
    QString img;
    QString lrcStr;
    std::map<int, QString> lrc;

    bool operator == (const mst a) const {
        bool res = true;
        for (auto p: lrc) {
            std::map<int, QString> a_lrc = a.lrc;
            if (a_lrc[p.first].size() == 0 && p.second != a_lrc[p.first]) {
                res = false;
                break;
            }
        }
        return res && name == a.name && singername == a.singername &&
                hashStr == a.hashStr && album_name == a.album_name &&
                time == a.time && url == a.url && img == a.img;
    }
};

#endif // MUSICSTRUCT_H
