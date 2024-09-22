#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "messengerclient.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , client(new MessengerClient)
{
    ui->setupUi(this);

    isClosedManually = false;

    ui->MessageBrowser->hide();
    ui->Message_edit->hide();
    ui->Send_btn->hide();
    ui->Nickname_edit->hide();
    ui->Join_btn->hide();
    ui->Loading_label->show();

    connect(client, &MessengerClient::onConnectedToServer, this, [this]() {
        ui->Nickname_edit->show();
        ui->Join_btn->show();
        ui->Loading_label->hide();
    });
    connect(client, &MessengerClient::onSuccessfulRegister, this, &MainWindow::slot_register);
    connect(client, &MessengerClient::onIncomingMessage, this, &MainWindow::slot_newMessage);
    connect(client, &MessengerClient::onDisconnect, this, [this]() {
        if (isClosedManually) return;

        QMessageBox::information(this,"Server down","The server has shut down.");
        QCoreApplication::exit();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    if (client)
        delete client;
}

void MainWindow::TryRegister()
{
    if (client->IsRegistered()) return;

    QString nickname = ui->Nickname_edit->text();
    if (nickname.size() == 0) return;

    client->TryRegister(nickname);
}

void MainWindow::FireInputToServer()
{
    const QString message = ui->Message_edit->text();
    if (message.length() == 0) return;
    ui->Message_edit->clear();

    client->SendMessageToServer(message);
}

void MainWindow::slot_register()
{
    ui->Join_btn->hide();
    ui->Nickname_edit->hide();

    ui->MessageBrowser->show();
    ui->Message_edit->show();
    ui->Send_btn->show();
}

void MainWindow::slot_newMessage(const QString& message, const QString& time, const QString& nickname)
{
    if (time.size() > 0)
    {
        ui->MessageBrowser->append(nickname + " [" + time + "]: " + message);
    } else {
        ui->MessageBrowser->append(message);
    }
}

void MainWindow::on_Nickname_edit_returnPressed() { TryRegister(); }
void MainWindow::on_Join_btn_clicked() { TryRegister(); }

void MainWindow::on_Message_edit_returnPressed() { FireInputToServer(); }
void MainWindow::on_Send_btn_clicked() { FireInputToServer(); }
