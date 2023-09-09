#ifndef __PIRATE_H__
#define __PIRATE_H__

// Type of a pirate.
typedef struct pirate pirate;

// Make a pirate given a name
pirate *make_pirate(char *name);

// Destroy a pirate given a name
void destroy_pirate(pirate *p);

// Get name of pirate
char *get_name(pirate *p);

#endif
