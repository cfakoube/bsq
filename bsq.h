#ifndef BSQ_H
# define BSQ_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct data_s {
    char **map;

    int nbline;
    int lenline;

    int bsqsize;
    int bsqX;
    int bsqY;

    char empty;
    char obstacle;
    char full;
}   data_t;

#endif