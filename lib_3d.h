#ifndef _LIB_3D_H_
#define _LIB_3D_H_

#include "lib_surface.h"

#define D -50.0
#define FX 1
#define FY 0.2

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
 * Zone etu
 */

t_point3d *definirPoint3d_etu(double x, double y, double z);

t_point3d *definirVecteur3d_etu(double x, double y, double z);

t_triangle3d *definirTriangle3d_etu(t_point3d *a, t_point3d *b, t_point3d *c);

t_triangle3d *copierTriangle3d_etu(t_triangle3d *t);

void differenceVecteur3d_etu(t_point3d *v1, t_point3d *v2); //v1 = v1-v2
void sommeVecteur3d_etu(t_point3d *v1, t_point3d *v2); //v1 = v1+v2
void divisionVecteur3d_etu(t_point3d *v1, int n); //v1 = v1/n
t_point3d *centreGraviteTriangle3d_etu(t_triangle3d *t);

double zmoyen_etu(t_triangle3d *t);

void remplirTriangle3d_etu(t_surface *surface, t_triangle3d *triangle, Uint32 c, double l, double h, double d);

void translationTriangle3d_etu(t_triangle3d *t, t_point3d *vecteur);

void rotationTriangle3d_etu(t_triangle3d *t, t_point3d *centre, float degreX, float degreY, float degreZ);

void transformationTriangle3d_etu(t_triangle3d *t, double mat[4][4]);


/*
 * Zone a adapter...
 */

static t_point3d *(*definirPoint3d)(double x, double y, double z) = definirPoint3d_PA;

static t_point3d *(*definirVecteur3d)(double x, double y, double z) = definirVecteur3d_PA;

static t_triangle3d *(*definirTriangle3d)(t_point3d *a, t_point3d *b, t_point3d *c) = definirTriangle3d_PA;

static t_triangle3d *(*copierTriangle3d)(t_triangle3d *t) = copierTriangle3d_PA;

static void (*differenceVecteur3d)(t_point3d *v1, t_point3d *v2) = differenceVecteur3d_PA;

static void (*sommeVecteur3d)(t_point3d *v1, t_point3d *v2) = sommeVecteur3d_PA;

static void (*divisionVecteur3d)(t_point3d *v1, int n) = divisionVecteur3d_PA;

static t_point3d *(*centreGraviteTriangle3d)(t_triangle3d *t) = centreGraviteTriangle3d_PA;

static double (*zmoyen)(t_triangle3d *t) = zmoyen_PA;

static void (*remplirTriangle3d)(t_surface *surface, t_triangle3d *triangle, Uint32 c, double l, double h,
                                 double d) = remplirTriangle3d_PA;

static void (*translationTriangle3d)(t_triangle3d *t, t_point3d *vecteur) = translationTriangle3d_PA;

static void (*rotationTriangle3d)(t_triangle3d *t, t_point3d *centre, float degreX, float degreY,
                                  float degreZ) = rotationTriangle3d_PA;

static void (*transformationTriangle3d)(t_triangle3d *t, double mat[4][4]) = transformationTriangle3d_PA;


void usage_lib_3d();

#endif
