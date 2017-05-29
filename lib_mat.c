#include <math.h>
#include "lib_3d.h"
#include "lib_mat.h"

// v1 = m*v2
void multiplication_vecteur(t_point3d *v1, double m[4][4], t_point3d *v2) {
    int i, j;

    for (i = 0; i < 4; i++) {
        v1->xyzt[i] = 0;
        for (j = 0; j < 4; j++) {
            v1->xyzt[i] += m[i][j] * v2->xyzt[j];
        }
    }
}

// m1 = m2*m3
void multiplication_matrice(double m1[4][4], double m2[4][4], double m3[4][4]) {
    int i, j, k;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m1[i][j] = 0;
            for (k = 0; k < 4; k++) {
                m1[i][j] += m2[i][k] * m3[k][j];
            }
        }
    }
}

//m1 = m2
void copier_matrice(double m1[4][4], double m2[4][4]) {
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            m1[i][j] = m2[i][j];
        }
    }
}

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

//TODO: Change with quaternions if time
void matrice_rotation(t_point3d *centre, float degreX, float degreY, float degreZ, double mat[4][4]) {
    if (centre != NULL) {

        double x1, y1, z1;
        x1 = degreX * M_PI / 180;
        y1 = degreY * M_PI / 180;
        z1 = degreZ * M_PI / 180;
        double a = cos(x1), b = sin(x1), c = cos(y1), d = sin(y1), e = cos(z1), f = sin(z1),
        x = centre->xyzt[0], y = centre->xyzt[1], z = centre->xyzt[2];
        double mat_rot[4][4] = {
                {e*c,-f*c,d,-x*e*c+(y*f*c+(-z*d+x))},
                {e*d*b+a*f,(-f*d*b+a*e),-c*b,(-e*d*b-a*f)*x+(y*f*d*b+(-y*a*e+(z*c*b+y)))},
                {-e*a*d+f*b,(f*a*d+e*b),a*c,(e*a*d-f*b)*x+((-f*a*d-e*b)*y+(-z*a*c+z))},
                {0,0,0,1}
        };
        copier_matrice(mat, mat_rot);
    }
}


void matrice_rotation_inv(t_point3d *centre, float degreX, float degreY, float degreZ, double mat[4][4]) {
    matrice_rotation(centre, -degreX, -degreY, -degreZ, mat);
}
