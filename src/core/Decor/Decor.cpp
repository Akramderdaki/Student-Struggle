#include "Decor.h"
#include <cassert>


Decor::Decor (bool vis, const std::string& n)
{
    visible = vis;
    nom = n;
}

Decor::~Decor () {}

bool Decor::getVisible () const {return visible;}
void Decor::setVisible (bool vis) {visible = vis;}

const std::string& Decor::getNom () const {return nom;}
