#include <math.h>
#include "lib_objet3d.h"
#include "lib_3d.h"

#define PARA_A definirPoint3d(-lx/2, -ly/2, -lz/2)
#define PARA_B definirPoint3d(lx/2, -ly/2, -lz/2)
#define PARA_C definirPoint3d(lx/2, ly/2, -lz/2)
#define PARA_D definirPoint3d(-lx/2, ly/2, -lz/2)
#define PARA_E definirPoint3d(-lx/2, -ly/2, lz/2)
#define PARA_F definirPoint3d(lx/2, -ly/2, lz/2)
#define PARA_G definirPoint3d(lx/2, ly/2, lz/2)
#define PARA_H definirPoint3d(-lx/2, ly/2, lz/2)

/**
 * Crée un objet 3d vide
 * Cet objet n'est pas une camera
 *
 * @return un pointeur sur objet3d
 */
t_objet3d *objet_vide_BH() {

    t_objet3d *objet3d = malloc(sizeof(t_objet3d));

    objet3d->est_trie = false;
    objet3d->est_camera = false;
    objet3d->tete = NULL;

    return objet3d;
}

/**
 * Crée une camera
 * zone l*h dans le champ n->f
 *
 * @param l
 * @param h
 * @param n
 * @param f
 * @param d
 * @return un pointeur sur camera
 */
t_objet3d *camera_BH(double l, double h, double n, double f, double d) {

    t_objet3d *camera = malloc(sizeof(t_objet3d));

    camera->est_trie = false;
    camera->est_camera = true;

    camera->largeur = l;
    camera->hauteur = h;
    camera->proche = n;
    camera->loin = f;
    camera->distance_ecran = d;

    camera->tete = NULL;

    return camera;
}

/**
 * Création d'un parallépipède
 *
 * @param lx longeur x
 * @param ly largeur x
 * @param lz profondeur z
 * @return un pointeur sur objet 3d parallépipède
 */
t_objet3d *parallelepipede_BH(double lx, double ly, double lz) {
    t_objet3d *parallepipede = objet_vide();
    //Création des maillons (12 triangles)
    //Maillon pour la chaine
    t_maillon *maillonTMP = NULL;

    for (int i = 0; i < 12; ++i) {
        t_maillon *maillon = malloc(sizeof(t_maillon));

        switch (i) {
            case 0:
                //ABC
                maillon->face = definirTriangle3d(PARA_A, PARA_B, PARA_C);
                maillon->couleur = ROUGEC;
                break;
            case 1:
                //ACD
                maillon->face = definirTriangle3d(PARA_A, PARA_C, PARA_D);
                maillon->couleur = ROUGEF;
                break;
            case 2:
                //DCG
                maillon->face = definirTriangle3d(PARA_D, PARA_C, PARA_G);
                maillon->couleur = VERTC;
                break;
            case 3:
                //DGH
                maillon->face = definirTriangle3d(PARA_D, PARA_G, PARA_H);
                maillon->couleur = VERTF;
                break;
            case 4:
                //HGF
                maillon->face = definirTriangle3d(PARA_H, PARA_G, PARA_F);
                maillon->couleur = BLEUC;
                break;
            case 5:
                //HFE
                maillon->face = definirTriangle3d(PARA_H, PARA_F, PARA_E);
                maillon->couleur = BLEUF;
                break;
            case 6:
                //EFB
                maillon->face = definirTriangle3d(PARA_E, PARA_F, PARA_B);
                maillon->couleur = JAUNEC;
                break;
            case 7:
                //AEB
                maillon->face = definirTriangle3d(PARA_A, PARA_E, PARA_B);
                maillon->couleur = JAUNEF;
                break;
            case 8:
                //HDE
                maillon->face = definirTriangle3d(PARA_H, PARA_D, PARA_E);
                maillon->couleur = PALEC;
                break;
            case 9:
                //HAD
                maillon->face = definirTriangle3d(PARA_H, PARA_A, PARA_D);
                maillon->couleur = PALEF;
                break;
            case 10:
                //FGC
                maillon->face = definirTriangle3d(PARA_F, PARA_G, PARA_C);
                maillon->couleur = ROSEC;
                break;
            case 11:
                //FCB
                maillon->face = definirTriangle3d(PARA_F, PARA_C, PARA_B);
                maillon->couleur = ROSEF;
                break;
            default:
                //WTF?
                return NULL;
        }

        !i ? (parallepipede->tete = maillon) : (maillonTMP->pt_suiv = maillon);
        maillonTMP = maillon;
    }
    return parallepipede;
}

t_objet3d *sphere_BH(double r, double nlat, double nlong) {}

t_objet3d *sphere_amiga_BH(double r, double nlat, double nlong) {}

t_objet3d *arbre_BH(double lx, double ly, double lz) {}

t_objet3d *damier_BH(double lx, double lz, double nx, double nz) {}

// attention, effectue une copie mirroir
/**
 * Effectuer une copie d'un objet 3d en dupliquant tous ses maillons
 *
 * @param o l'objet à copier
 * @return un pointeur sur la copie de l'objet
 */
