#ifndef LIB_MAT_H_
#define LIB_MAT_H_

void multiplication_vecteur(t_point3d *v1, double m[4][4], t_point3d *v2); // v1 = m*v2
void multiplication_matrice(double m1[4][4], double m2[4][4], double m3[4][4]); // m1 = m2*m3
void copier_matrice(double m1[4][4], double m2[4][4]); // m1 = m2

void matrice_translation(t_point3d *vecteur, double mat[4][4]);
void matrice_translation_inv(t_point3d *vecteur, double mat[4][4]);
#endif
