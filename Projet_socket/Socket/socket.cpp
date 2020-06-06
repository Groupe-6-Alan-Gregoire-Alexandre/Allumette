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
void Socket::donneesRecues()
{
    /* Même principe que lorsque le serveur reçoit un paquet :
    On essaie de récupérer la taille du message
    Une fois qu'on l'a, on attend d'avoir reçu le message entier (en se basant sur la taille annoncée tailleMessage)
    */
    QDataStream in(socket);

    if (tailleMessage == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16))
             return;

        in >> tailleMessage;
    }

    if (socket->bytesAvailable() < tailleMessage)
        return;


    // Si on arrive jusqu'à cette ligne, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;


    // On remet la taille du message à 0 pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}
