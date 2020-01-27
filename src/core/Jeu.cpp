#include "Jeu.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;


const int NB_NIVEAUX = 5; //Nb de fichier dans le dossier data/Niveaux


Jeu::Jeu (const string& nomPerso)
: perso(nomPerso), persoEnJeu(nomPerso), vendeur(0,21/2)
{
    /* Init de la taille du tableau de Niveaux */
    for (unsigned i=0; i<NB_NIVEAUX; ++i)
    {
        tabNiveau.push_back(NULL);
    }

    /* Init du jeu */
    initJeu(nomPerso);
}

Jeu::~Jeu ()
{
    for(unsigned i=0; i<tabNiveau.size(); ++i)
    {
        delete tabNiveau[i];
        tabNiveau[i] = NULL;
    }
}

Niveau* Jeu::chargerNiveau (const string& nomFichier)
{
    ifstream fic (nomFichier.c_str());
    if (!fic.is_open()) {cout<<"erreur d'ouverture d'un fichier Niveau: "<<nomFichier<<"\n"; exit(EXIT_FAILURE);}

    string titre;
    char trucmuche;

    /* Lecture de l'initialisation du Niveau */
    fic>>titre; assert(titre=="NIVEAU");
    string nomNiveau;
    int idNiveau, dimx, dimy, vuePerso, tempsRestant;
    float perso_posx, perso_posy;

    fic>>idNiveau;
    fic>>nomNiveau;
    fic>>dimx>>trucmuche>>dimy;
    fic>>vuePerso>>trucmuche>>tempsRestant;
    fic>>perso_posx>>trucmuche>>perso_posy;

    /* Création du niveau */
    Niveau* niv = new Niveau(idNiveau,nomNiveau,dimx,dimy,tempsRestant,vuePerso);

    /* Initialisation du personnage dans le niveau */
    perso.setPosX(perso_posx);
    perso.setPosY(perso_posy);

    /* Lecture des options des pièges */
    fic>>titre; assert(titre=="PIEGES");
    int nb; fic>>nb; //Nombre de pieges
    int pieges[nb][7]; //Tableau de paramètres pour construire un piège
    if (nb>0)
    {
        for (int i=0; i<nb; ++i) //Lecture des values et remplissage du tableau
        {
            fic>>trucmuche>>trucmuche;
            fic>>pieges[i][0]>>pieges[i][1]>>pieges[i][2]>>pieges[i][3];
            fic>>pieges[i][4]>>pieges[i][5]>>pieges[i][6];
        }
    }

    /* Lecture de la map */
    fic>>titre; assert(titre=="MAP");
    Decor * d;
    char c;
    for (int i=0; i<dimx; ++i)
    {
        for(int j=0; j<dimy; ++j)
        {
            fic>>c;
            if(c == '#') d = new Mur;      //Mur
            if(c == 'o') d = new Piece(1); //Piece
            if(c == 's') d = new Sortie;   //Sortie
            if(c == '*') d = new Sol;      //Sol

            /* Lecture des pièges du niveau */
            if(c >= '0' && c < '0'+nb) //Comparaison sur des valeurs ASCII pour trouver un chiffre
            {
                int ind = c - '0'; //Valeur numerique de c
                niv->ajoutPiege(pieges[ind][0],i,j,pieges[ind][1],pieges[ind][2],pieges[ind][3],
                                pieges[ind][4],pieges[ind][5],pieges[ind][6]);

                d = new Sol; //On ajoute aussi un fond de sol
            }

            niv->ajoutDecor(i,j,d);
        }
    }

    fic.close();

    return niv;
}

void Jeu::initNiveau(unsigned i, string f) //i numero du niveau
{
    assert(i>=0);

    /* Fichier du niveau */
    if (f=="") //Si f prend sa val par défaut, on récupère le fichier correspondant à l'indice i
    {
        stringstream file;
        file<<"data/Niveaux/niveau"<<i<<".txt";
        f = file.str();
    }

    //Si niveau déjà init, on le supprime pour recuperer ses donnees de base
    if (tabNiveau[i] != NULL) delete tabNiveau[i];

    tabNiveau[i]=chargerNiveau(f);

    persoEnJeu = perso; //Le perso est re init avec ses valeurs de début de niveau
}

