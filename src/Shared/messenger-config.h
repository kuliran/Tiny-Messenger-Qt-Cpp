#ifndef MESSENGER_CONFIG_H
#define MESSENGER_CONFIG_H

#include <QDataStream>

namespace MessengerConfig
{

inline const char* ClientHostname = "127.0.0.1";
inline const quint16 Port = 2029;
inline const QDataStream::Version QDataStreamVersion = QDataStream::Qt_6_3;
inline const unsigned int MaxServerMessageHistorySize = 3;

}

#endif // MESSENGER_CONFIG_H
