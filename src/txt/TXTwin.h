/**
@brief Module gerant une fenetre dans la console
@warning NON 100% FONCTIONNEL DU AUX MODIFICATIONS DES DONNEES POUR L'AFFICHAGE GRAPHIQUE
@file TXTwin.h
*/


#ifndef TXTWIN_H
#define TXTWIN_H


class TXTwin
{
    private:
        int dimx; /*!< Dimension en x du jeu */
        int dimy; /*!< Dimension en y du jeu */
        char * win; /*!< Tableau de caracteres du jeu, chacun representant un element (decor, piege, piece ou personnage) */

    public:
        /**
        @brief constructeur
        @param [in] dx : entier => dimx du jeu
        @param [in] dy : entier => dimy du jeu
        */
        TXTwin (int dx, int dy);

        /**
        @brief destructeur par defaut
        */
        ~TXTwin ();

        /**
        @brief permet d'effacer ce qui est affiche dans le terminal afin de le mettre a jour
        */
        void clear ();

        /**
        @brief insere le caractere c, de coordonnees (x,y) dans le niveau, dans le tableau 1D contenant les caracteres formant le jeu
        @param [in] x : entier => indice x du caractere dans le tableau 2D formant le jeu
        @param [in] y : entier => indice y du caractere dans le tableau 2D formant le jeu
        @param [in] c : caractere => caractere a ajouter au tableau de caracteres win du jeu
        @warning un caractere de coordonnees (x,y) sera place a l indice x*dimx+y du tableau, dimx etant la dimension en x du niveau
        */
        void print (int x, int y, char c);

        /**
        @brief insere la chaine de caracteres c, de coordonnees (x,y) dans le niveau, dans le tableau 1D contenant les caracteres formant le jeu
        @param [in] x : entier => indice x du caractere dans le tableau 2D formant le jeu
        @param [in] y : entier => indice y du caractere dans le tableau 2D formant le jeu
        @param [in] c : caractere => caractere a ajouter au tableau de caracteres win du jeu
        */
        void print (int x, int y, char* c);

        /**
        @brief ecrit un a un les caracteres du tableau de caracteres win dans le terminal pour former le jeu
        */
        void draw ();

        /**
        @brief met le jeu en pause
        */
        void pause();

        /**
        @brief  lit un caractere si une touche a ete pressee
        @return  touche : caractere lu
        */
        char getCh();
};

void termClear ();


#endif // TXTWIN_H
