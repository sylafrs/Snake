#include "../include/overall.h"

void troncStrFloat(char * str, int n)
{
    // La position actuelle et celle du point...
    int pos, pt;

    // On va jusqu'au point
    for(pos = 0; str[pos] != '\0' && str[pos] != '.'; pos++);

    // On va jusqu'a la position à tronquer
    for(pt = pos + 1; str[pos] != '\0' && pos-pt < n; pos++);

    // On tronque.
    if(str[pos] != '\0')
        str[pos] = '\0';

}

void erreur(const char * str)
{
    fprintf(stderr, "Erreur : %s\n", str);
    exit(1);
}

