#include "bsq.h"

void freetab(char **tab) {
    for (int i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

void print_tab(data_t *d) {
    if (d->bsqsize) {
        for (int i = d->bsqX; i < d->bsqsize + d->bsqX; i++)
            for (int j = d->bsqY; j < d->bsqsize + d->bsqY; j++)
                d->map[i][j] = d->full;
    }
    for (int i = 0; d->map[i]; i++)
        fprintf(stdout, "%s\n", d->map[i]);
}

void replace_if(data_t *d, int x, int y, int i) {
    if (i > d->bsqsize) {
        d->bsqsize = i;
        d->bsqX = x - i;
        d->bsqY = y - i;
    }
}

void max_square(data_t *d, int x, int y, int i) {
    if (x == d->nbline || y == d->lenline || d->map[x][y] == d->obstacle)
        return (replace_if(d, x, y, i));
    for (int j = i; j > 0; j--)
        if (d->map[x - j][y] == d->obstacle || d->map[x][y - j] == d->obstacle)
            return (replace_if(d, x, y, i));
    max_square(d, x + 1, y + 1, i + 1);
}

void bsq(data_t *d) {
    d->bsqsize = 0;
    for (int i = 0; i < d->nbline; i++)
        for (int j = 0; j < d->lenline; j++)
                max_square(d, i, j, 0);
    print_tab(d);
    freetab(d->map);
}

bool fill_map(data_t *d, FILE *f) {
    d->map = calloc(d->nbline + 1, sizeof(char *));
    for (int i = 0, len; i < d->nbline; i++) {
        size_t buff = 0;
        len = getline(&d->map[i], &buff, f);
        if (i == 0) 
            d->lenline = len - 1;
        if (len <= 0 || len - 1 != d->lenline || d->map[i][len - 1] != '\n')
            return false;
        d->map[i][len - 1] = '\0';
        for (int j = 0; d->map[i][j]; j++)
            if (d->map[i][j] != d->empty && d->map[i][j] != d->obstacle)
                return false;
    }
    fclose(f);
    return true;
} 

void set_data(char *av) {
    FILE *f = av ? fopen(av, "r") : stdin;
    if (f) {
        data_t d;
        if (fscanf(f, "%d %c %c %c\n", &d.nbline, &d.empty, &d.obstacle, &d.full) == 4 
            && d.nbline && d.empty != d.obstacle && d.obstacle != d.full && d.empty != d.full) {
                if (fill_map(&d, f))
                    return (bsq(&d));
                freetab(d.map);
        }
        fclose(f);
        fprintf(stdout, "Error: invald map\n");
    }
    else
        fprintf(stdout, "Error: can't open file\n");
}

int main(int ac, char **av) {
    if (ac == 1)
        set_data(NULL);
    else
        set_data(av[1]);
}