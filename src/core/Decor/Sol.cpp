#include "Sol.h"
#include <cassert>


Sol::Sol (bool vis, const std::string& n) : Decor(vis,n) {}

Sol::~Sol () {}

bool Sol::walkable () const {return true;}

bool Sol::fixe () const {return true;}

int Sol::recuperer () const {return 0;}

void Sol::testRegression ()
{
    Sol s;
    assert(s.getNom()=="sol");
    assert(s.fixe() == true);
    assert(s.walkable() == true);
    assert(s.recuperer() == 0);
    s.setVisible(false); assert(s.getVisible() == false);
}
