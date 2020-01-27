#include "Jeu.h"
#include <string>
#include <iostream>


using namespace std;



int choisir_classe(const string& classe)
{
    if (classe=="Mur") return 0;
    if (classe=="Piece") return 1;
    if (classe=="Sol") return 2;
    if (classe=="Sortie") return 3;
    if (classe=="Piege") return 4;
    if (classe=="Equipement") return 5;
    if (classe=="Vendeur") return 6;
    if (classe=="Niveau") return 7;
    if (classe=="Personnage") return 8;
    if (classe=="Jeu") return 9;

    cout<<endl<<"WARNING : La classe demandee n'a pas ete trouve..."<<endl;
    cout<<"Demarrage du test sur toutes les classes de src/core/"<<endl;
    return -1;
}

int exit_error(const string& msg)
{
    cout<<msg<<endl;
    return -1;
}

int main (int argc, char** argv)
{

    cout<<endl;
    cout<<"Tests de regressions des classes de donnees du jeu"<<endl;
    cout<<"Concerne les classes du dossier src/core/"<<endl;
    cout<<"Si une assertion echoue, la classe correspondante comporte des erreurs"<<endl;

    int go;

    if (argc==1) go=-1;
    if (argc==2) go = choisir_classe(argv[1]);
    if (argc>2)  return exit_error("Trop d'arguments...");

    cout<<endl;


    if (go==-1 || go==0)
    {
        cout<<"Classe Mur (fichier: src/core/Decor/Mur.cpp)"<<endl;
        Mur m; m.testRegression();
        cout<<"Mur OK"<<endl;
    }

    if (go==-1 || go==1)
    {
        cout<<"Classe Piece (fichier: src/core/Decor/Piece.cpp)"<<endl;
        Piece pi(10); pi.testRegression();
        cout<<"Piece OK"<<endl;
    }

    if (go==-1 || go==2)
    {
        cout<<"Classe Sol (fichier: src/core/Decor/Sol.cpp)"<<endl;
        Sol s; s.testRegression();
        cout<<"Sol OK"<<endl;
    }

    if (go==-1 || go==3)
    {
        cout<<"Classe Sortie (fichier: src/core/Decor/Sortie.cpp)"<<endl;
        Sortie st; st.testRegression();
        cout<<"Sortie OK"<<endl;
    }

    if (go==-1 || go==4)
    {
        cout<<"Classe Piege (fichier: src/core/Piege/Piege.cpp)"<<endl;
        Piege p(0,0,0); p.testRegression();
        cout<<"Piege OK"<<endl;
    }

    if (go==-1 || go==5)
    {
        cout<<"Classe Equipement (fichier: src/core/Vendeur/Equipement.cpp)"<<endl;
        Equipement e; e.testRegression();
        cout<<"Equipement OK"<<endl;
    }

    if (go==-1 || go==6)
    {
        cout<<"Classe Vendeur (fichier: src/core/Vendeur/Vendeur.cpp)"<<endl;
        Vendeur v; v.testRegression();
        cout<<"Vendeur OK"<<endl;
    }

    if (go==-1 || go==7)
    {
        cout<<"Classe Niveau (fichier: src/core/Niveau.cpp)"<<endl;
        Niveau niv; niv.testRegression();
        cout<<"Niveau OK"<<endl;
    }

    if (go==-1 || go==8)
    {
        cout<<"Classe Personnage (fichier: src/core/Personnage.cpp)"<<endl;
        Personnage perso; perso.testRegression();
        cout<<"Personnage OK"<<endl;
    }

    if (go==-1 || go==9)
    {
        cout<<"Classe Jeu (fichier: src/core/Jeu.cpp)"<<endl;
        Jeu j; j.testRegression();
        cout<<"Jeu OK"<<endl;
    }


    cout<<endl<<"Tout est OK!"<<endl;
    cout<<"a vos machines ;)"<<endl<<endl;

	return 0;
}
