#include "Image.h"
#include <cassert>
#include <stdlib.h>
#include <iostream>


Image::Image ()
{
    surface = NULL;
    texture = NULL;
}

Image::~Image () {}

void Image::chargerFichier (SDL_Renderer * renderer, const char* filename, int height, int weight)
{
    assert(height>0); //si weight ayant sa valeur par defaut (=-1) wieght = height

    //On supprime l'ancienne texture avant d'en créer une nouvelle
    if (texture != NULL) SDL_DestroyTexture(texture);

    surface = IMG_Load(filename);
    if (surface == NULL)
    {
        std::cout<<"Impossible de charger le fichier: "<< filename <<"\n";
        std::cout << SDL_GetError() << "\n";
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    if (texture == NULL)
    {
        std::cout << "Erreur de creation de texture depuis le fichier: "<< filename<<"\n";
        std::cout << SDL_GetError() << "\n";
        exit(1);
    }

    /* Taille de l'image */
    if (weight == -1) weight = height; //weight ayant sa valeur par défaut
    h = height;
    w = weight;
}

void Image::charger (SDL_Renderer * renderer)
{
    //On supprime l'ancienne texture avant d'en créer une nouvelle
    if (texture != NULL) SDL_DestroyTexture(texture);

    texture = SDL_CreateTextureFromSurface(renderer,surface);
    SDL_FreeSurface(surface);

    if (texture == NULL)
    {
        std::cout << "Erreur de creation de texture depuis une surface \n";
        std::cout << SDL_GetError() << "\n";
        exit(1);
    }
}

void Image::afficher (SDL_Renderer * renderer, int x, int y)
{
    int cp;
    SDL_Rect r; //Pour les dimensions de l'image
    r.x = x; r.y = y;
    r.w = w; r.h = h;

    cp = SDL_RenderCopy(renderer,texture,NULL,&r);
    assert(cp == 0);
}

SDL_Texture * Image::getTexture() const {return texture;}

void Image::setSurface(SDL_Surface * surf) {surface = surf;}

int Image::getH() const {return h;}

void Image::setH(int height) {h=height;}

int Image::getW() const {return w;}

void Image::setW(int weight) {w=weight;}
