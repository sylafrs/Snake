#include "../include/overall.h"
#include <stdlib.h>

void creerSurfaces(surfaces * tabS, TTF_Font ** police)
{
    SDL_Surface *fond, *mur, *ecran, *texte;
    SDL_Rect pos;
    SDL_Color color;
    int i;

    // On cree la surface de fond..
    if((fond = SDL_CreateRGBSurface(SDL_HWSURFACE, ECRAN_WIDTH, ECRAN_HEIGHT, ECRAN_BPP, 0, 0, 0, 0)) == NULL)
    {
        erreur("fond n'a pu etre cree");
    }

    // On ajoute toutes les surfaces à la map
    if(!ajoutSurface(tabS, "fond"       , fond                         ) ||
       !ajoutSurface(tabS, "mur"        , SDL_LoadBMP(IMG_MUR         )) ||
       !ajoutSurface(tabS, "teteDroite" , SDL_LoadBMP(IMG_TETE_DROITE )) ||
       !ajoutSurface(tabS, "teteGauche" , SDL_LoadBMP(IMG_TETE_GAUCHE )) ||
       !ajoutSurface(tabS, "teteHaut"   , SDL_LoadBMP(IMG_TETE_HAUT   )) ||
       !ajoutSurface(tabS, "teteBas"    , SDL_LoadBMP(IMG_TETE_BAS    )) ||
       !ajoutSurface(tabS, "corps"      , SDL_LoadBMP(IMG_CORPS       )) ||
       !ajoutSurface(tabS, "virageHD"   , SDL_LoadBMP(IMG_VIRAGE_HD   )) ||
       !ajoutSurface(tabS, "virageHG"   , SDL_LoadBMP(IMG_VIRAGE_HG   )) ||
       !ajoutSurface(tabS, "virageBG"   , SDL_LoadBMP(IMG_VIRAGE_BG   )) ||
       !ajoutSurface(tabS, "virageBD"   , SDL_LoadBMP(IMG_VIRAGE_BD   )) ||
       !ajoutSurface(tabS, "queueDroite", SDL_LoadBMP(IMG_QUEUE_DROITE)) ||
       !ajoutSurface(tabS, "queueGauche", SDL_LoadBMP(IMG_QUEUE_GAUCHE)) ||
       !ajoutSurface(tabS, "queueHaut"  , SDL_LoadBMP(IMG_QUEUE_HAUT  )) ||
       !ajoutSurface(tabS, "queueBas"   , SDL_LoadBMP(IMG_QUEUE_BAS   )) ||
       !ajoutSurface(tabS, "pomme"      , SDL_LoadBMP(IMG_POMME       )) ||
       !ajoutSurface(tabS, "titre"      , SDL_LoadBMP(IMG_TITRE       )) ||
       !ajoutSurface(tabS, "vie"        , SDL_LoadBMP(IMG_VIES        ))   )
    {
        erreur("une surface n'a pu etre chargee");
    }

    // On va creer le fond..
    ecran = utiliseSurface(tabS, "ecran");
    mur   = utiliseSurface(tabS, "mur"  );

    // Tout d'abord : on le met en vert
    SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, COLOR_FOND_R, COLOR_FOND_G, COLOR_FOND_B));

    // Puis on met le titre
    pos.x = POS_TITRE_X;
    pos.y = POS_TITRE_Y;
    coller(tabS, "titre", NULL, "fond", &pos);

    // La police du jeu..
    *police = TTF_OpenFont(POLICE, TAILLE_POLICE);
    if(*police == NULL)
        erreur("police non chargée");

    // Le texte (score)
    color.r = COLOR_SCORE_R;
    color.g = COLOR_SCORE_G;
    color.b = COLOR_SCORE_B;
    texte = TTF_RenderText_Solid(*police, TEXTE_SCORE, color);

    pos.x = POS_SCORE_TXT_X;
    pos.y = POS_SCORE_TXT_Y;
    SDL_BlitSurface(texte, NULL, fond, &pos);
    SDL_FreeSurface(texte);

    // Le texte (vies)
    color.r = COLOR_VIES_R;
    color.g = COLOR_VIES_G;
    color.b = COLOR_VIES_B;
    texte = TTF_RenderText_Solid(*police, TEXTE_VIES, color);

    pos.x = POS_VIES_TXT_X;
    pos.y = POS_VIES_TXT_Y;
    SDL_BlitSurface(texte, NULL, fond, &pos);
    SDL_FreeSurface(texte);

    for(i = 0; i < ZDG_CASES_W; i++)
    {
        pos.x = (CASE_WIDTH+1)*(i+1);
        pos.y = CASE_WIDTH+1;
        SDL_BlitSurface(mur, NULL, fond, &pos);
    }

    for(i = 1; i < ZDG_CASES_H-1; i++)
    {
        pos.x = CASE_WIDTH+1;
        pos.y = (CASE_WIDTH+1)*(i+1);
        SDL_BlitSurface(mur, NULL, fond, &pos);

        pos.x = (CASE_WIDTH+1)*(ZDG_CASES_W);
     // pos.y = (CASE_WIDTH+1)*(i+1)
        SDL_BlitSurface(mur, NULL, fond, &pos);
    }

    for(i = 0; i < ZDG_CASES_W; i++)
    {
        pos.x = (CASE_WIDTH+1)*(i+1);
        pos.y = (CASE_WIDTH+1)*(ZDG_CASES_H);
        SDL_BlitSurface(mur, NULL, fond, &pos);
    }

    SDL_BlitSurface(fond, NULL, ecran, NULL);
}

