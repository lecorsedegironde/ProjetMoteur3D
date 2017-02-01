#include "lib_3d.h"
#include "lib_mat.h"

/**
 * Déclaration d'un pointeur sur point
 * @param x coordonée x
 * @param y coordonée y
 * @param z coordonée z
 * @return le pointeur sur point
 */
t_point3d *definirPoint3d_BH(double x, double y, double z) {
    t_point3d *point3d = malloc(sizeof(t_point3d));
    point3d->xyzt[0] = x;
    point3d->xyzt[1] = y;
    point3d->xyzt[2] = z;
    point3d->xyzt[3] = 1;

    return point3d;
}

/**
 * Déclaration d'un pointeur sur vecteur utilisant un pointeur sur point
 * @param x coordonée x
 * @param y coordonée y
 * @param z coordonée z
 * @return le pointeur sur point qui matérialise le vecteur
 */
t_point3d *definirVecteur3d_BH(double x, double y, double z) {
    t_point3d *vector3d = malloc(sizeof(t_point3d));
    vector3d->xyzt[0] = x;
    vector3d->xyzt[1] = y;
    vector3d->xyzt[2] = z;
    vector3d->xyzt[3] = 0;

    return vector3d;
}

/**
 * Déclaration d'un pointeur sur triangle
 * @param a le point a du triangle
 * @param b le point b
 * @param c le point c
 * @return le pointeur sur triangle
 */
t_triangle3d *definirTriangle3d_BH(t_point3d *a, t_point3d *b, t_point3d *c) {
    t_triangle3d *triangle3d = malloc(sizeof(t_triangle3d));
    triangle3d->abc[0] = a;
    triangle3d->abc[1] = b;
    triangle3d->abc[2] = c;

    return triangle3d;
}

/**
 * Copie un triangle
 * @param t le pointeur sur le triangle à copier
 * @return le pointeur sur le triangle copié
 */
t_triangle3d *copierTriangle3d_BH(t_triangle3d *t) {
    t_triangle3d *copyTriangle = malloc(sizeof(t_triangle3d));
    for (int i = 0; i < 3; ++i) {
        t_point3d *copyPoint = definirPoint3d(t->abc[i]->xyzt[0], t->abc[i]->xyzt[1], t->abc[i]->xyzt[2]);
        copyTriangle->abc[i] = copyPoint;
    }

    return copyTriangle;
}

/**
 * Différence entre deux vecteurs
 * v1 = v1-v2, le résultat est stocké dans v1
 * @param v1 le pointeur sur vecteur 1
 * @param v2 le pointeur sur vecteur 2
 */
void differenceVecteur3d_BH(t_point3d *v1, t_point3d *v2) {
    v1->xyzt[0] = v1->xyzt[0] - v2->xyzt[0];
    v1->xyzt[1] = v1->xyzt[1] - v2->xyzt[1];
    v1->xyzt[2] = v1->xyzt[2] - v2->xyzt[2];
    v1->xyzt[3] = v1->xyzt[3] - v2->xyzt[3];
}

/**
 * Somme de deux vecteurs
 * v1 = v1+v2
 * @param v1 le pointeur sur vecteur 1
 * @param v2 le pointeur sur vecteur 2
 */
void sommeVecteur3d_BH(t_point3d *v1, t_point3d *v2) {
    v1->xyzt[0] = v1->xyzt[0] + v2->xyzt[0];
    v1->xyzt[1] = v1->xyzt[1] + v2->xyzt[1];
    v1->xyzt[2] = v1->xyzt[2] + v2->xyzt[2];
    v1->xyzt[3] = v1->xyzt[3] + v2->xyzt[3];
}

/**
 * Division d'un vecteur avec n
 * v1 = v1/n
 * @param v1
 * @param n
 */
void divisionVecteur3d_BH(t_point3d *v1, int n) {
    v1->xyzt[0] = v1->xyzt[0] / n;
    v1->xyzt[1] = v1->xyzt[1] / n;
    v1->xyzt[2] = v1->xyzt[2] / n;
    v1->xyzt[3] = v1->xyzt[3] / n;
}

/**
 * Calcul du centre de gravité d'un triangle
 * @param t le pointeur sur triangle
 * @return le pointeur sur point
 */
t_point3d *centreGraviteTriangle3d_BH(t_triangle3d *t) {
    //Centre de gravité :
    //x = a[x] + b[x] + c[x] / 3 et idem pour les autres
    double x = (t->abc[0]->xyzt[0] + t->abc[1]->xyzt[0] + t->abc[2]->xyzt[0]) / 3;
    double y = (t->abc[0]->xyzt[1] + t->abc[1]->xyzt[1] + t->abc[2]->xyzt[1]) / 3;
    double z = (t->abc[0]->xyzt[2] + t->abc[1]->xyzt[2] + t->abc[2]->xyzt[2]) / 3;

    return definirPoint3d(x, y, z);
}

/**
 * Calcul du z moyen d'un triangle
 * @param t le pointeur sur triangle
 * @return la valeur du zmoyen
 */
double zmoyen_BH(t_triangle3d *t) {
    return (t->abc[0]->xyzt[2] + t->abc[1]->xyzt[2] + t->abc[2]->xyzt[2]) / 3;
}

/**
 *
 * @param surface
 * @param triangle
 * @param c
 * @param l
 * @param h
 * @param d
 */
void remplirTriangle3d_BH(t_surface *surface, t_triangle3d *triangle, Uint32 c, double l, double h, double d) {

}

void translationTriangle3d_BH(t_triangle3d *t, t_point3d *vecteur) {
    //Création de la matrice
    double matTranslation[4][4] = {{1, 0, 0, vecteur->xyzt[0]},
                                   {0, 1, 0, vecteur->xyzt[1]},
                                   {0, 0, 1, vecteur->xyzt[2]},
                                   {0, 0, 0, 1}};
    //Pour chaque point, on le multiplie avec la matrice
    t_triangle3d * copy = copierTriangle3d(t);
    for (int i = 0; i < 3; ++i) {
        multiplication_vecteur(t->abc[i], matTranslation, copy->abc[i]);
    }
    free(copy);
}

void rotationTriangle3d_BH(t_triangle3d *t, t_point3d *centre, float degreX, float degreY, float degreZ) {
    //TODO Define rotation matrice
}

void transformationTriangle3d_BH(t_triangle3d *t, double mat[4][4]) {
    t_triangle3d * copy = copierTriangle3d(t);
    for (int i = 0; i < 3; ++i) {
        multiplication_vecteur(t->abc[i], mat, copy->abc[i]);
    }
    free(copy);
}