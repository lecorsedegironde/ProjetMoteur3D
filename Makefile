prog: prog.c fonctions.c lib_2d.o lib_mat.o lib_surface.o lib_3d_BH.o lib_objet3d_BH.o lib_scene3d_BH.o
	gcc -g prog.c fonctions.c lib_2d.o lib_mat.o lib_surface.o lib_3d_BH.o lib_objet3d_BH.o lib_scene3d_BH.o PA_3d.o PA_objet3d.o PA_scene3d.o -lm -lSDL -o prog

lib_3d_BH.o: lib_3d_BH.c lib_3d.h lib_2d.o
	gcc -c lib_3d_BH.c

lib_objet3d_BH.o: lib_objet3d_BH.c lib_objet3d.h lib_3d_BH.o
	gcc -c lib_objet3d_BH.c

lib_scene3d_BH.o: lib_scene3d_BH.c lib_scene3d.h lib_objet3d_BH.o
	gcc -c lib_scene3d_BH.c

###################
PA_3d.o: lib_3d.c lib_3d.h lib_2d.o
	gcc -c lib_3d.c -o PA_3d.o

PA_objet3d.o: lib_objet3d.c lib_objet3d.h PA_3d.o
	gcc -c lib_objet3d.c -o PA_objet3d.o

PA_scene3d.o: lib_scene3d.c lib_scene3d.h PA_objet3d.o
	gcc -c lib_scene3d.c -o PA_scene3d.o

###################
lib_2d.o: lib_2d.c lib_2d.h lib_surface.o
	gcc -c lib_2d.c

lib_surface.o: lib_surface.c lib_surface.h
	gcc -c lib_surface.c

lib_mat.o: lib_mat.c lib_mat.h
	gcc -c lib_mat.c

###################
clean:
	rm lib_*.o prog
