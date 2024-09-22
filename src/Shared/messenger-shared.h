#ifndef MESSENGER_SHARED_H
#define MESSENGER_SHARED_H

enum class ClientRequest: unsigned char
{
    Register = 0,
    SendMessage,
};

enum class ServerRequest: unsigned char
{
    RegisterResponse = 0,
    SendMessage,
};

#endif // MESSENGER_SHARED_H
