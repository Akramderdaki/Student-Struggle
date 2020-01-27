/**
@brief Module gerant le shop
@file Shop.h
*/

#ifndef SHOP_H
#define SHOP_H

#include "Jeu.h"
#include "Image.h"
#include <SDL.h>


class Shop
{
    private:
        SDL_Renderer * ren; /*!< Rendu de la zone d'affichage dans la fenetre */
        int winx; /*!< Coordonnee x du magasin */
        int winy; /*!< Coordonnee y du magasin */
        int TAILLE_SPRITE; /*!< Taille d'une case dans SDLjeu */
        bool actif; /*!< Indique si le shop est actif ou non */
        Image img_Fond; /*!< Image du cadre contenant les items */
        Image img_Items[12][2]; /*!< Tableau d'images 2D contenant les items à vendre /!\pas plus de 8 items a vendre/!\ */
        int vendu[12]; /*!< Tableau contenant les items deja vendus par rapport a leurs indices dans img_Items (si 0, item non vendu,si 1 item vendu) */
        Vendeur bob; /*!< Instance du vendeur recupere du jeu */
        Jeu * jeu; /*!< Pointeur sur le jeu */
        int nbItems; /*!< Nombre d'items que le vendeur vends */
        SDL_Rect * rect_item; /*!< Tableau de rectangle dans le quel sera affiché chaque item */
        SDL_Rect rect_fond; /*!< Rectangle recouvrant le fond (img_Fond) */

    public:

        /**
        @brief constructeur
        @param [in] j : Jeu -> pointeur sur le jeu
        @param [in] r : SDl_Renderer -> ren du shop
        @param [in] x : entier -> coordonnee x du shop
        @param [in] y : entier -> coordonnee y du shop
        @param [in] t : entier -> TAILLE_SPRITE du shop
        @param [in] a : booleen => le shop ne s'affiche pas tout de suite par defaut
        */
        Shop (Jeu * j, SDL_Renderer * r, int x, int y, int t, bool a=false);

        /**
        @brief destructeur par defaut
        */
        ~Shop ();

        /**
        @brief permet de vendre l'equipement pointe par la souris de coordonnees (x,y) si le perso est proche du vendeur
        @param [in] x : entier indiquant la coordonnee x de la souris
        @param [in] y : entier indiquant la coordonnee y de la souris
        */
        void vendre (int x, int y);

        /**
        @brief permet d'afficher les images des items dans leur cadre
        */
        void afficher ();

        /**
        @brief permet d'afficher le magasin si le perso est assez proche du marchand
        */
        void dansMagasin ();

        /**
        @brief initialise le tableau vendu[12] en mettant tous les items en vente (a 0)
        */
        void ouvrir ();

        /**
        @brief accesseur du booleen actif du magasin
        @return booleen
        */
        bool getActif () const;

        /**
        @brief mutateur du booleen actif du magasin
        @param [in] a : booleen indiquant si le magasin est ouvert ou pas
        */
        void setActif (bool a);

        /**
        @brief test de regression s'assurant du bon fonctionnement de la classe
        */
        void testRegression ();
};

   /**
   @brief permet de verifier qu'un point de coordonnees (x,y) appartient a un rectangle (pour verifier sur quel equipement la souris pointe lors d'un achat)
   @param [in] r : SDL_Rect -> rectangle
   @param [in] x : entier -> coordonnee x du point a tester
   @param [in] y : entier -> coordonnee y du point a tester
   @return booleen
   */
   bool in_rect(SDL_Rect r, int x, int y);


#endif // SHOP_H
