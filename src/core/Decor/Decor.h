/**
@brief Module gerant un decor. Decor est une classe mere contenant differents types : mur, piece, sol et sortie.
@file Decor/Decor.h
*/


#ifndef DECOR_H
#define DECOR_H

#include <string>


class Decor
{
    protected:
        bool visible; /*!< Affiche ou non un decor dans un niveau */
        std::string nom; /*!< Nom d'un decor */

    public:
        /**
        @brief constructeur
        @param [in] vis : booleen => visibilite du decor (visible ou pas)
        @param [in] n : chaine de caracteres => nom du decor
        */
        Decor (bool vis, const std::string& n);

        /**
        @brief destructeur virtuel par defaut
        */
        virtual ~Decor ();

        /**
        @brief accesseur du booleen indiquant si un decor est visible
        @return visible : booleen
        */
        bool getVisible () const;

        /**
        @brief mutateur du booleen indiquant si un decor est visible
        @param vis : booleen
        */
        void setVisible (bool vis);

        /**
        @brief accesseur de la chaine de caracteres contenant le nom d'un decor
        @return nom : chaine de caracteres
        */
        const std::string& getNom () const;

        /**
        @brief fonction virtuelle pure: indique si il est possible de marcher sur le decor
        @return booleen : true si il est possible de marcher dessus
        */
        virtual bool walkable () const = 0;

        /**
        @brief fonction virtuelle pure: indique si le decor est fixe ou non
        @return booleen : true si le decor est fixe (non deplacable)
        */
        virtual bool fixe () const = 0;

        /**
        @brief fonction virtuelle pure: 0 si le decor n'est pas recuperable ou x>0 si le decor est
        recuperable avec x la valeur du decor (la valeur des pieces par exemple)
        @return valeur : entier
        */
        virtual int recuperer () const = 0;
};


#endif // DECOR_H
