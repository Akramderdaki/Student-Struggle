/**
@brief Module gerant un niveau (une map)
@file Niveau.h
*/


#ifndef NIVEAU_H
#define NIVEAU_H

#include "Piege/Piege.h"
#include "Decor/Piece.h"
#include "Decor/Sortie.h"
#include "Decor/Mur.h"
#include "Decor/Sol.h"
#include <string>
#include <vector>


class Niveau
{
    private:
        unsigned id; /*!< Identifiant du niveau (0, 1, 2, 3 ...) */
        std::string nom; /*!< Nom du niveau */
        int dimx; /*!< Dimension en X du niveau */
        int dimy; /*!< Dimension en Y du niveau */
        std::vector <Decor*> tabDecor; /*!< Tableau de decors du niveau */
        std::vector <Piege> tabPieges; /*!< Tableau de pieges du niveau */
        int limiteTemps; /*!< Temps accorde pour finir le niveau en secondes (optionnel) */
        int vision; /*!< Vision du personnage (nombre de cases visibles autour de lui) */

    public:
        /**
        @brief constructeur avec parametres
        @param [in] idN = 0 : entier positif => identifiant du niveau (unsigned = unsigned int)
        @param [in] n = "" : chaine de caracteres => nom du niveau
        @param [in] dx = 21 : entier => dimx du niveau
        @param [in] dy = 21 : entier => dimy du niveau
        @param [in] temps = 0 : entier => limiteTemps du niveau (0 indique que le niveau n'a pas de limite de temps)
        @param [in] vis = 0 : entier => champ de vision du personnage dans un niveau (0 indique qu'il n'y a pas de restrictions)
        */
        Niveau (unsigned idN=0, const std::string& n="", int dx=21, int dy=21, int temps=0, int vis=0);

        /**
        @brief destructeur par defaut
        */
        ~Niveau ();

        /**
        @brief ajoute un decor dans le niveau a la position x,y
        @param [in] x : entier indiquant la coordonnee x du decor a ajouter
        @param [in] y : entier indiquant la coordonnee y du decor a ajouter
        @param [in] d : Decor* est un pointeur sur le decor a ajouter
        */
        void ajoutDecor (int x, int y, Decor * d);

        /**
        @brief supprime le decor de position x,y dans le niveau
        @param  [in] x : entier indiquant la coordonnee x du decor a supprimer
        @param  [in] y : entier indiquant la coordonnee y du decor a supprimer
        */
        void supprDecor (int x, int y);

        /**
        @brief ajoute un piege d'identifiant i dans le tableau de pieges du niveau
        @param  [in] i : entier indiquant l'identifiant du piege a ajouter
        @param  [in] x : flottant indiquant la coordonnee x du piege a ajouter
        @param  [in] y : flottant indiquant la coordonnee y du piege a ajouter
        @param  [in] dir : entier indiquant la direction du piege a ajouter (-1 fixe, 0 gauche, 1 haut, 2 droite, 3 bas)
        @param  [in] d : flottant indiquant les degats occasionnes par le piege a ajouter
        @param  [in] vis : booleen indiquant si le piege est visible ou pas
        @param  [in] vit : flottant indiquant la vitesse de deplacement du piege
        @param  [in] rebond : booleen indiquant si le piege rebondit lors de sa collision avec un mur
        @param  [in] delai : entier indiquant le delai d'activation du piege (0 si non)
        */
        void ajoutPiege (int i, float x, float y, int dir, float d,
                            bool vis, float vit, bool rebond, int delai);

        /**
        @brief procedure gerant les deplacements du piege d'indice i dans le tableau de pieges du niveau
        @param  [in] i : entier positif indiquant l'indice du piege dans le tableau
        */
        void deplacerPiege(unsigned i);

        /**
        @brief indique si l'element a la position de coordonnees (x,y) est un piege
        @param  [in] x : entier indiquant la coordonnee x de l'element a tester
        @param  [in] y : entier indiquant la coordonnee y de l'element a tester
        @return booleen
        */
        bool isPiege(int x, int y);

        /**
        @brief indique si la case de coordonnees (x,y) est accessible
        @param [in] x : entier indiquant la coordonnee x de la case a tester
        @param [in] y : entier indiquant la coordonnee y de la case a tester
        @return booleen
        */
        bool isWalkable (int x, int y) const;

