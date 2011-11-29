#include "../include/overall.h"

void initEvent(Events * event)
{
    int i;

    /* --- Events --- */
    event->quitter = false;

    for(i = 0; i < SDLK_LAST; i++)
    {
        event->clavier[i] = false;
    }

    /* --- Souris --- */
    SDL_GetMouseState(&(event->souris.x),
                      &(event->souris.y));

    event->souris.droite    =
    event->souris.gauche    =
    event->souris.milieu    =
    event->souris.x1        =
    event->souris.x2        =
    event->souris.wheelup   =
    event->souris.wheeldown = false;
}

void pause(int delay)
{
    int now = SDL_GetTicks();
    static int nextTime = 0;

    if(nextTime == 0)
        nextTime = now;

    if(nextTime > now)
    {
        SDL_Delay(nextTime - now);
    }

    nextTime = now + delay;
}

void refresh(Events * event, int delay)
{
    static SDL_Event eventSDL;

    pause(delay);

    // event.quitter = false;
    event->souris.wheelup = false;
    event->souris.wheeldown = false;

    while(SDL_PollEvent(&eventSDL))
    {
        switch(eventSDL.type)
        {
            /* --- Events --- */

            case SDL_QUIT:
                event->quitter = true;
            break;
            case SDL_KEYDOWN:
                event->clavier[eventSDL.key.keysym.sym] = true;
            break;
            case SDL_KEYUP:
                event->clavier[eventSDL.key.keysym.sym] = false;
            break;

            /* --- Souris --- */

            case SDL_MOUSEMOTION:
                event->souris.x = eventSDL.motion.x;
                event->souris.y = eventSDL.motion.y;
            break;

            case SDL_MOUSEBUTTONDOWN:
                switch(eventSDL.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        event->souris.gauche = true;
                    break;
                    case SDL_BUTTON_RIGHT:
                        event->souris.droite = true;
                    break;
                    case SDL_BUTTON_MIDDLE:
                        event->souris.milieu = true;
                    break;
                    case SDL_BUTTON_X1:
                        event->souris.x1 = true;
                    break;
                    case SDL_BUTTON_X2:
                        event->souris.x2 = true;
                    break;
                    case SDL_BUTTON_WHEELUP:
                        event->souris.wheelup = true;
                    break;
                    case SDL_BUTTON_WHEELDOWN:
                        event->souris.wheeldown = true;
                    break;
                    default:
                    break;
                }
            break;

            case SDL_MOUSEBUTTONUP:
                switch(eventSDL.button.button)
                {
                    case SDL_BUTTON_LEFT:
                        event->souris.gauche = false;
                    break;
                    case SDL_BUTTON_RIGHT:
                        event->souris.droite = false;
                    break;
                    case SDL_BUTTON_MIDDLE:
                        event->souris.milieu = false;
                    break;
                    case SDL_BUTTON_X1:
                        event->souris.x1 = false;
                    break;
                    case SDL_BUTTON_X2:
                        event->souris.x2 = false;
                    break;
                    default:
                    break;
                }
            break;

            /* --- reste --- */

            default:
            break;
        }
    }
}