t_objet3d *copierObjet3d_BH(t_objet3d *o) {
    t_objet3d *copyObject = malloc(sizeof(t_objet3d));
    t_maillon *parcoursMaillon = NULL;
    t_maillon *maillonTMP = NULL;
    t_bool isHead = true;

    //Copie des propriétés
    copyObject->est_camera = o->est_camera;
    copyObject->est_trie = o->est_trie;
    copyObject->distance_ecran = o->distance_ecran;
    copyObject->hauteur = o->hauteur;
    copyObject->largeur = o->largeur;
    copyObject->loin = o->loin;
    copyObject->proche = o->proche;

    //Si camera, un peu con mais on sait jamais
    copyObject->tete = o->tete;

    parcoursMaillon = o->tete;

    while (parcoursMaillon != NULL) {
        //Création nouveau maillon
        t_maillon *copyMaillon = malloc(sizeof(t_maillon));
        copyMaillon->couleur = parcoursMaillon->couleur;

        //Copier beaucoup de triangles semble causer une segfault ou le fait de réutiliser la même variable ?
        //Dans tous les cas ça marche avec malloc(0) ou pas
        copyMaillon->face = definirTriangle3d(ORIGIN, ORIGIN, ORIGIN);
        copyMaillon->face = copierTriangle3d(parcoursMaillon->face);

        if (isHead) {
            copyObject->tete = copyMaillon;
            isHead = false;
        } else {
            maillonTMP->pt_suiv = copyMaillon;
        }
        maillonTMP = copyMaillon;
        //On passe au maillon suivant
        parcoursMaillon = parcoursMaillon->pt_suiv;
    }
    return copyObject;
}

/**
 * Prend 2 objets 3d pour n'en faire qu'un seul
 *
 * @param o l'objet 3d récepteur
 * @param o2 l'objet 3d que l'on va rajouter à o
 */
void composerObjet3d_BH(t_objet3d *o, t_objet3d *o2) {
    //On va quand même tester, voir si c'est pas des cameras
    //TODO On est censé trier les objets ???
    if (!o->est_camera && !o2->est_camera) {
        t_maillon *maillonTMP = o->tete;

        while (maillonTMP->pt_suiv != NULL) {
            maillonTMP = maillonTMP->pt_suiv;
        }
        maillonTMP->pt_suiv = o2->tete;
    }

    free(o2);
}


void composerObjet3d_limite_en_z_BH(t_objet3d *o, t_objet3d *o2, t_objet3d *camera) {
    //Trier les triangles, du plus loin au plus proche

}

/**
 * Libérer tout les maillons de la chaine d'un objet 3d
 *
 * @param o l'objet à libérer
 */
void libererObjet3d_BH(t_objet3d *o) {
    t_maillon *maillonTMP = o->tete;

    while (maillonTMP != NULL) {
        freeTriangle(maillonTMP->face);
        maillonTMP = maillonTMP->pt_suiv;
    }

    free(maillonTMP);
    free(o->tete);
    free(o);
}

/**
 * Centre de gravité d'un objet 3d
 *
 * @param o objet dont on veut le centre de gravité
 * @return le centre de gravité
 */
t_point3d *centreGraviteObjet3d_BH(t_objet3d *o) {
    //Récupère les centres de gravité de tous les triangles et on les ajoute
    int i = 0; //Nb triangles
    double x = 0, y = 0, z = 0;
    t_maillon *maillonTMP = o->tete;

    while (maillonTMP != NULL) {
        t_point3d *point3d = centreGraviteTriangle3d(maillonTMP->face);
        x += point3d->xyzt[0];
        y += point3d->xyzt[1];
        z += point3d->xyzt[2];
        free(point3d);
        maillonTMP = maillonTMP->pt_suiv;
        ++i;
    }

    return definirPoint3d(x / i, y / i, z / i);
}

/**
 * On parcours l'objet pour dessiner chaque triangle
 *
 * @version 1 peintre
 * @param surface
 * @param pt_objet
 * @param camera
 */
void dessinerObjet3d_BH(t_surface *surface, t_objet3d *pt_objet, t_objet3d *camera) {
    t_maillon *maillonTMP = pt_objet->tete;
//    t_maillon *first = NULL;

//    Invert list
//    while (maillonTMP != NULL) {
//        t_maillon *nextMaillon = maillonTMP->pt_suiv;
//        maillonTMP->pt_suiv = first;
//        first = maillonTMP;
//        maillonTMP = nextMaillon;
//    }
//
//    maillonTMP = first;

    //Trier liste
    mergeSortZ(&maillonTMP);

    while (maillonTMP != NULL) {

        remplirTriangle3d(surface, maillonTMP->face, maillonTMP->couleur, camera->largeur, camera->hauteur,
                          camera->distance_ecran);
        maillonTMP = maillonTMP->pt_suiv;
    }
}

/**
 * Pour chaque maillon appliquer la translation
 *
 * @param pt_objet
 * @param vecteur
 */
