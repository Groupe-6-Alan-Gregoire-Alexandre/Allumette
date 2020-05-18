#include <QCoreApplication>
#include "allumettes.h"
using namespace std;
#include <iostream>




 /*enum joueur{
    J1,
    J2
 };

 enum type_code_partie
 {
     joueur_1_gagnant,
     joueur_2_gagnant,
 };*/


 int nb_allumette;
 QString J1;
 QString J2;

void afficher_allumette(){

    cout << "Bienvenue dans le jeu des allumettes" << endl;
    cout << "************************************" << endl;


    do {

        cout << "Choisissez le nombre d'allumettes (doit etre superieur a 7) : " << endl;
        cin >> nb_allumette;

        if(nb_allumette < 7){
        cout << "Le nombre d'allumette est insufisant" << endl ;
       }

     }while(nb_allumette < 7);

    cout << "Vous avez choisis " << nb_allumette << " allumettes" << endl ;


}

void jouer_un_coup(){

    int choix ;

 do{

      cout << "Combien d'allumettes voulez-vous enlevez (1 / 2 / 3) : " << endl ;
      cin >> choix ;

      if (choix == 1){
           nb_allumette = nb_allumette - 1 ;
      }
      else if (choix == 2)
           nb_allumette = nb_allumette - 2 ;
      else if (choix == 3)
           nb_allumette = nb_allumette - 3 ;
      else
          cout << "Veuillez choisir un autre nombre " << endl ;

      cout << "Il reste " << nb_allumette << " allumettes." << endl ;

    }while(nb_allumette !=0 );

    cout << "C'est gagne !!!" << endl ;

}

void jeu(){

    afficher_allumette();
    jouer_un_coup();

}

int main(int argc, char *argv[])
{
    jeu();

    QCoreApplication a(argc, argv);

    return a.exec();
}
