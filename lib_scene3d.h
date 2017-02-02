#ifndef LIB_SCENE3D_H_
#define LIB_SCENE3D_H_

#include "lib_surface.h"
#include "lib_3d.h"
#include "lib_objet3d.h"

typedef struct __scene3d t_scene3d;

#define _ARBRE_

#ifdef _ARBRE_
struct __scene3d
{
    t_objet3d *objet;
    double descendant[4][4];
    double montant[4][4];
    t_scene3d *pt_pere; // liste chainee de noeud
    t_scene3d *pt_fils; // descendants
    t_scene3d *pt_suiv; // liste chainee de noeud
};
#else
#define N_OBJET_MAX 30
struct __scene3d
{
	int *indices;
	t_objet3d **objet;
	int nb_objets;
    double descendant[4][4];
    double montant[4][4];
};
#endif

/*
 * Zone PA
 */

t_scene3d* definirScene3d_PA(t_objet3d *pt_objet);
t_scene3d* ajouter_relation_PA(t_scene3d* pt_feuille, t_objet3d *pt_objet); // ajout de l'objet en tete des fils
void translationScene3d_PA(t_scene3d *pt_scene, t_point3d *vecteur);
void rotationScene3d_PA(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY, float degreZ);
void dessinerScene3d_PA(t_surface *surface, t_scene3d* pt_scene);
void changerCamera_PA(t_scene3d *pt_objet); // modifie l'arbre de la scene pour que pt_objet en soit la racine, pt_racine ne veut plus rien dire

/*
 * Zone etu
 */

t_scene3d* definirScene3d_etu(t_objet3d *pt_objet);
t_scene3d* ajouter_relation_etu(t_scene3d* pt_feuille, t_objet3d *pt_objet); // ajout de l'objet en tete des fils
void translationScene3d_etu(t_scene3d *pt_scene, t_point3d *vecteur);
void rotationScene3d_etu(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY, float degreZ);
void dessinerScene3d_etu(t_surface *surface, t_scene3d* pt_scene);
void changerCamera_etu(t_scene3d *pt_objet); // modifie l'arbre de la scene pour que pt_objet en soit la racine, pt_racine ne veut plus rien dire

/*
 * Zone a adapter...
 */

extern t_scene3d* (*definirScene3d)(t_objet3d *pt_objet);
extern t_scene3d* (*ajouter_relation)(t_scene3d* pt_feuille, t_objet3d *pt_objet);
extern void (*translationScene3d)(t_scene3d *pt_scene, t_point3d *vecteur);
extern void (*rotationScene3d)(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY, float degreZ);
extern void (*dessinerScene3d)(t_surface *surface, t_scene3d* pt_scene);
extern void (*changerCamera)(t_scene3d *pt_objet);



void usage_lib_scene_3d();

#endif /* LIB_SCENE3D_H_ */
