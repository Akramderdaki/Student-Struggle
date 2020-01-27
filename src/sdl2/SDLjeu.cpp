#include "SDLjeu.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


using namespace std;


/* Retourne une taille de sprite en fonction de la taille max d'une grille et la dimension en y */
int getDimSprite (int h, int x)
{
    return ((float)h*0.85)/x;
}

/* Applique un coeff reducteur a framePerso pour ralentir l'affichage des differentes frames */
int frame_reduce (int frame, float vitesse)
{
    return frame*(vitesse/(vitesse+8.00)); // int return = float converti à l'entier d'avant
}

/* Quitte le programme si il y a une erreur a l'initialisation */
void SDLjeu::SDL_exit_error(const char* error)
{
    cout<<"Erreur d'initialisation de la SDL: "<<error<<"\n";
    SDL_Quit();
    exit(0);
}

/* Joue le son passe en parametre si le son du jeu est on */
void SDLjeu::jouerSon (Mix_Chunk * s, int channel, int loop)
{
    if (AvecSon) Mix_PlayChannel(channel, s, loop);
}



SDLjeu::SDLjeu (const string& nomPerso) : jeu(nomPerso)
{
    //Init de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) SDL_exit_error(SDL_GetError());

    //Init de la SDL texte
    if (TTF_Init() != 0) SDL_exit_error(TTF_GetError());

    //Init de la SDL image
    Uint32 flags_img = IMG_INIT_PNG;
    if(!(IMG_Init(flags_img) && flags_img)) SDL_exit_error(IMG_GetError());

    //Init de la SDL mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        cout << "Erreur d'initialisation de la SDL: " << Mix_GetError() << "\n";
        AvecSon = false; //pas de son si il y a une erreur d'init
    }
    else AvecSon = true;

    //Creation de la fenetre
    int dimx = jeu.getNiveau().getDimX(); //DImension en X du menu (taille de grille maximal du jeu)
    int dimy = jeu.getNiveau().getDimY(); //DImension en Y du menu (taille de grille maximal du jeu)

    SDL_DisplayMode dm; SDL_GetDesktopDisplayMode(0,&dm); //Taille de la fenêtre

    TAILLE_SPRITE = getDimSprite(dm.h,dimx); //Taille du sprite en fonction de la hauteur du moniteur et de la largeur du jeu

    Uint32 flags_win = SDL_WINDOW_RESIZABLE;
	TAILLE_BORDURE = TAILLE_SPRITE * 5;
	winx = dimy * TAILLE_SPRITE  + TAILLE_BORDURE*2;
	winy = dimx * TAILLE_SPRITE;

    win = SDL_CreateWindow("Student Struggle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winx, winy, flags_win);
    if (!win) SDL_exit_error(SDL_GetError());

    //Création du rendu
    //Vsync permet au jeu de s'update en même temps que la synchro verticale du moniteur
    Uint32 flags_ren = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    ren = SDL_CreateRenderer(win, -1, flags_ren);
 	if (!ren) SDL_exit_error(SDL_GetError());

    // FONTS
    police = TTF_OpenFont("data/font/roboto.ttf",TAILLE_SPRITE);
    if (police == NULL) SDL_exit_error(TTF_GetError());
    chargeTexte(); //on charge dans un tableau (map) l'ensemble des images de texte du jeu

    // SONS
    if (AvecSon) //si le son a ete init
    {
        //récupérer une pièce
        son_piece = Mix_LoadWAV("data/sons/son_piece.wav");
        if (son_piece==NULL) SDL_exit_error(Mix_GetError());

        //déclenchement d'un pièafficherTempsRestantge à piques
        son_piques = Mix_LoadWAV("data/sons/son_piques.wav");
        if (son_piques==NULL) SDL_exit_error(Mix_GetError());

        //collision avec boule de feu
        son_feu = Mix_LoadWAV("data/sons/son_feu.wav");
        if (son_feu==NULL) SDL_exit_error(Mix_GetError());

        //collision ave cune flèche
        son_fleche = Mix_LoadWAV("data/sons/son_fleche.wav");
        if (son_fleche==NULL) SDL_exit_error(Mix_GetError());

        //son de la sortie
        son_sortie = Mix_LoadWAV("data/sons/son_sortie.wav");
        if (son_sortie==NULL) SDL_exit_error(Mix_GetError());

        //bruit de pas droit
        son_droite = Mix_LoadWAV("data/sons/son_droite.wav");
        if (son_droite==NULL) SDL_exit_error(Mix_GetError());

        //bruit de pas gauche
        son_gauche = Mix_LoadWAV("data/sons/son_gauche.wav");
        if (son_gauche==NULL) SDL_exit_error(Mix_GetError());

        //son de clic
        son_clic = Mix_LoadWAV("data/sons/son_clic.wav");
        if (son_clic==NULL) SDL_exit_error(Mix_GetError());

        //soundtrack en menu
        son_menu = Mix_LoadMUS("data/sons/son_menu.mp3");
        if (son_menu==NULL) SDL_exit_error(Mix_GetError());
        sonMenuEnCours=false; //pour laisser la soundtrack dans le menu

        //soundtrack en jeu
        son_jeu = Mix_LoadMUS("data/sons/son_jeu.mp3");
        if (son_jeu==NULL) SDL_exit_error(Mix_GetError());
        sonJeuEnCours=false; //pour laisser la soundtrack entre les niveaux

    }

    //MENU DU JEU
    menu = new Menu(ren, TAILLE_BORDURE, TAILLE_SPRITE);

    //MAGASIN DU JEU
    shop = new Shop(&jeu, ren, winx, winy, TAILLE_SPRITE, true);

    //IMAGES DU JEU
    chargeImages();
}

