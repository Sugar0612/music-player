#include "Sql.h"

Sql::Sql(QString name, QString Password, QString Host, QString DataBaseName)
{
    db = QSqlDatabase::addDatabase("QMYSQL");    // 加载mysql 驱动
    db.setHostName(Host);  // 主机名
    db.setPort(3306); // 端口
    db.setDatabaseName(DataBaseName); // 库名
    db.setUserName(name); //用户名
    db.setPassword(Password); // 密码
    db.open();  //打开数据库
    sql = QSqlQuery(db);
}

Sql::Sql() {
    db = QSqlDatabase::addDatabase("QMYSQL");    // 加载mysql 驱动
    db.setHostName("127.0.0.1");  // 主机名
    db.setPort(3306); // 端口
    db.setDatabaseName("musicplayer"); // 库名
    db.setUserName("root"); //用户名
    db.setPassword("tsy20010612"); // 密码
    bool res = db.open();  //打开数据库

    if(res)
    {
        sql = QSqlQuery(db);
        qDebug() << "sql connect!";
    }
    else
    {
        qDebug() << "sql not connect!";
    }
}

bool Sql::InsertUser(QString id, QString name, QString password) {
    QString execStr = QString("insert into user values(%0, \"%1\", \"%2\");").arg(id) .arg(name) .arg(password);
    qDebug() << "InsertUser()->" << (execStr);
    bool res = sql.exec(execStr);
    sql.clear();
    return res;
}

bool Sql::LoginManager(QString name, QString password) {
    QString execStr = "select * from manager;";
    qDebug() << "LoginManager()->" << (execStr);
    sql.exec(execStr);
    bool res = false;
    while(sql.next()) {
        if (name == sql.value(1).value<QString>() && password == sql.value(2).value<QString>()) {
            res = true;
            break;
        }
    }
    sql.clear();
    return res;
}

int Sql::GetUserCount() {
    int res = -1;
    QString execStr = "select * from user;";
    qDebug() << "GetUserCount()->" << (execStr);
    sql.exec(execStr);
    while (sql.next()) {
        int value = sql.value(0).value<int>();
        res = (res < value) ? value : res;
    }
    sql.clear();
    return res;
}

bool Sql::LoginUser(QString name, QString password) {
    if (UserName.size() != 0) return false;

    bool res = false;
    QString execStr = "select * from user;";
    qDebug() << "LoginUser()-> " << execStr;
    sql.exec(execStr);
    while (sql.next()) {
        if (name == sql.value(1).value<QString>() && password == sql.value(2).value<QString>()) {
            UserName = sql.value(1).value<QString>();
            qDebug() << "Sql: user_name->" << UserName << endl;
            res = true;
            break;
        }
    }
    sql.clear();
    return res;
}

QVector<QVector<QString>> Sql::GetUserInfo() {
    QVector<QVector<QString>> res;
    QVector<QString> buf;
    QString execStr = "select * from user;";
    qDebug() << "GetUserInfo()-> " << execStr;
    sql.exec(execStr);
    while (sql.next()) {
        for (int i = 0; i < 3; ++i) {
            buf.push_back(sql.value(i).value<QString>());
        }
        res.push_back(buf);
        buf.clear();
    }
    sql.clear();
    return res;
}

// TODO.
bool Sql::DeleteUserInfo(QString name) {
    QString execStr = QString("delete from user where name = \"%0\";").arg(name);
    //qDebug() << "" << execStr;
    bool res = sql.exec(execStr);
    execStr = QString("delete from songlist where user = \"%0\";").arg(name);
    res = res && sql.exec(execStr);
    sql.clear();

    execStr = QString("delete from songgroups where username = \"%0\";").arg(name);
    res = res && sql.exec(execStr);
    sql.clear();

    execStr = QString("delete from listofsong where user = \"%0\";").arg(name);
    res = res && sql.exec(execStr);
    sql.clear();

    return res;
}

void Sql::GetUserMscList(QString username) {
    if (username.size() == 0) return;
    QString execStr = QString("select * from songlist where user = \"%0\";").arg(username);
    qDebug() << "GetUserMscList() ->" << execStr;
    sql.exec(execStr);

    while (sql.next()) {
        mst buffer;
        buffer.url = sql.value(1).value<QString>();
        buffer.name = sql.value(2).value<QString>();
        buffer.img = sql.value(3).value<QString>();
        buffer.lrcStr = sql.value(4).value<QString>();
        MscInfo.push_back(buffer);
    }
    sql.clear();
    emit GetSqlMscListFinished(MscInfo);
}

