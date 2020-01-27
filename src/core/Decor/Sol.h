/**
@brief Module gerant les decors de type sol (Decor etant la classe mere de Sol)
@file Decor/Sol.h
*/


#ifndef SOL_H
#define SOL_H

#include "Decor.h"


class Sol : public Decor
{
    public:
        /**
        @brief constructeur avec parametres
        @param [in] vis = true : booleen => un sol est par defaut visible
        @param [in] n = "sol" : chaine de caracteres => nom du decor
        */
        Sol(bool vis = true, const std::string& n="sol");

        /**
        @brief destructeur par defaut
        */
        ~Sol();

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
        void testRegression();
};


#endif // SOL_H