void dessinerSerpent(surfaces * tabS, Snake * serpent, TTF_Font * police)
{
    int i;
    char score[MAX_SCORE];
    char vitesse[MAX_VIT];
    char vittxt[MAX_VIT];
    SDL_Surface * texte;
    SDL_Color color;
    SDL_Rect pos;

    /* Verifications */
    if(serpent->queue == NULL || serpent->tete == NULL)
        erreur("une histoire sans queue ni tete");


    /* La pomme */
    pos.x = (serpent->pomme.x + 1) * (CASE_WIDTH + 1);
    pos.y = (serpent->pomme.y + 1) * (CASE_WIDTH + 1);
    coller(tabS, "pomme", NULL, "ecran", &pos);

    /* Les vies */
    pos.x = POS_VIES_X;
    pos.y = POS_VIES_Y;
    for(i = 0; i < serpent->vies; i++)
    {
        coller(tabS, "vie", NULL, "ecran", &pos);
        pos.x += (CASE_WIDTH + 1);
    }

    /* Le score */
    color.r = COLOR_SCORE_R;
    color.g = COLOR_SCORE_G;
    color.b = COLOR_SCORE_B;
    sprintf(score, "%d", serpent->score.points);
    texte = TTF_RenderText_Solid(police, score, color);

    pos.x = POS_SCORE_X;
    pos.y = POS_SCORE_Y;
    SDL_BlitSurface(texte, NULL, utiliseSurface(tabS, "ecran"), &pos);
    SDL_FreeSurface(texte);

    /* La vitesse */
    color.r = COLOR_VIT_R;
    color.g = COLOR_VIT_G;
    color.b = COLOR_VIT_B;

    sprintf(vitesse, "%f", serpent->vitesse);
    troncStrFloat(vitesse, FLOAT_VIT);
    sprintf(vittxt, TEXTE_VIT, vitesse);

    texte = TTF_RenderText_Solid(police, vittxt, color);
    pos.x = POS_VIT_X;
    pos.y = POS_VIT_Y;
    SDL_BlitSurface(texte, NULL, utiliseSurface(tabS, "ecran"), &pos);
    SDL_FreeSurface(texte);


    /* La queue */
    if(serpent->queue != serpent->tete)
    {
        pos.x = (serpent->queue->x + 1) * (CASE_WIDTH + 1);
        pos.y = (serpent->queue->y + 1) * (CASE_WIDTH + 1);
        switch(serpent->queue->dir)
        {
            case haut:
                coller(tabS, "queueHaut", NULL, "ecran", &pos);
            break;
            case bas:
                coller(tabS, "queueBas", NULL, "ecran", &pos);
            break;
            case gauche:
                coller(tabS, "queueGauche", NULL, "ecran", &pos);
            break;
            case inconnue:
                printf("Attention : direction inconnue dans la queue !\n");
            case droite:
                coller(tabS, "queueDroite", NULL, "ecran", &pos);
            break;
        }
    }

    Corps * corps = serpent->queue;
    char str[] = "virageXX";
    while(corps->suivant != serpent->tete)
    {
        corps = corps->suivant;

        pos.x = (corps->x + 1) * (CASE_WIDTH + 1);
        pos.y = (corps->y + 1) * (CASE_WIDTH + 1);

        if(corps->precedent->dir == corps->dir)
        {
            coller(tabS, "corps", NULL, "ecran", &pos);
        }
        else
        {
            strcpy(str, "virage");
            if(corps->precedent->dir == bas || corps->dir == haut)
            {
                strcat(str, "H");
            }
            else
            {
                strcat(str, "B");
            }

            if(corps->precedent->dir == gauche || corps->dir == droite)
            {
                strcat(str, "D");
            }
            else
            {
                strcat(str, "G");
            }

            coller(tabS, str, NULL, "ecran", &pos);
        }
    }

    pos.x = (serpent->tete->x + 1) * (CASE_WIDTH + 1);
    pos.y = (serpent->tete->y + 1) * (CASE_WIDTH + 1);

    switch(serpent->tete->dir)
    {
        case haut:
            coller(tabS, "teteHaut", NULL, "ecran", &pos);
        break;
        case bas:
            coller(tabS, "teteBas", NULL, "ecran", &pos);
        break;
        case gauche:
            coller(tabS, "teteGauche", NULL, "ecran", &pos);
        break;
        case inconnue:
            printf("Attention : direction de la tete du serpent inconnue !\n");
        case droite:
            coller(tabS, "teteDroite", NULL, "ecran", &pos);
        break;
    }
}

