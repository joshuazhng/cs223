#include "pirate_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check to ensure that there is at least four command-line arguments
    if (argc < 4) {
        fprintf(stderr, "Invalid arguments\n");
        return 1;
    }
    
    // Read in the file from the first command-line argument and check that it is indeed a file and the file is not NULL
    FILE* pirate_profiles_file = fopen(argv[1], "r");
    if (pirate_profiles_file == NULL) {
        fprintf(stderr, "Invalid filename: %s\n", argv[1]);
        return 1;
    }

    // Read in the file from the second command-line argument and check that it is indeed a file and the file is not NULL
    FILE* pc_pairs_file = fopen(argv[2], "r");
    if (pc_pairs_file == NULL) {
        fprintf(stderr, "Invalid filename: %s\n", argv[2]);
        return 1;
    }

    // Check to ensure that the third command-line argument is either -n, -v, or -t
    if ((strcmp(argv[3], "-n") != 0) && (strcmp(argv[3], "-v") != 0) && (strcmp(argv[3], "-t") != 0)) {
        fprintf(stderr, "Invalid argument: %s\n", argv[3]);
        return 1;
    }
    
    // Create the pirate list and a buffer to store each pirate name as you are creating the pirate list
    pirate_list* my_pirate_list = list_create();
    char buf[200];
    int n = 200;
    char buf_label[65];
    char buf_value[65];

    // Creating char pointer and deliminator for parsing through each line of file from fgets
    char* cptr;
    char delim[] = ":";

    // Creating index and pirate pointer to keep track of the current pirate being updated
    int index;
    pirate* current_pirate;

    // Enum data type to ensure that duplicate pirates are ignored and only the profile for the first pirate is stored
    enum read_state {New, Ignore} state = New;

    // While loop to create new pirates and add all corresponding information to their profile
    // Check what the label is and then determine how to use the value given
    while (fgets(buf, n, pirate_profiles_file) != NULL) {
        // Separating the label and value in each line of the file, storing them each as variables
        cptr = strtok(buf, delim);
        strcpy(buf_label, cptr);
        cptr = strtok(NULL, delim);
        strcpy(buf_value, cptr);

        if (buf_value[strlen(buf_value) - 1] == '\n') {
                buf_value[strcspn(buf_value, "\n")] = 0;
        }

        if (strcmp(buf_label, "name") == 0) {
            if (list_insert(my_pirate_list, make_pirate(buf_value), list_length(my_pirate_list)) != NULL) {
                state = Ignore;
            }
            else {
                state = New;
                index = list_length(my_pirate_list) - 1;
                current_pirate = list_access(my_pirate_list, index);
            }
        }

        else if (strcmp(buf_label, "title") == 0 && state == New) {
            set_title(current_pirate, buf_value);
        }

        else if (strcmp(buf_label, "vessel") == 0 && state == New) {
            set_vessel(current_pirate, buf_value);
        }

        else if (strcmp(buf_label, "treasure") == 0 && state == New) {
            int buf_int = atoi(buf_value);
            set_treasure(current_pirate, buf_int);
        }

        else if (strcmp(buf_label, "port") == 0 && state == New) {
            set_port(current_pirate, buf_value);
        }

        else if (strcmp(buf_label, "skill") == 0 && state == New) {
            set_skills(current_pirate, buf_value);
        }
    }
    
    // delim2 is the character used to separate the pirate and captain in each line of the file
    char delim2[] = "/";

    // Creating two pirate pointers to act as buffers for setting the captain for each pirate
    pirate *p1;
    pirate *p2;

    // While loop to read the pirate-captain pairs file and add the corresponding captains to the pirates listed
    while (fgets(buf, n, pc_pairs_file) != NULL) {
        cptr = strtok(buf, delim2);
        strcpy(buf_label, cptr);
        cptr = strtok(NULL, delim2);
        strcpy(buf_value, cptr);

        if (buf_value[strlen(buf_value) - 1] == '\n') {
                buf_value[strcspn(buf_value, "\n")] = 0;
        }

        for (int i = 0; i < list_length(my_pirate_list); i++) {
            char* name = get_name(list_access(my_pirate_list, i));
            if (strcmp(buf_label, name) == 0) {
                p1 = list_access(my_pirate_list, i);
            }
            if (strcmp(buf_value, name) == 0) {
                p2 = list_access(my_pirate_list, i);
            }
        }
        set_captain(p1, p2);
    }

    // Closing the two files after reading through them
    fclose(pirate_profiles_file);
    fclose(pc_pairs_file);

    list_sort(my_pirate_list, argv[3]);

    // Print the sorted list to stdout
    for (int i = 0; i < list_length(my_pirate_list); i++) {
        print_pirate(list_access(my_pirate_list, i));
        printf("\n");
    }

    // Loop through the entire pirate list to destroy each pirate individually
    for (int i = 0; i < list_length(my_pirate_list); i++) {
        destroy_pirate(list_access(my_pirate_list, i));
    }

    // Destroy the pirate list and return 0 exit code
    list_destroy(my_pirate_list);
    return 0;
}

