

#include <QCoreApplication>
#include "allumettes.h"
#include "serveur.h"
#include "client.h"

using namespace std;
#include <iostream>




enum joueur{
    J1,
    J2
};

enum type_code_partie
{
    non_finie,
    joueur_1_gagnant,
    joueur_2_gagnant,
};

//TODO  RETIRER LES VARIABLES GLOBALES : nb_alumette


// Affiche les allumettes
void afficher_allumette(int nb_allumette){
    for(int i = nb_allumette  ; i > 0 ; i--)
    {
        cout << " ! "  ;
    }

    cout << endl;
}

void choisirNombreAllumettesInitial(int * nb_allumette)
{
    do {
        cout << "Choisissez le nombre d'allumettes (doit etre superieur a 7) : " << endl;
        cin >> * nb_allumette;

        if( * nb_allumette < 7){
            cout << "Le nombre d'allumette est insufisant" << endl ;
        }

    }while( * nb_allumette < 7);

    cout << "Vous avez choisis " << * nb_allumette << " allumettes\n" << endl ;
}

// Méthode faisant jouer UN SEUL coup
void jouer_un_coup(int * nb_allumette){

    int choix ;


    do{
        cout << "\n\nCombien d'allumettes voulez-vous enlevez (1 / 2 / 3) : " << endl ;
        cin >> choix ;


        switch(choix)
        {
            case 1 :
                if(*nb_allumette >= 1)
                    *nb_allumette = *nb_allumette - 1 ;
                else
                    cout << "Vous ne pouvez pas enlever plus d'allumettes qu'il en reste." << endl;
                cout << "Il reste " << *nb_allumette << " allumettes.\n" << endl ;
                break;

            case 2 :
                if(*nb_allumette >= 2)
                    *nb_allumette = *nb_allumette - 2 ;
                else
                    cout << "Vous ne pouvez pas enlever plus d'allumettes qu'il en reste." << endl;



                cout << "Il reste " << *nb_allumette << " allumettes.\n" << endl ;
                break;

            case 3 :
                if(*nb_allumette >= 3)
                    *nb_allumette = *nb_allumette - 3 ;
                else
                    cout << "Vous ne pouvez pas enlever plus d'allumettes qu'il en reste." << endl;
                cout << "Il reste " << *nb_allumette << " allumettes.\n" << endl ;


                if(*nb_allumette <= 0)
                    break;

            default:

                cout << "Veuillez choisir un autre nombre " << endl ;
                break;

        }


    }while(choix < 1 || choix > 3);
}

// numero = 1 si serveur; 2 sinon
void jeu( int numero ){
    cout << "Bienvenue dans le jeu des allumettes" << endl;
    cout << "************************************" << endl;

    // déclaration des variables
    int joueur = 1;
    int nb_allumette;

    choisirNombreAllumettesInitial( & nb_allumette);
    afficher_allumette(nb_allumette);

    // jeu
    do
    {
        cout << "" << endl;
        cout << "### C'est au tour du joueur " << joueur << " ### " << endl;

        // on fait jouer un coup
        jouer_un_coup( & nb_allumette );

        // on affiche le plateaucf
        afficher_allumette( nb_allumette );

        // changement de joueur
        joueur = 3 - joueur;
    } while ( nb_allumette !=0 );

    cout << "Le joueur " << joueur << " a gagne la partie !" << endl ;
}

int main(int argc, char *argv[])
{
    std::cout << "Taper 1 pour serveur ; taper 2 pour client" << std::endl;
    int numero;
    std::cin >> numero;
    if ( numero == 1 )
    {
        std::cout << "avant la déclaration" << endl;
        Serveur s;
        std::cout << "après la déclaration" << endl;
    }
    else
    {
        std::cout << "avant la déclaration" << endl;
        Client c;
        c.envoyerMessages("Bonjour");
        std::cout << "après la déclaration" << endl;
    }

   // jeu(numero);

    QCoreApplication a(argc, argv);

    return a.exec();
}

