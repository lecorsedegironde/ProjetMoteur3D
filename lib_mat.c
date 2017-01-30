#include "lib_3d.h"
#include "lib_mat.h"

void multiplication_vecteur(t_point3d *v1, double m[4][4], t_point3d *v2) // v1 = m*v2
{
	int i, j;

	for(i=0; i<4; i++)
	{
		v1->xyzt[i] = 0;
		for(j=0; j<4; j++)
		{
			v1->xyzt[i] += m[i][j]*v2->xyzt[j];
		}
	}
}

void multiplication_matrice(double m1[4][4], double m2[4][4], double m3[4][4]) // m1 = m2*m3
{
	int i, j, k;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			m1[i][j] = 0;
			for(k=0; k<4; k++)
			{
				m1[i][j] += m2[i][k]*m3[k][j];
			}
		}
	}
}

void copier_matrice(double m1[4][4], double m2[4][4])
{
	int i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			m1[i][j] = m2[i][j];
		}
	}
}
