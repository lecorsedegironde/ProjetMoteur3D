#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_scene3d.h"

/** START SECTION LIB_3D **/
t_point3d *(*definirPoint3d)(double x, double y, double z) = definirPoint3d_BH;

t_point3d *(*definirVecteur3d)(double x, double y, double z) = definirVecteur3d_BH;

t_triangle3d *(*definirTriangle3d)(t_point3d *a, t_point3d *b, t_point3d *c) = definirTriangle3d_BH;

t_triangle3d *(*copierTriangle3d)(t_triangle3d *t) = copierTriangle3d_BH;

void (*differenceVecteur3d)(t_point3d *v1, t_point3d *v2) = differenceVecteur3d_BH;

void (*sommeVecteur3d)(t_point3d *v1, t_point3d *v2) = sommeVecteur3d_BH;

void (*divisionVecteur3d)(t_point3d *v1, int n) = divisionVecteur3d_BH;

t_point3d *(*centreGraviteTriangle3d)(t_triangle3d *t) = centreGraviteTriangle3d_BH;

double (*zmoyen)(t_triangle3d *t) = zmoyen_BH;

void (*remplirTriangle3d)(t_surface *surface, t_triangle3d *triangle, Uint32 c, double l, double h,
                          double d) = remplirTriangle3d_BH;

void (*translationTriangle3d)(t_triangle3d *t, t_point3d *vecteur) = translationTriangle3d_BH;

void (*rotationTriangle3d)(t_triangle3d *t, t_point3d *centre, float degreX, float degreY,
                           float degreZ) = rotationTriangle3d_BH;

void (*transformationTriangle3d)(t_triangle3d *t, double mat[4][4]) = transformationTriangle3d_BH;
/** END SECTION LIB_3D **/

/** START SECTION OBJET_3D **/
t_objet3d *(*objet_vide)() = objet_vide_BH;

t_objet3d *(*camera)(double l, double h, double n, double f, double d) = camera_BH;

t_objet3d *(*parallelepipede)(double lx, double ly, double lz) = parallelepipede_BH;

t_objet3d *(*sphere)(double r, double nlat, double nlong) = sphere_BH;

t_objet3d *(*sphere_amiga)(double r, double nlat, double nlong) = sphere_amiga_BH;

t_objet3d *(*arbre)(double lx, double ly, double lz) = arbre_BH;

t_objet3d *(*damier)(double lx, double lz, double nx, double nz) = damier_BH;

t_objet3d *(*copierObjet3d)(t_objet3d *o) = copierObjet3d_BH;

void (*composerObjet3d)(t_objet3d *o, t_objet3d *o2) = composerObjet3d_BH;

void (*composerObjet3d_limite_en_z)(t_objet3d *o, t_objet3d *o2, t_objet3d *camera) = composerObjet3d_limite_en_z_BH;

void (*libererObjet3d)(t_objet3d *o) = libererObjet3d_BH;

t_point3d *(*centreGraviteObjet3d)(t_objet3d *o) = centreGraviteObjet3d_BH;

void (*dessinerObjet3d)(t_surface *surface, t_objet3d *pt_objet, t_objet3d *camera) = dessinerObjet3d_BH;

void (*translationObjet3d)(t_objet3d *pt_objet, t_point3d *vecteur) = translationObjet3d_BH;

void (*rotationObjet3d)(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY,
                        float degreZ) = rotationObjet3d_BH;

void (*transformationObjet3d)(t_objet3d *pt_objet, double mat[4][4]) = transformationObjet3d_BH;
/** END SECTION OBJET_3D **/

/** START SECTION SCENE_3D **/
t_scene3d *(*definirScene3d)(t_objet3d *pt_objet) = definirScene3d_BH;

t_scene3d *(*ajouter_relation)(t_scene3d *pt_feuille, t_objet3d *pt_objet) = ajouter_relation_BH;

void (*translationScene3d)(t_scene3d *pt_scene, t_point3d *vecteur) = translationScene3d_PA;

void (*rotationScene3d)(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY,
                        float degreZ) = rotationScene3d_PA;

void (*dessinerScene3d)(t_surface *surface, t_scene3d *pt_scene) = dessinerScene3d_PA;

void (*changerCamera)(t_scene3d *pt_objet) = changerCamera_PA;
/** END SECTION SCENE_3D **/
