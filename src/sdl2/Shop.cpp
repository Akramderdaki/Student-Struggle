#include "Shop.h"
#include <cassert>
#include <sstream>


const int SHOP_DIMX = 6; //dimx du niveau shop dans data/Niveaux
const int SHOP_DIMY = 21; //dimy du niveau shop dans data/Niveaux


bool in_rect(SDL_Rect * r, int x, int y)
{
    return (x >= r->x) && (y >= r->y) &&
           (x < r->x + r->w) && (y < r->y + r->h);
}


Shop::Shop (Jeu * j, SDL_Renderer * r, int x, int y, int t, bool a)
{
    assert(x>0 && y>0 && t>0);
    jeu = j;
    ren = r;
    winx = x;
    winy = y;
    TAILLE_SPRITE = t;
    actif = a;

    bob = jeu->getVendeur(); //vendeur du jeu

    /* Fond */ //=>Situé sous le niveau avec une bordure de 50
    rect_fond.x = (winx - (SHOP_DIMY*TAILLE_SPRITE))/2 + 50;
    rect_fond.y = SHOP_DIMX*TAILLE_SPRITE + 50;
    rect_fond.h = winy - rect_fond.y - 50;
    rect_fond.w = SHOP_DIMY*TAILLE_SPRITE - 2*50;
    img_Fond.chargerFichier(ren, "data/img/shop/fond.png", rect_fond.h, rect_fond.w);

    /* Items */
    nbItems = bob.getTabMarchandises().size(); //nombre d'items a vendre
    rect_item = new SDL_Rect[nbItems];

    // pour garder une taille paire (ne pas gener l'affichage)
    int nb; (nbItems%2!=0) ? nb=nbItems+1 : nb=nbItems; //nb pour définir la taille des images

    //On assigne les coordonnées des rectangles d'items ainsi que leurs images
    int bordureX = rect_fond.w*0.05; //bordure de l'image de fond en X
    int bordureY = rect_fond.h*0.2; //bordure de l'image de fond en Y
    //On place les items dans le fond en prenant en compte les bordures
    for (int i=0; i<nbItems; ++i) //2 lignes composés de x/2 items
    {
        int coeffX = i%2; //i=0 : 0, i=1 : 1, i=2 : 0, i=3 : 1
        int coeffY = i/2; //i=0 : 0, i=1 : 0, i=2 : 1, i=3 : 1
        rect_item[i].w = (img_Fond.getW()-2*bordureX)/2 ;
        rect_item[i].h = (img_Fond.getH()-4*bordureX)/(nb/2) ; //bordure du bas = 4 bordureX (2*bordure cote)
        rect_item[i].x = rect_fond.x+bordureX + coeffX*rect_item[i].w;
        rect_item[i].y = rect_fond.y+bordureY + coeffY*rect_item[i].h;

        std::stringstream file; file<<"data/img/shop/item"<<i<<".png";
        img_Items[i][0].chargerFichier(ren, file.str().c_str(), rect_item[i].h, rect_item[i].w);
        std::stringstream file2; file2<<"data/img/shop/item"<<i<<"_v.png";
        img_Items[i][1].chargerFichier(ren, file2.str().c_str(), rect_item[i].h, rect_item[i].w);
        ouvrir(); //ouverture du magasin pas cher pas cher -50%
    }
}

Shop::~Shop ()
{
    delete [] rect_item;
    rect_item = NULL;
}

void Shop::vendre (int x, int y)
{
    /* Si la souris clique sur un item */
    for (int i=0; i<nbItems; ++i)
    {
        if (in_rect(&rect_item[i],x,y)) //la souris est sur l'image d'un item
        {
            if (jeu->interagirVendeur(i))
            {
                vendu[i]=1;
            }
        }
    }
}

void Shop::afficher ()
{
    /* Afficher le fond */
    img_Fond.afficher(ren,rect_fond.x,rect_fond.y);


    /* Afficher les items */
    for (int g=0; g<nbItems; ++g)
    {
        img_Items[g][vendu[g]].afficher(ren,rect_item[g].x,rect_item[g].y);
    }
}

void Shop::dansMagasin ()
{
    if (actif) //seulement si le personnage est dans la zone de vente
    {
        afficher();
    }
}

void Shop::ouvrir ()
{
    for (int i=0; i<nbItems; ++i)
    {
        vendu[i] = 0; //Tous les items sont en vente
    }
}

bool Shop::getActif () const {return actif;}

void Shop::setActif (bool a) {actif = a;}
