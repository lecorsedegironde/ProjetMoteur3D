#ifndef PROJETMOTEUR3D_EVENT_H
#define PROJETMOTEUR3D_EVENT_H

#include "lib_objet3d.h"

//Events
t_bool isMouseDown;

typedef struct {
    char key[SDLK_LAST];
    int mousex, mousey;
    int mousexdown, mouseydown;
    char mousebuttons[8];
    t_bool quit;
} Input;

void UpdateEvents(Input *in);

#endif //PROJETMOTEUR3D_EVENT_H
