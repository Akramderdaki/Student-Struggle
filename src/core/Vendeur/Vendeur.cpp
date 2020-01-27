#include "Vendeur.h"
#include <cassert>

using namespace std;


Vendeur::Vendeur (int x, int y)
{
    posx = x;
    posy = y;
}

Vendeur::~Vendeur () {}

void Vendeur::ajoutEquipement (const Equipement& item)
{
    assert(tabMarchandises.size()+1<13);
    tabMarchandises.push_back(item);
}

void Vendeur::vendre (unsigned i)
{
    tabMarchandises.at(i).setVendu(true);
}

int Vendeur::getNbItemEnVente ()
{
    int compteur = 0;

    for (unsigned i=0; i<tabMarchandises.size(); ++i)
    {
        if (!tabMarchandises[i].getVendu())
            compteur++;
    }

    return compteur;
}

const std::vector <Equipement>& Vendeur::getTabMarchandises() const {return tabMarchandises;}

Vendeur& Vendeur::operator = (const Vendeur& v)
{
    posx = v.posx;
    posy = v.posy;
    tabMarchandises.clear(); //on supprime les anciennes marchandises du marchand
    for (unsigned i=0; i<v.getTabMarchandises().size(); ++i)
    {
        if (i >= tabMarchandises.size()) //Si le marchand n'a pas assez d'item dans son sac
        {
            tabMarchandises.resize(i+1);
        }
        tabMarchandises[i] = v.tabMarchandises[i];
    }
    return *this;
}

int Vendeur::getPosX () const {return posx;}
int Vendeur::getPosY () const {return posy;}

void Vendeur::testRegression ()
{
    Equipement e1("potion", 100, 10, 0, 1, 5, false);
    Equipement e2("bottes", 0, 0, 2, 0, 5, false);
    Equipement e3("armure", 0, 100, -1, 0, 10, false);
    Vendeur v(1,1);

    assert(v.getPosX() == 1);
    assert(v.getPosY() == 1);

    v.ajoutEquipement(e1);
    v.ajoutEquipement(e2);
    v.ajoutEquipement(e3);

    v.vendre(2);
    assert(v.getTabMarchandises().size() == 3);
    assert(v.getTabMarchandises().at(2).getVendu() == true);

    Vendeur v2;
    v2=v;
    assert(v2.getTabMarchandises().size() == 3);
    assert(v2.getNbItemEnVente() == 2);
    assert(v2.getPosX() == 1);
    assert(v2.getPosY() == 1);
}