SDLjeu::~SDLjeu ()
{
    delete shop; shop=NULL;
    delete menu; menu=NULL;
    Mix_FreeChunk(son_sortie); son_sortie=NULL;
    Mix_FreeChunk(son_piece); son_piece=NULL;
    Mix_FreeChunk(son_gauche); son_gauche=NULL;
    Mix_FreeChunk(son_droite); son_droite=NULL;
    Mix_FreeChunk(son_fleche); son_fleche=NULL;
    Mix_FreeChunk(son_piques); son_piques=NULL;
    Mix_FreeChunk(son_feu); son_feu=NULL;
    Mix_FreeChunk(son_clic); son_clic=NULL;
    Mix_FreeMusic(son_menu); son_menu=NULL;
    Mix_FreeMusic(son_jeu); son_jeu=NULL;
    Mix_Quit();
    TTF_CloseFont(police); police=NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(ren); ren=NULL;
    SDL_DestroyWindow(win); win=NULL;
    SDL_Quit();
}

/* prends en compte la 2.5D */
bool SDLjeu::overlap(SDL_Rect box1, SDL_Rect box2, const Image& img)
{
    //On applique un reduce sur les coordonnees de la box1 pour gerer la profondeur et la hitbox
    float reduce_h = img.getH()*0.4; //collisions en 2.5D (profondeur)
    float reduce_w = img.getW()*0.1; //rend plus smooth les collisions lattérals

    if((box2.x >= box1.x + box1.w - reduce_w)      // trop à droite
	  || (box2.x + box2.w <= box1.x + reduce_w)    // trop à gauche
	  || (box2.y >= box1.y + box1.h)               // trop en bas
	  || (box2.y + box2.h <= box1.y + reduce_h))   // trop en haut
           return false;

    return true;
}

bool SDLjeu::isWalkable(const Niveau& niv, const Image& img, int x, int y)
{
    SDL_Rect box;
    box.x = y; box.y = x;
    box.h = img.getH();
    box.w = img.getW();

    /* Collisions avec les murs */
    for (int i=0; i<niv.getDimX(); ++i)
    {
        for (int j=0; j<niv.getDimY(); ++j)
        {
            //Si le decor i,j est un mur, on regarde si il y a une superposition avec le sprite box
            if (niv(i,j).getNom() == "mur")
            {
                SDL_Rect decor;
                decor.x = j*TAILLE_SPRITE;
                decor.y = i*TAILLE_SPRITE;
                decor.h = TAILLE_SPRITE;
                decor.w = TAILLE_SPRITE;

                if (overlap(box, decor, img)) return false;
            }
        }
    }

    /* collision avec le vendeur dans le cas du niveau shop d'id 0 */
	if (niv.getId() == 0)
	{
        SDL_Rect vendeur;
        vendeur.x = jeu.getVendeur().getPosY() * TAILLE_SPRITE;
        vendeur.y = jeu.getVendeur().getPosX() * TAILLE_SPRITE;
        vendeur.h = img_Vendeur.getH();
        vendeur.w = img_Vendeur.getW();
        if(overlap(box, vendeur, img)) return false;
    }

    return true;
}

int SDLjeu::collisions(Niveau& niv, Personnage& perso)
{
    SDL_Rect psg;
    psg.x = perso.getPosY();
    psg.y = perso.getPosX();
    psg.h = img_Perso[0][0].getH();
    psg.w = img_Perso[0][0].getW();

    int dirPerso = perso.getDirection();

    /* Collisions avec les éléments du décor */ //On parcourt le tableau de decor
    for (int i=0; i<niv.getDimX(); ++i)
    {
        for (int j=0; j<niv.getDimY(); ++j)
        {
            SDL_Rect decor;
            decor.x = j*TAILLE_SPRITE;
            decor.y = i*TAILLE_SPRITE;
            decor.h = TAILLE_SPRITE;
            decor.w = TAILLE_SPRITE;

            const Decor& d = niv(i,j);

            if (overlap(psg, decor, img_Perso[dirPerso][1])) //Si un decor a une collision avec le personnage
            {
                /* Collision avec la case sortie */
                if (d.getNom() == "sortie") //Case sortie
                {
                    jouerSon(son_sortie,-1,0);
                    return 1; //indication a la boucle de jeu de la sortie
                }

                /* Collision avec une piece */
                int val = d.recuperer();
                if (val > 0)
                {
                    perso.addMonnaie(val);
                    perso.prendsXP(50);
                    niv.supprDecor(i,j); //d est suppr et un nouveau decor sol est crée
                    jouerSon(son_piece,-1,0);
                }
            }
        }
    }

    /* Collisions avec les pieges */
    for (unsigned i=0; i<niv.getNbPieges(); ++i) //On parcourt le tableau de pieges
    {
        Piege& p = niv.getPiege(i);
        int dir; (p.getDir() == -1) ? dir=0 : dir=p.getDir(); //cas ou dir = -1
        SDL_Rect piege;
        piege.x = p.getPosY();
        piege.y = p.getPosX();
        piege.h = img_Piege[p.getId()][dir].getH();
        piege.w = img_Piege[p.getId()][dir].getW();

        if (overlap(psg,piege,img_Perso[dirPerso][1])) //Si un piege a une collision avec le personnage
        {
            if (p.getActif()) //il fait des degats si est actif
            {
                perso.perdreVie(p.getDegats());
                perso.prendsXP(-5);

                //Son du piege
                switch (p.getId())
                {
                    case 0 : jouerSon(son_feu,0,0); break;
                    case 1 : jouerSon(son_fleche,0,0); break;
                    case 2 : jouerSon(son_piques,0,0); break;
                }
            }

            //si le piège est non actif et sans délai d'activation => il s'active
            if (!p.getActif() && p.getActiveDelai()==0)
            {
                p.setActif(true);
            }
        }
    }

    /* Test si le perso est toujours en vie */
    if (!perso.enVie())
    {
        SDL_Delay(800); //pour voir ou tu meurt lol
        return -1; //indication a la boucle de jeu de la mort du perso
    }

    /* else */
    return 0; //aucune indication a la boucle a annoncer
}

