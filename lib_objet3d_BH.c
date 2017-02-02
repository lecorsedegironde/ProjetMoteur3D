#include "lib_objet3d.h"

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

    objet3d->est_trie = true;
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
        //Dans tous les cas ça marche avec malloc(0)
        copyMaillon->face = malloc(0);
        copyMaillon->face = copierTriangle3d(parcoursMaillon->face);
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
t_point3d *centreGraviteObjet3d_BH(t_objet3d *o) {}

void dessinerObjet3d_BH(t_surface *surface, t_objet3d *pt_objet, t_objet3d *camera) {}

void translationObjet3d_BH(t_objet3d *pt_objet, t_point3d *vecteur) {}

void translationObjet3d_fast_BH(t_objet3d *pt_objet, t_point3d *vecteur) {}

void rotationObjet3d_BH(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ) {}

void rotationObjet3d_fast_BH(t_objet3d *pt_objet, t_point3d *centre, float degreX, float degreY, float degreZ) {}

void transformationObjet3d_BH(t_objet3d *pt_objet, double mat[4][4]) {}
