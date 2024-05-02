/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QSlider *MusicSlider;
    QSlider *VolSlider;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1025, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MusicSlider = new QSlider(centralwidget);
        MusicSlider->setObjectName("MusicSlider");
        MusicSlider->setGeometry(QRect(200, 660, 701, 20));
        MusicSlider->setAutoFillBackground(false);
        MusicSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal{ \n"
"height: 12px; \n"
"left:  0px; \n"
"right: 0px; \n"
"border:0px;             \n"
"border-radius:6px;\n"
"background:rgba(0,0,0,100);            \n"
"} \n"
"QSlider::handle:horizontal{ \n"
"border-radius: 7px;\n"
"width:  14px;  \n"
"height: 10px;\n"
"margin: -2px -0px;\n"
"background: rgb(84,255,159);\n"
"} \n"
"QSlider::sub-page:horizontal\n"
"{\n"
"border-radius:6px;\n"
"background:rgba(84,255,159,1);\n"
"}"));
        MusicSlider->setMinimum(0);
        MusicSlider->setMaximum(100);
        MusicSlider->setValue(1);
        MusicSlider->setOrientation(Qt::Horizontal);
        VolSlider = new QSlider(centralwidget);
        VolSlider->setObjectName("VolSlider");
        VolSlider->setGeometry(QRect(690, 630, 111, 20));
        VolSlider->setAutoFillBackground(false);
        VolSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal{ \n"
"height: 8px; \n"
"left:  0px; \n"
"right: 0px; \n"
"border:0px;             \n"
"border-radius:4px;\n"
"background:rgba(0,0,0,100);            \n"
"} \n"
"QSlider::handle:horizontal{ \n"
"border-radius: 4px;\n"
"width:  8px;  \n"
"height: 10px;\n"
"margin: -1px -0px;\n"
"background: rgb(84,255,159);\n"
"} \n"
"QSlider::sub-page:horizontal\n"
"{\n"
"border-radius:6px;\n"
"background:rgba(84,255,159,1);\n"
"}"));
        VolSlider->setMaximum(100);
        VolSlider->setValue(100);
        VolSlider->setOrientation(Qt::Horizontal);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
