#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "pirate_list.h"

int INITIAL_CAPACITY = 25;
int RESIZE_FACTOR = 2;

struct implementation {
    size_t length;
    size_t capacity;
    pirate** pirate_ptr_array;
};

//Forward declaration of functions not found in pirate_list.h
void list_expand_if_necessary(pirate_list* pirates);

void list_contract_if_necessary(pirate_list* pirates);


pirate_list *list_create() {
    pirate_list* new_piratelist = malloc(sizeof(pirate_list));
    new_piratelist->pirate_ptr_array = malloc(sizeof(pirate*) * INITIAL_CAPACITY);
    new_piratelist->length = 0;
    new_piratelist->capacity = INITIAL_CAPACITY;
    return new_piratelist;
}

/*
 * Return the index of the pirate with the same name as p, or a value greater than or equal to the length of the list if there is no pirate in the list with a matching name.
 */
size_t list_index_of(pirate_list *pirates, pirate *p) {
    // For loop to go through list of pirates and check if the given pirate matches each pirate in the list
    for (size_t i = 0; i < pirates->length; i++) {
        if (strcmp(get_name(pirates->pirate_ptr_array[i]), get_name(p)) == 0) {
            return i;
        }
    }
    return pirates->length;
}

/*
 * Only if there is no pirate in the list with the same name as p, insert pirate p into the list at index idx by copying the pointer, shifting the latter part of the list one “slot” to the right.
 * If there is a pirate in the list with the same name as p, do nothing, and return a pointer to the pirate that was not inserted.
 * If the pirate was inserted into the list, return NULL
 */
pirate *list_insert(pirate_list *pirates, pirate *p, size_t idx) {
    // Check if there is a pirate in the list with the same name as p and if so, return a pointer to the pirate that was not inserted
    size_t i = (list_index_of(pirates, p));
    
    if (i < pirates->length) {
        //Found pirate in the list already, returning pointer to the pirate
        return pirates->pirate_ptr_array[i];
    }

    // If there is no match, check to see if the length is greater than or equal to capacity and resize as needed
    list_expand_if_necessary(pirates);

    // Shift the latter part of the list, up until the idx, one "slot" to the right
    if (idx < pirates->length) {
        for (size_t i = pirates->length; i > idx; i--) {
            pirates->pirate_ptr_array[i] = pirates->pirate_ptr_array[i-1];
        }
    }
    else {
        idx = pirates->length;
    }

    // Copy the pointer to the new pirate
    pirates->pirate_ptr_array[idx] = p;
    pirates->length++;

    // Return NULL to indicate that the pirate was inserted successfully
    return NULL;
}

/*
 * Remove the pirate from the list with the same name as p, and return a pointer to it.
 * If there is no pirate in the list with the same name as p, return NULL
 */
pirate *list_remove(pirate_list *pirates, pirate *p) {
    // Check if there is a pirate in the list with the same name as p
    size_t i = (list_index_of(pirates, p));

    //If there is a pirate in the list with the same name as p, remove the pirate from the list
    if (i < pirates->length) {
        pirate *removed = pirates->pirate_ptr_array[i];
        for (size_t j = i; j < pirates->length - 1; j++) {
            pirates->pirate_ptr_array[j] = pirates->pirate_ptr_array[j+1];
        }

        //Returning pointer to the pirate removed from the list
        return removed;
    }
    else {
        return NULL;
    }
}

/*
 * Return a pointer to the pirate pointed to by index idx in the list, or NULL if idx is not a valid index (i.e., it is >= the length of the list).
 */
pirate *list_access(pirate_list *pirates, size_t idx) {
    if (idx >= pirates->length) {
        return NULL;
    }
    else {
        return pirates->pirate_ptr_array[idx];
    }
}

/*
 * Sort the list of pirates in the order specified by the input sort_mode
 */
