#include "pirate_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    // Check to ensure that there is only one command-line argument
    if (argc >= 3 || argc == 1) {
        return 1;
    }

    // Read in the file
    FILE* pirate_names_file = fopen(argv[1], "r");

    // Ensure that the command-line argument is indeed a file and the file is not NULL
    if (pirate_names_file == NULL) {
        return 1;
    }
    
    // Create the pirate list and a buffer to store each pirate name as you are creating the pirate list
    pirate_list* my_pirate_list = list_create();
    char buf[65];
    int n = 65;

    // While loop to insert all of the pirates into the list
    while (fgets(buf, n, pirate_names_file) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strcspn(buf, "\n")] = 0;
        }
        list_insert(my_pirate_list, make_pirate(buf), list_length(my_pirate_list));
    }
    fclose(pirate_names_file);

    list_sort(my_pirate_list);

    // Print the sorted list to stdout
    for (int i = 0; i < list_length(my_pirate_list); i++) {
        printf("%s\n", get_name(list_access(my_pirate_list, i)));
    }

    for (int i = 0; i < list_length(my_pirate_list); i++) {
        destroy_pirate(list_access(my_pirate_list, i));
    }
    list_destroy(my_pirate_list);
    return 0;
}

