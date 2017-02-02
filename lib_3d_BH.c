#include <math.h>
#include "lib_3d.h"
#include "lib_mat.h"
#include "lib_2d.h"

/**
 * Déclaration d'un pointeur sur point
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
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
 *
 * @param t le pointeur sur triangle
 * @return la valeur du zmoyen
 */
double zmoyen_BH(t_triangle3d *t) {
    return (t->abc[0]->xyzt[2] + t->abc[1]->xyzt[2] + t->abc[2]->xyzt[2]) / 3;
}

/**
 * Projection d'un triangle 3d en un trianlge 2d et création de la surface d'affichage
 *
 * @param surface la surface a remplir avec un triangle 2d
 * @param triangle le triangle 3d à afficher
 * @param c la couleur du triangle
 * @param l paramètre caméra : rapport d'ouverture
 * @param h paramètre caméra : rapport d'ouverture
 * @param d paramètre caméra : distance par rapport au point de projection
 */
void remplirTriangle3d_BH(t_surface *surface, t_triangle3d *triangle, Uint32 c, double l, double h, double d) {
    //Création de la matricez
    double mat[4][4] = {{1 / l, 0,     0,     0},
                        {0,     1 / h, 0,     0},
                        {0,     0,     1 / d, 0},
                        {0,     0,     1,     0}};
    //Pour chaque point, on le multiplie avec la matrice
    t_triangle3d *copy = copierTriangle3d(triangle);
    for (int i = 0; i < 3; ++i) {
        multiplication_vecteur(copy->abc[i], mat, triangle->abc[i]);
    }

    //Création de 3 points 2d
    t_point2d *p1 = definirPoint2d((int) ((copy->abc[0]->xyzt[0] / copy->abc[0]->xyzt[2]) + RX / 2),
                                   (int) (-(copy->abc[0]->xyzt[1] / copy->abc[0]->xyzt[2]) + RY / 2));

    t_point2d *p2 = definirPoint2d((int) ((copy->abc[1]->xyzt[0] / copy->abc[1]->xyzt[2]) + RX / 2),
                                   (int) (-(copy->abc[1]->xyzt[1] / copy->abc[1]->xyzt[2]) + RY / 2));

    t_point2d *p3 = definirPoint2d((int) ((copy->abc[2]->xyzt[0] / copy->abc[2]->xyzt[2]) + RX / 2),
                                   (int) (-(copy->abc[2]->xyzt[1] / copy->abc[2]->xyzt[2]) + RY / 2));
    t_triangle2d *triangle2d = definirTriangle2d(p1, p2, p3);

    remplirTriangle2d(surface, triangle2d, c);

    //Free pointers
    free(copy->abc[0]);
    free(copy->abc[1]);
    free(copy->abc[2]);
    free(copy);
    free(p1);
    free(p2);
    free(p3);
    free(triangle2d);

}

/**
 * Applique une translation au triangle
 *
 * @param t le triangle à translater
 * @param vecteur le vecteur de translation
 */
void translationTriangle3d_BH(t_triangle3d *t, t_point3d *vecteur) {
    //Création de la matrice
    double matTranslation[4][4] = {{1, 0, 0, vecteur->xyzt[0]},
                                   {0, 1, 0, vecteur->xyzt[1]},
                                   {0, 0, 1, vecteur->xyzt[2]},
                                   {0, 0, 0, 1}};
    //Pour chaque point, on le multiplie avec la matrice
    t_triangle3d *copy = copierTriangle3d(t);
    for (int i = 0; i < 3; ++i) {
        multiplication_vecteur(t->abc[i], matTranslation, copy->abc[i]);
    }
    free(copy->abc[0]);
    free(copy->abc[1]);
    free(copy->abc[2]);
    free(copy);
}

/**
 * Applique une rotation au triangle à travers l'utilisation des angles d'euler
 * On aura pour cela calculé une matrice de rotation à partir de ces angles et on translatera
 * le triangle à l'origine avant d'appliquer la rotation puis de le retranslater à son point d'origine
 *
 * @param t le triangle auquel appliquer la rotation
 * @param centre vecteur utilisé
 * @param degreX
 * @param degreY
 * @param degreZ
 */
void rotationTriangle3d_BH(t_triangle3d *t, t_point3d *centre, float degreX, float degreY, float degreZ) {
    //Transformation des angles d'euler en matrice de rotation
    double a = cos(degreX), b = sin(degreX),
            c = cos(degreY), d = sin(degreY),
            e = cos(degreZ), f = sin(degreZ);
    double matRotation[4][4] = {{c * e,                (-c) * f,             d,        0},
                                {b * d * e + a * f,    -(b * d * f) + a * e, -(b * c), 0},
                                {-(a * d * e) + b * f, a * d * f + b * e,    a * c,    0},
                                {0,                    0,                    0,        1}};
    //Translation des points vers l'origine, application de la matrice et tranlation inverse
    translationTriangle3d(t, definirVecteur3d(0, 0, 0));
    t_triangle3d *copy = copierTriangle3d(t);
    for (int i = 0; i < 3; ++i) {
        multiplication_vecteur(t->abc[i], matRotation, copy->abc[i]);
    }
    free(copy->abc[0]);
    free(copy->abc[1]);
    free(copy->abc[2]);
    free(copy);
    translationTriangle3d(t, centre);
}

/**
 * Applique une matrice de transformation donnée à un triangle
 *
 * @param t le triangle sur lequel appliquer la matrice
 * @param mat la matrice à appliquer
 */
void transformationTriangle3d_BH(t_triangle3d *t, double mat[4][4]) {
    t_triangle3d *copy = copierTriangle3d(t);
    for (int i = 0; i < 3; ++i) {
        multiplication_vecteur(t->abc[i], mat, copy->abc[i]);
    }
    free(copy->abc[0]);
    free(copy->abc[1]);
    free(copy->abc[2]);
    free(copy);

}