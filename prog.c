#include <stdio.h>
#include "lib_surface.h"
#include "lib_3d.h"
#include "lib_objet3d.h"
#include "lib_scene3d.h"
#include "event.h"

#define N_CAMERA 1
//#define DUREE 3*60

t_scene3d *scene, *cams[N_CAMERA];
t_bool is_pause = false;
t_bool quit = false;

t_objet3d *cam;
//int idx_cam = 1;

int dxTotal = 0, dyTotal = 0, dzTotal = 0;
float rxTotal = 0, ryTotal = 0;

void handle_events(Input in) {
    int dx = 0, dy = 0, dz = 0;
    float rx = 0, ry = 0;

    if (in.mouse_motion && in.mousebuttons[SDL_BUTTON_LEFT]) {
        //rotation de la camera active
        // definition : 200px = rotation de 90° sur un axe
        rx = (float) (90.0 * (in.mousey - in.mouseyp) / 200.0);
        ry = (float) (90.0 * (in.mousex - in.mousexp) / 200.0);
    }

    if (in.key[SDLK_w]) {
        dz--;
    } else if (in.key[SDLK_s]) {
        dz++;
    }

    if (in.key[SDLK_a]) {
        dx--;
    } else if (in.key[SDLK_d]) {
        dx++;
    }

    if (in.key[SDLK_UP]) {
        dy++;
    } else if (in.key[SDLK_DOWN]) {
        dy--;
    }


    if (in.key[SDLK_r]) {
        dx = -dxTotal;
        dy = -dyTotal;
        dz = -dzTotal;
        rx = -rxTotal;
        ry = -ryTotal;
    }

    if (in.key[SDLK_SPACE]) {
        is_pause ? (is_pause = false) : (is_pause = true);
    }

    if (in.key[SDLK_ESCAPE] || in.quit) {
        quit = true;
    }
    dxTotal += dx;
    dyTotal += dy;
    dzTotal += dz;
    rxTotal += rx;
    ryTotal += ry;

    t_point3d *centre = definirPoint3d(0, 0, 0);
    t_point3d *deplacement = definirVecteur3d(dx, dy, dz);

    rotationScene3d(scene, centre, rx, ry, 0);
    translationScene3d(scene, deplacement);
    free(deplacement);
    free(centre);
}

int main(int argc, char **argv) {
    t_surface *surface = NULL;
    int cpt = 0;
    int timestart, oldtime;
    char buf[50];
    t_point3d *origine = definirPoint3d(0, 0, 0);
    t_point3d *centre_voiture = definirPoint3d(0, 50, -300);
    t_point3d *v = definirVecteur3d(2, 0, 0), *vi = definirVecteur3d(-2, 0, 0);
    t_scene3d *scn_sol, *scn_voiture, *scn_arb, *scn_r1, *scn_r2, *scn_r3, *scn_r4;
    int i = 0, sens = 1;

    //Declare and initialise input
    Input in;
    memset(&in, 0, sizeof(in));

    scn_sol = definirScene3d(damier(1000, 1000, 11, 11));

    cam = camera(1.0, 1.0, -100, -2000, -400);
    cams[0] = ajouter_relation(scn_sol, cam);

    scn_voiture = ajouter_relation(scn_sol, parallelepipede(100, 50, 50));
    translationScene3d(scn_voiture, centre_voiture);

    scn_r1 = ajouter_relation(scn_voiture, sphere_amiga(20, 6, 8));
    translationScene3d(scn_r1, definirVecteur3d(50, -25, 25));
    scn_r2 = ajouter_relation(scn_voiture, sphere_amiga(20, 6, 8));
    translationScene3d(scn_r2, definirVecteur3d(50, -25, -25));
    scn_r3 = ajouter_relation(scn_voiture, sphere(20, 6, 8));
    translationScene3d(scn_r3, definirVecteur3d(-50, -25, 25));
    scn_r4 = ajouter_relation(scn_voiture, sphere(20, 6, 8));
    translationScene3d(scn_r4, definirVecteur3d(-50, -25, -25));

    scn_arb = ajouter_relation(scn_sol, arbre(30, 150, 30)); // l'arbre repose sur le sol
    translationScene3d(scn_arb,
                       definirVecteur3d(500, 75, 0)); //75 car il est centre sur le sol et on le veut pose dessus
//    printf("%d faces\n", nb_faces);

    //rotationScene3d(scn_cam2, origine, 0, 30, 0);
    //translationScene3d(scn_cam2, definirVecteur3d(0,200,0));

    changerCamera(cams[0]);
    scene = cams[0];


    surface = creerFenetre(RX, RY);
    timestart = SDL_GetTicks();
//    oldtime = timestart;

    while (/*++i < DUREE * 60 && */!quit) // DUREE " * 60FPS
    {
        effacerFenetre(surface, 0);

        //Update events state
        UpdateEvents(&in);
        //handle events change
        handle_events(in);

        if (!is_pause) {
            ++i;
            rotationScene3d(scn_r1, origine, 0, 0, sens * 5);
            rotationScene3d(scn_r2, origine, 0, 0, sens * 5);
            rotationScene3d(scn_r3, origine, 0, 0, sens * 5);
            rotationScene3d(scn_r4, origine, 0, 0, sens * 5);

            if (i % (3 * 60) == 0) sens = -sens;
            if (sens > 0) translationScene3d(scn_voiture, vi);
            else translationScene3d(scn_voiture, v);
        }
        dessinerScene3d(surface, scene);

        majEcran(surface);
        /* Framerate fixe a env 120 FPS max */
//        SDL_Delay(MAX(0, (1000. / 120.) - (SDL_GetTicks() - oldtime)));
        oldtime = SDL_GetTicks();

        cpt++;
        sprintf(buf, "%d FPS", (int) (cpt * 1000.0 / (oldtime - timestart)));
        SDL_WM_SetCaption(buf, NULL);
    }
    SDL_Quit();

    usage_lib_3d();
    usage_lib_objet_3d();
    usage_lib_scene_3d();

    return 0;
}