void SDLjeu::actionClavierPixel (Personnage& perso, const Niveau& niv, char touche)
{
    float perso_x = perso.getPosX();
    float perso_y = perso.getPosY();
    float vitesse =  perso.getVitesse();

    /* Obtenir la vitesse en pixel en fonction des FPS */
    /* Le perso se déplace de x pixels, en fonction de son nombre de FPS */
    /* Plus il a des FPS lents, plus x sera élevé et inversement */
    float deltaTime = FPS_perso.get_ticks() / 1000.f; //Delta temps depuis le dernier lancement du timer
    //Nb de pixel en fonction d'une vitesse en pixel / s (vitesse*TAILLESPRITE) et d'un delta temps
    float vitessePix = (vitesse*TAILLE_SPRITE) * deltaTime;

    const Image& img = img_Perso[perso.getDirection()][0]; //image du perso au moment du deplacement (pour la collision)
    switch (touche)
    {
        case 'g': //gauche
        {
            perso.setDirection(0);
            if (isWalkable(niv, img, perso_x, perso_y-vitessePix)) //si il peut se deplacer a cette position
            {
                perso.setPosY(perso_y-vitessePix);
            }
            break;
        }
        case 'd': //droite
        {
            perso.setDirection(2);
            if (isWalkable(niv, img, perso_x, perso_y+vitessePix)) //si il peut se deplacer a cette position
            {
                perso.setPosY(perso_y+vitessePix);
            }
            break;
        }
        case 'h': //haut
        {
            perso.setDirection(1);
            if (isWalkable(niv, img, perso_x-vitessePix, perso_y)) //si il peut se deplacer a cette position
            {
                perso.setPosX(perso_x-vitessePix);
            }
            break;
        }
        case 'b': //bas
        {
            perso.setDirection(3);
            if (isWalkable(niv, img, perso_x+vitessePix, perso_y)) //si il peut se deplacer a cette position
            {
                perso.setPosX(perso_x+vitessePix);
            }
            break;
        }
    }

    //pour ne pas accélerer les animations/sons si plusieurs touches appuyées
    if (!perso_a_bouge) //perso_a_bouge est false une seule fois par boucle
    {
        /* Update des frames du Perso */
        framePerso++;

        /* frame_reduce reduit la vitesse de défilement des frames */
        if (frame_reduce(framePerso,vitesse) >= 8) framePerso = 1;

        int frameMax = 8/(vitesse/(vitesse+8.00)); //nombre maximum que peut atteindre framePerso

        //On joue le son de pas gauche a la frame X
        if (framePerso==(frameMax*2)/8)
        {
            jouerSon(son_gauche,1,0);
        }

        //On joue le son de pas droite a la frame Y
        if (framePerso==(frameMax*6)/8)
        {
            jouerSon(son_droite,1,0);
        }

        perso_a_bouge=true; //plus d'update d'image avant la fin de la boucle
    }
}

