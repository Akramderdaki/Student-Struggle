/**
@brief Module gerant les decors de type piece (Decor etant la classe mere de Piece)
@file Decor/Piece.h
*/


#ifndef PIECE_H
#define PIECE_H

#include "Decor.h"


class Piece : public Decor
{
    private:
        int valeur; /*!< Valeur d'une Piece */

    public:
        /**
        @brief constructeur avec parametres
        @param [in] val : entier => valeur de la piece
        @param [in] vis = true : booleen => une piece est par defaut visible
        @param [in] n = "piece" : chaine de caracteres => nom du decor
        */
        Piece (int val, bool vis=true, const std::string& n="piece");

        /**
        @brief detructeur par defaut
        */
        ~Piece ();

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
        recuperable avec x la valeur du decor (ici, la valeur des pieces)
        @return valeur : entier
        */
        virtual int recuperer () const;

        /**
        @brief test de regression s'assurant du bon fonctionnement de la classe
        */
        void testRegression ();
};


#endif // PIECE_H