void Jeu::initJeu (string nomPerso)
{
    //Si nomPerso prends sa valeur par defaut (=""), on recupere le nom du perso init par le constructeur
    if (nomPerso == "") nomPerso = perso.getNom();

    perso = Personnage(nomPerso); //On crée un perso avec des caracteristiques de base

    /* Init du vendeur et de son shop */
    vendeur = Vendeur(0,21/2); //on crée un nouveau vendeur
    initVendeur(); //on init les items de son magasin

    nivEnCours = 1; //menu
    persoEnJeu = perso; //personnage parcourant les niveaux
    saveId = nivEnCours; //Save le numero de niveau pour le shop

    /* (Re) Init des niveaux de tabNiveaux */
    for (unsigned i=0; i<NB_NIVEAUX; ++i)
    {
        if (tabNiveau[i] != NULL) delete tabNiveau[i];
        tabNiveau[i]=NULL;
    }

    /* Init du 1er niveau (menu) */
    initNiveau(1);
}

void Jeu::niveauSuivant ()
{
    /* 2 CAS :
    La méthode est appelé en sortie de Niveau => Le perso va dans le shop d'id niveau 0
    La méthode est appelé en sortie de shop => Le perso va dans le niveau suivant si il existe / le jeu se termine
    Dans ce cas, saveId contient la valeur du niveau suivant
    */

    perso = persoEnJeu; //save du perso avec les valeurs de fin de niveau

    /* Si le perso atteint le dernier niveau */
    if (nivEnCours >= tabNiveau.size() - 1) //-1 : on ne compte pas le shop
    {
        finJeu();
    }

    /* Si le perso est dans le magasin il passe au niveau suivant */
    else if (nivEnCours == 0)
    {
        nivEnCours = saveId;
        initNiveau(nivEnCours);
    }

    /* Si il sort du menu d'avant jeu (niveau 1) */
    else if (nivEnCours == 1)
    {
        nivEnCours++;
        initNiveau(nivEnCours);
    }

    /* Sinon il finit un niveau et rentre dans le magasin */
    else
    {
        perso.prendsXP(250);
        nivEnCours++;
        goMagasin();
    }
}

void Jeu::recommencer ()
{
    perso.setNbVies(perso.getNbVies()-1); //le perso perd un essai
    perso.prendsXP(-75);
    if (perso.getNbVies() == 0) initJeu(); //si plus d'essai -> on recommence
    else initNiveau(nivEnCours); //sinon on recommence le niveau en cours
}

void Jeu::finJeu ()
{
    nivEnCours = -1;
    perso = persoEnJeu;
}

/* ATTENTION */
/* POUR UN AFFICHAGE GRAPHIQUE (SDL2), VEUILLEZ UTILISEZ LA FONCTION DE SDLJEU PREVU A CETTE EFFET */
void Jeu::actionClavier (const Niveau& niv, char touche)
{
    switch (touche)
    {
        case 'g': //gauche
        {
            persoEnJeu.depGauche(niv);
            break;
        }
        case 'd': //droite
        {
            persoEnJeu.depDroite(niv);
            break;
        }
        case 'h': //haut
        {
            persoEnJeu.depHaut(niv);
            break;
        }
        case 'b': //bas
        {
            persoEnJeu.depBas(niv);
            break;
        }
    }
}

/* ATTENTION */
/* POUR UN AFFICHAGE GRAPHIQUE (SDL2), VEUILLEZ UTILISEZ LA FONCTION DE SDLJEU PREVU A CETTE EFFET */
void Jeu::updateNiveau (Niveau& niv)
{
    for (unsigned i=0; i<niv.getPieges().size(); ++i)
    {
        niv.deplacerPiege(i);
    }

    persoEnJeu.setSubiDegats(false); //Le perso peut perdre des dégats (régulateur)
}

/* ATTENTION */
/* POUR UN AFFICHAGE GRAPHIQUE (SDL2), VEUILLEZ UTILISEZ LA FONCTION DE SDLJEU PREVU A CETTE EFFET */
//return -> 0:noCollision, -1:perdu, 1:gagne
int Jeu::collisionPerso (Niveau& niv)
{
    int perso_x = persoEnJeu.getPosX();
    int perso_y = persoEnJeu.getPosY();

    /* On s'assure que le personnage est bien sur une case valide */
    assert(niv.isWalkable(perso_x, perso_y));

    /* Decor ou le personnage marche */
    Decor& d = niv(perso_x,perso_y);

    /* Collision avec une piece */
    int val = d.recuperer();
    if (val > 0)
    {
        persoEnJeu.addMonnaie(val);
        persoEnJeu.prendsXP(50);
        niv.supprDecor(perso_x,perso_y);
    }

    /* Collision avec la case sortie */
    if (d.getNom() == "sortie") //Case sortie
    {
        niveauSuivant();
        return 1;
    }

    /* Enlève de la vie au Perso si collision avec un piège */
    if (niv.isPiege(perso_x,perso_y))
    {
        Piege p = niv.getPiege(perso_x,perso_y);
        persoEnJeu.perdreVie(p.getDegats());
        persoEnJeu.prendsXP(-5);
    }

    /* Test vie perso */
    if (!persoEnJeu.enVie())
    {
        recommencer();
        return -1;
    }

    else return 0;
}

