#ifndef _LIB_3D_H_
#define _LIB_3D_H_

#include "lib_surface.h"

#define D -50.0
#define FX 1
#define FY 0.2

#define ORIGIN definirPoint3d(0,0,0)

typedef struct {
    double xyzt[4];
} t_point3d;

typedef struct {
    t_point3d *abc[3];
} t_triangle3d;

/*
 * Zone PA
 */

t_point3d *definirPoint3d_PA(double x, double y, double z);

t_point3d *definirVecteur3d_PA(double x, double y, double z);

t_triangle3d *definirTriangle3d_PA(t_point3d *a, t_point3d *b, t_point3d *c);

t_triangle3d *copierTriangle3d_PA(t_triangle3d *t);

void differenceVecteur3d_PA(t_point3d *v1, t_point3d *v2); //v1 = v1-v2
void sommeVecteur3d_PA(t_point3d *v1, t_point3d *v2); //v1 = v1+v2
void divisionVecteur3d_PA(t_point3d *v1, int n); //v1 = v1/n
t_point3d *centreGraviteTriangle3d_PA(t_triangle3d *t);

double zmoyen_PA(t_triangle3d *t);

void remplirTriangle3d_PA(t_surface *surface, t_triangle3d *triangle, Uint32 c, double l, double h, double d);

void translationTriangle3d_PA(t_triangle3d *t, t_point3d *vecteur);

void rotationTriangle3d_PA(t_triangle3d *t, t_point3d *centre, float degreX, float degreY, float degreZ);

void transformationTriangle3d_PA(t_triangle3d *t, double mat[4][4]);

/*
 * Zone BH
 */

t_point3d *definirPoint3d_BH(double x, double y, double z);

t_point3d *definirVecteur3d_BH(double x, double y, double z);

t_triangle3d *definirTriangle3d_BH(t_point3d *a, t_point3d *b, t_point3d *c);

t_triangle3d *copierTriangle3d_BH(t_triangle3d *t);

void differenceVecteur3d_BH(t_point3d *v1, t_point3d *v2); //v1 = v1-v2
void sommeVecteur3d_BH(t_point3d *v1, t_point3d *v2); //v1 = v1+v2
void divisionVecteur3d_BH(t_point3d *v1, int n); //v1 = v1/n
t_point3d *centreGraviteTriangle3d_BH(t_triangle3d *t);

double zmoyen_BH(t_triangle3d *t);

void remplirTriangle3d_BH(t_surface *surface, t_triangle3d *triangle, Uint32 c, double l, double h, double d);

void translationTriangle3d_BH(t_triangle3d *t, t_point3d *vecteur);

void rotationTriangle3d_BH(t_triangle3d *t, t_point3d *centre, float degreX, float degreY, float degreZ);

void transformationTriangle3d_BH(t_triangle3d *t, double mat[4][4]);

void freeTriangle(t_triangle3d *t);
/*
 * Zone a adapter...
 */

extern t_point3d *(*definirPoint3d)(double x, double y, double z);

extern t_point3d *(*definirVecteur3d)(double x, double y, double z);

extern t_triangle3d *(*definirTriangle3d)(t_point3d *a, t_point3d *b, t_point3d *c);

extern t_triangle3d *(*copierTriangle3d)(t_triangle3d *t);

extern void (*differenceVecteur3d)(t_point3d *v1, t_point3d *v2);

extern void (*sommeVecteur3d)(t_point3d *v1, t_point3d *v2);

extern void (*divisionVecteur3d)(t_point3d *v1, int n);

extern t_point3d *(*centreGraviteTriangle3d)(t_triangle3d *t);

extern double (*zmoyen)(t_triangle3d *t);

extern void (*remplirTriangle3d)(t_surface *surface, t_triangle3d *triangle, Uint32 c, double l, double h, double d);

extern void (*translationTriangle3d)(t_triangle3d *t, t_point3d *vecteur);

extern void (*rotationTriangle3d)(t_triangle3d *t, t_point3d *centre, float degreX, float degreY, float degreZ);

extern void (*transformationTriangle3d)(t_triangle3d *t, double mat[4][4]);


void usage_lib_3d();

#endif
