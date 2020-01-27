/**
@brief Module gerant une image avec SDL
@file Image.h
*/


#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <SDL_image.h>


class Image
{
    private:
        SDL_Surface * surface; /*!< Zone d'affichage d'une image */
        SDL_Texture * texture; /*!< Rectange de pixels */
        int h,w; /*!< Hauteur et largeur des images */

    public:
        /**
        @brief constructeur par defaut
        */
        Image ();

        /**
        @brief destructeur par defaut
        */
        ~Image ();

        /**
        @brief charge une image en une texture dans un rendu depuis un fichier
        @param [in] ren : SDl_Renderer -> zone d'affichage
        @param [in] fichier : chaine de caracteres -> nom du fichier a charger
        @param [in] height : entier -> hauteur de l'image
        @param [in] weight : entier -> largeur de l'image (-1 par defaut => prends la meme valeur que la hauteur)
        */
        void chargerFichier (SDL_Renderer * ren, const char* fichier, int height, int weight=-1);

        /**
        @brief cree une texture dans le rendu depuis la surface
        @param [in] ren : SDl_Renderer -> zone d'affichage
        */
        void charger (SDL_Renderer * ren);

        /**
        @brief permet d'afficher une texture aux coordonnees x et y dans un rendu donne
        @param [in] ren : SDl_Renderer -> zone d'affichage
        @param [in] x : entier -> coordonnee x du rectangle a recuperer
        @param [in] y : entier -> coordonnee y du rectangle a recuperer
        */
        void afficher (SDL_Renderer * ren, int x, int y);

        /**
        @brief accesseur de la texture d'une image
        @return texture
        */
        SDL_Texture * getTexture() const;

        /**
        @brief mutateur de la surface d'une image
        @param [in] surf : SDL_surface
        */
        void setSurface(SDL_Surface * surf);

        /**
        @brief accesseur de la largeur d'une image
        @return entier
        */
        int getW() const;

        /**
        @brief mutateur de la largeur d'une image
        @param [in] weight : entier indiquant la largeur
        */
        void setW(int weight);

        /**
        @brief accesseur de la hauteur de l'image
        @return entier
        */
        int getH() const;

        /**
        @brief mutateur de la hauteur de l'image
        @param [in] height : entier indiquant la hauteur
        */
        void setH(int height);
};


#endif // IMAGE_H
