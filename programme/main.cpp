

#include <QCoreApplication>
#include "allumettes.h"
using namespace std;
#include <iostream>




enum joueur{
    J1,
    J2
};

struct plateau
{
    joueur nb_allumette;
};

enum type_code_partie
{
    non_finie,
    joueur_1_gagnant,
    joueur_2_gagnant,
};

//TODO  RETIRER LES VARIABLES GLOBALES : nb_alumette

int nb_allumette;

// Affiche les allumettes
void afficher_allumette(){
    for(int i = nb_allumette  ; i > 0 ; i--)
    {
        cout << " ! "  ;
    }

    cout << endl;
}

void choisirNombreAllumettesInitial()
{
    do {
        cout << "Choisissez le nombre d'allumettes (doit etre superieur a 7) : " << endl;
        cin >> nb_allumette;

        if(nb_allumette < 7){
            cout << "Le nombre d'allumette est insufisant" << endl ;
        }

    }while(nb_allumette < 7);

    cout << "Vous avez choisis " << nb_allumette << " allumettes\n" << endl ;
}

// Méthode faisant jouer UN SEUL coup
void jouer_un_coup(){

    int choix ;


    do{
        cout << "\n\nCombien d'allumettes voulez-vous enlevez (1 / 2 / 3) : " << endl ;
        cin >> choix ;


    switch(choix)
    {
case 1 :
        if(nb_allumette >= 1)
            nb_allumette = nb_allumette - 1 ;
        else
            cout << "Vous ne pouvez pas enlever plus d'allumettes qu'il en reste." << endl;
    cout << "Il reste " << nb_allumette << " allumettes.\n" << endl ;
    break;

case 2 :
    if(nb_allumette >= 2)
        nb_allumette = nb_allumette - 2 ;
    else
        cout << "Vous ne pouvez pas enlever plus d'allumettes qu'il en reste." << endl;



    cout << "Il reste " << nb_allumette << " allumettes.\n" << endl ;
    break;

case 3 :
        if(nb_allumette >= 3)
            nb_allumette = nb_allumette - 3 ;
        else
            cout << "Vous ne pouvez pas enlever plus d'allumettes qu'il en reste." << endl;
    cout << "Il reste " << nb_allumette << " allumettes.\n" << endl ;


    if(nb_allumette <= 0)

   break;

   default:

        cout << "Veuillez choisir un autre nombre " << endl ;
        break;

        }


    }while(choix < 1 || choix > 3);
}


void jeu(){
    cout << "Bienvenue dans le jeu des allumettes" << endl;
    cout << "************************************" << endl;

    // déclaration des variables
    int joueur = 1;

    choisirNombreAllumettesInitial();
    afficher_allumette();

    // jeu
    do
    {
        cout << "" << endl;
        cout << "### C'est au tour du joueur " << joueur << " ### " << endl;

        // on fait jouer un coup
        jouer_un_coup();

        // on affiche le plateaucf
        afficher_allumette(  );

        // changement de joueur
        joueur = 3 - joueur;
    } while ( nb_allumette !=0 );

    // TODO afficher qui a gagné
    cout << "Le joueur " << joueur << " a gagne la partie !" << endl ;
}

int main(int argc, char *argv[])
{
    jeu();


    QCoreApplication a(argc, argv);

    return a.exec();
}