void Sql::GetUserSongGroups(QString name) {
    if (name.size() == 0) return;
    QString execStr = QString("select * from songgroups where username = \"%0\";").arg(name);
    qDebug() << "GetUserSongGroups() ->" << execStr;
    sql.exec(execStr);

    QVector<QString> Songgroups;
    while (sql.next()) {
        mst buffer;
        Songgroups.push_back(sql.value(1).value<QString>());
    }
    sql.clear();

    emit GetSqlSongGroupsFinished(Songgroups);
}

void Sql::InsertMscInfo(mst info) {
    if (UserName.size() == 0) return;
    QString execStr = QString("insert into songlist values(\"%0\", \"%1\", \"%2\", \"%3\", \"%4\");").arg(UserName).arg(info.url).arg(info.name).arg(info.img).arg(info.lrcStr);
    //qDebug() << "InsertMscInfo()-> " << execStr;
    sql.exec(execStr);
    sql.clear();
}

void Sql::DeleteMusicInfo(mst info) {
    if (UserName.size() == 0) return;
    QString execStr = QString("delete from songlist where user = \"%0\" and url = \"%1\" and name = \"%2\";").arg(UserName) .arg(info.url).arg(info.name);
    qDebug() << "DeleteMusicInfo()-> " << execStr;
    sql.exec(execStr);
    sql.clear();
}

bool Sql::CheckSongGroup(QString name) {
    if (UserName.size() == 0) return false;
    QString execStr = QString("select * from songgroups where username = \"%0\";").arg(UserName);
    qDebug() << "CheckSongGroup()-> " << execStr;
    sql.exec(execStr);
    while (sql.next()) {
        if(sql.value(1).value<QString>() == name) return false;
    }
    sql.clear();
    return true;
}

bool Sql::CheckListofSong(mst data, QString listname) {
    if (UserName.size() == 0) return false;
    QString execStr = QString("select * from listofsong where user = \"%0\" and listname = \"%1\";").arg(UserName).arg(listname);
    sql.exec(execStr);
    while (sql.next()) {
        if(sql.value(3).value<QString>() == data.name && sql.value(4).value<QString>() == data.singername) return false;
    }
    sql.clear();
    return true;
}

bool Sql::InsertNewSongGroup(QString name) {
    if (!CheckSongGroup(name)) return false;
    QString execStr = QString("insert into songgroups values(\"%0\", \"%1\");").arg(UserName).arg(name);
    qDebug() << "InsertNewSongGroup()-> " << execStr;
    bool res = sql.exec(execStr);
    sql.clear();
    return res;
}

void Sql::DeleteSongGroup(QString name) {
    if(UserName.size() == 0) return;

    //delete songgrounps.
    QString execStr = QString("delete from songgroups where username = \"%0\" and name = \"%1\";").arg(UserName).arg(name);
    qDebug() << "DeleteSongGroup()->delete songgroups: " << execStr;
    sql.exec(execStr);
    sql.clear();

    //delete songlist of songgroups.
    execStr = QString("delete from listofsong where user = \"%0\" and listname = \"%1\";").arg(UserName).arg(name);
    qDebug() << "DeleteSongGroup()->delete songlist:" << execStr;
    sql.exec(execStr);
    sql.clear();
}

void Sql::GetPlaysongList() {
    if(UserName.isEmpty()) return;

    QVector<QString> list;
    QString execStr = QString("select * from songgroups where username = \"%0\";").arg(UserName);
    qDebug() << "GetPlaysongList()->: " << execStr;
    sql.exec(execStr);

    while(sql.next()) {
        list.push_back(sql.value(1).value<QString>());
    }
    GetSqlSongListFinished(list);
    sql.clear();
}

bool Sql::InsertListOfSong(mst info, QString ListName) {
    if(UserName.isEmpty() || ListName.isEmpty() || !CheckListofSong(info, ListName)) {
        qDebug() << "insert list error!";
        return false;
    }
    QString execStr = QString("insert into listofsong values(\"%0\", \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\");").arg(UserName).arg(ListName).arg(info.url)
            .arg(info.name).arg(info.singername).arg(info.album_name).arg(info.time).arg(info.img).arg(info.lrcStr);
    qDebug() << "InsertListOfSong()-> " << execStr;
    bool res = sql.exec(execStr);
    sql.clear();
    return res;
}

QVector<mst> Sql::GetMusicInThisList(QString listname) {
    if(UserName.size() == 0 || listname.size() == 0) return QVector<mst>();

    QString execStr = QString("select * from listofsong where user = \"%0\" and listname = \"%1\";").arg(UserName).arg(listname);
    sql.exec(execStr);

    QVector<mst> res;
    mst buf;
    while(sql.next()) {
        buf.url = sql.value(2).value<QString>();
        buf.name = sql.value(3).value<QString>();
        buf.singername = sql.value(4).value<QString>();
        buf.album_name = sql.value(5).value<QString>();
        buf.time = sql.value(6).value<QString>();
        buf.img = sql.value(7).value<QString>();
        buf.lrcStr = sql.value(8).value<QString>();
        res.push_back(buf);
    }
    sql.clear();
    return res;
}

