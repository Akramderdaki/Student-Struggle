/**
@brief Module gerant le menu principal et le menu de fin du jeu
@file Menu.h
*/

#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "Niveau.h"
#include "Image.h"


class Menu
{
    private:
        bool menuPrincipal; /*!< Indique si c'est le menu avant le jeu (le menu principal) ou apres la fin du jeu */
        bool option; /*!< Indique si la page d'options (pour menu principal) ou de credits (pour menu fin jeu) est ouverte */
        bool son; /*!< Indique si le son est active ou desactive */
        int TAILLE_SPRITE; /*!< Taille d'une case dans SDLjeu  */
        int TAILLE_BORDURE; /*!< Taille des bordures de SDLjeu */
        SDL_Renderer *ren; /*!< rendu de SDLjeu */
        Image img_MenuBoutons[3][2]; /*!< Tableau 2D d'images contenant les boutons du menu */
        Image img_FinJeuBoutons[2][2]; /*!< Tableau 2D d'images contenant les boutons de menu de fin du jeu */
        Image img_options; /*!< Image du cadre de la fenetre d'options */
        Image img_credits; /*!< Image du cadre de la fenetre de credits */
        Image img_son[2]; /*!< Image des boutons d'activation et desactivation du son */
        Image img_retour; /*!< Image du bouton retour de la fenetre d'options*/
        Image img_commandes; /*!< Image des commandes de la fenetre d'options */
        int hover0, hover1, hover2; /*!< Indiquent si les boutons du menu sont survoles par la souris ou pas (exemple: hover0=1 si le bouton jouer est survole, 0 sinon) */

    public:
        /**
        @brief constructeur
        @param [in] r : SDL_Renderer => renderer du jeu
        @param [in] T_B : entier => TAILLE_BORDURE du jeu
        @param [in] T_S : entier => TAILLE_SPRITE du jeu
        */
        Menu (SDL_Renderer *r, int T_B, int T_S);

        /**
        @brief destructeur par defaut
        */
        ~Menu ();

        /**
        @brief permet de charger les images du menu
        */
        void chargeImage();

        /**
        @brief permet d'afficher les images du menu
        */
        void afficherMenu ();

        /**
        @brief permet de passer les entiers hover0, hover1 et hover2 a 1 quand la souris survole les boutons correspondant, et 0 sinon
        @param [in] sourisX : entier => coordonnee x de la souris
        @param [in] sourisY : entier => coordonnee y de la souris
        */
        void afficheHover(int sourisX, int sourisY);

        /**
        @brief permet de traiter les clics du menu de debut du jeu
        @param [out] niv : Niveau sur lequel on travaille (pour ajouter une sortie apres avoir clique sur jouer)
        @param [in] clicX : entier indiquant la coordonnee x de la souris au moment du clic
        @param [in] clicY : entier indiquant la coordonnee y de la souris au moment du clic
        @param [out] stop : Booleen qui passe a true si le joueur demande a arreter le jeu
        @return entier => 1 si le joueur a clique sur le bouton d'activation/desactivation du son, 0 sinon
        */
        int traitementClic(Niveau & niv, int clicX, int clicY, bool &stop);

        /**
        @brief permet de traiter les clics du menu de fin du jeu
        @param [in] clicX : entier indiquant la coordonnee x de la souris au moment du clic
        @param [in] clicY : entier indiquant la coordonnee y de la souris au moment du clic
        @param [out] stop : Booleen qui passe a true si le joueur demande a arreter le jeu
        @return entier => 1 si le joueur veut rejouer, 0 sinon
        */
        int traitementClicFinJeu(int clicX, int clicY, bool &stop);

        /**
        @brief accesseur de son du menu
        @return booleen indiquant si le son est active ou pas
        */
        bool getSon() const;

        /**
        @brief accesseur de option du menu
        @return booleen indiquant si la fenetre d'options est ouverte ou pas
        */
        bool getOption() const;

        /**
        @brief mutateur de menuPrincipal du menu
        @param booleen indiquant si c'est le menu principal ou le menu de fin du jeu
        */
        void setMenuPrincipale(bool m);
};


#endif // MENU_H
