#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED

    #include "overall.h"

    /**
      * @struct Souris
      * @brief Evenements de la souris
      */
    typedef struct Souris {
        int x;          ///< Position (x) de la souris
        int y;          ///< Position (y) de la souris
        bool droite;    ///< Clic sur le bouton droit
        bool gauche;    ///< Clic sur le bouton gauche
        bool milieu;    ///< Clic sur le bouton du milieu (molette)
        bool x1;        ///< Bouton x1 (???)
        bool x2;        ///< Bouton x2 (???)
        bool wheelup;   ///< Molette vers le haut
        bool wheeldown; ///< Molette vers le bas
    } Souris ;

    /**
      * @struct Events
      * @brief La structure des evenements
      */
    typedef struct Events {
        bool clavier[SDLK_LAST]; ///< Appui sur une touche
        Souris souris;           ///< Evenements de la souris
        bool quitter;            ///< Bouton Quitter (X)
    } Events ;

    /**
      * @brief Met la structure à zéro
      * @param event
      *     La structure des evenements
      */
    void initEvent(Events * event);

    /**
      * @brief Fait une pause
      * @param delay
      *     temps en milisecondes
      */
    void pause(int delay);

    /**
      * @brief Met à jour notre structure des evenements (en vidant la file des SDL_Event)
      * @param event
      *     La structure des evenements
      * @param delay
      *     Temps minimum entre deux refresh
      */
    void refresh(Events * event, int delay);

#endif // EVENTS_H_INCLUDED
