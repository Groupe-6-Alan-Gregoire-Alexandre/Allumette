#include "socket.h"

Socket::Socket(QObject *parent) : QObject(parent)
{

}

void Socket::Connect(){

    socket = new QTcpSocket (this);

    socket->connectToHost("127.0.0.1",4242);

    if(socket->waitForConnected(3000)){
        qDebug() << "connected";

        socket->write("hello\r\n\r\n\r\n");

        socket->waitForBytesWritten(1000);
        socket->waitForReadyRead(3000);
        qDebug() << "Read :" << socket->bytesAvailable() ;

        qDebug() << socket->readAll();

        socket->close();
    }
    else{
        qDebug() << "not connect";
    }








}
