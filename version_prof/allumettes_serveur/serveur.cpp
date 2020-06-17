#include "serveur.h"

#include <QtNetwork>
#include <iostream>
#include <sstream>
#include <QString>


//###############################################################################################################
// Constructeur
Serveur::Serveur()
    :   m_tcp_serveur(0), m_network_session(0), m_blockSize(0)
{
    std::cout << "Serveur::Serveur()" << std::endl;
    QNetworkConfigurationManager manager;
    QNetworkConfiguration config = manager.defaultConfiguration();
    m_network_session = new QNetworkSession(config, this);

    // La méthode sessionOuverte sera appelée sur le signal opened
    connect(m_network_session, SIGNAL(opened()), this, SLOT(sessionOuverte()));

    // Ouverture de la session
    m_network_session->open();

    // La méthode connexionClient sera appelée sur le signal newConnection
    connect(m_tcp_serveur, SIGNAL(newConnection()), this, SLOT(connexionClient()));
}

//###############################################################################################################
// Destructeur
Serveur::~Serveur()
{

}

//###############################################################################################################
// Méthode appelée lors de l'ouverture de session
void Serveur::sessionOuverte()
{
    std::cout << "Serveur::sessionOuverte()" << std::endl;
    m_tcp_serveur = new QTcpServer(this); // instanciation

    if (!m_tcp_serveur->listen(QHostAddress::Any, 53000)) // on écoute sur le port 53000
    {
        std::cout << "Le serveur n'a pas été correctement lancee." << std::endl;
    }
    else
    {
        std::cout << "Le serveur est pret \n\nIP: " << m_tcp_serveur->serverAddress().toString().toStdString()
                  << std::endl << "port: " << m_tcp_serveur->serverPort() << std::endl
                  <<  "Lancez l'application Client maintenant." << std::endl;
    }
}

//###############################################################################################################
// Méthode appelée lors de l'ouverture d'une connexion avec un client
void Serveur::connexionClient()
{
    std::cout << "Serveur::connexionClient()" << std::endl;
    // instanciation
    m_socket_client = m_tcp_serveur->nextPendingConnection();

    // La méthode lireTexte sera appelée sur le signal readyRead
    connect(m_socket_client, SIGNAL(readyRead()), this, SLOT(lireTexte()));

    jeu();
}

//###############################################################################################################
// Méthode appelée lors de la réception d'un texte
void Serveur::lireTexte()
{
    // lecture de tout ce que l'on a recu
    std::string line = m_socket_client->readAll().toStdString();

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
        // on transforme le caractère en nombre
        int nombre = strings[i][1] - '0';

        if ( nombre > m_nb_allumettes )
        {
            envoiMessage("Il n'y a pas assez d'allumettes. Rechoississez !\n");
            envoiMessage("?");
        }
        else
        {
            m_nb_allumettes = m_nb_allumettes - nombre;
            fin_de_tour();
        }
    }
}


//###############################################################################################################
// Méthode envoyant un texte au client
void Serveur::envoiMessage( const std::string& s )
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

    m_socket_client->write(block);
    m_socket_client->flush();
}

//###############################################################################################################
// Méthode envoyant un texte au client et l'affichant sur le serveur
void Serveur::afficherPartout( const std::string& s  )
{
    std::cout << "\t" << s << std::endl;
    envoiMessage(s);
}


//###############################################################################################################
// Affiche les allumettes
void Serveur::afficher_allumette(){
    std::string m( "Il reste ");
    m = m + QString::number( m_nb_allumettes ).toStdString() + " allumettes.";
    afficherPartout(m);

    std::string s = "";

    for(int i = m_nb_allumettes  ; i > 0 ; i--)
    {
        s = s + " ! ";
    }

    afficherPartout(s);
}

//###############################################################################################################
void Serveur::choisirNombreAllumettesInitial()
{
    do {
        std::cout << "Choisissez le nombre d'allumettes (doit etre superieur a 7) : " << std::endl;
        std::cin >> m_nb_allumettes;

        if( m_nb_allumettes < 7){
            std::cout << "Le nombre d'allumette est insufisant" << std::endl ;
        }

    }while( m_nb_allumettes < 7);

    std::cout << "Vous avez choisi " << m_nb_allumettes << " allumettes\n" << std::endl ;
}


//###############################################################################################################
// Méthode faisant jouer UN SEUL coup au serveur
void Serveur::jouer_un_coup_serveur(){

    int choix ;

    do{
        std::cout << "\n\nCombien d'allumettes voulez-vous enlevez (1 / 2 / 3) : " << std::endl ;
        std::cin >> choix ;


        switch(choix)
        {
            case 1 :
                if(m_nb_allumettes >= 1)
                    m_nb_allumettes = m_nb_allumettes - 1 ;
                else
                    std::cout << "Vous ne pouvez pas enlever plus d'allumettes qu'il en reste." << std::endl;

                break;

            case 2 :
                if(m_nb_allumettes >= 2)
                    m_nb_allumettes = m_nb_allumettes - 2 ;
                else
                    std::cout << "Vous ne pouvez pas enlever plus d'allumettes qu'il en reste." << std::endl;




                break;

            case 3 :
                if(m_nb_allumettes >= 3)
                    m_nb_allumettes = m_nb_allumettes - 3 ;
                else
                    std::cout << "Vous ne pouvez pas enlever plus d'allumettes qu'il en reste." << std::endl;



                if(m_nb_allumettes <= 0)
                    break;

            default:

                std::cout << "Veuillez choisir un autre nombre " << std::endl ;
                break;
        }
    }while(choix < 1 || choix > 3);
}


//###############################################################################################################
// Méthode faisant jouer UN SEUL coup au client
void Serveur::jouer_un_coup_client(){
    envoiMessage("?");
}

//###############################################################################################################
void Serveur::fin_de_tour()
{
    m_joueur = 3 - m_joueur;

    if ( m_nb_allumettes != 0 )
    {
        afficher_allumette();
        jouer_un_coup();
    }
    else
    {
        std::string s( "Le joueur ");
        s = s + QString::number(m_joueur).toStdString() + " a gagne la partie !";
        afficherPartout(s);
    }
}

//###############################################################################################################
// Méthode faisant jouer UN SEUL coup
void Serveur::jouer_un_coup(){

    if ( m_joueur == 1 )
    {
        jouer_un_coup_serveur();
        fin_de_tour();
    }
    else
        jouer_un_coup_client();
}

//###############################################################################################################
void Serveur::jeu(  ){
    afficherPartout("Bienvenue dans le jeu des allumettes");
    afficherPartout("************************************");

    // déclaration des variables
    m_joueur = 1;

    choisirNombreAllumettesInitial();
    afficher_allumette();

    jouer_un_coup();
}
