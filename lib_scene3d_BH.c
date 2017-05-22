#include <assert.h>
#include <math.h>
#include "lib_scene3d.h"
#include "lib_mat.h"
#include "lib_3d.h"

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
    //Matrices de translation et d'invertion
    if (pt_scene != NULL) {
        double des[4][4];
        double mont[4][4];
        //Matrice temporaire
        double temp[4][4];
        if (pt_scene->objet->est_camera) {
            //Ouch
            matrice_translation_inv(vecteur, des);
            matrice_translation(vecteur, mont);
        } else {
            matrice_translation(vecteur, des);
            matrice_translation_inv(vecteur, mont);
        }
        multiplication_matrice(temp, des, pt_scene->descendant);
        memcpy(&pt_scene->descendant, &temp, sizeof temp);

        multiplication_matrice(temp, mont, pt_scene->montant);
        memcpy(&pt_scene->montant, &temp, sizeof temp);
    }
}

void rotationScene3d_BH(t_scene3d *pt_scene, t_point3d *centre, float degreX, float degreY, float degreZ) {
    //Matrices de rotation et d'invertion
    if (pt_scene != NULL) {
        double des[4][4];
        double mont[4][4];
        //Matrice temporaire
        double temp[4][4];

        if (pt_scene->objet->est_camera) {
            //Ouch
            matrice_rotation(centre, degreX, degreY, degreZ, des);
            matrice_rotation_inv(centre, degreX, degreY, degreZ, mont);
        } else {
            matrice_rotation_inv(centre, degreX, degreY, degreZ, des);
            matrice_rotation(centre, degreX, degreY, degreZ, mont);
        }

        multiplication_matrice(temp, pt_scene->descendant, des);
        memcpy(&pt_scene->descendant, &temp, sizeof temp);

        multiplication_matrice(temp, mont, pt_scene->montant);
        memcpy(&pt_scene->montant, &temp, sizeof temp);

    }
}

void dessinerScene3d_BH(t_surface *surface, t_scene3d *pt_scene) {
    assert(pt_scene->objet->est_camera);
    //Save camera for easier use
    t_objet3d *camera = pt_scene->objet;

    //Create Big 3d object containing all triangles
    t_objet3d *composeObject = objet_vide();

    t_point3d *vector = definirVecteur3d(0, 0, 0);
    double des[4][4];
    double mont[4][4];
    double temp[4][4];
    //Create identity matrix
    matrice_translation(vector, des);
    matrice_translation_inv(vector, mont);

    multiplication_matrice(temp, des, pt_scene->descendant);
    memcpy(&des, &temp, sizeof temp);
    multiplication_matrice(temp, pt_scene->montant, mont);
    memcpy(&mont, &temp, sizeof temp);

    if (pt_scene->pt_fils != NULL) compose_scene(pt_scene->pt_fils, composeObject, camera, des, mont);
    //Tri objet
    sortObjet3d(composeObject);
    //Dessiner objet
    dessinerObjet3d(surface, composeObject, camera);
    //Free object
    libererObjet3d(composeObject);
}

void compose_scene(t_scene3d *scene, t_objet3d *composeObject, t_objet3d *camera, double des[4][4], double mont[4][4]) {
    if (scene != NULL) {
        //Create temp matrix for applying to object
        double des_temp[4][4];
        double mont_temp[4][4];
        //Multiply matrix with scene mat
        multiplication_matrice(des_temp, des, scene->descendant);
        multiplication_matrice(mont_temp, scene->montant, mont);

        //Copy object and apply transformations
        t_objet3d *copy = copierObjet3d(scene->objet);
        transformationObjet3d(copy, des_temp);

        //Compose object into big object
        composerObjet3d_limite_en_z(composeObject, copy, camera);

        //Compose sons
        compose_scene(scene->pt_fils, composeObject, camera, des_temp, mont_temp);
        //Compose siblings
        compose_scene(scene->pt_suiv, composeObject, camera, des, mont);

    }
}

// modifie l'arbre de la scene pour que pt_objet en soit la racine, pt_racine ne veut plus rien dire
void changerCamera_BH(t_scene3d *pt_objet);