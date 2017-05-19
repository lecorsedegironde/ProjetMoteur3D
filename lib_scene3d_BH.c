#include <assert.h>
#include "lib_scene3d.h"
#include "lib_mat.h"

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
    //Actually matrix are the same as we copy their value we can use only one
    double matrix[4][4] = {{1, 0, 0, 0},
                           {0, 1, 0, 0},
                           {0, 0, 1, 0},
                           {0, 0, 0, 1}};
    //Copy the array into the struct one
    memcpy(&scene3d->descendant, &matrix, sizeof matrix);
    memcpy(&scene3d->montant, &matrix, sizeof matrix);
    return scene3d;
}

/**
 * Ajouter l'objet en tête des fils de la feuille/noeud ?
 *
 * @param pt_feuille le truc où on doit ajouter le fils
 * @param pt_objet le fils à ajouter
 * @return le fils
 */
t_scene3d *ajouter_relation_BH(t_scene3d *pt_feuille, t_objet3d *pt_objet) {
    t_scene3d *pt_fils = definirScene3d(pt_objet);
    pt_fils->pt_pere = pt_feuille;
    pt_fils->pt_suiv = pt_feuille->pt_fils;
    pt_feuille->pt_fils = pt_fils;
    return pt_fils;
}

void translationScene3d_BH(t_scene3d *pt_scene, t_point3d *vecteur) {
//    translationScene3d_PA(pt_scene, vecteur);
//    printf("Oups");
    //Matrices de translation et d'invertion
    double mat[4][4];
    double inv[4][4];
    //Matrice temporaire
    double temp[4][4];
    matrice_translation(vecteur, mat);
    matrice_translation_inv(vecteur, inv);
    if(pt_scene!=NULL){
        multiplication_matrice(temp,mat,pt_scene->descendant);
        memcpy(&pt_scene->descendant, &temp, sizeof temp);

        multiplication_matrice(temp,pt_scene->montant,inv);
        memcpy(&pt_scene->montant, &temp, sizeof temp);
    }
}

void rotationScene3d_BH(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY, float degreZ);

void dessinerScene3d_BH(t_surface *surface, t_scene3d *pt_scene) {
    assert(pt_scene->objet->est_camera);
    //Save camera for easier use
    t_objet3d *camera = pt_scene->objet;
    t_scene3d *son = pt_scene->pt_fils;
    //Draw sons
    while (son != NULL) {
        t_scene3d *brother = son->pt_suiv;
        dessinerObjet3d(surface, son->objet, camera);
//        if (brother != )
        son = son->pt_fils;
    }
}

// modifie l'arbre de la scene pour que pt_objet en soit la racine, pt_racine ne veut plus rien dire
void changerCamera_BH(t_scene3d *pt_objet);

void matrice_translation(t_point3d *vecteur, double mat[4][4]) {
    if (vecteur != NULL) {
        mat[0][0] = 1;
        mat[0][1] = 0;
        mat[0][2] = 0;
        mat[0][3] = vecteur->xyzt[0];

        mat[1][0] = 0;
        mat[1][1] = 1;
        mat[1][2] = 0;
        mat[1][3] = vecteur->xyzt[1];

        mat[2][0] = 0;
        mat[2][1] = 0;
        mat[2][2] = 1;
        mat[2][3] = vecteur->xyzt[2];

        mat[3][0] = 0;
        mat[3][1] = 0;
        mat[3][2] = 0;
        mat[3][3] = 1;
    }
}

void matrice_translation_inv(t_point3d *vecteur, double mat[4][4]) {
    if (vecteur != NULL) {
        mat[0][0] = 1;
        mat[0][1] = 0;
        mat[0][2] = 0;
        mat[0][3] = -vecteur->xyzt[0];

        mat[1][0] = 0;
        mat[1][1] = 1;
        mat[1][2] = 0;
        mat[1][3] = -vecteur->xyzt[1];

        mat[2][0] = 0;
        mat[2][1] = 0;
        mat[2][2] = 1;
        mat[2][3] = -vecteur->xyzt[2];

        mat[3][0] = 0;
        mat[3][1] = 0;
        mat[3][2] = 0;
        mat[3][3] = 1;
    }
}