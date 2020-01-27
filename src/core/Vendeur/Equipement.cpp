#include "Equipement.h"
#include <cassert>

Equipement::Equipement (const std::string& n, int v, int vMax, int vit, int nbV, int p, bool vend)
{
    nom = n;
    vie = v;
    vieMax = vMax;
    vitesse = vit;
    nbVies = nbV;
    prix = p;
    vendu = vend;
}

Equipement::~Equipement () {}

void Equipement::setVendu (bool v) {vendu = v;}
bool Equipement::getVendu () const {return vendu;}

int Equipement::getPrix () const {return prix;}

int Equipement::getVitesse () const {return vitesse;}

int Equipement::getVieMax () const {return vieMax;}

int Equipement::getNbVies () const {return nbVies;}

int Equipement::getVie () const {return vie;}

const std::string& Equipement::getNom () const {return nom;}

void Equipement::testRegression ()
{
    Equipement p;
    Equipement p1("stuff",1,1,1,1,1,true);
    assert(p.getNom() == "");
    assert(p.getPrix() == 0);
    assert(p.getVendu() == false);
    assert(p.getVie() == 0);
    assert(p.getVieMax() == 0);
    assert(p.getNbVies() == 0);
    assert(p.getVitesse() == 0);
    assert(p1.getNom() == "stuff");
    assert(p1.getPrix() == 1);
    assert(p1.getVendu() == true);
    assert(p1.getVie() == 1);
    assert(p1.getVieMax() == 1);
    assert(p1.getNbVies() == 1);
    assert(p1.getVitesse() == 1);

    p1.setVendu(true);
    assert(p1.getVendu() == true);
}
