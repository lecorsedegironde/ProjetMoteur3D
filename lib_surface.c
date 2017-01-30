#include "lib_surface.h"

void definirPixel(t_surface *surface, int x, int y, Uint32 pixel)
{
    unsigned char * p;
    SDL_Surface *ecran = surface->ecran;
    int bpp = ecran->format->BytesPerPixel;
    p = (unsigned char *)ecran->pixels + y * ecran->pitch + x * bpp;
    *(unsigned long*)p = pixel;
}

t_surface *creerFenetre(int x, int y)
{
    t_surface *S;
    SDL_Surface *ecran = NULL;

    S = (t_surface *) malloc(sizeof(t_surface));

    if (S != NULL)
    {
        ecran = SDL_SetVideoMode(x, y, 32, SDL_HWSURFACE);

        S->ecran = ecran;
        S->x = x;
        S->y = y;
        S->xmin = (int*)malloc(RY*sizeof(int));
        S->xmax = (int*)malloc(RY*sizeof(int));


        if (S->xmin==NULL || S->xmax==NULL)
        {
        	free(S->xmin);
        	free(S->xmax);
            free(S);
        } else {
	
	  memset(S->xmax, 0, RY*sizeof(int));
	  memset(S->xmin, RX-1, RY*sizeof(int));
	}
    }
    return S;
}

void effacerFenetre(t_surface * surface, Uint32 couleur)
{
    SDL_FillRect(obtenirEcran(surface), NULL, couleur);
}

t_surface * chargerImageBMP(char *fichier)
{
    t_surface *S;
    SDL_Surface *image = NULL;

    S = (t_surface *) malloc(sizeof(t_surface));

    if (S != NULL)
    {
        image = SDL_LoadBMP(fichier);

        S->ecran = image;
        S->x = image->w;
        S->y = image->h;

    }
    return S;
}

SDL_Surface *obtenirEcran(t_surface *surface)
{
    SDL_Surface *ecran = surface->ecran;
    return ecran;
}

void majEcran(t_surface *surface)
{
    SDL_Flip(obtenirEcran(surface));
}

Uint32 echelle_de_couleur(int z) // z \in [0, 1275]
{
	if (z<255)
	{
		return (255<<16) + (z<<8) + 0;
	} else if (z<510) {
		return ((510-z)<<16) + (255<<8) + 0;
	} else if (z<765) {
		return 0 + (255<<8) + (z-510);
	} else if (z<1020) {
		return 0 + ((1020-z)<<8) + 255;
	} else if (z<1275) {
		return ((z-1020)<<16) + 0 + 255;
	} else {
		if (z>1400) z = 1400;
		return (255<<16) + 0 + (1530-z);
	}
}