void Sql::DeleteMusicInThisList(QString listname, mst info) {
    if(UserName.size() == 0 || listname.size() == 0) return;

    QString execStr = QString("delete from listofsong where user = \"%0\" and listname = \"%1\" and url = \"%2\";").arg(UserName).arg(listname).arg(info.url);
    sql.exec(execStr);
    sql.clear();
    return;
}

QPair<bool, QString> Sql::GetUserPassword(QString account, QString pwd_md5) {
    if(account.size() == 0) return QPair<bool, QString>(false, "");

    Md5 md5;
    QString execStr = QString("select * from user where name = \"%0\";").arg(account);
    sql.exec(execStr);

    while(sql.next()) {
        QString pwd = sql.value(2).value<QString>();
        if (pwd_md5 == md5.MD5Encryption(pwd)) return QPair<bool, QString>(true, pwd);
    }
    sql.clear();

    return QPair<bool, QString>(false, "");
}

void Sql::RequestLikeList(mst info) {
    qDebug() << "request likelist add: user:=>" << UserName;
    if (UserName.size() == 0) return;

    QDate date = QDate::currentDate();
    QString execStr = QString("insert into likelist values(\"%0\", \"%1\", \"%2\", \"%3\", \"%4\", \"%5\", \"%6\", \"%7\", \"%8\");")
                      .arg(UserName).arg(date.toString("yyyy-MM-dd")).arg(info.url) .arg(info.name).arg(info.singername).arg(info.album_name)
                      .arg(info.time).arg(info.img).arg(info.lrcStr);
    //qDebug() << "RequestLikeList()-> " << execStr;
    bool res = sql.exec(execStr);
    sql.clear();
}

void Sql::RequestCancleLikeList(mst info) {
    qDebug() << "request likelist cancle: user:=>" << UserName;
    if (UserName.size() == 0) return;

    QString execStr = QString("delete from likelist where user = \"%0\" and url = \"%1\" and name = \"%2\";").arg(UserName).arg(info.url).arg(info.name);
    sql.exec(execStr);
    sql.clear();
    return;
}

void Sql::checkLikeMusic(mst info) {
    if (UserName.size() == 0) return;
    QString execStr = QString("select * from likelist where user = \"%0\" and url = \"%1\" and name = \"%2\";").arg(UserName).arg(info.url).arg(info.name);
    sql.exec(execStr);
    while(sql.next()) {
        if (UserName == sql.value(0).value<QString>() &&
            info.url == sql.value(2).value<QString>() &&
            info.name == sql.value(3).value<QString>()) {
            qDebug() << info.name << " is like music!";
            emit ThisIsLikeMusic();
            return;
        }

    }
    sql.clear();

    emit ThisNotLikeMusic();
    return;
}

QVector<mst> Sql::SelectLikeMusic(QString Type) {
    QVector<mst> res;
    QMap<QString, QMap<QString, int>> liver;

    QString execStr = QString("select * from likelist;");
    sql.exec(execStr);

    QDate localDate = QDate::currentDate();
    QString YearStr = localDate.toString("yyyy");
    QString MonthStr = localDate.toString("MM");
    QString DayStr = localDate.toString("dd");
    while(sql.next()) {
        QString time = sql.value(1).toString();
        QString StrTime = AnalyzeDate(time, Type);

        mst buf;
        buf.url = sql.value(2).value<QString>();
        buf.name = sql.value(3).value<QString>();
        buf.singername = sql.value(4).value<QString>();
        buf.album_name = sql.value(5).value<QString>();
        buf.time = sql.value(6).value<QString>();
        buf.img = sql.value(7).value<QString>();
        buf.lrcStr = sql.value(8).value<QString>();
        if((StrTime != YearStr && StrTime != MonthStr && StrTime != DayStr) || liver[buf.name][buf.singername] > 0) continue;
        res.push_back(buf);
        liver[buf.name][buf.singername] = 1;
    }
    qDebug() << "Clear";
    sql.clear();
    return res;
}

// yyyy-MM-dd
QString Sql::AnalyzeDate(QString Str, QString Type) {
    if (Str.isEmpty()) return "";

    int idx = 0;
    if (Type == "yyyy") idx = 0;
    if (Type == "MM") idx = 5;
    if (Type == "dd") idx = 8;

    QString res = "";
    for (int i = idx; Str[i] != '-' && i < Str.size(); ++i) {
        res += Str[i];
    }
    qDebug() << "AnalyzeDate()->: " << res;
    return res;
}

Sql::~Sql() {
    db.close();
}
