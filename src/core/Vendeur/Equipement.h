/**
@brief Module gerant un equipement propose chez le vendeur
@file Vendeur/Equipement.h
*/


#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H

#include <string>


class Equipement
{
    private:
        std::string nom; /*!< Nom d'un equipement */
        int vie; /*!< Vie ajoutee au personnage (instantanne) */
        int vieMax; /*!< Vie maximum ajoutee au personnage (PV max)*/
        int nbVies; /*!< Nb de vies ajoutees au personnage (coeurs) */
        int vitesse; /*!< Vitesse ajoutee au personnage */
        int prix; /*!< Prix de l'equipement */
        bool vendu; /*!< Indique si l'equipement a ete achete */

    public:
        /**
        @brief constructeur avec parametres
        @param [in] n = "" : chaine de caracteres => nom de l'equipement
        @param [in] v = 0 : entier => vie de l'equipement
        @param [in] vMax = 0 : entier => vieMax de l'equipement
        @param [in] vit = 0 : entier => vitesse de l'equipement
        @param [in] nbV = 0 : entier => nbVies de l'equipement
        @param [in] p = 0 : entier => prix de l'equipement
        @param [in] vend = false : booleen => achat de l'equipement
        */
        Equipement (const std::string& n="", int v=0, int vMax=0, int vit=0, int nbV=0, int p=0, bool vend=false);

        /**
        @brief destructeur par defaut
        */
        ~Equipement ();

        /**
        @brief mutateur du booleen vendu d'un equipement
        @return v : booleen
        */
        void setVendu (bool v);

        /**
        @brief accesseur du booleen vendu d'un equipement
        @return vendu : booleen
        */
        bool getVendu () const;

        /**
        @brief accesseur du prix d'un equipement
        @return prix : entier
        */
        int getPrix () const;

        /**
        @brief accesseur de la vitesse d'un equipement
        @return vitesse : entier
        */
        int getVitesse () const;

        /**
        @brief accesseur de la vie max d'un equipement
        @return vieMax : entier
        */
        int getVieMax () const;

        /**
        @brief accesseur du nombre de vies d'un equipement
        @return nbVies : entier
        */
        int getNbVies () const;

        /**
        @brief accesseur de la vie d'un equipement
        @return vie : entier
        */
        int getVie () const;

        /**
        @brief accesseur du nom d'un equipement
        @return nom : chaine de caracteres
        */
        const std::string& getNom () const;

        /**
        @brief test de regression s'assurant du bon fonctionnement de la classe
        */
        void testRegression ();
};


#endif // EQUIPEMENT_H
