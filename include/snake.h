#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

    #include "overall.h"

    /**
      * @enum Direction
      * @brief Code une direction
      */
    typedef enum Direction {
        inconnue = 0, ///< La direction est temporairement inconnue
        droite = 1,   ///< Vers la droite
        haut = 2,     ///< Vers le haut
        gauche = 3,   ///< Vers la gauche
        bas = 4       ///< Vers le bas
    } Direction ;

    /**
      * @struct Corps
      * @brief Une partie du corps du serpent
      */
    typedef struct Corps {
        Direction dir;              ///< Direction après
        int x;                      ///< Abscisse de la partie du corps
        int y;                      ///< Ordonnée de la partie du corps
        struct Corps * suivant;     ///< Pointeur vers la prochaine case
        struct Corps * precedent;   ///< Pointeur vers la case suivante
    } Corps ;

    /**
      * @struct Pomme
      * @brief Structure representant une pomme
      */
    typedef struct Pomme {
        int x;          ///< Position (x) de la pomme
        int y;          ///< Position (y) de la pomme
        int apparition; ///< Temps passé jusqu'à son apparition
    } Pomme ;

    /**
      * @struct Score
      * @brief Structure contenant les infos d'une partie
      */
    typedef struct Score {
        int pommes; ///< Nombre de pommes mangées
        int temps;  ///< Combien de temps resté en vie
        int points; ///< Nombre de points gagnés
        int taille; ///< La taille du serpent
        int cases;  ///< Nombre de cases parcourues
    } Score ;

    /**
      * @struct Snake
      * @brief Structure contenant des infos quand au serpent et une liste doublement chainee pour le corps
      */
    typedef struct Snake {
        Corps * tete;  ///< Pointeur vers la tete
        Corps * queue; ///< Pointeur vers la queue
        float vitesse; ///< Vitesse du serpent (case/seconde)
        int vies;      ///< Nombre de vies restantes
        Pomme pomme;   ///< Endroit où se trouve la pomme
        Score score;   ///< Le score de la partie en cours
    } Snake ;

    /* Fonctions */
    void initSerpent(Snake*);          ///< Valeurs initiale d'une partie
    void cleanSerpent(Snake*);         ///< Libere les cases
    void nouvellePartie(Snake*);       ///< Commence une nouvelle partie
    void nouvellePomme(Snake*);        ///< Teleporte la pomme
    void avancer(Snake*);              ///< Avance d'une case
    void tourner(Snake*, Direction);   ///< Pour tourner
    bool mordre(Snake*);               ///< S'est-on mordu, ou un mur ?
    bool manger(Snake*);               ///< As t-on mange une pomme
    void grandir(Snake*);              ///< Ajoute une case
    void evenements(Events *, Snake*); ///< Gere les evenements

#endif // SNAKE_H_INCLUDED
