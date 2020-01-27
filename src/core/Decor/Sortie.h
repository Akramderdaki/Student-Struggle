/**
@brief Module gerant les decors de type sortie (Decor etant la classe mere de Sortie)
@file Decor/Sortie.h
*/


#ifndef SORTIE_H
#define SORTIE_H

#include "Decor.h"


class Sortie : public Decor
{
    public:
        /**
        @brief constructeur avec parametres
        @param [in] vis = true : booleen => une sortie est visible par defaut
        @param [in] n = "sortie" : chaine de caracteres => nom du decor
        */
        Sortie (bool vis=true, const std::string& n="sortie");

        /**
        @brief destructeur par defaut
        */
        ~Sortie ();

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


#endif //SORTIE_H
