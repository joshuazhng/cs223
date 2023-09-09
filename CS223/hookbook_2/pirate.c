#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pirate.h"

struct pirate {
    char* name;
    char* title;
    pirate* captain;
    char* vessel;
    int treasure;
    char* port;
    char** skills_list;
    size_t skills_count;
    size_t skills_capacity;
};

// Defining constants to use within the functions
int SKILLS_INITIAL_CAPACITY = 25;
int SKILLS_RESIZE_FACTOR = 2;
char* NONE = "(None)";

pirate *make_pirate(char *name) {
    pirate *new_pirate = malloc(sizeof(pirate));
    new_pirate->name = malloc(strlen(name) + 1);
    strcpy(new_pirate->name, name);
    new_pirate->title = NONE;
    new_pirate->captain = NULL;
    new_pirate->vessel = NONE;
    new_pirate->treasure = 0;
    new_pirate->port = NONE;
    new_pirate->skills_list = malloc(sizeof(char*) * SKILLS_INITIAL_CAPACITY);
    new_pirate->skills_count = 0;
    new_pirate->skills_capacity = SKILLS_INITIAL_CAPACITY;
    return new_pirate;
}

void destroy_pirate(pirate *p) {
    free(p->name);
    if (p->title != NONE) {
        free(p->title); 
    }
    if (p->vessel != NONE) {
        free(p->vessel);
    }
    if (p->port != NONE) {
        free(p->port);
    }
    for (int i = 0; i < p->skills_count; i++) {
        free(p->skills_list[i]);
    }
    free(p->skills_list);
    free(p);
}

char *get_name(pirate *p) {
    return p->name;
}

char *get_vessel(pirate *p) {
    return p->vessel;
}

int get_treasure(pirate *p) {
    return p->treasure;
}

void set_title(pirate *p, char *title) {
    p->title = malloc(strlen(title) + 1);
    strcpy(p->title, title);
}

void set_captain(pirate *p, pirate *c) {
    p->captain = c;
}

void set_vessel(pirate *p, char *vessel) {
    p->vessel = malloc(strlen(vessel) + 1);
    strcpy(p->vessel, vessel);
}

void set_treasure(pirate *p, int treasure) {
    p->treasure = treasure;
}

void set_port(pirate *p, char *port) {
    p->port = malloc(strlen(port) + 1);
    strcpy(p->port, port);
}

void set_skills(pirate *p, char *skill) {
    skills_expand_if_necessary(p);
    p->skills_list[p->skills_count] = malloc(strlen(skill) + 1);
    strcpy(p->skills_list[p->skills_count++], skill);
}

void print_pirate(pirate *p) {
    printf("Pirate: %s\n", p->name);
    printf("    Title: %s\n", p->title);
    if (p->captain == NULL) {
        printf("    Captain: (None)\n");
    }
    else {
        printf("    Captain: %s\n", p->captain->name);
        printf("        Captain's Title: %s\n", p->captain->title);
        printf("        Captain's Favorite Port of Call: %s\n", p->captain->port);
    }
    printf("    Vessel: %s\n", p->vessel);
    printf("    Treasure: %d\n", p->treasure);
    printf("    Favorite Port of Call: %s\n", p->port);
    print_skills(p);
}

void print_skills(pirate *p) {
    if (p->skills_count == 0) {
        printf("    Skills: (None)\n");
        return;
    }
    
    // Insertion sort algorithm to sort all the skills into increasing lexicographic order
    int j;
    char* skill;
    for (size_t i = 1; i < p->skills_count; i++) {
        j = i;
        while (j > 0 && (strcmp(p->skills_list[j-1], p->skills_list[j])) > 0) {
            skill = p->skills_list[j];
            p->skills_list[j] = p->skills_list[j-1];
            p->skills_list[j-1] = skill;
            j = j - 1;
        }
    }

    char* previous_skill = NULL;
    for (size_t i = 0; i < p->skills_count; i++) {
        if (previous_skill == NULL) {
            printf("    Skills: %s *", p->skills_list[i]);
        }
        else if (strcmp(previous_skill, p->skills_list[i]) == 0) {
            printf("*");
        }
        else {
            printf("\n            %s *", p->skills_list[i]);
        }
        previous_skill = p->skills_list[i];
    }
    printf("\n");
}

void skills_expand_if_necessary(pirate* p) {
    if (p->skills_count >= p->skills_capacity) {
        p->skills_capacity *= SKILLS_RESIZE_FACTOR;
        char **ptr = realloc(p->skills_list, sizeof(char*) * p->skills_capacity);
        if (ptr != NULL) {
            fprintf(stderr, "Expand to %zu\n", p->skills_capacity);
            p->skills_list = ptr;
        }
        else {
            p->skills_capacity /= SKILLS_RESIZE_FACTOR;
        }
    }
}

