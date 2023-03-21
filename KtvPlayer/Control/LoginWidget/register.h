#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>

#include <Control/NewButton.h>
#include <Module/Sql/Sql.h>

#include <QFont>
#include <QDebug>
#include <QMessageBox>

class Register : public QWidget
{
        Q_OBJECT
public:
    Register(QWidget *p, int x, int y, int width, int height);
    void ClearLineEditText();

private:
    const QString ResPath = ":/Resources/Texture/";

    QFont NorFont;
    QLabel *AccountLab, *PassLab{};
    QLineEdit *account, *password;
    NewButton *OkBtn{}, *CancelBtn{};

signals:
    void CloseRegister();
    void RequestRegister(QString, QString);
};

#endif // REGISTER_H
