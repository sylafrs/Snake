#include "../include/overall.h"
#include <time.h>

void evenements(Events * event, Snake * serpent)
{
    #ifdef MODE_DEUX_TOUCHES
        Direction dir = serpent->tete->dir;
    #endif

    if(event->clavier[SDLK_p])
    {
        event->clavier[SDLK_p] = false;
        do
        {
            refresh(event, 30);
        }
        while(!event->clavier[SDLK_p] && !event->clavier[SDLK_ESCAPE] && !event->quitter);
        event->clavier[SDLK_p] = false;
    }

    #ifndef MODE_DEUX_TOUCHES
        if(event->clavier[SDLK_UP])
        {
            tourner(serpent, haut);
            event->clavier[SDLK_UP] = false;
        }
        else if(event->clavier[SDLK_DOWN])
        {
            tourner(serpent, bas);
            event->clavier[SDLK_DOWN] = false;
        }
        else
    #endif
    if(event->clavier[SDLK_LEFT])
    {
        #ifndef MODE_DEUX_TOUCHES
            tourner(serpent, gauche);
        #else
            dir++;
            if(dir > 4)
                dir = 1;

            tourner(serpent, dir);
        #endif
        event->clavier[SDLK_LEFT] = false;
    }
    else if(event->clavier[SDLK_RIGHT])
    {
        #ifndef MODE_DEUX_TOUCHES
            tourner(serpent, droite);
        #else
            dir--;
            if(dir < 1)
                dir = 4;

            tourner(serpent, dir);
        #endif

        event->clavier[SDLK_RIGHT] = false;
    }
}

void initSerpent(Snake * serpent)
{
    static bool debut = true;

    if(debut)
    {
        serpent->score.pommes = 0;
        serpent->score.temps = 0;
        serpent->score.points = 0;
        serpent->score.taille = 0;

        serpent->vies = SERPENT_DEBUT_VIES;
        debut = false;
    }

    serpent->vitesse = SERPENT_DEBUT_VITESSE;

    serpent->tete = malloc(sizeof(Corps));
    if(serpent->tete == NULL)
        erreur("impossible d'allouer la tete du serpent :o");

    serpent->tete->x = SERPENT_DEBUT_TETE_X;
    serpent->tete->y = SERPENT_DEBUT_TETE_Y;
    serpent->tete->dir = SERPENT_DEBUT_DIR;
    serpent->tete->suivant = NULL;

    int i;
    Corps * corps = serpent->tete;
    for(i = 0; i < SERPENT_DEBUT_TAILLE; i++)
    {
        corps->precedent = malloc(sizeof(Corps));
        if(corps->precedent == NULL)
            erreur("allocation d'une case Corps impossible");

        corps->precedent->suivant = corps;
        corps = corps->precedent;

        corps->dir = SERPENT_DEBUT_DIR;
        switch(SERPENT_DEBUT_DIR)
        {
            case haut:
                corps->y = corps->suivant->y + 1;
                corps->x = corps->suivant->x;
            break;
            case bas:
                corps->y = corps->suivant->y - 1;
                corps->x = corps->suivant->x;
            break;
            case inconnue:
                fprintf(stdout, "Attention : Direction inconnue dans initSerpent !\n");
            case droite:
                corps->x = corps->suivant->x - 1;
                corps->y = corps->suivant->y;
            break;
            case gauche:
                corps->x = corps->suivant->x + 1;
                corps->y = corps->suivant->y;
            break;
        }
    }

    corps->precedent = NULL;
    serpent->queue = corps;

    nouvellePomme(serpent);
}

void cleanSerpent(Snake * serpent)
{
    Corps * corps = serpent->queue;

    while(corps->suivant != NULL)
    {
        corps = corps->suivant;
        free(corps->precedent);
    }
}

void nouvellePartie(Snake * serpent)
{
    cleanSerpent(serpent);
    return initSerpent(serpent); // nouvellePomme(serpent);
}

