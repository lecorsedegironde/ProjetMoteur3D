#include "lib_scene3d.h"

t_scene3d *definirScene3d_BH(t_objet3d *pt_objet);

// ajout de l'objet en tete des fils
t_scene3d *ajouter_relation_BH(t_scene3d *pt_feuille, t_objet3d *pt_objet);

void translationScene3d_BH(t_scene3d *pt_scene, t_point3d *vecteur);

void rotationScene3d_BH(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY, float degreZ);

void dessinerScene3d_BH(t_surface *surface, t_scene3d *pt_scene);

// modifie l'arbre de la scene pour que pt_objet en soit la racine, pt_racine ne veut plus rien dire
void changerCamera_BH(t_scene3d *pt_objet);
