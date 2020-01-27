#include "Sortie.h"
#include <cassert>


Sortie::Sortie (bool vis, const std::string& n) : Decor(vis,n) {}

Sortie::~Sortie () {}

bool Sortie::walkable () const {return true;}

bool Sortie::fixe () const {return true;}

int Sortie::recuperer () const {return 0;}

void Sortie::testRegression ()
{
    Sortie s;
    assert(s.getNom()=="sortie");
    assert(s.fixe() == true);
    assert(s.walkable() == true);
    assert(s.recuperer() == 0);
    s.setVisible(false); assert(s.getVisible() == false);
}
