#ifndef MESSAGEHISTORY_H
#define MESSAGEHISTORY_H

#include <QByteArray>

class MessageHistory
{
public:
    MessageHistory(unsigned int maxSize);
    void Add(QByteArray* messageData);
    bool Get(unsigned int index, QByteArray*& read_data) const;
    unsigned int Size() const noexcept;
private:
    struct Message
    {
        QByteArray* data = nullptr;
        Message* next = nullptr;
    };

    bool At(unsigned int index, Message*& read_msg) const;
private:
    Message* m_head;
    unsigned int m_maxSize;
    unsigned int m_size;
};

#endif // MESSAGEHISTORY_H
