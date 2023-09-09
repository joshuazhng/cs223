#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pirate.h"

struct pirate {
    char* name;
};

pirate *make_pirate(char *name) {
    pirate *new_pirate = malloc(sizeof(pirate));
    new_pirate->name = malloc(strlen(name) + 1);
    strcpy(new_pirate->name, name);
    return new_pirate;
}

void destroy_pirate(pirate *p) {
    free(p->name);
    free(p);
}

char *get_name(pirate *p) {
    return p->name;
}


