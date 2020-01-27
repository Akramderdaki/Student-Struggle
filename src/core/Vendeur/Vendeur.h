/**
@brief Module gerant le vendeur
@file Vendeur/Vendeur.h
*/


#ifndef VENDEUR_H
#define VENDEUR_H

#include <vector>
#include "Equipement.h"


class Vendeur
{
    private:
        std::vector <Equipement> tabMarchandises; /*!< Tableau d'Equipement que possede le Vendeur */
        int posx, posy; /*!< Position en x et en y du vendeur */

    public:
        /**
        @brief constructeur avec parametres
        @param [in] x : entier => la position en x du vendeur est a 0 par defaut
        @param [in] y : entier => la position en y du vendeur est a 0 par defaut
        @warning le marchand ne vends pas plus de 12 items
        */
        Vendeur (int x=0, int y=0);

        /**
        @brief destructeur par defaut
        */
        ~Vendeur ();

        /**
        @brief ajoute un equipement au vendeur
        @param [in] item : Equipement qui sera ajoute au magasin
        */
        void ajoutEquipement (const Equipement& item);

        /**
        @brief Vends un equipement d'indice i dans le tableau d'equipements
        @param  [in] i : entier positif  indiquant l'indice de l'equipement a vendre
        */
        void vendre (unsigned i);

        /**
        @brief accesseur du nombre d'equipements pas encore vendus
        @return compteur : entier indiquant le nombre d'equipements restant
        */
        int getNbItemEnVente ();

        /**
        @brief accesseur du tableau d'equipement du vendeur
        @return tabMarchandises : tableau d'equipements
        */
        const std::vector<Equipement>& getTabMarchandises () const;

        /**
        @brief surcharge de l'operateur = pour affecter les caracteristiques d'un vendeur a un autre
        @param v : Vendeur dont les donnees ont ete copiees
        @return this : Vendeur possedant de nouvelles caracteristiques
        */
        Vendeur& operator = (const Vendeur& v);

        /**
        @brief accesseur de la position en x du vendeur
        @return posx : entier
        */
        int getPosX () const;

        /**
        @brief accesseur de la position en y du Vendeur
        @return posy : entier
        */
        int getPosY () const;

        /**
        @brief test de regression s'assurant du bon fonctionnement de la classe
        */
        void testRegression ();
};


#endif // VENDEUR_H
