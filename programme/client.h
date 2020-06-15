#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>

class Client: public QObject
{
        Q_OBJECT
    public:
        explicit Client();

        void Connect ();
        void envoyerMessages(const QString &message);

    private slots:
        void donneesRecues();

    signals:

    private:
        QTcpSocket *socket;
        quint16 tailleMessage;
};

#endif // CLIENT_H
