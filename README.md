## Tiny Messenger Qt-Cpp

A really small messenger made in **Qt C++** for both client and server applications.
The network system used is **QTcpSocket**. To display window UI "Qt Widgets Application" on **qmake** build is used.

Features:
- Network data is transfered safely thanks to including a 2 bytes integer value (quint16) at the beginning of every request, which shows how big the request actually is, to prevent processing data before it's fully transfered.
- Each client writes a custom nickname before joining the chat
- Each message displays the **nickname** of the sender and the current **date time** from server
- **Message history**
- When **server shuts down**, all clients are notified and are forced to close the app

How to use + showcase:
- Through **Qt Creator** https://youtu.be/3PITUqkupc8
- Through files https://youtu.be/5w9QAmrLV1I


My first experience with Qt Creator.

kuliran - September 2024
