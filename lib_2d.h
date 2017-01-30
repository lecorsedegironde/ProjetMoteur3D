#ifndef _LIB_2D_H_
#define _LIB_2D_H_

#include "lib_surface.h"

typedef struct
{
    int x, y;
} t_point2d;

typedef struct
{
    t_point2d t[3];
} t_triangle2d;

t_point2d *definirPoint2d(int x, int y);
t_triangle2d *definirTriangle2d(t_point2d * a, t_point2d * b, t_point2d * c);
void remplirTriangle2d(t_surface * surface, t_triangle2d * triangle, Uint32 c);

#endif
