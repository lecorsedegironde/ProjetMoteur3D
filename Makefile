prog: prog.c lib_2d.o lib_mat.o lib_surface.o lib_3d_etu.o lib_objet3d_etu.o lib_scene3d_etu.o
	gcc -g prog.c lib_2d.o lib_mat.o lib_surface.o lib_3d_etu.o lib_objet3d_etu.o lib_scene3d_etu.o PA_3d.o PA_objet3d.o PA_scene3d.o -lm -lSDL -o prog

lib_3d_etu.o: lib_3d_etu.c lib_3d.h
	gcc -c lib_3d_etu.c

lib_objet3d_etu.o: lib_objet3d_etu.c lib_3d.h
	gcc -c lib_objet3d_etu.c

lib_scene3d_etu.o: lib_scene3d_etu.c lib_3d.h
	gcc -c lib_scene3d_etu.c

###################
PA_3d.o: lib_3d.c lib_3d.h
	gcc -c lib_3d.c -o PA_3d.o

PA_objet3d.o: lib_objet3d.c lib_objet3d.h lib_3d.h
	gcc -c lib_objet3d.c -o PA_objet3d.o

PA_scene3d.o: lib_scene3d.c lib_scene3d.h lib_objet3d.h lib_3d.h
	gcc -c lib_scene3d.c -o PA_scene3d.o

###################
lib_2d.o: lib_2d.c lib_2d.h
	gcc -c lib_2d.c

lib_surface.o: lib_surface.c lib_surface.h
	gcc -c lib_surface.c

lib_mat.o: lib_mat.c lib_mat.h
	gcc -c lib_mat.c

###################
clean:
	rm lib_*.o prog