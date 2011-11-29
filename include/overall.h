#ifndef OVERALL_H_INCLUDED
#define OVERALL_H_INCLUDED

    typedef enum bool {
        true=1,false=0
    } bool ;

    void troncStrFloat(char * str, int n);
    void erreur(const char * str);

    #include "SDL/SDL.h"
    #include "SDL/SDL_ttf.h"

    #include "events.h"
    #include "surfaces.h"
    #include "snake.h"
    #include "graphique.h"

    #include "constantes.h"

#endif // OVERALL_H_INCLUDED
