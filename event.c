#include "event.h"

void UpdateEvents(Input *in) {
    //Declare SDL_Event
    SDL_Event event;

    //Prevent bad reading of wheel movement
    in->mousebuttons[SDL_BUTTON_WHEELUP] = 0;
    in->mousebuttons[SDL_BUTTON_WHEELDOWN] = 0;

    //Mouse motion may have stopped
    in->mouse_motion = false;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            //Key pressed updated in tab
            case SDL_KEYDOWN:
                in->key[event.key.keysym.sym] = 1;
                break;

                //Key released updated
            case SDL_KEYUP:
                in->key[event.key.keysym.sym] = 0;
                break;

                //Move mouse
            case SDL_MOUSEMOTION:
                in->mousexp = in->mousex;
                in->mouseyp = in->mousey;
                in->mousex = event.motion.x;
                in->mousey = event.motion.y;
                in->mouse_motion = true;
                break;

                //On click
            case SDL_MOUSEBUTTONDOWN:
                in->mousebuttons[event.button.button] = 1;
                break;

                //On click release
            case SDL_MOUSEBUTTONUP:
                if (event.button.button != SDL_BUTTON_WHEELUP && event.button.button != SDL_BUTTON_WHEELDOWN)
                    in->mousebuttons[event.button.button] = 0;
                break;

                //On quit
            case SDL_QUIT:
                in->quit = true;
                break;

            default:
                break;
        }
    }
}
