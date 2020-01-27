/**
@brief Module gerant le jeu avec affichage SDL2
@file SDLjeu.h
*/


#ifndef SDLJEU_H
#define SDLJEU_H

#include "Image.h"
#include "Timer.h"
#include "Menu.h"
#include "Shop.h"
#include "Jeu.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <map>
#include <string>


class SDLjeu
{
    private:
        SDL_Window * win; /*!< Fenetre du jeu */
        SDL_Renderer * ren; /*!< Rendu de la fenetre du jeu */
        TTF_Font * police; /*!< Police utilisee pour l'ecriture */
        Jeu jeu; /*!< Donnees du jeu */
        Menu * menu; /*!< Menu principal et de fin de jeu */
        Shop * shop; /*!< Magasin du jeu */
        Image img_Perso[4][8]; /*!< Tableau 2D contenant les images du personnage */
        Image img_Sol; /*!< Image du sol */
        Image img_Piege[4][4]; /*!< Tableau 2D contenant les images des pieges */
        Image img_Mur; /*!< Image des murs */
        Image img_Sortie; /*!< Image de la case de sortie */
        Image img_Piece; /*!< Image des pieces */
        Image img_Vendeur; /*!< Image du vendeur */
        Image img_HUD[3]; /*!< Image des informations head up display (coeurs pour les vies, barre verte de PV, et piece pour la monnaie) */
        std::map<std::string, Image> img_texte; /*!< Tableau contenant les images de texte du jeu */
        Mix_Chunk * son_piece; /*!< Son lorsqu'on ramasse une piece */
        Mix_Chunk * son_piques; /*!< Son lorsqu'on percute des piques */
        Mix_Chunk * son_feu; /*!< Son lorsqu'on percute une boule de feu */
        Mix_Chunk * son_sortie; /*!< Son lorsqu'on accede a la sortie */
        Mix_Chunk * son_gauche; /*!< Son de pas du personnage quand il se dirige vers la gauche */
        Mix_Chunk * son_droite; /*!< Son de pas du personnage quand il se dirige vers la droite */
        Mix_Chunk * son_fleche; /*!< Son lorsqu'on percute une fleche */
        Mix_Chunk * son_clic; /*!< Son lorsqu'on effectue un clic */
        Mix_Music * son_jeu; /*!< Musique pendant le jeu */
        Mix_Music * son_menu; /*!< Musique du menu */
        bool AvecSon; /*!< Indique si le son est active ou pas */
        bool sonJeuEnCours; /*!< Indique si la musique du jeu est deja lancee ou pas (pour qu'elle continue entre les niveaux) */
        bool sonMenuEnCours; /*!< Indique si la musique du menu et deja lancee ou pas (pour qu'elle continue entre les menus) */
        int winx, winy; /*!< Dimensions en x et y de la fenetre de jeu */
        int centreurX,centreurY; /*!< Permettent de centrer le niveau dans la fenetre */
        int TAILLE_SPRITE; /*!< Taille d'une case dans le jeu  */
        int TAILLE_BORDURE; /*!< Taille des bordures a droite et a gauche du niveau */
        int framePerso; /*!< Entier incremente en boucle permettant d'afficher les images successives du personnage quand il bouge */
        bool perso_a_bouge; /*!< Indique si le personnage est en mouvement (permet de gerer quand plusieurs touches sont appuyees en meme temps) */
        Timer FPS_perso; /*!< Chronometre qui sert de compteur pour deplacer le personnage a une vitesse par seconde constante */
        Timer FPS_pieges; /*!< Chronometre qui sert de compteur pour deplacer les pieges a une vitesse par seconde constante */
        Timer horloge; /*!< Chronometre pour le temps restant du niveau */
        Timer scoreJeu; /*!< Chronometre pour le score du jeu */

    public:
        /**
        @brief constructeur de la classe
        @param [in] nomPerso : chaine de caracteres => nom du personnage (choisi par le joueur)
        */
        SDLjeu (const std::string& nomPerso);

        /**
        @brief destructeur par defaut
        */
        ~SDLjeu ();

         /**
        @brief Initialise les images des differents textes et leur dimension
        */
        void chargeTexte ();

        /**
        @brief charge toutes les images du jeu
        */
        void chargeImages ();

        /**
        @brief quitte la SDL en cas d'erreur
        @param [in] error : chaine de caracteres indiquant l'erreur en question (elle sera affichee dans le terminal)
        */
        void SDL_exit_error (const char* error);

        /**
        @brief joue un son un nombre determine de fois
        @param [in] s : pointeur vers Mix_chunk : le son a jouer
        @param [in] channel : entier indiquant le canal sur lequel on joue le son (si -1 le son est joue sur le premier canal disponible, sinon sur le canal dont le numero est designe par channel)
        @param [in] loop : entier indiquant le nombre de fois que le son doit etre joue (si 0 le son est joue une fois, sinon le son est joue loop+1 fois)
        */
        void jouerSon (Mix_Chunk * s, int channel, int loop);

        /**
        @brief indique s'il y a une superposition entre les rectangles box1 et box2
        Prends en compte la 2.5D : depassements de la box1 sur la box2 pour donner un effet de profondeur
        @param [in] box1 : Rectangle SDL numero 1 dont on teste les coordonnees
        @param [in] box2 : Rectangle SDL numero 2 dont on teste les coordonnees
        @param [in] img : Image de la box depassant sur l'autre pour donner l'effet de profondeur
        @return booleen qui vaut true s'il y a une superposition (en 2.5D)
        */
        bool overlap (SDL_Rect box1, SDL_Rect box2, const Image& img);

