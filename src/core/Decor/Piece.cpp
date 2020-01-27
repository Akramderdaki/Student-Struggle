#include "Piece.h"
#include <cassert>


Piece::Piece (int val, bool vis, const std::string& n) : Decor(vis,n)
{
    valeur = val;
}

Piece::~Piece () {}

bool Piece::walkable () const {return true;}

bool Piece::fixe () const {return true;}

int Piece::recuperer () const {return valeur;}

void Piece::testRegression ()
{
    Piece p(10);
    assert(p.getNom()=="piece");
    assert(p.fixe() == true);
    assert(p.walkable() == true);
    assert(p.recuperer() == 10);
    p.setVisible(false); assert(p.getVisible() == false);
}
