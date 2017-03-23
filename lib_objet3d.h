#ifndef _LIB_OBJET3D_H_
#define _LIB_OBJET3D_H_

#include "lib_surface.h"
#include "lib_3d.h"

typedef enum {
    false = 0, true
} t_bool;

typedef struct __liste3d t_maillon;

struct __liste3d {
    t_triangle3d *face;
    Uint32 couleur;
    t_maillon *pt_suiv;
};

typedef struct __objet3d t_objet3d;

struct __objet3d {
    t_bool est_trie;
    t_bool est_camera;
    double largeur, hauteur; // pas de sens si ce n'est pas une camera
    double proche, loin, distance_ecran; // pas de sens si ce n'est pas une camera
    t_maillon *tete; // pas de sens si c'est une camera
};

extern int nb_faces;

/*
 * Zone PA
 */

t_objet3d *objet_vide_PA();

t_objet3d *camera_PA(double l, double h, double n, double f, double d); // zone l*h dans le champ n->f
t_objet3d *parallelepipede_PA(double lx, double ly, double lz);

t_objet3d *sphere_PA(double r, double nlat, double nlong);

t_objet3d *sphere_amiga_PA(double r, double nlat, double nlong);

t_objet3d *arbre_PA(double lx, double ly, double lz);

t_objet3d *damier_PA(double lx, double lz, double nx, double nz);

t_objet3d *copierObjet3d_PA(t_objet3d *o); // attention, effectue une copie mirroir
void composerObjet3d_PA(t_objet3d *o, t_objet3d *o2);

void composerObjet3d_limite_en_z_PA(t_objet3d *o, t_objet3d *o2, t_objet3d *camera);

void libererObjet3d_PA(t_objet3d *o);

t_point3d *centreGraviteObjet3d_PA(t_objet3d *o);

void dessinerObjet3d_PA(t_surface *surface, t_objet3d *pt_objet, t_objet3d *camera);

void translationObjet3d_PA(t_objet3d *pt_objet, t_point3d *vecteur);

void translationObjet3d_fast_PA(t_objet3d *pt_objet, t_point3d *vecteur);

void rotationObjet3d_PA(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);

void rotationObjet3d_fast_PA(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);

void transformationObjet3d_PA(t_objet3d *pt_objet, double mat[4][4]);

/*
 * Zone BH
 */

t_objet3d *objet_vide_BH();

t_objet3d *camera_BH(double l, double h, double n, double f, double d); // zone l*h dans le champ n->f
t_objet3d *parallelepipede_BH(double lx, double ly, double lz);

t_objet3d *sphere_BH(double r, double nlat, double nlong);

t_objet3d *sphere_amiga_BH(double r, double nlat, double nlong);

t_objet3d *arbre_BH(double lx, double ly, double lz);

t_objet3d *damier_BH(double lx, double lz, double nx, double nz);

t_objet3d *copierObjet3d_BH(t_objet3d *o); // attention, effectue une copie mirroir
void composerObjet3d_BH(t_objet3d *o, t_objet3d *o2);

void composerObjet3d_limite_en_z_BH(t_objet3d *o, t_objet3d *o2, t_objet3d *camera);

void libererObjet3d_BH(t_objet3d *o);

t_point3d *centreGraviteObjet3d_BH(t_objet3d *o);

void dessinerObjet3d_BH(t_surface *surface, t_objet3d *pt_objet, t_objet3d *camera);

void translationObjet3d_BH(t_objet3d *pt_objet, t_point3d *vecteur);

void rotationObjet3d_BH(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);

void transformationObjet3d_BH(t_objet3d *pt_objet, double mat[4][4]);

void mergeSortZ(t_maillon **pMaillon);

void frontBackSplit(t_maillon *source, t_maillon **frontRef, t_maillon **backRef);

t_maillon *sortedMergeZ(t_maillon *a, t_maillon *b);

t_maillon *cloneMaillon(t_maillon* liste);

t_objet3d *sphereCreation(double r, double nlat, double nlong, t_bool colorGeneration);

/*
 * Zone a adapter...
 */

extern t_objet3d *(*objet_vide)();

extern t_objet3d *(*camera)(double l, double h, double n, double f, double d);

extern t_objet3d *(*parallelepipede)(double lx, double ly, double lz);

extern t_objet3d *(*sphere)(double r, double nlat, double nlong);

extern t_objet3d *(*sphere_amiga)(double r, double nlat, double nlong);

extern t_objet3d *(*arbre)(double lx, double ly, double lz);

extern t_objet3d *(*damier)(double lx, double lz, double nx, double nz);

extern t_objet3d *(*copierObjet3d)(t_objet3d *o);

extern void (*composerObjet3d)(t_objet3d *o, t_objet3d *o2);

extern void (*composerObjet3d_limite_en_z)(t_objet3d *o, t_objet3d *o2, t_objet3d *camera);

extern void (*libererObjet3d)(t_objet3d *o);

extern t_point3d *(*centreGraviteObjet3d)(t_objet3d *o);

extern void (*dessinerObjet3d)(t_surface *surface, t_objet3d *pt_objet, t_objet3d *camera);

extern void (*translationObjet3d)(t_objet3d *pt_objet, t_point3d *vecteur);

extern void (*translationObjet3d_fast)(t_objet3d *pt_objet, t_point3d *vecteur);

extern void (*rotationObjet3d)(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);

extern void (*rotationObjet3d_fast)(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ);

extern void (*transformationObjet3d)(t_objet3d *pt_objet, double mat[4][4]);


void usage_lib_objet_3d();

#endif