        /**
        @brief indique si la case avec laquelle le personnage entre en collision est accessible
        @param [in] niv : Niveau dans lequel le joueur joue au moment de la collision
        @param [in] img : Image du personnage au moment de la verification
        @param [in] perso_x : entier indiquant les coordonnees x (en pixel) du personnage
        @param [in] perso_y : entier indiquant les coordonnees y (en pixel) du personnage
        @return booleen
        */
        bool isWalkable (const Niveau& niv, const Image& img, int perso_x, int perso_y);

        /**
        @brief gere les collisions avec les differents elements du niveau (pieces, pieges, sortie)
        @param [in,out] niv : Niveau dans lequel le joueur joue au moment de la collision
        @param [in,out] perso : Personnage
        @return entier => -1 si le personnage est mort, 1 si il est passe au niveau suivant, 0 sinon
        */
        int collisions (Niveau& niv, Personnage& perso);

        /**
        @brief gere les deplacements (par pixels) du personnage en fonction des touches sur lesquelles le joueur appuye
        @param [in,out] perso : Personnage
        @param [in] niv : Niveau dans lequel le personnage evolue
        @param [in] touche : caractere indiquant la touche sur laquelle le joueur a appyue
        */
        void actionClavierPixel (Personnage& perso, const Niveau& niv, char touche);

        /**
        @brief gere les deplacements (par pixels) des pieges
        @param [in] niv : Niveau dans lequel evoluent les pieges
        */
        void deplacerPieges (Niveau& niv);

        /**
        @brief permet d'afficher le texte SDL
        @param [in] img : chaine de caracteres indiquant l'index de la map<string,Image> img_texte a afficher
        @param [in] txt : chaine de caracteres contenant le texte a afficher
        @param [in] x : entier contenant la coordonnee x du texte a afficher
        @param [in] y : entier contenant la coordonnee y du texte a afficher
        @param [in] r : entier indiquant la quantite de rouge (RVB) de la couleur du texte a afficher
        @param [in] v : entier indiquant la quantite de vert (RVB) de la couleur du texte a afficher
        @param [in] v : entier indiquant la quantite de bleu (RVB) de la couleur du texte a afficher
        @param [in] propre : booleen indiquant la maniere d'afficher le texte (Solid (pas propre) ou Blended (propre))
        */
        void ecrireTexte(const std::string& img, const std::string& txt,
                            int x, int y, Uint8 r=20, Uint8 v=20, Uint8 b=20, bool propre=false);

        /**
        @brief colorie en noir tout ce qui n'est pas dans le champ de vision du personnage (ne laissant qu'un disque de visibilite autour de lui)
        @param [in] perso : Personnage
        @param [in] visionPerso : entier indiquant le rayon du disque formant le champ de vision du personnage
        */
        void champsVisionPerso (const Personnage& perso, int visionPerso);

        /**
        @brief affichage les informations concernant le personnage a gauche de chaque niveau (HUD pour Head-up display => affichage tete haute)
        @param [in] perso : Personnage
        */
        void afficherHUD (const Personnage& perso);

        /**
        @brief affichage le temps restant pour finir le niveau a gauche de l'ecran
        @param [in] niv : Niveau dans lequel joue le joueur
        */
        void afficherTempsRestant (const Niveau& niv);

        /**
        @brief affichage des pieges dans le niveau
        @param [in] niv : Niveau dans lequel les pieges sont
        */
        void afficherPieges (const Niveau& niv);

        /**
        @brief gere l'affichage de tout le jeu
        @param [in] niv : Niveau a afficher
        @param [in] niv : Personnage
        */
        void afficher (const Niveau & niv, const Personnage& perso);

       /**
        @brief fonction principale gerant le jeu
        (lancement des musiques, gestion des niveaux, gestion du personnage, boucle pour la gestion des evements, etc...)
        @return 0 : pour terminer le jeu a un moment donne
        */
        int jouer ();

        /**
        @brief gestion du menu de fin du jeu
        @return entier => 1 si le joueur veut rejouer, 0 sinon
        */
        int finJeu ();

        /**
        @brief calcul du score final du joueur en fonction des pieces recuperees, des objets achetes, des pieges touches,
        du nombre de fois ou l'on recommence, du temps passe pour finir le jeu, de la vie restante par rapport a la vie maximale
        @return chaine de caracteres contenant le score du joueur
        */
        std::string score ();

        /**
        @brief lit les musiques du jeu et du menu et gere la transition musicale entre les niveaux
        */
        void lireSoundTrack();
};

/**
@brief permet d'obtenir la dimension d'une case en fonction de la taille maximale de la fenetre de jeu
(qui differe selon la resolution de l'ecran de l'ordinateur sur lequel le joueur joue)
@param [in] h : entier indiquant la hauteur de la fenetre de jeu
@param [in] x : entier indiquant la taille en x du menu (taille maximale)
@return entier
*/
int getDimSprite(int h, int x);

/**
@brief Applique un coefficient reducteur a framePerso pour ralentir l'affichage successif des differentes images (pour un deplacement fluide du joueur)
@param [in] frame : entier incremente en boucle pour gerer les frames perso
@param [in] vitesse : flottant indiquant la vitesse de l'element qui se deplace
@return entier indiquant l'indice de l'image a afficher
*/
int frame_reduce(int frame, float vitesse);


#endif // SDLJEU_H
