/**
@brief Module gerant les decors de type mur (Decor etant la classe mere de Mur)
@file Decor/Mur.h
*/


#ifndef MUR_H
#define MUR_H

#include "Decor.h"


class Mur : public Decor
{
    public:
        /**
        @brief constructeur avec parametres
        @param [in] vis = true : booleen => les decors de type mur sont visibles par defaut
        @param [in] n = "mur" : chaine de caracteres => nom du decor
        */
        Mur (bool vis=true, const std::string& n="mur");

        /**
        @brief destructeur par defaut
        */
        ~Mur ();

        /**
        @brief fonction virtuelle: indique si il est possible de marcher sur le decor
        @return booleen : true si il est possible de marcher dessus
        */
        virtual bool walkable () const;

        /**
        @brief fonction virtuelle pure: indique si le decor est fixe ou non
        @return booleen : true si le decor est fixe (non deplacable)
        */
        virtual bool fixe () const;

        /**
        @brief fonction virtuelle pure: 0 si le decor n'est pas recuperable ou x>0 si le decor est
        recuperable avec x la valeur du decor (la valeur des pieces par exemple)
        @return valeur : entier
        */
        virtual int recuperer () const;

        /**
        @brief test de regression s'assurant du bon fonctionnement de la classe
        */
        void testRegression ();
};


#endif // MUR_H
