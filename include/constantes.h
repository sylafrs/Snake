#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

    #define ECRAN_WIDTH    800//1024
    #define ECRAN_HEIGHT   260//600
    #define ECRAN_BPP      32
    #define FULLSCREEN     false

    #define COLOR_FOND_R   0
    #define COLOR_FOND_G   255
    #define COLOR_FOND_B   128

    #define IMG_TITRE        "../img/titre.bmp"
    #define IMG_MUR          "../img/mur.bmp"
    #define IMG_POMME        "../img/pomme.bmp"
    #define IMG_VIES         IMG_POMME
    #define IMG_TETE_DROITE  "../img/teteDroite.bmp"
    #define IMG_TETE_GAUCHE  "../img/teteGauche.bmp"
    #define IMG_TETE_BAS     "../img/teteBas.bmp"
    #define IMG_TETE_HAUT    "../img/teteHaut.bmp"
    #define IMG_CORPS        "../img/corps.bmp"
    #define IMG_VIRAGE_HD    "../img/virHD.bmp"
    #define IMG_VIRAGE_HG    "../img/virHG.bmp"
    #define IMG_VIRAGE_BD    "../img/virBD.bmp"
    #define IMG_VIRAGE_BG    "../img/virBG.bmp"
    #define IMG_QUEUE_DROITE "../img/queueDroite.bmp"
    #define IMG_QUEUE_GAUCHE "../img/queueGauche.bmp"
    #define IMG_QUEUE_BAS    "../img/queueBas.bmp"
    #define IMG_QUEUE_HAUT   "../img/queueHaut.bmp"

    #define ZDG_CASES_H      20
    #define ZDG_CASES_W      40
    #define CASE_WIDTH       11

    #define POS_TITRE_X      (((ZDG_CASES_W + 2) * CASE_WIDTH) + ECRAN_WIDTH - 135)/2
    #define POS_TITRE_Y      1 * CASE_WIDTH

    #define POS_VIES_X       (((ZDG_CASES_W - 1) * CASE_WIDTH) + ECRAN_WIDTH + 55)/2
    #define POS_VIES_Y       200 + CASE_WIDTH
    #define POS_VIES_TXT_X   (((ZDG_CASES_W - 1) * CASE_WIDTH) + ECRAN_WIDTH - 53)/2
    #define POS_VIES_TXT_Y   200
    #define COLOR_VIES_R     0
    #define COLOR_VIES_G     0
    #define COLOR_VIES_B     0
    #define TEXTE_VIES       "Vies :"

    // #define MODE_DEUX_TOUCHES // A definir pour activer.
    #define SERPENT_DEBUT_TETE_X    4
    #define SERPENT_DEBUT_TETE_Y    1
    #define SERPENT_DEBUT_DIR       droite
    #define SERPENT_DEBUT_TAILLE    3
    #define SERPENT_DEBUT_VITESSE   3 // cases par secondes
    #define SERPENT_DEBUT_VIES      3

    // Macro pour augmenter la vitesse.
    #include <math.h>
    #define SERPENT_AUG_VIT(vitesse) (vitesse + 1.0/sqrt(vitesse))

    #define POLICE            "../fonts/comic.ttf"
    #define TAILLE_POLICE     18

    #define TEXTE_SCORE       "Points"
    #define COLOR_SCORE_R     0
    #define COLOR_SCORE_G     0
    #define COLOR_SCORE_B     0
    #define POS_SCORE_TXT_X   (((ZDG_CASES_W + 2) * CASE_WIDTH) + ECRAN_WIDTH - texte->w)/2
    #define POS_SCORE_TXT_Y   100
    #define POS_SCORE_X       (((ZDG_CASES_W + 2) * CASE_WIDTH) + ECRAN_WIDTH - texte->w)/2
    #define POS_SCORE_Y       120
    #define MAX_SCORE         10

    #define TEXTE_VIT         "Vitesse : %s case/seconde"
    #define FLOAT_VIT         2
    #define COLOR_VIT_R       0
    #define COLOR_VIT_G       0
    #define COLOR_VIT_B       0
    #define POS_VIT_X         (((ZDG_CASES_W + 2) * CASE_WIDTH) + ECRAN_WIDTH - texte->w)/2
    #define POS_VIT_Y         150
    #define MAX_VIT           42

#endif // CONSTANTES_H_INCLUDED