void Jeu::initVendeur ()
{
    //Equipement(nom,vie,vieMax,vitesse,nbVies,prix,vendu)
    vendeur.ajoutEquipement(Equipement("Potion de vie", 0, 0, 0, 1, 2, false));
    vendeur.ajoutEquipement(Equipement("Bottes de débutant", 0, 0, 2, 0, 4, false));
    vendeur.ajoutEquipement(Equipement("Bouclier d'or", 0, 50, 0, 0, 5, false));
    vendeur.ajoutEquipement(Equipement("Couronne d'or", 0, 50, 3, 1, 10, false));
}

bool Jeu::interagirVendeur (unsigned i)
{
    assert(i>=0 && i<= vendeur.getTabMarchandises().size()); //i indice de tabMarchandise
    Equipement e = vendeur.getTabMarchandises().at(i); //On récupère l'Equipement à acheter

    //Si le personnage a assez d'argent pour acheter l'equipement encore en vente
    if (persoEnJeu.getMonnaie() >= e.getPrix() && e.getVendu() == false)
    {
        if (e.getVieMax()>0) //vieMax monte aussi la vie courante, on update seulement si item monte vie max
            persoEnJeu.setVieMax ( persoEnJeu.getVieMax() + e.getVieMax() );
        persoEnJeu.setVie ( persoEnJeu.getVie() + e.getVie() );
        persoEnJeu.setNbVies ( persoEnJeu.getNbVies() + e.getNbVies() );
        persoEnJeu.setVitesse ( persoEnJeu.getVitesse() + e.getVitesse() );
        persoEnJeu.addMonnaie ( -e.getPrix() );
        persoEnJeu.prendsXP(100);
        vendeur.vendre(i);
        return true;
    }

    return false;
}

void Jeu::goMagasin()
{
    saveId = nivEnCours; //on save l'id du niveau en cours pour y retourner apres le magasin
    nivEnCours = 0; //id du magasin : 0
    initNiveau(nivEnCours, "data/Niveaux/shop.txt");
}

Niveau& Jeu::getNiveau () {return *tabNiveau[nivEnCours];}

const Niveau& Jeu::getNiveau (unsigned i) {return *tabNiveau[i];}

Personnage& Jeu::getPerso () {return persoEnJeu;}
const Personnage& Jeu::getPerso () const {return persoEnJeu;}

Vendeur& Jeu::getVendeur () {return vendeur;}
const Vendeur& Jeu::getVendeur () const {return vendeur;}

int Jeu::getNivEnCours () const {return (int) nivEnCours;}

void Jeu::testRegression ()
{
    Jeu j("Casper");

    assert(j.getNivEnCours() == 1 && j.getPerso().getNom() == "Casper");

    Niveau * niv = j.chargerNiveau("data/Niveaux/niveau1.txt");
    assert(niv->getId()==1);

    /* interaction avec le niveau */
    j.niveauSuivant();
    assert(j.getNivEnCours() == 2); //1e vrai niv
    j.recommencer();
    j.niveauSuivant();
    assert(j.getNivEnCours() == 0); //shop
    j.updateNiveau(j.getNiveau());
    j.finJeu();
    assert(j.getNivEnCours() == -1);

    /* interagir avec le vendeur */
    assert(j.getVendeur().getTabMarchandises().size() == 4);
    j.getPerso().addMonnaie(3); j.interagirVendeur(0);
    assert(j.getPerso().getMonnaie() == 1);
    assert(j.getVendeur().getTabMarchandises()[0].getVendu() == true);
    j.interagirVendeur(0); assert(j.getPerso().getMonnaie() == 1); //Deja vendu
    j.interagirVendeur(1); assert(j.getPerso().getMonnaie() == 1); //Pas assez d'argent
}
