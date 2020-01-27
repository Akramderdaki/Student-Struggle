#include "Personnage.h"
#include <cassert>


Personnage::Personnage (const std::string& n)
{
    nom = n;
    score = 1;
    vie = 100;
    vieMax = 100;
    subiDegats = false;
    nbVies = 3;
    vitesse = 5;
    direction = 2;
    posx = 0;
    posy = 0;
    monnaie = 0;
}

Personnage::~Personnage () {}

void Personnage::depDroite (const Niveau& niv) //pour version texte
{
    if (niv.isWalkable(posx,posy+1))
    {
        posy += 1;
    }
    direction = 2;
}

void Personnage::depGauche (const Niveau& niv) //pour version texte
{
    if (niv.isWalkable(posx,posy-1))
    {
        posy -= 1;
    }
    direction = 0;
}

void Personnage::depHaut (const Niveau& niv) //pour version texte
{
    if (niv.isWalkable(posx-1,posy))
    {
        posx -= 1;
    }
    direction = 1;
}

void Personnage::depBas (const Niveau& niv) //pour version texte
{
    if (niv.isWalkable(posx+1,posy))
    {
        posx += 1;
    }
    direction = 3;
}

void Personnage::perdreVie (int degat)
{
    if(subiDegats==false && degat!=0)
    {
        vie -= degat;
        subiDegats=true;
    }
}

void Personnage::prendsXP (float xp)
{
    score += xp;
}

bool Personnage::enVie () const
{
    if(vie>0) return true;
    else return false;
}

const std::string& Personnage::getNom () const {return nom;}
void Personnage::setNom (const std::string& n) {nom = n;}

float Personnage::getScore () const {return score;}

int Personnage::getVie () const {return vie;}
void Personnage::setVie (int v) {if (v>vieMax) v=vieMax; vie = v;}

int Personnage::getVieMax () const {return vieMax;}
void Personnage::setVieMax (int vMax) {vieMax = vMax; vie = vMax;}

bool Personnage::getSubiDegats () const {return subiDegats;}
void Personnage::setSubiDegats (bool s) {subiDegats = s;}

int Personnage::getNbVies () const {return nbVies;}
void Personnage::setNbVies (int nbV) {nbVies = nbV;}

float Personnage::getVitesse () const {return vitesse;}
void Personnage::setVitesse (float vit) {vitesse = vit;}

int Personnage::getDirection () const {return direction;}
void Personnage::setDirection (int dir) {direction = dir;}

float Personnage::getPosX () const {return posx;}
void Personnage::setPosX (float x) {posx = x;}

float Personnage::getPosY () const {return posy;}
void Personnage::setPosY (float y) {posy = y;}

int Personnage::getMonnaie () const {return monnaie;}
void Personnage::addMonnaie (int val) {monnaie += val;}

Personnage& Personnage::operator = (const Personnage& p)
{
    nom = p.getNom();
    score = p.getScore();
    vie = p.getVie();
    vieMax = p.getVieMax();
    subiDegats = p.getSubiDegats();
    nbVies = p.getNbVies();
    vitesse = p.getVitesse();
    direction = p.getDirection();
    posx = p.getPosX();
    posy = p.getPosY();
    monnaie = p.getMonnaie();
    return *this;
}

void Personnage::testRegression ()
{
    Personnage p("nom");

    //on set car les valeurs du perso init peuvent changer
    p.prendsXP(2);
    p.setVieMax(150);
    p.setVie(160);
    p.setVitesse(2);
    p.setDirection(0);
    p.setPosX(1);
    p.setPosY(1);
    p.addMonnaie(5);
    p.setNbVies(4);

    assert(p.getScore() == 3);
    assert(p.getVie() == 150);
    assert(p.getVieMax() == 150);
    assert(p.getVitesse() == 2);
    assert(p.getDirection() == 0);
    assert(p.getPosX() == 1);
    assert(p.getPosY() == 1);
    assert(p.getMonnaie() == 5);
    assert(p.getNbVies() == 4);

    p.perdreVie(100); assert(p.getVie() == 50);
    p.perdreVie(50); assert(p.getVie() == 50);
    p.setSubiDegats(false); p.perdreVie(50); assert(!p.enVie());

    Personnage p2("oui");
    p2 = p;
    assert(p2.getScore() == 3);
    assert(p2.getVie() == 0);
    assert(p2.getVieMax() == 150);
    assert(p2.getVitesse() == 2);
    assert(p2.getDirection() == 0);
    assert(p2.getPosX() == 1);
    assert(p2.getPosY() == 1);
    assert(p2.getMonnaie() == 5);
    assert(p2.getNbVies() == 4);
}
