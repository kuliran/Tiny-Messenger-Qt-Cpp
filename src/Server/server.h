#ifndef SERVER_H
#define SERVER_H

#include "messagehistory.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

struct Client
{
    QTcpSocket* socket;
    QString* nickname;
    qintptr socketDescriptor;
    bool isRegistered;

    ~Client()
    {
        socket->disconnect();
        delete nickname;
    }
};

class Server: public QTcpServer
{
public:
    Server();
    ~Server();

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slot_incomingMessage();

private:
    void SendMessageToClients(const QString& message, const QString& nickname);
    bool FindClient(qintptr socketDescriptor, Client*& read_client, qsizetype* read_i = nullptr) const;

    // Client requests
    void RegisterClient(qintptr socketDescriptor, const QString& nickname);
    void AcceptMessage(qintptr socketDescriptor, const QString& message);
private:
    QVector<Client*> m_clients;
    quint16 m_blockSize;
    MessageHistory m_history;
};

#endif // SERVER_H
