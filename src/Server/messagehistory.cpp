#include "messagehistory.h"
#include <QDebug>

MessageHistory::MessageHistory(unsigned int maxSize)
{
    m_maxSize = maxSize;
    m_head = new MessageHistory::Message;
    m_size = 0;
}

void MessageHistory::Add(QByteArray* messageData)
{
    if (m_size == m_maxSize)
    {
        Message* newHead = m_head->next;
        delete m_head->data;
        delete m_head;
        m_head = newHead;

        Message* msg;
        if (!At(m_maxSize-2, msg))
            throw "Internal MessageHistory error";

        Message* newMsg = new Message{messageData};
        newMsg->data = messageData;
        msg->next = newMsg;
    } else {
        Message* msg;
        if (!At(m_size, msg))
            throw "Internal MessageHistory error";

        m_size++;

        msg->data = messageData;
        if (m_size != m_maxSize)
            msg->next = new Message;
    }
}

bool MessageHistory::Get(unsigned int index, QByteArray*& read_data) const
{
    Message* msg = nullptr;
    if (At(index, msg) && msg->data)
    {
        read_data = msg->data;
        return true;
    }
    return false;
}

unsigned int MessageHistory::Size() const noexcept { return m_size; }

bool MessageHistory::At(unsigned int index, Message*& read_msg) const
{
    Message* next = m_head;
    for (unsigned int i = 0; i < index; i++)
    {
        next = next->next;
        if (!next)
            return false;
    }

    read_msg = next;
    return true;
}
