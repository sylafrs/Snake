#include "../include/overall.h"
#include <string.h>

bool ajoutSurface(surfaces * tabS, const char* str, SDL_Surface* surf)
{
    int i;
    mapSurf** temp;

    if(surf == NULL)
    {
        fprintf(stderr, "Erreur : la surface passee est NULL (%s)\n", str);
        return false;
    }

    if(tabS->nbSurfs > 0)
    {
        if(utiliseSurface(tabS, str) != NULL)
        {
            fprintf(stderr, "Erreur : nom deja utilise (%s)\n", str);
            return false;
        }

        temp = malloc((tabS->nbSurfs + 1)*sizeof(mapSurf*));
        if(temp == NULL)
        {
            fprintf(stderr, "(1) Erreur : allocation de la case pour la surface (%s)\n", str);
            return false;
        }

        for(i = 0; i < tabS->nbSurfs; i++)
        {
            temp[i] = tabS->surfs[i];
        }

        temp[i] = malloc(sizeof(mapSurf));
        if(temp[i] == NULL)
        {
            free(temp);
            fprintf(stderr, "(2) Erreur : allocation de la case pour la surface (%s)\n", str);
            return false;
        }

        temp[i]->surf = surf;
        strcpy(temp[i]->nom, str);

        free(tabS->surfs);
        tabS->surfs = temp;
        tabS->nbSurfs = tabS->nbSurfs + 1;

        return true;
    }

    tabS->surfs = malloc(sizeof(mapSurf*));
    if(tabS->surfs == NULL)
    {
        fprintf(stderr, "(3) Erreur : allocation de la case pour la surface (%s)\n", str);
        return false;
    }

    *(tabS->surfs) = malloc(sizeof(mapSurf));
    if(*(tabS->surfs) == NULL)
    {
        free(tabS->surfs);
        fprintf(stderr, "(4) Erreur : allocation de la case pour la surface (%s)\n", str);
        return false;
    }

    (**(tabS->surfs)).surf = surf;
    strcpy((**(tabS->surfs)).nom, str);

    tabS->nbSurfs = 1;

    return true;
}

SDL_Surface* utiliseSurface(surfaces * tabS, const char* str)
{
    if(tabS == NULL)
    {
        fprintf(stderr, "Erreur : Tableau NULL\n");
        fprintf(stderr, "utiliseSurface (%s)\n", str);
        exit(1);
    }

    int i = 0;
    while(i < tabS->nbSurfs)
    {
        if(strcmp(tabS->surfs[i]->nom, str) == 0)
        {
            return tabS->surfs[i]->surf;
        }
        i++;
    }
    return NULL;
}

bool supprSurface(surfaces * tabS, const char* str, bool liberer)
{
    mapSurf** temp;
    int i;
    bool trouve = false;

    if(tabS->nbSurfs <= 0)
    {
        return false;
    }

    if(utiliseSurface(tabS, str) == NULL)
    {
        fprintf(stderr, "Erreur : surface introuvable\n");
        return false;
    }

    if(tabS->nbSurfs == 1)
    {
        if(liberer)
        {
            SDL_FreeSurface((**(tabS->surfs)).surf);
        }
        free(*(tabS->surfs));
        free(tabS->surfs);
        tabS->nbSurfs--;

        return true;
    }

    temp = malloc(sizeof(mapSurf*)*(tabS->nbSurfs-1));

    i = 0;
    while(i < tabS->nbSurfs)
    {
        if(strcmp(tabS->surfs[i]->nom, str) != 0)
        {
            temp[i-trouve] = tabS->surfs[i];
        }
        else
        {
            trouve = true;
        }
        i++;
    }

    free(tabS->surfs);
    tabS->surfs = temp;
    tabS->nbSurfs = tabS->nbSurfs - 1;

    return true;
}

bool coller(surfaces * tabS, const char* str1, SDL_Rect* a, const char* str2, SDL_Rect* b)
{
    SDL_Surface* surf1 = utiliseSurface(tabS, str1);
    if(surf1 == NULL)
    {
        fprintf(stderr, "Erreur : %s introuvable", str1);
        return false;
    }

    SDL_Surface* surf2 = utiliseSurface(tabS, str2);
    if(surf1 == NULL)
    {
        fprintf(stderr, "Erreur : %s introuvable", str2);
        return false;
    }

    if(SDL_BlitSurface(surf1, a, surf2, b) != 0)
    {
        fprintf(stderr, "Erreur : surfaces trouvees mais collage impossible");
        return false;
    }
    return true;
}

void viderTabS(surfaces * tabS, bool liberer)
{
    int i;

    for(i = 0; i < tabS->nbSurfs; i++)
    {
        if(liberer)
        {
            SDL_FreeSurface(tabS->surfs[i]->surf);
        }
        free(tabS->surfs[i]);
    }
    free(tabS->surfs);
    tabS->nbSurfs = 0;
}

bool initSDL(surfaces * tabS, int w, int h, int bpp, bool fullscreen)
{
    SDL_Surface* ecran = NULL;

    tabS->nbSurfs = 0;

    if(SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur : initialisation de la SDL echouee\n");
        return false;
    }

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur : initialisation de SDL_ttf echouee (polices)\n");
        return false;
    }

    if(fullscreen)
        ecran = SDL_SetVideoMode(w, h, bpp, SDL_FULLSCREEN|SDL_HWSURFACE);
    else
        ecran = SDL_SetVideoMode(w, h, bpp, SDL_HWSURFACE);

    if(ecran == NULL)
    {
        cleanSDL(NULL, tabS);
        fprintf(stderr, "Erreur : initialisation de la fenetre echouee\n");
        return false;
    }

    if(!ajoutSurface(tabS, "ecran", ecran))
    {
        cleanSDL(NULL, tabS);
        return false;
    }

    return true;
}

void cleanSDL(TTF_Font * police, surfaces * tabS)
{
    supprSurface(tabS, "ecran", false);
    viderTabS(tabS, true);

    if(police != NULL)
        TTF_CloseFont(police);

    SDL_Quit();
    TTF_Quit();
}
