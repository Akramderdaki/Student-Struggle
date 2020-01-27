#include "SDLjeu.h"
#include <iostream>
#include <string>

using namespace std;

/*! \mainpage Page principale
 *
 * \section Description
 *
 * - Projet en c/c++ realise dans le cadre de l'UE LIFAP4, enseignee en L2 Informatique a l'Universite Lyon 1 Claude Bernard, France. \n
 * Le jeu dispose d'un affichage console (version texte) et d'un affichage graphique (sdl2). \n
 *
 * - Etat : termine
 * - Date de realisation : 25/02/19 - 06/05/19
 *
 * - C'est un jeu de plateforme, compose de 3 niveaux, a terminer en ayant score le plus haut possible. \n
 * Vous incarnez un etudiant s'inscrivant pour sa licence a Lyon 1, et devant surmonter les epreuves que sont les UEs, \n
 * afin de progresser vers le titre tant desire de developpeur confirme. \n
 *
 *
 * \section Membres
 * - Nour Ben Abdallah
 * - Jean Brignone
 * - Akram Derdaki
 * - Gaspard Goupy
 *
 *
 * \section Licence
 *
 * Ce projet est libre d'utilisation.
 * Vous etes invite a respecter les regles suivantes:
 *	- Toutes les sources originales doivent etre citees
 *	- Toute utilisation commerciale est interdite
 *
 *
 * \section Compilation
 *
 * \subsection make
 * - make / make default => produit un executable du jeu en version texte & sdl2 \n
 * - make all            => produit un executable du jeu en version texte, sdl2 et de test des classes du jeu \n
 * - make jeu_txt        => produit un executable du jeu en version texte (bin/txt/student-struggle_txt) \n
 * - make jeu_sdl        => produit un executable du jeu en version sdl2 (bin/sdl2/student-struggle_sdl) \n
 * - make jeu_test       => produit un executable de test des classes de donnees du jeu (bin/jeu_test) \n
 *
 * \subsection Code::Blocks
 * Ouvrez le fichier student-struggle.cbp et compilez le projet depuis codeblocks \n
 * en choisissant la version souhaitee a compiler (build->select target) \n
 *
 *
 * \section Informations
 * Veuillez lire le fichier README.txt \n\n
 *
 *
 * \section Screenshots
 *\n\n
 * \image html img_menu.png
 *\n\n
 * \image html img_lifap4.png
 *\n\n
 * \image html img_amala.png
 *\n\n
 * \image html img_fin.png
 *\n\n
 */




int main (int argc, char** argv)
{
    string nomPerso;
    cout<<"Rentrez le nom de votre personnage: ";
    cin>>nomPerso;
    SDLjeu j(nomPerso);
    j.jouer();
    return 0;
}
