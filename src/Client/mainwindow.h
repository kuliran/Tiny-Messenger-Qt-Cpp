#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "messengerclient.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isClosedManually;

public slots:
    void slot_register();
    void slot_newMessage(const QString& message, const QString& time, const QString& nickname);

private slots:
    void on_Nickname_edit_returnPressed();

    void on_Join_btn_clicked();

    void on_Message_edit_returnPressed();

    void on_Send_btn_clicked();

private:
    void TryRegister();
    void FireInputToServer();
private:
    Ui::MainWindow *ui;
    MessengerClient *client;
};
#endif // MAINWINDOW_H
