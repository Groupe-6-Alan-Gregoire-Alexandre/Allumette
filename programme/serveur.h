#ifndef SERVEUR_H
#define SERVEUR_H

#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>

class Serveur : QObject
{
        Q_OBJECT

    public:
        Serveur();
        void envoyerDonnees(const QString &message);

    public slots:
        void onNewConnection();
        void onSocketStateChanged(QAbstractSocket::SocketState socketState);
        void onReadyRead();
        void donneesRecues();

    private:
        QTcpServer m_server;
        QList<QTcpSocket*>  clients;
        quint16 tailleMessage;
};

#endif // SERVEUR_H
