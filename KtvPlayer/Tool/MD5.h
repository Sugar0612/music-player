#ifndef MD5_H
#define MD5_H

#include <QString>
#include <QCryptographicHash>

class Md5 {
public:
    Md5() {};

    QString MD5Encryption(QString pwd) {
        QByteArray btArray;
        btArray.append(pwd);

        QCryptographicHash hash(QCryptographicHash::Md5);
        hash.addData(btArray); //将btArray作为参数加密
        QByteArray resultArray = hash.result();//得到hash加密后的结果

        QString md5 = resultArray.toHex(); //将字节数组内容转换为字符串
        return md5; //返回加密后的密码
    }
};


#endif // MD5_H
