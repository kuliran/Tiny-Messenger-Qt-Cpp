#include "server.h"
#include <messenger-config.h>
#include <messenger-shared.h>
#include <QTime>

Server::Server()
    : m_history(MessageHistory(MessengerConfig::MaxServerMessageHistorySize))
{
    m_blockSize = 0;

    if (!this->listen(QHostAddress::Any, MessengerConfig::Port))
    {
        qDebug() << "<< ERROR OPENING SERVER! >>" << this->errorString().toStdString();
        return;
    }

    qDebug() << "Server Started.";
}

Server::~Server()
{
    for (qsizetype i = 0; i < m_clients.size(); i++)
        delete m_clients[i];

    m_clients.clear();
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    auto* socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slot_incomingMessage);
    connect(socket, &QTcpSocket::disconnected, socket, [socketDescriptor, this]() {
        qDebug() << "CLIENT" << socketDescriptor << "disconnected.";

        Client* client;
        qsizetype i;

        if (!FindClient(socketDescriptor, client, &i)) return;

        m_clients.removeAt(i);
        client->socket->deleteLater();
    });

    QString *nickname = new QString("");
    Client *client = new Client{socket, nickname, socketDescriptor, false};
    m_clients.push_back(client);

    qDebug() << "CLIENT connected:" << socketDescriptor;
}


void Server::slot_incomingMessage()
{
    auto *socket = dynamic_cast<QTcpSocket*>(sender());

    QDataStream in(socket);
    in.setVersion(MessengerConfig::QDataStreamVersion);
    if (in.status() == QDataStream::Ok)
    {
        for (;;)
        {
            if (m_blockSize == 0)
            {
                if (socket->bytesAvailable() < 2)
                {
                    qDebug() << "<< ERROR: data is less than 2 bytes >>";
                    break;
                }
                in >> m_blockSize;
            }
            if (socket->bytesAvailable() < m_blockSize)
            {
                qDebug() << "<< ERROR: data is less than expected >>";
                break;
            }

            ClientRequest request;
            QString message;
            in >> request >> message;

            // qDebug() << sizeof(request); - prints out 1, because it's an unsigned char

            switch(request)
            {
            case ClientRequest::Register:
            {
                RegisterClient(socket->socketDescriptor(), message);
                break;
            }
            case ClientRequest::SendMessage:
            {
                AcceptMessage(socket->socketDescriptor(), message);
                break;
            }
            default:
                break;
            }
            break;
        }
    } else {
        qDebug() << "<< DATA STREAM ERROR! >>";
    }

    m_blockSize = 0;
}

void Server::SendMessageToClients(const QString& message, const QString& nickname)
{
    QByteArray* data = new QByteArray;
    data->clear();

    QDataStream out = QDataStream(data, QIODevice::WriteOnly);
    out.setVersion(MessengerConfig::QDataStreamVersion);

    QString currTime = QTime::currentTime().toString("hh:mm");
    out << quint16(0) << ServerRequest::SendMessage << nickname << currTime << message;
    out.device()->seek(0);
    out << quint16(data->size() - sizeof(quint16));

    for (int i = 0; i < m_clients.size(); i++)
    {
        m_clients[i]->socket->write(*data);
    }

    // Write to MessageHistory
    m_history.Add(data);
}

bool Server::FindClient(qintptr socketDescriptor, Client*& read_client, qsizetype* read_i) const
{
    for (qsizetype i = 0; i < m_clients.size(); i++)
    {
        if (m_clients[i]->socketDescriptor == socketDescriptor)
        {
            read_client = m_clients[i];
            if (read_i)
                *read_i = i;

            return true;
        }
    }
    return false;
}


// Client Requests
void Server::RegisterClient(qintptr socketDescriptor, const QString& nickname)
{
    if (nickname == "") return;

    Client* client;
    if (!FindClient(socketDescriptor, client)) return;
    if (client->isRegistered) return;

    *client->nickname = nickname;
    client->isRegistered = true;
    qDebug() << "CLIENT" << socketDescriptor << "registered as" << nickname.toStdString();

    // Send response to client that they have successfully registered on server
    QByteArray data = QByteArray();
    data.clear();

    QDataStream out = QDataStream(&data, QIODevice::WriteOnly);
    out.setVersion(MessengerConfig::QDataStreamVersion);

    out << quint16(0) << ServerRequest::RegisterResponse;
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));

    client->socket->write(data);

    // Send messages from MessageHistory
    QByteArray* messageData;
    for (unsigned int i = 0; i < m_history.Size(); i++)
    {
        if (!m_history.Get(i, messageData)) break;

        client->socket->write(*messageData);
        client->socket->flush();
    }
}

void Server::AcceptMessage(qintptr socketDescriptor, const QString& message)
{
    if (message == "") return;

    Client* client;
    if (!FindClient(socketDescriptor, client)) return;
    if (!client->isRegistered) return;


    //out << "[Message]:" << client->nickname << "said" << message();

    qDebug() << "[Message]:" << client->nickname->toStdString() << "said" << message.toStdString();
    SendMessageToClients(message, *client->nickname);

    QTextStream ts( stdout );
}
