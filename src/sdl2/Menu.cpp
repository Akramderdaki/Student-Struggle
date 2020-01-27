#include "Menu.h"
#include <cassert>
#include <iostream>


Menu::Menu(SDL_Renderer * r, int T_B, int T_S)
{
    assert(T_B>=0 && T_S>0);
    ren=r;
    TAILLE_SPRITE=T_S;
    TAILLE_BORDURE=T_B;
    hover0=0;
    hover1=0;
    hover2=0;
    menuPrincipal=true;
    option=false;
    son=true;
}

Menu::~Menu() {}

void Menu::chargeImage()
{
    img_MenuBoutons[0][0].chargerFichier(ren, "data/img/menu/jouer_0.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_MenuBoutons[0][1].chargerFichier(ren, "data/img/menu/jouer_1.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_MenuBoutons[1][0].chargerFichier(ren, "data/img/menu/options_0.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_MenuBoutons[1][1].chargerFichier(ren, "data/img/menu/options_1.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_MenuBoutons[2][0].chargerFichier(ren, "data/img/menu/quitter_0.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_MenuBoutons[2][1].chargerFichier(ren, "data/img/menu/quitter_1.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_FinJeuBoutons[0][0].chargerFichier(ren, "data/img/menu/rejouer_0.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_FinJeuBoutons[0][1].chargerFichier(ren, "data/img/menu/rejouer_1.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_FinJeuBoutons[1][0].chargerFichier(ren, "data/img/menu/credits_0.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_FinJeuBoutons[1][1].chargerFichier(ren, "data/img/menu/credits_1.png", TAILLE_SPRITE*3, TAILLE_SPRITE*9);
    img_options.chargerFichier(ren, "data/img/menu/options.png", TAILLE_SPRITE*17, TAILLE_SPRITE*17);
    img_credits.chargerFichier(ren, "data/img/menu/credits.png", TAILLE_SPRITE*17, TAILLE_SPRITE*17);
    img_son[0].chargerFichier(ren, "data/img/menu/son_actif.png", TAILLE_SPRITE*2, TAILLE_SPRITE*5);
    img_son[1].chargerFichier(ren, "data/img/menu/son_non_actif.png", TAILLE_SPRITE*2, TAILLE_SPRITE*5);
    img_retour.chargerFichier(ren, "data/img/menu/retour.png", TAILLE_SPRITE, TAILLE_SPRITE*2);
    img_commandes.chargerFichier( ren, "data/img/menu/commandes.png", TAILLE_SPRITE*8, TAILLE_SPRITE*15);
}

void Menu::afficherMenu ()
{
    int indiceSon;
    (son==true) ? indiceSon=0 : indiceSon=1; //indiceSon a 1 si il y a du son

    if (option == false) //afichage du menu si les options ne sont pas ouvertes
    {
        if (menuPrincipal) //Menu d'avant jeu
        {
            img_MenuBoutons[0][hover0].afficher(ren, TAILLE_BORDURE+6*TAILLE_SPRITE, 6*TAILLE_SPRITE);
            img_MenuBoutons[1][hover1].afficher(ren, TAILLE_BORDURE+6*TAILLE_SPRITE, 10*TAILLE_SPRITE);
        }

        else //Menu de fin de jeu
        {
            SDL_SetRenderDrawColor(ren, 63, 80, 96, 255);
            SDL_RenderClear(ren);
            img_FinJeuBoutons[0][hover0].afficher(ren, TAILLE_BORDURE+6*TAILLE_SPRITE, 6*TAILLE_SPRITE);
            img_FinJeuBoutons[1][hover1].afficher(ren, TAILLE_BORDURE+6*TAILLE_SPRITE, 10*TAILLE_SPRITE);
        }

        img_MenuBoutons[2][hover2].afficher(ren, TAILLE_BORDURE+6*TAILLE_SPRITE, 14*TAILLE_SPRITE);
    }

    else //Si les options sont ouvertes
    {
        if (menuPrincipal) //Menu d'avant jeu
        {
            img_options.afficher(ren, 7*TAILLE_SPRITE, 2*TAILLE_SPRITE);
            img_son[indiceSon].afficher(ren, 9*TAILLE_SPRITE, 6*TAILLE_SPRITE);
            img_retour.afficher(ren, 9*TAILLE_SPRITE, 16*TAILLE_SPRITE);
            img_commandes.afficher(ren, 8*TAILLE_SPRITE, 8*TAILLE_SPRITE);
        }

        else //Menu de fin de jeu
        {
            img_credits.afficher(ren, 7*TAILLE_SPRITE, 2*TAILLE_SPRITE);
            img_retour.afficher(ren, 9*TAILLE_SPRITE, 16*TAILLE_SPRITE);
        }
    }
}

void Menu::afficheHover(int sourisX, int sourisY)
{
    if(!option) //Hover des boutons si options pas ouvertes
    {
        if((sourisX>TAILLE_BORDURE+6*TAILLE_SPRITE) && (sourisX<TAILLE_BORDURE+15*TAILLE_SPRITE))
        {
            if((sourisY>6*TAILLE_SPRITE)&&(sourisY<9*TAILLE_SPRITE))
            {
                hover0=1;
            }
            else
            {
                hover0=0;
            }
            if ((sourisY>10*TAILLE_SPRITE)&&(sourisY<13*TAILLE_SPRITE))
            {
                hover1=1;
            }
            else
            {
                hover1=0;
            }
            if((sourisY>14*TAILLE_SPRITE)&&(sourisY<17*TAILLE_SPRITE))
            {
                hover2=1;
            }
            else
            {
                hover2=0;
            }
        }
        else
        {
            hover0=0;
            hover1=0;
            hover2=0;
        }
    }

}

int Menu::traitementClic(Niveau & niv, int clicX, int clicY, bool &stop)
{
    if (!option) //Detection du clic sur les boutons
    {
        if((clicX>TAILLE_BORDURE+6*TAILLE_SPRITE) && (clicX<TAILLE_BORDURE+15*TAILLE_SPRITE)) //dans la fenetre du niveau
        {
            if((clicY>6*TAILLE_SPRITE)&&(clicY<9*TAILLE_SPRITE)) //JOUER
            {
                Sortie *sortie=new Sortie;
                niv.ajoutDecor (1, 10, sortie); //on cree une sortie pour commencer le jeu

                //reset des valeurs pour le menu de fin
                option = false;
                hover0=0;
                hover1=0;
                hover2=0;
            }

            if ((clicY>10*TAILLE_SPRITE)&&(clicY<13*TAILLE_SPRITE)) //OPTIONS
            {
                option=true;
            }

            if((clicY>14*TAILLE_SPRITE)&&(clicY<17*TAILLE_SPRITE)) //QUITTER
            {
                stop = true;
            }
        }
    }

    else
    {
        //son on/off
        if((clicX>9*TAILLE_SPRITE) && (clicX<14*TAILLE_SPRITE)&&(clicY>6*TAILLE_SPRITE)&&(clicY<8*TAILLE_SPRITE))
        {
            (son==true) ? son=false : son=true;
            return 1;
        }

        //sortir des options
        if((clicX>9*TAILLE_SPRITE) && (clicX<11*TAILLE_SPRITE)&&(clicY>16*TAILLE_SPRITE)&&(clicY<17*TAILLE_SPRITE))
        {
            option=false;
        }
    }

    return 0;
}

int Menu::traitementClicFinJeu(int clicX, int clicY, bool &stop)
{
    if (!option) //Detection du clic sur les boutons
    {
        if((clicX>TAILLE_BORDURE+6*TAILLE_SPRITE) && (clicX<TAILLE_BORDURE+15*TAILLE_SPRITE)) //dans la fenetre du niveau
        {
            if((clicY>6*TAILLE_SPRITE)&&(clicY<9*TAILLE_SPRITE)) //JOUER
            {
                stop = true;
                //reset des valeurs pour le menu d'avant jeu
                menuPrincipal=true;
                option = false;
                hover0=0;
                hover1=0;
                hover2=0;
                return 1; //pour rejouer
            }

            if ((clicY>10*TAILLE_SPRITE)&&(clicY<13*TAILLE_SPRITE)) //CREDITS
            {
                option=true;
            }

            if((clicY>14*TAILLE_SPRITE)&&(clicY<17*TAILLE_SPRITE)) //QUITTER
            {
                stop = true;
            }
        }
    }

    else //Detection du clic dans les options
    {
        //quitter les options
        if((clicX>9*TAILLE_SPRITE) && (clicX<11*TAILLE_SPRITE)&&(clicY>16*TAILLE_SPRITE)&&(clicY<17*TAILLE_SPRITE))
        {
            option=false;
        }
    }

    return 0;
}

bool Menu::getSon() const {return son;}

bool Menu::getOption() const {return option;}

void Menu::setMenuPrincipale(bool m) {menuPrincipal=m;}