void SDLjeu::deplacerPieges(Niveau& niv)
{
    /* Obtenir la vitesse en pixel en fonction des FPS */
    /* Le piege se déplace de x pixels, en fonction de son nombre de FPS */
    /* Plus il a des FPS lents, plus x sera élevé et inversement */
    float deltaTime = FPS_pieges.get_ticks() / 1000.f; //Delta temps depuis le dernier mouvement en secondes

    for (unsigned i=0; i<niv.getNbPieges(); ++i) //on parcourt le tableau de pieges
    {
        Piege& p = niv.getPiege(i);

        //cas ou le piege est fixe => on prends sa 1e image
        int imgDir; (p.getDir() == -1) ? imgDir=0 : imgDir=p.getDir(); //si dir = -1

        const Image& img = img_Piege[p.getId()][imgDir]; //image du piege au moment du deplacement

        float posx = p.getPosX();
        float posy = p.getPosY();
        int dir = p.getDir();
        int activeDelai = p.getActiveDelai();

        /* Pièges mouvants */
        if (dir != -1)
        {
            int dirx, diry;
            float depx, depy;
            p.getVectFromDir(dirx, diry); //dirx & diry coords du vecteur direction (0 ou 1)

            float vitessePix = (p.getVitesse()*TAILLE_SPRITE) * deltaTime; //Nb de pixel en fonction d'une vitesse/s et d'un temps
            depx=dirx*vitessePix;
            depy=diry*vitessePix;

            /* Si il peut se déplacer a la case suivante */
            if (isWalkable(niv, img, posx+depx, posy+depy))
            {
                if (activeDelai>0) //Pièges ayant un délai d'activation
                {
                    if (p.getDelai() >= activeDelai*10) //deplacement si compteur >= delai d'activation
                    {
                        p.setPosX(p.getPosX() + depx);
                        p.setPosY(p.getPosY() + depy);
                        p.setActif(true);
                        p.setVisible(true);
                    }

                    p.setDelai(p.getDelai()+1); //incrementation compteur
                }
                else //Si il n'a pas de delai d'activation
                {
                    p.setPosX(p.getPosX() + depx);
                    p.setPosY(p.getPosY() + depy);
                }
            }

            /* Sinon il change de direction */
            else
            {
                if (p.getRebond()) //Si le piège rebondi
                {
                    if (dir == 0) {p.setDir(2);}
                    if (dir == 1) {p.setDir(3);}
                    if (dir == 2) {p.setDir(0);}
                    if (dir == 3) {p.setDir(1);}
                }
                else //sinon il reprends sa position initiale
                {
                    p.setPosX(p.getInitX());
                    p.setPosY(p.getInitY());
                    p.setDelai(0); //Le compteur passe à 0 et est incrémenté jusqu'à activeDelai si le piège a un delai d'activation
                    p.setActif(false);
                    p.setVisible(false);
                }
            }
        }

        /* Pièges statiques */
        else
        {
            if (activeDelai > 0) //piege qui change d'état
            {
                if (p.getDelai() >= activeDelai*10) //changement d'etat si compteur >= delai d'activation
                {
                    (p.getActif()) ? p.setActif(false) : p.setActif(true);
                    p.setDelai(0);
                }

                p.setDelai(p.getDelai()+1); //incrementation compteur pour activer le piege
            }
        }
    }
}

void SDLjeu::ecrireTexte(const string& img, const string& txt,
                        int x, int y, Uint8 r, Uint8 v, Uint8 b, bool propre)
{
    if (propre) img_texte[img].setSurface(TTF_RenderText_Blended(police,txt.c_str(),{r,v,b}));

    else img_texte[img].setSurface(TTF_RenderText_Solid(police,txt.c_str(),{r,v,b}));

    img_texte[img].charger(ren);
    img_texte[img].afficher(ren,x,y);
}

void SDLjeu::champsVisionPerso(const Personnage& perso, int visionPerso)
{
    int perso_x = perso.getPosX();
    int perso_y = perso.getPosY();
    int visPix = visionPerso * TAILLE_SPRITE; //VisionPerso en pixel
    SDL_Rect r1,r2,r3,r4;

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); //On set la couleur noire (ce que le perso ne verra pas)

    /* bandes noires autour du personnage */
    /* Bord haut */
    r1.x=TAILLE_BORDURE; r1.y=0; //Coin haut gauche
    r1.w=winx-TAILLE_BORDURE*2; r1.h=perso_x-visPix; //Coin bas droit //-TAILLE_BORDURE*2 car on commence a x=TAILLE_BORDURE
    /* Bord gauche */
    r2.x=TAILLE_BORDURE; r2.y=0;
    r2.w=perso_y-visPix; r2.h=winy; if (r2.w<0) r2.w=0; //r2.w ne doit pas être négatif
    /* Bord droit */
    r3.x=perso_y+visPix+TAILLE_SPRITE+TAILLE_BORDURE; r3.y=0; //+TAILLE_SPRITE = taille du perso (les coords sont à la pos haut gauche)
    r3.w=winx-TAILLE_BORDURE-r3.x; r3.h=winy; if (r3.w<0) r3.w=0; //r3.w ne doit pas être négatif
    /* Bord bas */
    r4.x=TAILLE_BORDURE; r4.y=perso_x+visPix+TAILLE_SPRITE; //+TAILLE_SPRITE = taille du perso (les coords sont à la pos haut gauche)
    r4.w=winx-TAILLE_BORDURE*2; r4.h=winy-(perso_x+visPix); //-TAILLE_BORDURE*2 car on commence a x=TAILLE_BORDURE

    SDL_RenderFillRect(ren,&r1); //bord haut
    SDL_RenderFillRect(ren,&r2); //bord gauche
    SDL_RenderFillRect(ren,&r3); //bord droit
    SDL_RenderFillRect(ren,&r4); //bord bas

    /* Bords arrondis */
    SDL_Point centre;
    centre.x = perso_y+(TAILLE_SPRITE/2.00)+TAILLE_BORDURE;
    centre.y = perso_x+(TAILLE_SPRITE/2.00);
    int rayon = (visionPerso+1) * TAILLE_SPRITE; // +1 pour rendre les bords plus smooths

    //pixel par pixel pour rendre les bords arrondis
    //on dessine un cercle noir autour du personnage
    for (int w = 0; w <= rayon * 2 ; w++)
    {
        for (int h = 0; h <= rayon * 2 ; h++)
        {
            int dx = rayon - w; // horizontal
            int dy = rayon - h; // vertical
            if ((dx*dx + dy*dy) >= (rayon*TAILLE_SPRITE)) //si en dehors du rayon
            {
                //si on sort du canvas niveau on affiche pas les contours
                if (centre.x + dx<TAILLE_BORDURE) {dx=0; dy=0;}
                if (centre.x + dx>winx-TAILLE_BORDURE) {dx=0; dy=0;}
                SDL_RenderDrawPoint(ren, centre.x + dx, centre.y + dy);
            }
        }
    }
}

