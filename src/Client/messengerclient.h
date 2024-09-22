#ifndef MESSENGERCLIENT_H
#define MESSENGERCLIENT_H

#include <messenger-shared.h>
#include <QObject>
#include <QTcpSocket>
#include <QTime>

class MessengerClient: public QObject
{
    Q_OBJECT
public:
    MessengerClient();
    ~MessengerClient();
    bool IsRegistered() const noexcept;

    // Client requests
    void TryRegister(const QString& nickname);
    void SendMessageToServer(const QString& message);
signals:
    void onConnectedToServer();
    void onIncomingMessage(const QString& message, const QString& time, const QString& nickname);
    void onSuccessfulRegister();
    void onDisconnect();

private slots:
    void slot_incomingMessage();

private:
    void FireServer(ClientRequest request, const QString& message);
private:
    QTcpSocket *m_socket;
    QByteArray m_data;
    quint16 m_blockSize;
    bool m_isRegistered;
};

#endif // MESSENGERCLIENT_H
