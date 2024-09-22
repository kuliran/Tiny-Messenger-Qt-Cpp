/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *MessageBrowser;
    QPushButton *Send_btn;
    QLineEdit *Message_edit;
    QPushButton *Join_btn;
    QLineEdit *Nickname_edit;
    QLabel *Loading_label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(377, 501);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MessageBrowser = new QTextBrowser(centralwidget);
        MessageBrowser->setObjectName("MessageBrowser");
        MessageBrowser->setGeometry(QRect(60, 50, 256, 341));
        Send_btn = new QPushButton(centralwidget);
        Send_btn->setObjectName("Send_btn");
        Send_btn->setGeometry(QRect(220, 400, 91, 24));
        Message_edit = new QLineEdit(centralwidget);
        Message_edit->setObjectName("Message_edit");
        Message_edit->setGeometry(QRect(60, 400, 151, 24));
        Join_btn = new QPushButton(centralwidget);
        Join_btn->setObjectName("Join_btn");
        Join_btn->setGeometry(QRect(270, 10, 91, 24));
        Nickname_edit = new QLineEdit(centralwidget);
        Nickname_edit->setObjectName("Nickname_edit");
        Nickname_edit->setGeometry(QRect(110, 10, 151, 24));
        Loading_label = new QLabel(centralwidget);
        Loading_label->setObjectName("Loading_label");
        Loading_label->setGeometry(QRect(100, 220, 171, 22));
        QFont font;
        font.setPointSize(13);
        Loading_label->setFont(font);
        Loading_label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 377, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Send_btn->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        Join_btn->setText(QCoreApplication::translate("MainWindow", "Join", nullptr));
        Nickname_edit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Enter nickname", nullptr));
        Loading_label->setText(QCoreApplication::translate("MainWindow", "Connecting to server...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