void SDLjeu::afficherHUD (const Personnage& perso)
{
	int vie = perso.getVie();         //vie courante du perso
	int vieMax = perso.getVieMax();   //vie maximum du perso
	int nbVies = perso.getNbVies();   //nb de vies du perso
	int monnaie=perso.getMonnaie();   //argent du perso
	string nomPerso = perso.getNom(); //nom du perso
	int padding; //pour mise en page de l'hud

    //image de texte contenant le nom du perso
    padding = 10;
    int centreurPersoX = (TAILLE_BORDURE - img_texte["nomPerso"].getW())/2;
    ecrireTexte("nomPerso",nomPerso,centreurPersoX,padding);

    //Nb de vies restante
	int marge = ((TAILLE_BORDURE / nbVies) - img_HUD[0].getW()) / 2; //offset pour centrer chaque image
	padding += img_texte["nomPerso"].getH() + 50;
	for (int i=0; i<nbVies; ++i)
	{
        img_HUD[0].afficher(ren, marge + i*(TAILLE_BORDURE/nbVies), padding);
	}

	// barre de vie totale
	padding += img_HUD[0].getH() + 30;
	SDL_Rect r_vie;
	r_vie.x=10; r_vie.y=padding;
	r_vie.h=TAILLE_SPRITE/2; r_vie.w=TAILLE_BORDURE-20;
    SDL_SetRenderDrawColor(ren, 240, 40, 40, 255);
	SDL_RenderFillRect(ren,&r_vie);

	//barre de vie restante
    SDL_Rect r_vieRestante;
    r_vieRestante.x=10; r_vieRestante.y=padding;
    r_vieRestante.h=TAILLE_SPRITE/2; r_vieRestante.w=((float)vie/(float)vieMax)*r_vie.w;
    SDL_SetRenderDrawColor(ren, 0, 200, 0, 255);
	SDL_RenderFillRect(ren,&r_vieRestante);

    //image de texte contenant la vie restante
    stringstream vieRestante; vieRestante << vie << "/" << vieMax;
    ecrireTexte("vieRestante",vieRestante.str(),r_vie.w/2-img_texte["vieRestante"].getW()/2,padding);

    //image de texte contenant la monnaie du perso
    padding += img_texte["vieRestante"].getH() + 30;
    marge = ( TAILLE_BORDURE - (img_HUD[2].getW()+img_texte["monnaie"].getW()) ) / 2;
    stringstream pieces; pieces << monnaie;
    img_HUD[2].afficher(ren, marge, padding);
    ecrireTexte("monnaie",pieces.str(),marge+img_HUD[2].getW(),padding);
}

void SDLjeu::afficherTempsRestant (const Niveau& niv)
{
    int marge;

    /* Temps courant */
    int tempsCourant = niv.getLimiteTemps() - horloge.get_s();
    int minutes = tempsCourant/60, secondes = tempsCourant%60;
    stringstream tempsR; tempsR<<"Temps restant: ";
    if (minutes<10) tempsR<<"0";
    tempsR<<minutes<<":";
    if (secondes<10) tempsR<<"0";
    tempsR<<secondes;

    /* Affichage */
    marge = ( TAILLE_BORDURE - img_texte["tempsRestant"].getW() ) / 2;
    ecrireTexte("tempsRestant",tempsR.str(),marge,winy/2);
}

void SDLjeu::afficherPieges(const Niveau& niv)
{
    int x,y,dir,id;
    for (unsigned i=0; i<niv.getNbPieges(); ++i)
    {
        const Piege p = niv.getPiege(i);

        x = p.getPosX(); y = p.getPosY();
        id = p.getId(); dir = p.getDir();

        if (p.getVisible()) //on affiche seulement les pieges visibles
        {
            if (dir == -1) //on change la direction pour l'img des pieges statiques
            {
                (p.getActif()) ? dir = 1 : dir = 0;
            }

            img_Piege[id][dir].afficher(ren, centreurX+y, centreurY+x);
        }
    }
}

