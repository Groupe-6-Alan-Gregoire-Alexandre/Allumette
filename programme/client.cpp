#include "client.h"

#include <iostream>

Client::Client()
{
    std::cout << "Client::Client()" << std::endl;
    Connect();
}

void Client::Connect(){
    std::cout << "Client::Connect()" << std::endl;

    socket = new QTcpSocket(this);

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
void Client::donneesRecues()
{
    std::cout << "Client::donneesRecues()" << std::endl;
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
void Client::envoyerMessages(const QString &message)
{
    std::cout << "Client::envoyerMessages" << std::endl;
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    out << (quint16) 0; // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    out << message; // On ajoute le message à la suite
    out.device()->seek(0); // On se replace au début du paquet
    out << (quint16) (paquet.size() - sizeof(quint16)); // On écrase le 0 qu'on avait réservé par la longueur du message


    // Envoi du paquet préparé à tous les clients connectés au serveur
    for (int i = 0; i < socket->size(); i++)
    {
        socket->write(paquet);
    }

}

