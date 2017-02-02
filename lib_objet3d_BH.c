#include "lib_objet3d.h"

t_objet3d *objet_vide_PA() {}

t_objet3d *camera_PA(double l, double h, double n, double f, double d) {} // zone l*h dans le champ n->f
t_objet3d *parallelepipede_PA(double lx, double ly, double lz) {}

t_objet3d *sphere_PA(double r, double nlat, double nlong) {}

t_objet3d *sphere_amiga_PA(double r, double nlat, double nlong) {}

t_objet3d *arbre_PA(double lx, double ly, double lz) {}

t_objet3d *damier_PA(double lx, double lz, double nx, double nz) {}

t_objet3d *copierObjet3d_PA(t_objet3d *o) {} // attention, effectue une copie mirroir
void composerObjet3d_PA(t_objet3d *o, t_objet3d *o2) {}

void composerObjet3d_limite_en_z_PA(t_objet3d *o, t_objet3d *o2, t_objet3d *camera) {}

void libererObjet3d_PA(t_objet3d *o) {}

t_point3d *centreGraviteObjet3d_PA(t_objet3d *o) {}

void dessinerObjet3d_PA(t_surface *surface, t_objet3d *pt_objet, t_objet3d *camera) {}

void translationObjet3d_PA(t_objet3d *pt_objet, t_point3d *vecteur) {}

void translationObjet3d_fast_PA(t_objet3d *pt_objet, t_point3d *vecteur) {}

void rotationObjet3d_PA(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ) {}

void rotationObjet3d_fast_PA(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ) {}

void transformationObjet3d_PA(t_objet3d *pt_objet, double mat[4][4]) {}