void avancer(Snake * serpent)
{
    if(serpent->queue == NULL || serpent->tete == NULL)
        erreur("c'est une erreur sans queue ni tete\n");

    Corps * ancienneQueue = serpent->queue;

    if(serpent->queue != serpent->tete)
    {
        /* On met la queue à la prochaine place de la tete */
        serpent->queue = serpent->queue->suivant;

        serpent->tete->suivant = ancienneQueue;
        ancienneQueue->precedent = serpent->tete;

        serpent->tete = ancienneQueue;
        serpent->tete->suivant = NULL;

        serpent->tete->dir = serpent->tete->precedent->dir;
        serpent->tete->x   = serpent->tete->precedent->x; // modifié dans le
        serpent->tete->y   = serpent->tete->precedent->y; // switch plus bas
    }
    switch(serpent->tete->dir)
    {
        case haut:
            serpent->tete->y--;
        break;
        case bas:
            serpent->tete->y++;
        break;
        case inconnue:
            printf("Attention : direction inconnue !\n");
        case droite:
            serpent->tete->x++;
        break;
        case gauche:
            serpent->tete->x--;
        break;
    }
}

void tourner(Snake * serpent, Direction dir)
{
    if(serpent->tete == NULL)
        erreur("le serpent n'a plus de tete :O");

    Corps * avant = serpent->tete->precedent;
    bool possible;

    switch(dir)
    {
        case haut:
            possible = (serpent->tete->y - 1 != avant->y);
        break;
        case bas:
            possible = (serpent->tete->y + 1 != avant->y);
        break;
        case inconnue:
            printf("Attention : tourner, dir incoonue !");
        case droite:
            possible = (serpent->tete->x + 1 != avant->x);
        break;
        case gauche:
            possible = (serpent->tete->x - 1 != avant->x);
        break;
    }

    if(possible)
        serpent->tete->dir = dir;
}

bool mordre(Snake * serpent)
{
    Corps * corps;

    if(serpent->tete != NULL && serpent->queue != serpent->tete && serpent->queue != NULL)
    {
        corps = serpent->queue;
        while(corps->suivant != serpent->tete && corps->suivant != NULL)
        {
            if(corps->x == serpent->tete->x &&
               corps->y == serpent->tete->y   )
            {
                return true;
            }

            corps = corps->suivant;
        }
    }

    if(serpent->tete->x <= 0             ||
       serpent->tete->y <= 0             ||
       serpent->tete->x >= ZDG_CASES_W-1 ||
       serpent->tete->y >= ZDG_CASES_H-1    )
    {
        return true;
    }

    return false;
}

bool manger(Snake * serpent)
{
    if(serpent->tete->x == serpent->pomme.x && serpent->tete->y == serpent->pomme.y)
    {
        nouvellePomme(serpent);
        return true;
    }
    return false;
}

void nouvellePomme(Snake * serpent)
{
    static bool init = true;
    bool bonnePos = false;
    Corps * corps;

    if(init)
    {
        srand(time(NULL));
        init = false;
    }

    while(!bonnePos)
    {
        bonnePos = true;
        serpent->pomme.x = ((rand()/(double)RAND_MAX)*(ZDG_CASES_W-3)) + 1;
        serpent->pomme.y = ((rand()/(double)RAND_MAX)*(ZDG_CASES_H-3)) + 1;

        corps = serpent->queue;
        while(bonnePos && corps != NULL)
        {
            bonnePos = (corps->x != serpent->pomme.x || corps->y != serpent->pomme.y);
            corps = corps->suivant;
        }
    }

    serpent->pomme.apparition = SDL_GetTicks();
}

void grandir(Snake * serpent)
{
    serpent->vitesse = SERPENT_AUG_VIT(serpent->vitesse);

    serpent->queue->precedent = malloc(sizeof(Corps));
    if(serpent->queue->precedent == NULL)
        erreur("nouvelle case impossible");

    serpent->queue->precedent->suivant = serpent->queue;
    serpent->queue = serpent->queue->precedent;
    serpent->queue->precedent = NULL;
}