void SDLjeu::afficher (const Niveau& niv, const Personnage& perso)
{
    int dimx = niv.getDimX();
    int dimy = niv.getDimY();

    //Pour centrer les tiles au centre de la fenêtre suivant le niveau et la bordure
    centreurX = winx/2 - (dimy*TAILLE_SPRITE)/2;
    centreurY = winy/2 - (dimx*TAILLE_SPRITE)/2;

    if (niv.getId() == 0) centreurY = 0; //Pour ne pas centrer le shop en Y

    //Couleur de fond
	SDL_SetRenderDrawColor(ren, 63, 80, 96, 255);
    //On remplit la fenêtre de la couleur choisie
	SDL_RenderClear(ren);

	int visionPerso = niv.getVision();

	string n;

	/* On affiche les decors du niveau */
    for (int i=0; i<dimx; ++i)
    {
        for (int j=0; j<dimy; ++j)
        {
            const Decor& d = niv(i,j);
            n = d.getNom();

            /* Base de sol du niveau */
            img_Sol.afficher(ren, centreurX+j*TAILLE_SPRITE, centreurY+i*TAILLE_SPRITE);

            if (n == "mur")
            {
                img_Mur.afficher(ren, centreurX+j*TAILLE_SPRITE, centreurY+i*TAILLE_SPRITE);
            }

            if (n == "piece")
            {
                img_Piece.afficher(ren, centreurX+j*TAILLE_SPRITE+TAILLE_SPRITE*0.15, centreurY+i*TAILLE_SPRITE+TAILLE_SPRITE*0.15);
            }

            if (n == "sortie")
            {
                img_Sortie.afficher(ren, centreurX+j*TAILLE_SPRITE, centreurY+i*TAILLE_SPRITE);
            }

            if (d.getVisible() == 0) //On remplace le sprite par un sol
            {
                img_Sol.afficher(ren, centreurX+j*TAILLE_SPRITE, centreurY+i*TAILLE_SPRITE);
            }
        }
    }

    /* Pieges du niveau */
    afficherPieges(niv);

    /* Marchand dans le cas du niveau shop (id : 0) */
    if (niv.getId() == 0)
    {
        int posX = jeu.getVendeur().getPosY()*TAILLE_SPRITE +centreurX;
        int posY = jeu.getVendeur().getPosX() +centreurY;
        img_Vendeur.afficher(ren,posX,posY);

        /* Si le personnage respecte touttess ses conditions et peut accéder au shop */
        if (perso.getPosX()>=posY && perso.getPosX()<=posY+img_Vendeur.getH()+img_Perso[0][1].getH() &&
            perso.getPosY()+centreurX>=posX && perso.getPosY()+centreurX<=posX+img_Vendeur.getW()-img_Perso[0][1].getH())
        {
            shop->setActif(true);
        }
        else shop->setActif(false);

        shop->dansMagasin(); //on affiche le magasin (si actif = true)
    }

    /* Image du personnage */
    /* frame_reduce reduit la vitesse de défilement des frames */
    float vitesse = perso.getVitesse();
	img_Perso [ perso.getDirection() ] [ frame_reduce(framePerso,vitesse) ]
    .afficher(ren, centreurX+perso.getPosY(), centreurY+perso.getPosX());

	/* On applique le champs de vision du personnage dans le niveau si il a été définit */
	if (visionPerso > 0)
	{
        champsVisionPerso(perso, visionPerso);
	}

	/* HUD du personnage */
	afficherHUD(perso);

	/* Nom du Niveau */
    string nomNiv = niv.getNom();
    ecrireTexte("nomNiveau", nomNiv, winx-TAILLE_BORDURE+10, winy/2);

    /* Affiche le temps restant du niveau courant si il y a une limite */
    if (niv.getLimiteTemps())
    {
        afficherTempsRestant(niv);
    }

    /* Affiche le menu */
    if(niv.getId()==1)
    {
        menu->afficherMenu();
    }
}

int SDLjeu::jouer () //Appelé à chaque nouveau niveau pour les init
{
  	/* On lance la soundrack du jeu */
  	lireSoundTrack();

    /* Si le nivEnCours == -1 > Le jeu est terminé */
    /* En attente du choix joueur : quitter / relancer */
    if (jeu.getNivEnCours() == -1)
    {
        scoreJeu.pause(); /* Timer pour le score du jeu */
        int choixJ = finJeu(); /* Menu de fin de jeu */
        if (choixJ == 0) return 0; //Fin jeu
    }

    /* Si le niveau est le menu */
    if (jeu.getNivEnCours() ==  1)
    {
        shop->ouvrir();  /* On (re) ouvre le magasin */
        scoreJeu.start(); /* Timer pour le score du jeu */
    }

    SDL_Event e;
    int collision;
    bool stop=false, limiteTemps=false;

  	Personnage& perso = jeu.getPerso();
  	Niveau& niv = jeu.getNiveau();

  	/* Initialisation de la position du personnage */
  	perso.setPosX(perso.getPosX() * TAILLE_SPRITE);
  	perso.setPosY(perso.getPosY() * TAILLE_SPRITE);
    framePerso=0; //Image a l'arret du personnage

  	/* Initialisation de la position des pieges */
  	for (unsigned i=0; i<niv.getNbPieges(); ++i)
  	{
        Piege& p = niv.getPiege(i);
        p.setInitX(p.getPosX() * TAILLE_SPRITE);
        p.setInitY(p.getPosY() * TAILLE_SPRITE);
  	}

  	/* On lance les timers de ticks */ //=> gérer les FPS
    FPS_perso.start();
    FPS_pieges.start();
    if (niv.getLimiteTemps()) horloge.start(); //limite de temps

    Uint32 temps = SDL_GetTicks(); //Gere les degats subis par le personnage

	while (!stop)
	{
	    /* Update du niveau */
	    deplacerPieges(niv);

	    /* Régulation des dégats subis par le personnage */
        if (SDL_GetTicks() - temps > 500) //toutes les 100ms
        {
            perso.setSubiDegats(false);
            temps = SDL_GetTicks();
        }

        /* On restart le timer de ticks pour les fps des pieges */
        FPS_pieges.start();

		/* Gestion des évenements */
		while (SDL_PollEvent(&e))
        {
            /* Touche clavier */
            if (e.type == SDL_KEYDOWN)
            {
                /* Fermer la fenêtre avec Escape */
                if (e.key.keysym.sym == SDLK_ESCAPE) stop = true;
            }

            /* Dans le shop */
            if (jeu.getNivEnCours() == 0)
            {
                if (e.type == SDL_MOUSEBUTTONDOWN) //clic souris
                {
                    if (shop->getActif())
                    {
                        jouerSon(son_clic,-1,0);
                        shop->vendre(e.button.x, e.button.y);
                    }
                }
            }

            /* Dans le menu */
            if (jeu.getNivEnCours() == 1)
            {
                if (e.type == SDL_MOUSEMOTION) //hover souris
                {
                    menu->afficheHover(e.motion.x, e.motion.y);
                }

                if (e.type==SDL_MOUSEBUTTONDOWN) //clic souris
                {
                    jouerSon(son_clic,-1,0);
                    int action = menu->traitementClic(niv, e.button.x, e.button.y, stop);
                    //modification du son
                    if (action == 1)
                    {
                        AvecSon = menu->getSon();
                        lireSoundTrack(); //on relit la soundtrack
                    }
                }
            }

            /* Fermer la fenêtre avec la croix */
            if (e.type == SDL_QUIT) stop = true;

            /* Frame de l'image "arret" du personnage quand on lache une touche */
            if (e.type == SDL_KEYUP) framePerso = 0;
        }

        /* Gestion des évenements de déplacement du personnage */
        perso_a_bouge=false; //Pour gérer les animations perso avec plusieurs touches appuyées sans augmenter la vitesse de defilement des images
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_UP]) actionClavierPixel(perso,niv,'h');
        if(state[SDL_SCANCODE_DOWN]) actionClavierPixel(perso,niv,'b');
        if(state[SDL_SCANCODE_LEFT]) actionClavierPixel(perso,niv,'g');
        if(state[SDL_SCANCODE_RIGHT]) actionClavierPixel(perso,niv,'d');

        /*On restart le timer de ticks pour les fps du perso */
        FPS_perso.start(); //=> pour le calcul du déplacement du perso

        /* Affichage */
        afficher(niv, perso);

        SDL_RenderPresent(ren); //Nouveau rendu

        /* Collisions du personnage avec le niveau */
        collision = collisions(niv,perso);

        /* Check de la limite de temps si il y en a une */
        if (niv.getLimiteTemps())
        {
            if (horloge.get_s() > niv.getLimiteTemps())
            {
                limiteTemps = true; //On arrete le jeu
            }
        }

        /* Recommencer le niveau */
        if (collision ==-1 || limiteTemps)
        {
            stop=true;
            jeu.recommencer();
            jouer();
        }

		/* Niveau suivant */
		if (collision ==1)
        {
            stop = true;
            jeu.niveauSuivant();
            jouer();
        }
	}

	return 0;
    //Ne rien mettre ici : EOF (F FOR FUNCTION HEHE)
}

