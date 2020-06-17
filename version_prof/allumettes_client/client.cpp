
#include <QtNetwork>
#include <QThread>
#include <iostream>
#include <sstream>
#include "client.h"

Client::Client()
    :   m_networkSession(0)
{
    std::cout << "Application Client" << std::endl;
    m_tcpSocket = new QTcpSocket(this);

    // La méthode afficherErreur sera appelée sur le signal error
    connect(m_tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(afficherErreur(QAbstractSocket::SocketError)));

    QNetworkConfigurationManager manager;
    QNetworkConfiguration config;

    std::cout << "Ouverture session" << std::endl;
    m_networkSession = new QNetworkSession(config, this);

    m_networkSession->open();

    m_tcpSocket->abort();

    // La méthode sessionOuverte sera appelée sur le signal opened
    connect(m_tcpSocket, SIGNAL(disconnected()), this, SLOT(se_connecter()));
    connect(m_tcpSocket, SIGNAL(connected()), this, SLOT(on_connecte()));

    // La méthode lireTexte sera appelée sur le signal readyRead
    connect(m_tcpSocket, SIGNAL(readyRead()), this, SLOT(lireTexte()));

    // connexion au serveur sur le port 53000
    se_connecter();
}


//###############################################################################################################
void Client::on_connecte()
{
    std::cout << "Client::on_connecte()" << std::endl;
}


//###############################################################################################################
void Client::se_connecter()
{
    std::cout << "Client::se_connecter()" << std::endl;
    // optionnellement améliorer en donnant la possibilité de choisir l'IP du serveur

    m_tcpSocket->connectToHost( QHostAddress("127.0.0.1").toString(),53000 );
}

//###############################################################################################################
// Méthode appelée lors d'un déclenchement d'une excepetion sur un socket
void Client::afficherErreur(QAbstractSocket::SocketError socketError)
{
    std::cout << "Client::afficherErreur()" << std::endl;
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
            std::cout << "Le serveur n'a pas ete trouve. Verifiez le parametrage du serveur et du port." << std::endl;
            break;
        case QAbstractSocket::ConnectionRefusedError:
            std::cout << "La communication a ete refusee. Verifiez que le serveur est pret, ainsi que le parametrage du serveur et du port." << std::endl;
            break;
        default:
            std::cout << "L'erreur suivante s'est produite : " << m_tcpSocket->errorString().toStdString() << std::endl;
    }
}


//###############################################################################################################
// Méthode faisant jouer UN SEUL coup
void Client::jouer_un_coup(){

    int choix ;

    do{
        std::cout << "\n\nCombien d'allumettes voulez-vous enlevez (1 / 2 / 3) : " << std::endl ;
        std::cin >> choix ;

        if ( choix < 1 || choix > 3 )
            std::cout << "Mauvais nombre" << std::endl ;
    } while(choix < 1 || choix > 3);

    envoiMessage( QString::number(choix).toStdString() );
}


//###############################################################################################################
// Méthode appelée lors de la réception d'un texte
void Client::lireTexte()
{
    // lecture de tout ce que l'on a recu
    std::string line = m_tcpSocket->readAll().toStdString();

    // on découpe suivant les séparateurs "|"
    std::vector<std::string> strings;
    std::string s;
    std::istringstream f(line);
    while (getline(f, s, '|')) {
        // on ne garde que les messages commencant par M
        if ( s[1] == 'M' )
        {
            s.erase(0,2);
            strings.push_back(s + "\n");
        }
    }

    // On traite les messages
    for ( unsigned int i = 0; i < strings.size(); ++i )
    {
        if ( strings[i][1] == '?' )
        {
            jouer_un_coup();
        }
        else
            std::cout << "\t" << strings[i] << std::endl;
    }
}


//###############################################################################################################
// Méthode envoyant un texte au client
void Client::envoiMessage( const std::string& s )
{
    // On envoie le message avec le séparateur "|"
    // Le message commence par M
    std::string mess = "|M" + s + "|";

    QString texte = tr(mess.c_str());
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    out << (quint16)0;
    out << texte;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    m_tcpSocket->write(block);
    m_tcpSocket->flush();
}




