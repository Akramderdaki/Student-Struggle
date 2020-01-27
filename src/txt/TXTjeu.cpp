#include "TXTjeu.h"
#include "TXTwin.h"
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // WIN32


void afficher (TXTwin & win, Jeu & jeu)
{
    const Niveau& niv = jeu.getNiveau();
	Personnage perso = jeu.getPerso();

	win.clear();

	int visionPerso = niv.getVision();

    // Affichage du niveau
    char c;
    for (int a=0; a<niv.getDimX(); ++a)
    {
        for (int b=0; b<niv.getDimY(); ++b)
        {
            const Decor& d = niv(a,b);
            std::string n = d.getNom();

            if (n == "mur") c='#';
            if (n == "sol") c='*';
            if (n == "piece") c='O';
            if (n == "piege") c='P';
            if (n == "sortie") c='S';

            /* Si le perso ne peut pas voir toutes les cases */
            if (visionPerso != 0
                && !niv.dansVisionPerso(a,b,perso.getPosX(),perso.getPosY()))
            {
                    c='?';
            }
            if (d.getVisible() == 0) c='*';
            win.print(a,b,c);
        }
    }
    // Affichage du personnage
	win.print(perso.getPosX(),perso.getPosY(),'H');

	win.draw();
}

void jouer (Jeu& jeu)
{
    Niveau& niv = jeu.getNiveau();
    TXTwin * win = new TXTwin (niv.getDimX(), niv.getDimX());

	bool play = true;
	int c, collision;

	do {
	    afficher(*win,jeu);

        #ifdef _WIN32
        Sleep(100);
		#else
		usleep(100000);
        #endif // WIN32

		jeu.updateNiveau(niv);
		collision = jeu.collisionPerso(niv);

		c = win->getCh();
		switch (c) {
			case 'q':
				jeu.actionClavier(niv,'g');
				break;
			case 'd':
				jeu.actionClavier(niv,'d');
				break;
			case 'z':
				jeu.actionClavier(niv,'h');
				break;
			case 's':
				jeu.actionClavier(niv,'b');
				break;
			case 'm':
				play = false;
				break;
		}

		/* Arret du jeu (recommencer:-1 / niveau suivant:1) */
		if (collision != 0)
        {
            play = false;
            delete win; win = NULL;
            jouer (jeu);
        }

	} while (play);

	if (win!=NULL) {delete win; win = NULL;}
}
