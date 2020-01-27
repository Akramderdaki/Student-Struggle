/**
@brief Module gerant le jeu
@file Jeu.h
*/


#ifndef JEU_H
#define JEU_H

#include "Niveau.h"
#include "Personnage.h"
#include "Vendeur/Vendeur.h"
#include <vector>
#include <string>


class Jeu
{
    private:
        std::vector <Niveau*> tabNiveau; /*!< Tableau de pointeurs sur les niveaux du jeu */
        unsigned nivEnCours; /*!< Identifiant du Niveau en cours du jeu */
        unsigned saveId; /*!< Sauvegarde de l'identifiant du niveau pour passer au suivant apres le magasin (d'indice niveau 0) */
        Personnage perso; /*!< Sauvegarde des caracteristiques du personnage pour retrouver les memes quand le perso meurt dans un niveau */
        Personnage persoEnJeu; /*!< Personnage parcourant les niveaux */
        Vendeur vendeur; /*!< Vendeur du jeu proposant des equipements au personnage */

    public:
        /**
        @brief constructeur
        @param [in] nomPerso : chaine de caracteres => attribue au personnage un nom
        */
        Jeu (const std::string& nomPerso="No Name");

        /**
        @brief destructeur par defaut
        */
        ~Jeu ();

        /**
        @brief Cree un niveau depuis un fichier
        @param [in] nomFichier : chaine de caracteres designant le nom du fichier contenant le niveau a charger
        @return Niveau* un pointeur sur le niveau a charger dans le tableau de niveaux
        @warning Retourne une adresse du niveau (=modifiable)
        */
        Niveau* chargerNiveau (const std::string& nomFichier);

        /**
        @brief initialise le niveau i depuis un fichier pour
        -> Charger un niveau
        -> Initialiser un niveau avec les positions initiales
        @param i : entier positif (unsigned = unsigned int)
        @param f :chaine de caracteres => nom du fichier (optionnel)
        */
        void initNiveau(unsigned i, std::string f=""); //f ne peut etre passé en const car modifié

        /**
        @brief initialise le jeu (vendeur, perso, taille de tabNiveaux et le premier niveau)
        @param [in] nomPerso = "" : chaine de caracteres
        @warning si nomPerso prend sa valeur par defaut, elle sera remplacee par le nom du perso definit lors de l'appel constructeur
        */
        void initJeu (std::string nomPerso=""); //pas const car il peut etre modifié

        /**
        @brief passe au niveau suivant
        -> Dans le shop entre les niveaux
        -> Jusqu'a ce qu'on arrive au dernier niveau => finJeu()
        */
        void niveauSuivant ();

        /**
        @brief recommence le niveau actuel avec les caracteristiques perso de debut de niveau
        -> Jusqu'a ce que le perso n'ai plus de vie -> InitJeu()
        */
        void recommencer ();

        /**
        @brief fin du jeu : le personnage est arrive au bout de tous les niveaux
        */
        void finJeu ();

        /**
        @brief gere les actions du personnage en fonction d'une touche donnee
        @param [in] touche : caractere
        @param [in] niv : Niveau
        @warning Pour un affichage graphique (sdl2) veuillez utiliser les fonctions de SDLjeu remplacant celle-ci
        */
        void actionClavier (const Niveau& niv, char touche);

        /**
        @brief actualise le jeu
        @warning Pour un affichage graphique (sdl2) veuillez utiliser les fonctions de SDLjeu remplacant celle-ci
        */
        void updateNiveau (Niveau& niv);

        /**
        @brief verifie si il y a eu une collision avec le personnage
        @return entier => (0 = pas de Collision) (1 = collision avec la sortie) (-1 = collision avec un piege + plus de vie; perdu)
        @warning Pour un affichage graphique (sdl2) veuillez utiliser les fonctions de SDLjeu remplacant celle-ci
        */
        int collisionPerso (Niveau& niv);

        /**
        @brief initialise les equipements du vendeur
        */
        void initVendeur ();

        /**
        @brief interaction avec le vendeur d'equipements
        @param i : entier positif => indice de l'equipement selectionne dans le tableau d'equipements du vendeur (unsigned = unsigned int)
        @return booleen => true si l'equipement d'indice i a ete vendu, false sinon
        */
        bool interagirVendeur (unsigned i);

        /**
        @brief Permet d'aller au magasin entre chaque niveau :
        Sauvegarde l'indice du prochain niveau et passe au niveau 0 (shop)
        */
        void goMagasin ();

        /**
        @brief retourne le niveau en cours
        @return tabNiveau[nivEnCours] : Niveau en cours
        @warning le Niveau est modifiable (passe par reference)
        */
        Niveau& getNiveau ();

        /**
        @brief retourne le niveau d'indice i dans le tableau de niveaux
        @return tabNiveau[i] : Niveau voulu
        */
        const Niveau& getNiveau (unsigned i);

        /**
        @brief accesseur du personnage du jeu
        @return perso : Personnage*
        @warning les caracteristiques du perso sont modifiables (passe par reference)
        */
        Personnage& getPerso ();

        /**
        @brief accesseur du Personnage du Jeu
        @return perso : Personnage*
        @warning const : non modifiable
        */
        const Personnage& getPerso () const;

        /**
        @brief accesseur du vendeur du jeu
        @return vendeur : Vendeur*
        @warning les caracteristiques du vendeur sont modifiables (passe par reference)
        */
        Vendeur& getVendeur ();

        /**
        @brief accesseur du vendeur du jeu
        @return vendeur : Vendeur*
        @warning const : non modifiable
        */
        const Vendeur& getVendeur () const;

        /**
        @brief accesseur de l'identifiant du niveau en cours dans le jeu
        @return nivEnCours : entier indiquant l'identifiant du niveau
        */
        int getNivEnCours () const;

        /**
        @brief test de regression s'assurant du bon fonctionnement de la classe
        */
        void testRegression ();
};


#endif // JEU_H