void translationObjet3d_BH(t_objet3d *pt_objet, t_point3d *vecteur) {
    //Création de la matrice
    double matTranslation[4][4] = {{1, 0, 0, vecteur->xyzt[0]},
                                   {0, 1, 0, vecteur->xyzt[1]},
                                   {0, 0, 1, vecteur->xyzt[2]},
                                   {0, 0, 0, 1}};
    transformationObjet3d(pt_objet, matTranslation);
}

void translationObjet3d_fast_BH(t_objet3d *pt_objet, t_point3d *vecteur) {}

/**
 * Applique une rotation à un objet 3d
 *
 * @param pt_objet
 * @param centre
 * @param degreX
 * @param degreY
 * @param degreZ
 */
void rotationObjet3d_BH(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ) {
//Création de la matrice de rotation
    double a = cos(degreX), b = sin(degreX), c = cos(degreY), d = sin(degreY), e = cos(degreZ), f = sin(degreZ);
    double matRotation[4][4] = {{c * e,                (-c) * f,             d,        0},
                                {b * d * e + a * f,    -(b * d * f) + a * e, -(b * c), 0},
                                {-(a * d * e) + b * f, a * d * f + b * e,    a * c,    0},
                                {0,                    0,                    0,        1}};
    translationObjet3d(pt_objet, ORIGIN);
    transformationObjet3d(pt_objet, matRotation);
    translationObjet3d(pt_objet, centre);
}

void rotationObjet3d_fast_BH(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ) {}


/**
 * Applique une matrice de transformation à un objet
 *
 * @param pt_objet
 * @param mat
 */
void transformationObjet3d_BH(t_objet3d *pt_objet, double mat[4][4]) {
    t_maillon *maillonTMP = pt_objet->tete;

    while (maillonTMP != NULL) {
        transformationTriangle3d(maillonTMP->face, mat);
        maillonTMP = maillonTMP->pt_suiv;
    }
}

/**
 * MergeSort pour pouvoir trier la liste en fonction des z_moyens
 *
 * @param pMaillon le pointeur sur la liste à trier
 */
void mergeSortZ(t_maillon **pMaillon) {
    //Création des pointeurs temporaires
    t_maillon *head = *pMaillon;
    t_maillon *a;
    t_maillon *b;

    //Si la liste est vide ou ne contient qu'un seul élémet -> On quitte
    if (head != NULL) {
        if (head->pt_suiv != NULL) {
            //Divise la liste en 2
            frontBackSplit(head, &a, &b);

            //Tri récursif de ces deux parties
            mergeSortZ(&a);
            mergeSortZ(&b);

            //On fusionne les deux listes triées
            *pMaillon = sortedMergeZ(a, b);
        }
    }
}

/**
 * Permet de diviser une liste en deux
 * Si il a un nombre impair de maillons -> dans la première partie
 * Méthode des pointeurs fast and slow
 *
 * @param source la liste a trier
 * @param frontRef pointeur sur la première partie
 * @param backRef pointeur sur la seconde partie
 */
void frontBackSplit(t_maillon *source, t_maillon **frontRef, t_maillon **backRef) {
    t_maillon *fast;
    t_maillon *slow;

    //Si la liste fait moins de 2 maillons
    if (source == NULL || source->pt_suiv == NULL) {
        //On met la liste dans la tête et on renvoie NULL dans la deuxième liste
        *frontRef = source;
        *backRef = NULL;
    } else {
        //Le pointeur fast va deux fois plus vite que le pointeur slow donc lorsqu'il arrive à la fin de la liste
        //l'autre ne sera qu'au milieu de celle-ci
        slow = source;
        fast = source->pt_suiv;

        while (fast != NULL) {
            fast = fast->pt_suiv;
            //Si celui-ci n'est pas NULL -> pas à la fin de la liste on peut avancer
            if (fast != NULL) {
                //On peut donc avancer slow ici (pour pouvoir avoir le cas des listes de longueur impaire)
                slow = slow->pt_suiv;
                fast = fast->pt_suiv;
            }
        }
        //Donc slow est au milieu de la liste
        *frontRef = source;
        *backRef = slow->pt_suiv;
        //Divise la liste en deux :
        slow->pt_suiv = NULL;
    }
}

/**
 * Fusionne deux listes triées
 *
 * @param a liste 1
 * @param b liste 2
 * @return une liste triée
 */
t_maillon *sortedMergeZ(t_maillon *a, t_maillon *b) {
    t_maillon *result = NULL;

    //Cas de bases
    if (a == NULL) {
        result = b;
    } else if (b == NULL) {
        result = a;
    } else {
        //Ici on vérifie l'ordre des données
        if (zmoyen(a->face) <= zmoyen(b->face)) {
            result = a;
            //Récursion
            result->pt_suiv = sortedMergeZ(a->pt_suiv, b);
        } else {
            result = b;
            //Récursion
            result->pt_suiv = sortedMergeZ(a, b->pt_suiv);
        }
    }
    return result;
}
