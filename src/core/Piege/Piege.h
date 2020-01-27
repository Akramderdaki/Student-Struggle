/**
@brief Module gerant les pieges (0 : boule de feu, 1 : fleches, 2 : pics, 3 : trou)
@file Piege/Piege.h
*/


#ifndef PIEGE_H
#define PIEGE_H

class Piege
{
    private:
        int id; /*!< Identifiant du piege */
        float initX, initY; /*!< Position en x et position en y initiales */
        float posx, posy; /*!< Position en x et position en y courante */
        int direction; /*!< Direction vers laquelle se dirige le piege: -1 fixe, 0 gauche, 1 haut, 2 droite, 3 bas */
        bool actif; /*!< Indique si un piege est actif ou pas (fait des degats ou non) */
        float degats; /*!< Indique les degats occasionnes par le piege */
        int visible; /*!< Indique si un piege est visible ou pas */
        float vitesse; /*!< Indique la vitesse de deplacement du piege */
        bool rebondi; /*!< Indique si un piege rebondit lors de la collision avec un mur */
        int activeDelai; /*!< Indique de delai d'activation du piege */
        int delai; /*!< compteur de 0 a activeDelai pour activer un piege */

    public:
        /**
        @brief constructeur
        @param [in] i : entier => id du piege
        @param [in] x : flottant => posx initiale du piege
        @param [in] y : flottant => posy initiale du piege
        @param [in] dir = -1 : entier => direction du piege qui est par defaut fixe (-1 fixe, 0 gauche, 1 haut, 2 droite, 3 bas)
        @param [in] d = 100 : flottant => un piege occasionne 100 points de degat par defaut
        @param [in] vis = true : booleen => un piege est par defaut visible
        @param [in] vit = 0 : flottant => un piege est par defaut fixe
        @param [in] rebond = true : booleen => un piege rebondit par defaut
        @param [in] del = 0 : entier => un piege n'a pas de delai d'activation par defaut
        */
        Piege (int i, float x, float y, int dir=-1, float d=100,
                bool vis=true, float vit=0, bool rebond=true, int del=0);

        /**
        @brief destructeur par defaut
        */
        ~Piege ();

        /**
        @brief accesseur de la position en x du piege
        @return posx : flottant
        */
        float getPosX () const;

        /**
        @brief mutateur de la position en x du piege
        @param [in] x : flottant
        */
        void setPosX (float x);

        /**
        @brief accesseur de la position en y du piege
        @return posy : flottant
        */
        float getPosY () const;

        /**
        @brief mutateur de la position en y du piege
        @param [in] y : flottant
        */
        void setPosY (float y);

        /**
        @brief accesseur de la position en x initiale du piege
        @return flottant
        */
        float getInitX() const;

        /**
        @brief mutateur de la position en x initiale du piege
        @param [in] x : flottant
        */
        void setInitX(float x);

        /**
        @brief accesseur de la position en y initiale du piege
        @return flottant
        */
        float getInitY() const;

        /**
        @brief mutateur de la position en y initiale du piege
        @param [in] y : flottant
        */
        void setInitY(float y);

        /**
        @brief accesseur de la direction du piege
        @return entier
        */
        int getDir() const;

        /**
        @brief mutateur de la direction du piege
        @param [in] dir : entier
        */
        void setDir(int dir);

        /**
        @brief accesseur du booleen actif du piege
        @return booleen
        */
        bool getActif() const;

        /**
        @brief mutateur du booleen actif du piege
        @param [in] a : booleen
        */
        void setActif(bool a);

        /**
        @brief accesseur des degats du piege
        @return flottant
        */
        float getDegats() const;

        /**
        @brief mutateur des degats du piege
        @param [in] d : flottant
        */
        void setDegats(float d);

        /**
        @brief accesseur de la visibilite du piege
        @return booleen
        */
        bool getVisible() const;

        /**
        @brief mutateur de la visibilite du piege
        @param [in] vis : booleen
        */
        void setVisible(bool vis);

        /**
        @brief accesseur de la vitesse du piege
        @return flottant
        */
        float getVitesse() const;

        /**
        @brief mutateur de la vitesse du piege
        @param [in] v : entier
        */
        void setVitesse(float v);

        /**
        @brief accesseur du delai d'activation du piege
        @return entier
        */
        int getActiveDelai() const;

        /**
        @brief accesseur du compteur de delai d'activation du piege
        @return entier
        */
        int getDelai() const;

        /**
        @brief mutateur du compteur de delai d'activation du piege
        @param [in] d : entier
        */
        void setDelai(int d);

        /**
        @brief accesseur du booleen rebondi du piege
        @return booleen
        */
        bool getRebond() const;

        /**
        @brief accesseur de l'id du piege
        @return entier
        */
        int getId() const;

        /**
        @brief traduit la donnee membre direction de la classe en un vecteur direction de coordonnees (dirx, diry)
        @param [int,out] dirx : entier indiquant les coordonnees x du vecteur direction
        @param [int,out] diry : entier indiquant les coordonnees y du vecteur direction
        */
        void getVectFromDir(int& dirx, int& diry);

        /**
        @brief surcharge de l'operateur "=" permettant de copier les caracteristiques d'un piege dans un autre
        @param [in] p : Piege dont on copie les caracteristiques
        @return Modifie directement les donnees du piege appelant cet operateur
        */
        Piege& operator = (const Piege& p);

        /**
        @brief test de regression s'assurant du bon fonctionnement de la classe
        */
        void testRegression ();
};


#endif // PIEGE_H