void list_sort(pirate_list *pirates, char *sort_mode) {
    int j;
    pirate *key;

    // Sorting in increasing lexicographic order by the pirate's name
    if (strcmp("-n", sort_mode) == 0) {
        for (size_t i = 1; i < pirates->length; i++) {
            j = i;
            while (j > 0 && (strcmp(get_name(pirates->pirate_ptr_array[j-1]), get_name(pirates->pirate_ptr_array[j]))) > 0) {
                key = pirates->pirate_ptr_array[j];
                pirates->pirate_ptr_array[j] = pirates->pirate_ptr_array[j-1];
                pirates->pirate_ptr_array[j-1] = key;
                j = j - 1;
            }
        }
    }
    
    // Sorting in increasing lexicographic order by the pirate's current vessel
    else if (strcmp("-v", sort_mode) == 0) {
        for (size_t i = 1; i < pirates->length; i++) {
            j = i;
            while (j > 0 && (strcmp(get_vessel(pirates->pirate_ptr_array[j-1]), get_vessel(pirates->pirate_ptr_array[j]))) > 0) {
                key = pirates->pirate_ptr_array[j];
                pirates->pirate_ptr_array[j] = pirates->pirate_ptr_array[j-1];
                pirates->pirate_ptr_array[j-1] = key;
                j = j - 1;
            }
        }
    }
    
    // Sorting in decreasing order by the number of treasures
    else { //if (strcmp("-t", sort_mode) == 0)
        for (size_t i = 1; i < pirates->length; i++) {
            j = i;
            while (j > 0 && (get_treasure(pirates->pirate_ptr_array[j-1]) < get_treasure(pirates->pirate_ptr_array[j]))) {
                key = pirates->pirate_ptr_array[j];
                pirates->pirate_ptr_array[j] = pirates->pirate_ptr_array[j-1];
                pirates->pirate_ptr_array[j-1] = key;
                j = j - 1;
            }
        }
    }
}  

/*
 * Return the number of pirates in the list.
 */
size_t list_length(pirate_list *pirates) {
    return pirates->length;
}

/*
 * Free all memory associated with the pirate_list, but leave the memory associated with the pirates in the list untouched (it is someone else's job to free the pirates; maybe that dog with the keys in the Pirates of the Caribbean).
 */
void list_destroy(pirate_list *pirates) {
    free(pirates->pirate_ptr_array);
    free(pirates);
}

/*
 * Check if the actual number of pirates in the array is "too large"; if it is, increase the capacity of the array by a factor of RESIZE_FACTOR.
 * If the array capacity was changed, print to stderr the string "Expand to ", followed by the new capacity of the list and a newline. Here is a possible print statement:
 *
 *     fprintf(stderr, "Expand to %zu\n", new_capacity);
 *
 * If the capacity was not changed, do nothing.
 */
void list_expand_if_necessary(pirate_list* pirates) {
    if (pirates->length >= pirates->capacity) {
        pirates->capacity *= RESIZE_FACTOR;
        pirate **ptr = realloc(pirates->pirate_ptr_array, sizeof(pirate*) * pirates->capacity);
        if (ptr != NULL) {
            fprintf(stderr, "Expand to %zu\n", pirates->capacity);
            pirates->pirate_ptr_array = ptr;
        }
        else {
            pirates->capacity /= RESIZE_FACTOR;
        }
    }
}

/*
 * Check if the actual number of pirates in the array is "too small"; if it is, decrease the capacity of the array by a factor of RESIZE_FACTOR.
 * If the array capacity was changed, print to stderr the string "Contract to " followed by the new capacity of the list. Here is a possible print statement:
 *
 *     fprintf(stderr, Contract to %zu\n, new_capacity);
 *
 * If the capacity was not changed, do nothing.
 *
 * The capacity of the array must never fall below INITIAL_CAPACITY!
 */
void list_contract_if_necessary(pirate_list* pirates) {
    if (pirates->length < (pirates->capacity / (2 * RESIZE_FACTOR)) && (pirates->capacity / RESIZE_FACTOR) >= INITIAL_CAPACITY) {
        pirates->capacity /= RESIZE_FACTOR;
        pirate **ptr = realloc(pirates->pirate_ptr_array, sizeof(pirate*) * pirates->capacity);
        if (ptr != NULL) {
            fprintf(stderr, "Contract to %zu\n", pirates->capacity);
            pirates->pirate_ptr_array = ptr;
        }
        else {
            pirates->capacity *= RESIZE_FACTOR;
        }
    }
}

