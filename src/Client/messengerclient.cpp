#include "messengerclient.h"
#include <messenger-config.h>

MessengerClient::MessengerClient()
{
    m_blockSize = 0;
    m_socket = new QTcpSocket(this);
    m_isRegistered = false;

    connect(m_socket, &QTcpSocket::connected, this, &MessengerClient::onConnectedToServer);
    connect(m_socket, &QTcpSocket::readyRead, this, &MessengerClient::slot_incomingMessage);
    connect(m_socket, &QTcpSocket::disconnected, this, [this]() {
        emit onDisconnect();
    });

    m_socket->connectToHost(QString(MessengerConfig::ClientHostname), MessengerConfig::Port);
}

MessengerClient::~MessengerClient()
{
    delete m_socket;
}

bool MessengerClient::IsRegistered() const noexcept { return m_isRegistered; }


// Client Requests
void MessengerClient::TryRegister(const QString &nickname) { FireServer(ClientRequest::Register, nickname); }
void MessengerClient::SendMessageToServer(const QString &message) { FireServer(ClientRequest::SendMessage, message); }


void MessengerClient::slot_incomingMessage()
{
    QDataStream in(m_socket);
    in.setVersion(MessengerConfig::QDataStreamVersion);

    if (in.status() == QDataStream::Ok)
    {
        for (;;)
        {
            if (m_blockSize == 0)
            {
                if (m_socket->bytesAvailable() < 2)
                {
                    qDebug() << "<< ERROR: data is less than 2 bytes >>";
                    break;
                }

                in >> m_blockSize;
            }
            if (m_socket->bytesAvailable() < m_blockSize)
            {
                qDebug() << "<< ERROR: data is less than expected >>";
                break;
            }

            ServerRequest request;
            in >> request;

            switch(request)
            {
            case ServerRequest::RegisterResponse:
            {
                m_isRegistered = true;
                emit onSuccessfulRegister();

                break;
            }
            case ServerRequest::SendMessage:
            {
                if (!m_isRegistered) return;
                QString time;
                QString message, nickname;
                in >> nickname >> time >> message;
                m_blockSize = 0;

                emit onIncomingMessage(message,time,nickname);
                break;
            }
            default:
                break;
            }

            break;
        }
    } else {
        emit onIncomingMessage("[message read error]","","");
    }
    //qDebug("incoming");
    // If there's another incoming message, process it from QTcpSocket buffer
    if (m_socket && m_socket->canReadLine())
       emit m_socket->readyRead();
}

void MessengerClient::FireServer(ClientRequest request, const QString& message)
{
    if (!m_socket) return;

    m_data.clear();
    QDataStream out(&m_data, QIODevice::WriteOnly);
    out.setVersion(MessengerConfig::QDataStreamVersion);

    out << quint16(0) << quint8(request) << message;
    out.device()->seek(0);
    out << quint16(m_data.size() - sizeof(quint16));

    m_socket->write(m_data);
}

