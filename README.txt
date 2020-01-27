****************************************************
                 STUDENT STRUGGLE                  
                 Project ID: 8909 
                                           
             LIFAP4 - L2 INFORMATIQUE              
         UNIVERSITE CLAUDE BERNARD LYON 1         
****************************************************
														
		Realise par :
																			Ben Abdallah Nour p1710076
																			Brignone Jean p1709655
																			Derdaki Akram p1612272
																			Goupy Gaspard p1708658




******************
LICENCE :
******************

Ce projet est libre d'utilisation.
Vous etes invite a respecter les regles suivantes:
	- Toutes les sources originales doivent etre citees
	- Toute utilisation commerciale est interdite 




******************
DESCRIPTION :
******************

Projet en c/c++ realise dans le cadre de l'UE LIFAP4, enseignee en L2 Informatique a l'Universite Lyon 1 Claude Bernard, France.
Le jeu dispose d'un affichage console (version texte) et d'un affichage graphique (sdl2). 

Etat : termine
Date de realisation : 25/02/19 - 06/05/19


C'est un jeu de plateforme, compose de 3 niveaux, a terminer en ayant score le plus haut possible.
Vous incarnez un etudiant s'inscrivant pour sa licence a Lyon 1, et devant surmonter les epreuves que sont les UEs, 
afin de progresser vers le titre tant desire de developpeur confirme. 




******************
FONCTIONNALITES :
******************

- Jeu en 2.5D (vue en profondeur)
- Menu d'avant jeu & de fin de jeu 
- Niveau de parcours d'obstacles
- Niveau de labyrinthe dans le noir avec temps limite
- Boutique entre les niveaux avec la possibilite d'acheter de l'equipement pour s'ameliorer
- Possibilite de recuperer des pieces dans les niveaux pour la boutique
- Score final calculé de manière complexe
- Affichage d'un HUD pour les informations du personnage
- Nombre d'essai limite avant de recommencer a 0
- Soundtrack pour le menu et le jeu 
- Sons d'effets dans le jeu
- Possibilite d'activer et couper le son du jeu dans le menu




******************
COMPILER :
******************

=> Le projet se compile avec un Makefile, utilisant GCC


- LIGNE DE COMMANDE :
	
	Installer make	
		[WINDOWS] https://www.gnu.org/software/make/
		[LINUX] adressez vous à votre distribution
		
	commandes :
		make all            => produit un executable du jeu en version texte, sdl2 et de test de regression
		make / make default => produit un executable du jeu en version texte & sdl2
		make jeu_txt        => produit un executable du jeu en version texte
		make jeu_sdl        => produit un executable du jeu en version sdl2


- CODE::BLOCKS :
	
	ouvrez le fichier student-struggle.cbp et compilez le projet depuis codeblocks, 
	en choisissant la version souhaitee a compiler (build->select target)




******************
EXECUTABLES :
******************

make cree trois executables :
	
	- bin/jeu_test  = tests de regression s'assurant du bon fonctionnement des classes
	
	- bin/txt/student-struggle_txt   = version console du jeu
	
	- bin/sdl2/student-struggle_sdl  = version avec affichage SDL du jeu
	



******************
DOCUMENTATION :
******************

=> Documentation du projet generee avec doxygen

Pour lire la documentation    : ouvrez dans votre navigateur le fichier doc/html/index.html
Pour generer la documentation : make doxygen / doxygen doc/doxyfile.doxy

La documentation est modifiable a vos souhait et vos preferences 

le dossier doc/ contient aussi le cahier des charges, et le diaporama de la soutenance du projet




******************
COMMANDES MAKE :
******************

make all       : produit les trois executables et supprime le dossier obj/
make default   : produit les executables version texte et sdl2 et supprime le dossier obj/
make jeu_txt   : produit l'executable version texte
make jeu_sdl   : produit l'executable version sdl2
make jeu_test  : produit l'executable de test des classes de donnees du jeu
make clean     : supprime le dossier obj/
make veryclean : supprime le dossier obj/ et les trois executables
make doxygen   : genere la documentation avec le fichier doc/doxyfile.doxy




******************
COMMENT JOUER :
******************
	
- Jeu version SDL : 
	Déplacement avec les touches directionnelles
	Quitter avec la touche Echap
	
- Jeu version console
	Déplacement avec les touches zqsd
	Quitter avec la touche m
	
	
	
	
******************
ARBORESCENCE :
******************
/student-struggle
	. student-struggle.cbp     => fichier CodeBlocks du projet
	. student-struggle.layout  => fichier de configuration 
	. student-struggle.depend  => fichier de configuration
	. Makefile                 => fichier pour compiler le jeu
	. src/                     => fichiers sources du jeu
		. core/                  => fichiers des donnees du jeu
		. sdl2/		               => fichiers d'affichage graphique SDL du jeu
		. txt/                   => fichiers d'affichage console du jeu
		. test/                  => fichiers de tests (tests de regression)
	. data/                    => fichiers des assets du jeu
		. img/                   => fichiers d'images du jeu
		. sons/                  => fichiers de sons du jeu
		. font/                  => fichiers de polices d'ecriture du jeu
		. Niveaux/               => fichiers de donnees des niveaux du jeu
	. doc/                     => fichiers de documentation du jeu
		. doxyfile.doxy          => fichier de configuration de la documentation doxygen
		. html/                  => fichiers de la documentation doxygen au format html
		. data/                  => fichiers d'images pour la documentation doxygen
		. +files                 => fichiers pour la presentation du projet
	. bin/                     => fichiers executables
		. sdl2/                  => fichiers .dll et executable du jeu sous sdl
		. txt/                   => executable du jeu en version console
		. jeu_test               => executable des tests de regression du jeu
	
	
	
	
******************
TELECHARGEMENT :
******************
	
	Lien vers la forge :
	https://forge.univ-lyon1.fr/p1708658/student-struggle




******************
CONTACTS :
******************

	Gaspard GOUPY     : gaspard.goupy@etu.univ-lyon1.fr
	Jean Brignone     : jean.brignone@etu.univ-lyon1.fr
	Akram Derdaki     : akram.derdaki@etu.univ-lyon1.fr
	Nour Ben Abdallah : nour.ben-abdallah@etu.univ-lyon1.fr




******************
TESTS REGRESSION :
******************

Pour effectuer des tests sur les classes de donnees du jeu, vous pouvez creer
l'executable bin/jeu_test a partir de la commande : make jeu_test

Sous CodeBlocks, choisissez la cible jeuTEST et compilez.

Il est possible de faire un test de regression sur une classe precise en ajoutant le nom 
de cette classe en parametre a la commande bin/jeu_test
Exemple : bin/jeu_test Personnage




******************
INFOS DEVS :
******************

	-Les niveaux sont stockes dans un tableau de la sorte :
		niveau[0] : shop.txt
		niveau[1] : niveau1.txt (menu d'avant jeu)
		niveau[2] : niveau2.txt
		niveau[3] : niveau3.txt
		niveau[4] : niveau4.txt
		
	-Les datas des niveaux sont ecrites au format texte, dans data/Niveaux
	
	-Les dimensions du menu (niveau1.txt) définissent la taille de la grille maximal du jeu, ainsi que la taille de la fenetre sdl2
	 Afin d'assurer le bon fonctionnement du jeu, il est preferable de garder les memes dimensions pour les autres niveaux
	
	-Pour construire un niveau, ouvrez le fichier data/Niveaux/tuto_pour_creer_un_niveau.txt
	
	-La classe Timer est tiré du site LAZYFOO => (http://lazyfoo.net) 
	
	

