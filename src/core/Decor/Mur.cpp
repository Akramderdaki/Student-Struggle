#include "Mur.h"
#include <cassert>


Mur::Mur (bool vis, const std::string& n) : Decor(vis,n) {}

Mur::~Mur () {}

bool Mur::walkable () const {return false;}

bool Mur::fixe () const {return true;}

int Mur::recuperer () const {return 0;}

void Mur::testRegression ()
{
    Mur m;
    assert(m.getNom()=="mur");
    assert(m.fixe() == true);
    assert(m.walkable() == false);
    assert(m.recuperer() == 0);
    m.setVisible(false); assert(m.getVisible() == false);
}
