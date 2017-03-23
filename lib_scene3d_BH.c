#include "lib_scene3d.h"

/**
 * On commence par définir une scene avec un objet
 * @param pt_objet Un pointeur sur objet3d
 * @return une scene
 */
t_scene3d *definirScene3d_BH(t_objet3d *pt_objet) {

    t_scene3d *scene3d = malloc(sizeof(t_scene3d));
    //Attribuer l'objet à la scene
    scene3d->objet = pt_objet;
    //Le pointeur suivant de la chaine
    scene3d->pt_suiv = NULL;
    scene3d->pt_fils = NULL;
    scene3d->pt_pere = NULL;

    //Set up matrix
    //Actually matrix are the same as we copy their value wu can use only one
    double matrix[4][4] = {{1, 0, 0, 0},
                               {0, 1, 0, 0},
                               {0, 0, 1, 0},
                               {0, 0, 0, 1}};
    //Copy the array into the struct one
    memcpy(&scene3d->descendant, &matrix, sizeof matrix);
    memcpy(&scene3d->montant, &matrix, sizeof matrix);
    return scene3d;
}

// ajout de l'objet en tete des fils
/**
 * Ajouter l'objet en tête des fils de la feuille/noeud ?
 *
 * @param pt_feuille le truc où on doit ajouter le fils
 * @param pt_objet le fils à ajouter
 * @return la nouvelle scene avec le fils
 */
t_scene3d *ajouter_relation_BH(t_scene3d *pt_feuille, t_objet3d *pt_objet) {
//    t_scene3d *

    return NULL;
}

void translationScene3d_BH(t_scene3d *pt_scene, t_point3d *vecteur);

void rotationScene3d_BH(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY, float degreZ);

void dessinerScene3d_BH(t_surface *surface, t_scene3d *pt_scene);

// modifie l'arbre de la scene pour que pt_objet en soit la racine, pt_racine ne veut plus rien dire
void changerCamera_BH(t_scene3d *pt_objet);
