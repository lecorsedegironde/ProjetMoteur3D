#ifndef _LIB_OBJET3D_H_
#define _LIB_OBJET3D_H_

#include "lib_surface.h"
#include "lib_3d.h"

typedef enum {
	false=0, true
} t_bool;

typedef struct __liste3d t_maillon;

struct __liste3d
{
    t_triangle3d *face;
    Uint32 couleur;
    t_maillon *pt_suiv;
};

typedef struct __objet3d t_objet3d;

struct __objet3d
{
	t_bool est_trie;
	t_bool est_camera;
	double largeur,hauteur; // pas de sens si ce n'est pas une camera
	double proche,loin,distance_ecran; // pas de sens si ce n'est pas une camera
    t_maillon *tete; // pas de sens si c'est une camera
};

extern int nb_faces;

/*
 * Zone PA
 */

t_objet3d* objet_vide_PA();
t_objet3d *camera_PA(double l, double h, double n, double f, double d); // zone l*h dans le champ n->f
t_objet3d* parallelepipede_PA(double lx, double ly, double lz);
t_objet3d* sphere_PA(double r, double nlat, double nlong);
t_objet3d* sphere_amiga_PA(double r, double nlat, double nlong);
t_objet3d* arbre_PA(double lx, double ly, double lz);
t_objet3d* damier_PA(double lx, double lz, double nx, double nz);
t_objet3d *copierObjet3d_PA(t_objet3d *o); // attention, effectue une copie mirroir
void composerObjet3d_PA(t_objet3d* o, t_objet3d* o2);
void composerObjet3d_limite_en_z_PA(t_objet3d* o, t_objet3d* o2, t_objet3d *camera);
void libererObjet3d_PA(t_objet3d *o);
t_point3d *centreGraviteObjet3d_PA(t_objet3d *o);
void dessinerObjet3d_PA(t_surface *surface, t_objet3d* pt_objet, t_objet3d *camera);

void translationObjet3d_PA(t_objet3d* pt_objet, t_point3d *vecteur);
void translationObjet3d_fast_PA(t_objet3d* pt_objet, t_point3d *vecteur);
void rotationObjet3d_PA(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);
void rotationObjet3d_fast_PA(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);
void transformationObjet3d_PA(t_objet3d* pt_objet, double mat[4][4]);

/*
 * Zone etu
 */

t_objet3d* objet_vide_etu();
t_objet3d *camera_etu(double l, double h, double n, double f, double d); // zone l*h dans le champ n->f
t_objet3d* parallelepipede_etu(double lx, double ly, double lz);
t_objet3d* sphere_etu(double r, double nlat, double nlong);
t_objet3d* sphere_amiga_etu(double r, double nlat, double nlong);
t_objet3d* arbre_etu(double lx, double ly, double lz);
t_objet3d* damier_etu(double lx, double lz, double nx, double nz);
t_objet3d *copierObjet3d_etu(t_objet3d *o); // attention, effectue une copie mirroir
void composerObjet3d_etu(t_objet3d* o, t_objet3d* o2);
void composerObjet3d_limite_en_z_etu(t_objet3d* o, t_objet3d* o2, t_objet3d *camera);
void libererObjet3d_etu(t_objet3d *o);
t_point3d *centreGraviteObjet3d_etu(t_objet3d *o);
void dessinerObjet3d_etu(t_surface *surface, t_objet3d* pt_objet, t_objet3d *camera);

void translationObjet3d_etu(t_objet3d* pt_objet, t_point3d *vecteur);
void translationObjet3d_fast_etu(t_objet3d* pt_objet, t_point3d *vecteur);
void rotationObjet3d_etu(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);
void rotationObjet3d_fast_etu(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);
void transformationObjet3d_etu(t_objet3d* pt_objet, double mat[4][4]);

/*
 * Zone a adapter...
 */

static t_objet3d* (*objet_vide)() = objet_vide_PA;
static t_objet3d *(*camera)(double l, double h, double n, double f, double d) = camera_PA;
static t_objet3d* (*parallelepipede)(double lx, double ly, double lz) = parallelepipede_PA;
static t_objet3d* (*sphere)(double r, double nlat, double nlong) = sphere_PA;
static t_objet3d* (*sphere_amiga)(double r, double nlat, double nlong) = sphere_amiga_PA;
static t_objet3d* (*arbre)(double lx, double ly, double lz) = arbre_PA;
static t_objet3d* (*damier)(double lx, double lz, double nx, double nz) = damier_PA;
static t_objet3d *(*copierObjet3d)(t_objet3d *o) = copierObjet3d_PA;
static void (*composerObjet3d)(t_objet3d* o, t_objet3d* o2) = composerObjet3d_PA;
static void (*composerObjet3d_limite_en_z)(t_objet3d* o, t_objet3d* o2, t_objet3d *camera) = composerObjet3d_limite_en_z_PA;
static void (*libererObjet3d)(t_objet3d *o) = libererObjet3d_PA;
static t_point3d *(*centreGraviteObjet3d)(t_objet3d *o) = centreGraviteObjet3d_PA;
static void (*dessinerObjet3d)(t_surface *surface, t_objet3d* pt_objet, t_objet3d *camera) = dessinerObjet3d_PA;

static void (*translationObjet3d)(t_objet3d* pt_objet, t_point3d *vecteur) = translationObjet3d_PA;
static void (*translationObjet3d_fast)(t_objet3d* pt_objet, t_point3d *vecteur) = translationObjet3d_fast_PA;
static void (*rotationObjet3d)(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ) = rotationObjet3d_PA;
static void (*rotationObjet3d_fast)(t_objet3d* pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ) = rotationObjet3d_fast_PA;
static void (*transformationObjet3d)(t_objet3d* pt_objet, double mat[4][4]) = transformationObjet3d_PA;




void usage_lib_objet_3d();

#endif
