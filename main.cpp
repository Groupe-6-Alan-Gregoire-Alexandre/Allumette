#include <QCoreApplication>
#include "allumettes.h"


 /*enum joueur{
    J1,
    J2
 };*/

void afficher() {

    QString J1;
    QString J2;

  cout << "Bienvenue dans le jeu des allumettes" << endl;
  cout << "                                    " << endl;
  cout << "Nommer le joueur 1" << endl;

  cout << "Choisissez le nombre d'allumettes (doit etre superieur a 7) : " << endl;



}

void afficher_allumette(){

    int nb_allumette;

    do {

        cin >> nb_allumette;

        if(nb_allumette < 7){
        cout << "Le nombre d'allumette est insufisant" << endl ;
       }

     }while(nb_allumette < 7);

    cout << "Vous avez choisis " << nb_allumette << " allumettes" ;


}

void jouer_un_coup(){



}

void jeu(){

    afficher();
    afficher_allumette();

}

int main(int argc, char *argv[])
{
    jeu();

    QCoreApplication a(argc, argv);

    return a.exec();
}
