
#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>
#include <QObject>

class QTcpSocket;
class QNetworkSession;

class Client : public QObject
{
        Q_OBJECT

    public:
        Client();
        void envoiMessage( const std::string& s);

    private slots:
        void afficherErreur(QAbstractSocket::SocketError socketError);
        void on_connecte();
        void se_connecter();
        void lireTexte();

    private:
        void jouer_un_coup();

    private:
        QTcpSocket *m_tcpSocket;
        QNetworkSession *m_networkSession;

        QByteArray m_data;
};

#endif
