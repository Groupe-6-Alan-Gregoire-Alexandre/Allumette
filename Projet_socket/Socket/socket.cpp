#include "socket.h"

Socket::Socket(QObject *parent) : QObject(parent)
{

}

void Socket::Connect(){

    socket = new QTcpSocket (this);

    socket->connectToHost("voidrealms.com",80);

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
