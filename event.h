#ifndef PROJETMOTEUR3D_EVENT_H
#define PROJETMOTEUR3D_EVENT_H

#include "lib_objet3d.h"

//Events

typedef struct {
    char key[SDLK_LAST];
    int mousex, mousey;
    int mousexp, mouseyp;
    t_bool mouse_motion;
    char mousebuttons[8];
    t_bool quit;
} Input;

void UpdateEvents(Input *in);

#endif //PROJETMOTEUR3D_EVENT_H