int SDLjeu::finJeu ()
{
    SDL_Event e;
    bool stop = false;
    bool rejouer = false;

    menu->setMenuPrincipale(false); //on passe au menu de fin de jeu
    while (!stop)
    {
		/* Gestion des évenements */
		while (SDL_PollEvent(&e))
        {
            /* Touche clavier */
            if (e.type == SDL_KEYDOWN)
            {
                /* Fermer la fenêtre avec Escape */
                if (e.key.keysym.sym == SDLK_ESCAPE)
                {
                    stop = true;
                }
            }

            /* Hover de la souris sur les boutons */
            if (e.type == SDL_MOUSEMOTION) //hover souris
            {
                menu->afficheHover(e.motion.x, e.motion.y);
            }

            /* Clic souris */
            if (e.type==SDL_MOUSEBUTTONDOWN) //clic souris
            {
                rejouer = menu->traitementClicFinJeu(e.button.x, e.button.y, stop);
            }

            /* Fermer la fenêtre avec la croix */
            if (e.type == SDL_QUIT) stop = true;
        }

        menu->afficherMenu();
        if (!menu->getOption())
        {
            ecrireTexte("victoire","Tu as obtenu ta licence d'informatique!",50,10,255,255,255,true);
            ecrireTexte("score",score(),(winx-img_texte["score"].getW())/2,
                                        10+img_texte["victoire"].getH(),255,255,255,true);
        }

        SDL_RenderPresent(ren); //Nouveau rendu
    }

    if (rejouer == true)
    {
        jeu.initJeu();
        return 1;
    }

    return 0;
}

void SDLjeu::lireSoundTrack()
{
    if (AvecSon)
  	{
        if (jeu.getNivEnCours() == 1 || jeu.getNivEnCours() == -1) //Son du menu
        {
            if (!sonMenuEnCours)
            {
                Mix_PlayMusic(son_menu,-1);
                sonJeuEnCours=false; //pour laisser la soundtrack entre les niveaux
                sonMenuEnCours=true; //pour laisser la soundtrack dans le menu
            }
        }

        else if (!sonJeuEnCours) //On lance le son en jeu si il n'a pas deja demarre
        {
            Mix_PlayMusic(son_jeu,-1);
            sonJeuEnCours=true; //pour laisser la soundtrack entre les niveaux
            sonMenuEnCours=false; //pour laisser la soundtrack dans le menu
        }
    }
    else //(pour stopper la musique depuis le menu)
    {
        Mix_HaltMusic();
        sonJeuEnCours=false;
        sonMenuEnCours=false;
    }
}

string SDLjeu::score () //obligé de renvoyer l'objet string...
{
    float scorePerso = jeu.getPerso().getScore();
    float scoreTemps = scoreJeu.get_s()*0.5;
    float scoreVie = 100*(jeu.getPerso().getVie()/jeu.getPerso().getVieMax());

    float s = scorePerso+scoreVie - scoreTemps;
    if (s<=0) s=0.1; //meme si t'es nul tu as pas un score negatif ...

    stringstream score; score<<"Ton score est de : ";
    score<<s;
    return score.str();
}

