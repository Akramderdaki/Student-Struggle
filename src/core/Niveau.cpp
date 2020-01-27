#include "Niveau.h"
#include <iostream>
#include <cassert>
#include <cstdlib>


//Gerer le tableau 2D de decor dans le vecteur 1D
int Niveau::ind(int i, int j) {return dimy*i+j;}
int Niveau::ind(int i, int j) const {return dimy*i+j;}


Niveau::Niveau (unsigned idN, const std::string& n, int dx, int dy, int temps, int vis)
{
    assert(dx>0 && dy>0 && temps>=0 && vis>=0);
    id = idN;
    nom = n;
    dimx = dx;
    dimy = dy;
    limiteTemps = temps;
    vision = vis;

    /* Initialisation du tableau 2D afin de définir sa taille */
    for (int i=0; i<dimx*dimy; ++i) tabDecor.push_back(NULL);
}

Niveau::~Niveau ()
{
    for (int i=0; i<dimx*dimy; ++i)
    {
        delete tabDecor[i];
        tabDecor[i] = NULL;
    }
}

void Niveau::ajoutDecor (int x, int y, Decor * d)
{
    assert(x>=0 && y>=0 && x<dimx && y<dimy);
    tabDecor[ind(x,y)]=d;
}

void Niveau::supprDecor (int x, int y)
{
    assert(x>=0 && x<dimx && y>=0 && y<dimy);
    delete tabDecor[ind(x,y)];
    tabDecor[ind(x,y)] = new Sol;
}

void Niveau::ajoutPiege (int i, float x, float y, int dir, float d,
                            bool vis, float vit, bool rebond, int delai)
{
    tabPieges.push_back(Piege(i,x,y,dir,d,vis,vit,rebond,delai));
}

void Niveau::deplacerPiege(unsigned i)
{
    assert(i>=0 && i<tabPieges.size());
    int dir = tabPieges[i].getDir();
    if (dir != -1) //Le piege se deplace si il n'est pas fixe (dir=-1)
    {
        int dirx, diry;
        float posx = tabPieges[i].getPosX();
        float posy = tabPieges[i].getPosY();
        tabPieges[i].getVectFromDir(dirx, diry); //vecteur dirx,diry en fct de la direction
        if (isWalkable(posx+dirx,posy+diry)) //Si il peut se déplacer dans le niveau
        {
            posx+=dirx;
            posy+=diry;
        }
        else //Sinon il change de direction
        {
            if (dir == 0) {tabPieges[i].setDir(2);}
            if (dir == 1) {tabPieges[i].setDir(3);}
            if (dir == 2) {tabPieges[i].setDir(0);}
            if (dir == 3) {tabPieges[i].setDir(1);}
        }
    }
}

bool Niveau::isPiege(int x, int y)
{
    for (unsigned i=0; i<tabPieges.size(); ++i) //On parcourt le ableau de piege pour trouver le piege de coord x,y
    {        if (tabPieges[i].getPosX()==x && tabPieges[i].getPosY()==y)
        {
            return true;
        }
    }
    return false;
}

bool Niveau::isWalkable(int x, int y) const
{
    if (x>=0 && x<dimx && y>=0 && y<dimy)
        return tabDecor[ind(x,y)]->walkable();
    else return false;
}

bool Niveau::dansVisionPerso(int a, int b, float x, float y) const
{
    assert(x>=0 && y>=0 && x<dimx && y<dimy); //position perso
    if (vision > 0)
    {
        for (int i=x-vision; i<=x+vision; ++i)
        {
            for (int j=y-vision; j<=y+vision; ++j)
            {
                if (i==a && j==b) return true; //dans vision perso
            }
        }

        return false; //Si pas dans vision perso
    }
    else return true; //si pas de vision limité
}

Decor& Niveau::operator () (int i, int j)
{
    assert(i>=0 && j>=0 && i<dimx && j<dimy);
    return *tabDecor[ind(i,j)];
}

const Decor& Niveau::operator () (int i, int j) const
{
    assert(i>=0 && j>=0 && i<dimx && j<dimy);
    return *tabDecor[ind(i,j)];
}

Piege& Niveau::getPiege(int x, int y)
{
    for (unsigned i=0; i<tabPieges.size(); ++i)
    {        if (tabPieges[i].getPosX()==x && tabPieges[i].getPosY()==y)
        {
            return tabPieges[i];
        }
    }

    return tabPieges[0]; //pour eviter warning
}

const Piege& Niveau::getPiege(unsigned i) const {return tabPieges[i];}

unsigned Niveau::getNbPieges() const {return tabPieges.size();}

Piege& Niveau::getPiege(unsigned i) {return tabPieges[i];}

const std::vector<Piege>& Niveau::getPieges() const {return tabPieges;}

unsigned Niveau::getId () const {return id;}

const std::string& Niveau::getNom () const {return nom;}

int Niveau::getDimX () const {return dimx;}

int Niveau::getDimY () const {return dimy;}

int Niveau::getLimiteTemps () const {return limiteTemps;}

int Niveau::getVision () const {return vision;}
void Niveau::setVision (int vis) {vision = vis;}

void Niveau::testRegression ()
{
    Niveau n(1,"LIFAP4");
    assert(n.getId() == 1 && n.getNom() == "LIFAP4" && n.getDimX() == 21 && n.getDimY() == 21);
    assert(n.getLimiteTemps() == 0 && n.getVision() == 0);

    Decor * d1 = new Sol; n.ajoutDecor(0,1,d1);
    Decor * d2 = new Mur; n.ajoutDecor(1,1,d2);
    Decor * d3 = new Piece(10); n.ajoutDecor(0,2,d3);
    Decor * d4 = new Sortie; n.ajoutDecor(5,2,d4);
    n.ajoutPiege(1,0,0,2,100,1,1,0,0);

    assert(n(1,1).getNom() == "mur");
    assert(n.isWalkable(1,1) == false);
    n.supprDecor(1,1);
    assert(n.isWalkable(1,1) == true);
    assert(n.dansVisionPerso(0,1,4,4));

    assert(n.isPiege(0,0));
    n.deplacerPiege(0);
    assert(n.getPieges().size() == n.getNbPieges());

    n.setVision(2); assert(n.getVision() == 2);
    assert(!n.dansVisionPerso(5,5,8,8));

    //delete d1; delete d2; delete d3; delete d4; //erreur memoire??
    //d1=NULL; d2=NULL; d3=NULL; d4=NULL;
}
