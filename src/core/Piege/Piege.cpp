#include "Piege.h"
#include <cassert>


Piege::Piege (int i, float x, float y, int dir, float d, bool vis, float vit, bool rebond, int del)
{
    assert(x>=0 && y>=0 && dir>=-1 && dir<=3);

    id = i;
    initX = x;
    initY = y;
    posx = x;
    posy = y;
    direction = dir;
    degats = d;
    visible = vis;
    vitesse = vit;
    rebondi = rebond;
    activeDelai = del;
    delai = 0;

    //on set les pièges fixe comme non actif de base, et les pièges mouvants comme actif
    if (dir==-1) actif=false;
    else actif=true;
}

Piege::~Piege () {}

float Piege::getPosX () const {return posx;}
void Piege::setPosX (float x) {posx = x;}

float Piege::getPosY () const {return posy;}
void Piege::setPosY (float y) {posy = y;}

float Piege::getInitX() const {return initX;}
void Piege::setInitX(float x) {initX=x; posx=x;}

float Piege::getInitY() const {return initY;}
void Piege::setInitY(float y) {initY=y; posy=y;}

int Piege::getDir() const {return direction;}
void Piege::setDir(int dir) {direction=dir;}

bool Piege::getActif() const {return actif;}
void Piege::setActif(bool a) {actif = a;}

float Piege::getDegats() const {return degats;}
void Piege::setDegats(float d) {degats=d;}

bool Piege::getVisible() const {return visible;}
void Piege::setVisible(bool vis) {visible=vis;}

float Piege::getVitesse() const {return vitesse;}
void Piege::setVitesse(float v) {vitesse=v;}

int Piege::getDelai() const {return delai;}
void Piege::setDelai(int d) {delai=d;}

int Piege::getActiveDelai() const {return activeDelai;}

bool Piege::getRebond() const {return rebondi;}

int Piege::getId() const {return id;}

void Piege::getVectFromDir(int& dirx, int& diry) //traduit une dir (int) en un vecteur direction (x,y)
{
    assert(direction != -1);
    switch (direction)
    {
        case 0: dirx=0; diry=-1; break;
        case 1: dirx=-1; diry=0; break;
        case 2: dirx=0; diry=1; break;
        case 3: dirx=1; diry=0; break;
    }
}

Piege& Piege::operator = (const Piege& p)
{
    id = p.getId();
    posx = p.getPosX();
    posy = p.getPosY();
    initX = p.getInitX();
    initY = p.getInitY();
    direction = p.getDir();
    degats = p.getDegats();
    visible = p.getVisible();
    vitesse = p.getVitesse();
    rebondi = p.getRebond();
    delai = p.getDelai();
    activeDelai = p.getActiveDelai();
    actif = p.getActif();
    return *this;
}


void Piege::testRegression ()
{
    Piege p1(0, 0, 0, 0);
    assert(p1.getId()==0);
    assert(p1.getDir()==0);
    assert(p1.getActif() == true);
    assert(p1.getDegats()==100);
    assert(p1.getVisible()==true);
    assert(p1.getVitesse()==0);
    assert(p1.getRebond()==true);
    assert(p1.getActiveDelai()==0);
    assert(p1.getInitX() == 0);
    assert(p1.getInitY() == 0);
    assert(p1.getPosX() == 0);
    assert(p1.getPosY() == 0);

    p1.setInitX(1);
    p1.setInitY(1);
    p1.setPosX(2);
    p1.setPosY(2);

    p1.setActif(false);
    p1.setDegats(50);
    p1.setVisible(false);
    p1.setVitesse(3);
    p1.setDelai(1);
    p1.setDir(2);

    int dirx, diry;
    p1.getVectFromDir(dirx, diry);
    assert(dirx==0 && diry==1);

    Piege p2(1, 4, 5);
    p2=p1;

    assert(p2.getId() == 0);
    assert(p2.getDir() == 2);
    assert(p2.getDegats() == 50);
    assert(p2.getVisible() == false);
    assert(p2.getVitesse() == 3);
    assert(p2.getRebond() == true);
    assert(p2.getActiveDelai() == 0);
    assert(getActif() == false);
    assert(p2.getInitX() == 1);
    assert(p2.getInitY() == 1);
    assert(p2.getPosX() == 2);
    assert(p2.getPosY() == 2);
}
