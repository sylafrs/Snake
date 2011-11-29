#ifndef SURFACES_H_INCLUDED
#define SURFACES_H_INCLUDED

    #include "overall.h"

    typedef struct mapSurf {
        SDL_Surface* surf;
        char nom[20];
    } mapSurf ;

    typedef struct surfaces {
        mapSurf** surfs;
        int nbSurfs;
    } surfaces ;

    bool ajoutSurface(surfaces * tabS, const char* str, SDL_Surface* surf);

    SDL_Surface* utiliseSurface(surfaces * tabS, const char* str);

    bool supprSurface(surfaces * tabS, const char* str, bool liberer);

    void viderTabS(surfaces * tabS, bool liberer);

    bool coller(surfaces * tabS,
                const char* str1, SDL_Rect* a,
                const char* str2, SDL_Rect* b);

    bool initSDL(surfaces * tabS, int w, int h, int bpp, bool fullscreen);
    void cleanSDL(TTF_Font * police, surfaces * tabS);

#endif // SURFACES_H_INCLUDED
