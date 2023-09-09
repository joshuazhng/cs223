#ifndef __PIRATE_H__
#define __PIRATE_H__

// Type of a pirate.
typedef struct pirate pirate;

// Make a pirate given a name
pirate *make_pirate(char *name);

// Destroy a pirate given a pirate
void destroy_pirate(pirate *p);

// Get name of pirate
char *get_name(pirate *p);

// Get current vessel for the pirate
char *get_vessel(pirate *p);

// Get number of treasures the pirate has collected
int get_treasure(pirate *p);

// Set the title of a pirate given the title as a string
void set_title(pirate *p, char *title);

// Set the captain of a pirate given the captain as a pirate
void set_captain(pirate *p, pirate *c);

// Set the current vessel of a pirate given the name as a string
void set_vessel(pirate *p, char *vessel);

// Set the number of treasures of a pirate given the number as an integer
void set_treasure(pirate *p, int treasure);

// Set the favorite port of a pirate given the port as a string
void set_port(pirate *p, char *port);

// Add a skill to the pirate's profile
void set_skills(pirate *p, char *skill);

// Print the list of skills in accordance with the spec
void print_skills(pirate*p);

// Print a pirate by printing the fields in the appropriate order
void print_pirate(pirate *p);

/* Check if the actual number of skills in the array is "too large"; if it is, increase the capacity of the array by a factor of RESIZE_FACTOR.
 * If the array capacity was changed, print to stderr the string "Expand to ", followed by the new capacity of the list and a newline. 
 * If the capacity was not changed, do nothing.
 */
void skills_expand_if_necessary(pirate* p);

#endif
