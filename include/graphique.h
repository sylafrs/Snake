#ifndef GRAPHIQUE_H_INCLUDED
#define GRAPHIQUE_H_INCLUDED

    #include "overall.h"

    /**
      * @brief alloue toutes les surfaces, polices
      * @param tabS
      *     (resultat) Map de surfaces
      * @param police
      *     (resultat) adresse du pointeur de TTF_Font à allouer
      */
    void creerSurfaces(surfaces * tabS, TTF_Font ** police);

    /**
      * @brief Dessine le serpent, grace à sa structure, avec les surfaces données et la police
      * @param tabS
      *    (donnee) Map de surfaces
      * @param snake
      *    (donnee) le serpent
      * @param police
      *    (donnee) La police à utiliser
      */
    void dessinerSerpent(surfaces * tabS, Snake * snake, TTF_Font * police);

#endif // GRAPHIQUE_H_INCLUDED
