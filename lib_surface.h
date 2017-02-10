#ifndef _LIB_SURFACE_H_
#define _LIB_SURFACE_H_

#include <stdlib.h>
#include <SDL/SDL.h>

//#define BIG_SCREEN
#ifndef BIG_SCREEN
#define RX 1024
#define RY 768
#else
#define RX 800
#define RY 600
#endif

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

#define BLANC  0x00ffffff
#define GRISC  0x00aaaaaa
#define GRISF  0x00555555
#define NOIR   0x00000000

#define ROUGEC 0x00ff0000
#define ROUGEF 0x00880000
#define VERTC  0x0000ff00
#define VERTF  0x00008800
#define BLEUC  0x000000ff
#define BLEUF  0x00000088

#define JAUNEC 0x00ffff00
#define JAUNEF 0x00888800
#define PALEC  0x0000ffff
#define PALEF  0x00008888
#define ROSEC  0x00ff00ff
#define ROSEF  0x00880088

#define MARRON1 0x00AD4F09
#define MARRON2 0x00A76726
#define MARRON3 0x0088421D
#define MARRON4 0x00AE642D

/* pour affichage avec %s dans printf, exemple :
 * printf("couleur = %s\n", COULEUR(valeur_numerique));
 */
#define COULEUR(c) ((c==BLANC)?"BLANC":(\
(c==GRISC)?"GRISC":(\
(c==GRISF)?"GRISF":(\
(c==NOIR)?"NOIR":(\
(c==ROUGEC)?"ROUGEC":(\
(c==ROUGEF)?"ROUGEF":(\
(c==VERTC)?"VERTC":(\
(c==VERTF)?"VERTF":(\
(c==BLEUC)?"BLEUC":(\
(c==BLEUF)?"BLEUF":(\
(c==JAUNEC)?"JAUNEC":(\
(c==JAUNEF)?"JAUNEF":(\
(c==PALEC)?"PALEC":(\
(c==PALEF)?"PALEF":(\
(c==ROSEC)?"ROSEC":(\
(c==ROSEF)?"ROSEF":(\
(c==MARRON1)?"MARRON1":(\
(c==MARRON2)?"MARRON2":(\
(c==MARRON3)?"MARRON3":(\
(c==MARRON4)?"MARRON4":(\
"AUTRE")))))))))))))))))))))


typedef struct {
    SDL_Surface *ecran;
    int x, y;
	int *xmin; // eviter un malloc dans remplirTriangle2d
	int *xmax;
} t_surface;

t_surface *creerFenetre(int x, int y);
void effacerFenetre(t_surface * surface, Uint32 couleur);
void definirPixel(t_surface *surface, int x, int y, Uint32 pixel);
SDL_Surface *obtenirEcran(t_surface *surface);
void majEcran(t_surface *surface);
Uint32 echelle_de_couleur(int z);

#endif
