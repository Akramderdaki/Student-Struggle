/**
@brief Module gerant le personnage
@file Personnage.h
*/


#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "Niveau.h"
#include <string>


class Personnage
{
    private:
        std::string nom; /*!< Nom du personnage */
        float score; /*!< Score du personnage */
        float posx; /*!< Position en X du personnage */
        float posy; /*!< Position en Y du personnage */
        float vitesse; /*!< Vitesse du pPersonnage */
        int vie; /*!< Nombre de points de vie courant du personnage */
        int vieMax; /*!< Nombre de points de vie maximum du personnage */
        bool subiDegats; /*!< Booleen pour reguler les degats subits */
        int nbVies; /*!< Nombre de vies du personnage (coeurs) */
        int direction; /*!< Direction du Personnage (representee par des entiers => gauche:0, droite:2, haut:1, bas:3) */
        int monnaie; /*!< Argent du personnage en jeu */


    public:
        /**
        @brief constructeur avec parametre
        @param [in] n : chaine de caracteres => nom du personnage
        */
        Personnage (const std::string& n = "No Name");

        /**
        @brief destructeur par defaut
        */
        ~Personnage ();

        /**
        @brief Deplacement du Personnage vers la droite
        @param [in] niv : Niveau dans lequel evolue le personnage
        @warning SEULEMENT POUR LA VERSION TEXTE
        */
        void depDroite (const Niveau& niv);

        /**
        @brief Deplacement du personnage vers la gauche
        @param [in] niv : Niveau dans lequel evolue le personnage
        @warning SEULEMENT POUR LA VERSION TEXTE
        */
        void depGauche (const Niveau& niv);

        /**
        @brief Deplacement du personnage vers le haut
        @param [in] niv : Niveau dans lequel evolue le personnage
        @warning SEULEMENT POUR LA VERSION TEXTE
        */
        void depHaut (const Niveau& niv);

        /**
        @brief Deplacement du personnage vers le bas
        @param [in] niv : Niveau dans lequel evolue le personnage
        @warning SEULEMENT POUR LA VERSION TEXTE
        */
        void depBas (const Niveau& niv);

        /**
        @brief Enleve des points de vie au personnage
        @param [in] degat : entier indiquant les degats subis
        */
        void perdreVie (int degat);

        /**
        @brief ajoute des points de score au personnage
        @param [in] xp : flottant indiquant le nombre de points de score gagnes
        */
        void prendsXP (float xp);

        /**
        @brief indique si le personnage est encore en vie
        @return booleen
        */
        bool enVie () const;

        /**
        @brief accesseur du nom du personnage
        @return nom : chaine de caracteres
        */
        const std::string& getNom () const;

        /**
        @brief mutateur du nom du personnage
        @param [in] nom : chaine de caracteres
        */
        void setNom (const std::string& n);

        /**
        @brief accesseur du score du personnage
        @return score : flottant
        */
        float getScore () const;

        /**
        @brief accesseur de la vie du personnage
        @return vie : entier
        */
        int getVie () const;

        /**
        @brief mutateur de la vie du personnage
        @param [in] v : entier indiquant les nouveaux points de vie du personnage
        */
        void setVie (int v);

        /**
        @brief accesseur de la vie max du personnage
        @return vieMax : entier
        */
        int getVieMax () const;

        /**
        @brief mutateur de la vie max du personnage
        @param [in] vMax : entier indiquant le nouveau maximum de points de vie du personnage
        @warning vieMax augmente aussi la vie courante
        */
        void setVieMax (int vMax);

        /**
        @brief accesseur de subiDegats du personnage
        @return subiDegats : booleen indiquant si le personnage a subi des degats pendant le tour
        */
        bool getSubiDegats () const;

        /**
        @brief mutateur de subiDegats du personnage
        @param [in] s = true : booleen => setSubiDegats indique par defaut que le personnage a subi des degats
        */
        void setSubiDegats (bool s=true);

        /**
        @brief accesseur du nombre de vies (coeurs) du personnage
        @return nbVies : entier
        */
        int getNbVies () const;

        /**
        @brief mutateur du nombre de vies (coeurs) du personnage
        @param [in] nbV : entier indiquant le nouveau nombre de vies
        */
        void setNbVies (int nbV);

        /**
        @brief accesseur de la vitesse du personnage
        @return vitesse : flottant
        */
        float getVitesse () const;

        /**
        @brief mutateur de la vitesse du Personnage
        @param [in] vit : flottant indiquant la nouvelle vitesse du personnage
        */
        void setVitesse (float vit);

        /**
        @brief accesseur de la direction du personnage
        @return direction : entier
        @warning Direction est un entier representant une dir (0 -> gauche, 2 -> droite, 1 -> haut, 3 -> bas)
        */
        int getDirection () const;

        /**
        @brief mutateur de la direction du personnage
        @param [in] dir : entier indiquant la nouvelle direction du personnage
        @warning Direction est un entier representant une dir (0 -> gauche, 2 -> droite, 1 -> haut, 3 -> bas)
        */
        void setDirection (int dir);

        /**
        @brief accesseur de la posX du personnage
        @return posx : flottant
        */
        float getPosX () const;

        /**
        @brief mutateur de la posX du personnage
        @param [in] x : flottant indiquant la nouvelle position en x du personnage
        */
        void setPosX (float x);

        /**
        @brief accesseur de la posY du personnage
        @return posy : flottant
        */
        float getPosY () const;

        /**
        @brief mutateur de la posY du personnage
        @param [in] y : flottant indiquant la nouvelle position en y du personnage
        */
        void setPosY (float y);

        /**
        @brief accesseur de la monnaie du personnage
        @return monnaie : entier
        */
        int getMonnaie () const;

        /**
        @brief ajoute de la monnaie au personnage
        @param [in] val : entier indiquant l'argent a ajouter a celui du personnage
        */
        void addMonnaie (int val);

        /**
        @brief surchage de l'operateur = pour copier les caracteristiques d'un personnage dans un autre
        @param [in] p : Personnage dont les caracteristiques sont copiees
        @return Modifie directement l'instance qui appelle cet operateur
        */
        Personnage& operator = (const Personnage& p);

        /**
        @brief test de regression s'assurant du bon fonctionnement de la classe
        */
        void testRegression ();
};


#endif // PERSONNAGE_H
