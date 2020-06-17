#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class QTcpServer;
class QTcpSocket;
class QNetworkSession;

class Serveur : public QObject{
    Q_OBJECT

public:
    Serveur();
    ~Serveur();

private slots:
    void sessionOuverte();
    void connexionClient();
    void lireTexte();

private:
    void jeu();
    void envoiMessage( const std::string& s );
    void afficherPartout( const std::string& s );
    void jouer_un_coup_serveur();
    void jouer_un_coup_client();
    void jouer_un_coup();
    void fin_de_tour();

    void afficher_allumette();
    void choisirNombreAllumettesInitial();

private:
    QTcpServer *m_tcp_serveur; // La socket général
    QTcpSocket *m_socket_client; // La socket client
    QNetworkSession *m_network_session; // La session de connexion
    quint16 m_blockSize;

    int m_nb_allumettes;
    int m_joueur;

};

#endif