        /**
        @brief indique si le decor de coordonnees (a,b) est dans le champ de vision du personnage de coordonnees (x,y)
        @param a,b : entiers => coordonnees d'un decor
        @param x,y : flottants => coordonnees du personnage
        @return booleen
        */
        bool dansVisionPerso (int a, int b, float x, float y) const;

        /**
        @brief surcharge de l'operateur () afin d'acceder au decor(i,j) dans le tableau
        @param [in] i : entier indiquant la coordonnee en x du decor
        @param [in] j : entier indiquant la coordonnee en y du decor
        @return *tabDecor[ind(i,j)] : pointeur sur le Decor d'indice i,j
        @warning renvoie une reference non modifiable
        */
        const Decor& operator () (int i, int j) const;

        /**
        @brief surcharge de l'operateur () afin d'acceder au decor(i,j) dans le tableau
        @param [in] i : entier indiquant la coordonnee en x du decor
        @param [in] j : entier indiquant la coordonnee en y du decor
        @return *tabDecor[ind(i,j)] : pointeur sur le Decor d'indice i,j
        @warning renvoie une reference modifiable
        */
        Decor& operator () (int i, int j);

        /**
        @brief permet d'acceder au piege de coordonnees (x,y)
        @param [in] x : entier indiquant la coordonnee x du piege
        @param [in] y : entier indiquant la coordonnee y du piege
        @return tabPieges[i]: Piege d'indice i dans le tableau de pieges du niveau
        @warning renvoie une reference modifiable
        */
        Piege& getPiege(int x, int y);

        /**
        @brief permet d'acceder au piege d'indice i dans le tableau de pieges du niveau
        @param [in] i : entier positif indiquant l'indice du piege dans le tableau
        @return tabPieges[i]: Piege d'indice i dans le tableau de pieges du niveau
        @warning renvoie une reference non modifiable
        */
        const Piege& getPiege(unsigned i) const;

        /**
        @brief permet d'acceder au piege d'indice i dans le tableau de pieges du niveau
        @param [in] i : entier positif indiquant l'indice du piege dans le tableau
        @return tabPieges[i]: Piege d'indice i dans le tableau de pieges du niveau
        @warning renvoie une reference modifiable
        */
        Piege& getPiege(unsigned i);

        /**
        @brief permet d'acceder au tableau de pieges du niveau
        @return tabPieges: Tableau de pieges
        @warning renvoie une reference modifiable
        */
        const std::vector<Piege>& getPieges() const;

        /**
        @brief accesseur du nombre de pieges dans un niveau
        @return tabPieges.size(): entier positif indiquant la taille du tableau de pieges du niveau
        */
        unsigned getNbPieges() const;

        /**
        @brief accesseur de l'identifiant du niveau
        @return id : entier positif (unsigned = unsigned int)
        */
        unsigned getId () const;

        /**
        @brief accesseur du nom du Niveau
        @return nom : chaine de caracteres
        */
        const std::string& getNom () const;

        /**
        @brief accesseur de dimX du niveau
        @return dimx : entier
        */
        int getDimX () const;

        /**
        @brief accesseur de dimY du niveau
        @return dimy : entier
        */
        int getDimY () const;

        /**
        @brief accesseur de la limiteTemps du niveau
        @return limiteTemps : entier
        @warning 0 = pas de limite de temps
        */
        int getLimiteTemps () const;

        /**
        @brief accesseur de la vision du personnage dans un niveau
        @return vision : entier indiquant le nombre de cases entrant dans le champ de vision du personnage
        */
        int getVision () const;

        /**
        @brief mutateur de la vision d'un Personnage dans un niveau
        @param [in] vis : entier indiquant le nouveau nombre de cases entrant dans le champ de vision du personnage
        */
        void setVision (int vis);

        /**
        @brief Retourne l'indice 1D de i,j indices d'un tableau 2D
        @param i,j : int (indices du tableau 2D)
        @return dimx*dimy*j+i
        */
        int ind(int i, int j);

        /**
        @brief Retourne l'indice dans un tableau 1D d'un element d'indice i,j  dans tableau 2D de taille [dimx][dimy]
        @param i,j : entiers indiquant les indices de l'element dans le tableau 2D
        @return dimx*dimy*j+i : entier indiquant l'indice de l'elements dans le tableau 1D
        */
        int ind(int i, int j) const;

        /**
        @brief test de regression s'assurant du bon fonctionnement de la classe
        */
        void testRegression ();
};


#endif // NIVEAU_H