void SDLjeu::chargeImages ()
{
    int taille_perso = TAILLE_SPRITE*0.7; //On réduit la taille du perso par rapport aux autres sprites

    /* TOOOUUSS les sprites du personnage */
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<=8; ++j)
        {
        	string dir; stringstream sj; sj << j;
			string mvt = (j==0) ? "a" : "m"+sj.str();
        	if (i==0) {dir = "g";} if (i==1) {dir = "h";} if (i==2) {dir = "d";} if (i==3) {dir = "b";}

            string file = "data/img/personnage/personnage_"+dir+"_"+mvt+".png";

            img_Perso[i][j].chargerFichier(ren, file.c_str(), taille_perso);
        }
    }

    /* Pieges */
    img_Piege[0][0].chargerFichier(ren, "data/img/pieges/feu_g.png", TAILLE_SPRITE);
    img_Piege[0][1].chargerFichier(ren, "data/img/pieges/feu_h.png", TAILLE_SPRITE);
    img_Piege[0][2].chargerFichier(ren, "data/img/pieges/feu_d.png", TAILLE_SPRITE);
    img_Piege[0][3].chargerFichier(ren, "data/img/pieges/feu_b.png", TAILLE_SPRITE);

    img_Piege[1][0].chargerFichier(ren, "data/img/pieges/fleche_g.png", TAILLE_SPRITE/4,TAILLE_SPRITE);
    img_Piege[1][1].chargerFichier(ren, "data/img/pieges/fleche_h.png", TAILLE_SPRITE,TAILLE_SPRITE/4);
    img_Piege[1][2].chargerFichier(ren, "data/img/pieges/fleche_d.png", TAILLE_SPRITE/4,TAILLE_SPRITE);
    img_Piege[1][3].chargerFichier(ren, "data/img/pieges/fleche_b.png", TAILLE_SPRITE,TAILLE_SPRITE/4);

    img_Piege[2][0].chargerFichier(ren, "data/img/pieges/pics_non_actif.png", TAILLE_SPRITE);
    img_Piege[2][1].chargerFichier(ren, "data/img/pieges/pics_actif.png", TAILLE_SPRITE);

    img_Piege[3][0].chargerFichier(ren, "data/img/pieges/sol_non_actif.png", TAILLE_SPRITE);
    img_Piege[3][1].chargerFichier(ren, "data/img/pieges/sol_actif.png", TAILLE_SPRITE);


    /* Pieces */
    img_Piece.chargerFichier(ren, "data/img/decor/piece.png", TAILLE_SPRITE*0.75);

    /* Mur */
    img_Mur.chargerFichier(ren, "data/img/decor/mur.png", TAILLE_SPRITE);

    /* Sol */
    img_Sol.chargerFichier(ren, "data/img/decor/sol.png", TAILLE_SPRITE);

    /* Sortie */
    img_Sortie.chargerFichier(ren, "data/img/decor/sortie.png", TAILLE_SPRITE);

    /* Marchand */
    img_Vendeur.chargerFichier(ren, "data/img/shop/vendeur.png", TAILLE_SPRITE*2);

    /* HUD */
    img_HUD[0].chargerFichier(ren, "data/img/personnage/hud/nbVies.png", TAILLE_SPRITE);
    img_HUD[1].chargerFichier(ren, "data/img/personnage/hud/vie.png", TAILLE_SPRITE/2, TAILLE_SPRITE/40);
    img_HUD[2].chargerFichier(ren, "data/img/personnage/hud/piece.png", TAILLE_SPRITE);

    /* MENU */
    menu->chargeImage();
}

void SDLjeu::chargeTexte ()
{
    /* nom du niveau */
    img_texte["nomNiveau"].setH(TAILLE_SPRITE);
    img_texte["nomNiveau"].setW(TAILLE_BORDURE-20);

    /* nom du personnage */
    int taille = jeu.getPerso().getNom().length() * 50;
    if (taille >= TAILLE_BORDURE - 50) taille = TAILLE_BORDURE - 50; //taille max du nom
    img_texte["nomPerso"].setH(TAILLE_SPRITE);
    img_texte["nomPerso"].setW(taille);

    /* vie restante du personnage */
    img_texte["vieRestante"].setH(TAILLE_SPRITE/2);
    img_texte["vieRestante"].setW(TAILLE_SPRITE*2);

    /* monnaie du personnage */
    img_texte["monnaie"].setH(TAILLE_SPRITE);
    img_texte["monnaie"].setW(TAILLE_SPRITE/2);

    /* temps restant */
    img_texte["tempsRestant"].setH(TAILLE_SPRITE);
    img_texte["tempsRestant"].setW(TAILLE_BORDURE*0.9);

    /* texte de fin */
    img_texte["victoire"].setH(TAILLE_SPRITE * 3);
    img_texte["victoire"].setW(winx - 100);

    /* score */
    img_texte["score"].setH(img_texte["victoire"].getH()/2);
    img_texte["score"].setW(img_texte["victoire"].getW()/2);
    /* le lore */
    img_texte["mort"].setH(TAILLE_SPRITE/2);
    img_texte["mort"].setW(TAILLE_SPRITE/2);
}
