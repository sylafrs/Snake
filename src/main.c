#include "../include/overall.h"

/*
    Idées :
        -> faire un score.
        -> faire un compteur de cases parcouru depuis la derniere pomme.
        -> un petit nombre de cases augmentera le score.
*/

int main(int argc, char* argv[])
{
    surfaces tabSurfaces;       // Map {char* , Surface*}
    SDL_Surface *ecran, *fond;  // Surfaces SDL
    int temps = 0;              // Un peut chrono
    bool perdu = false;         // Booléen : si l'on a perdu
    TTF_Font * police;

    Events event;               // Structure d'evenements
    Snake snake;                // Structure du jeu.

    // Initialise la SDL (video), et la fenetre principale (ecran)
    if(!initSDL(&tabSurfaces, ECRAN_WIDTH, ECRAN_HEIGHT, ECRAN_BPP, FULLSCREEN))
    {
        fprintf(stderr, "Erreur : initSDL echoue\n");
        return 1;
    }

    // Change le titre de la fenetre
    SDL_WM_SetCaption("Sylafrs' Snake", NULL);

    // On charge toutes les surfaces
    creerSurfaces(&tabSurfaces, &police);
    ecran = utiliseSurface(&tabSurfaces, "ecran"); // On utilisera souvent l'ecran..
    fond  = utiliseSurface(&tabSurfaces, "fond");  // ..et le fond.

    // Rafraichit l'ecran
    SDL_Flip(ecran);

    initEvent(&event);      // Initialise event.
    initSerpent(&snake);    // Initialise snake

    // Tant que l'on ne veut pas quitter et que l'on a pas perdu
    while(!event.quitter && !event.clavier[SDLK_ESCAPE] && !perdu)
    {
        // Evenements
        refresh(&event, 30);            // Met à jour la structure
        evenements(&event, &snake);     // Gere les evenements

        // On entre ici tout les "1000/serpent.vitesse" millisecondes
        if(SDL_GetTicks() >= temps + 1000/snake.vitesse)
        {
            // On avance
            avancer(&snake);

            // Et on met à jour l'ecran
            dessinerSerpent(&tabSurfaces, &snake, police);
            SDL_Flip(ecran);
            SDL_BlitSurface(fond, NULL, ecran, NULL);

            temps = SDL_GetTicks();

            // Si on s'est mordu ou si on s'est pris le mur..
            if(mordre(&snake))
            {
                SDL_Delay(1000); // Pause
                snake.vies--;  // On perd une vie
                perdu = (snake.vies <= 0); // perdu si on est mort..

                // Si on est pas mort
                if(!perdu)
                {
                    // On recommence une partie
                    nouvellePartie(&snake);

                    // On redessine tout ça..
                    dessinerSerpent(&tabSurfaces, &snake, police);
                    SDL_Flip(ecran);
                    SDL_BlitSurface(fond, NULL, ecran, NULL);

                    // On fait une pitite pause
                    SDL_Delay(1000);
                }
            }

            // Si on mange une pomme
            if(manger(&snake))
            {
                // On grandit !
                grandir(&snake);

                snake.score.points++;
            }
        }
    }

    cleanSerpent(&snake);           // Nettoie la structure du serpent
    cleanSDL(police, &tabSurfaces); // Nettoie la SDL, la fenetre, les surfaces, etc..
    return 0;                       // On peut quitter en toute tranquillité
}
