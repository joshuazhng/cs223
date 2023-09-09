#include <stdlib.h>
#include "life.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    //Checking to make sure there are at least 3 command line arguments
    if (argc < 4) {
        return 1;
    }

    //Taking in the command line arguments as variables
    int time_steps = atoi(argv[1]);
    int game_size = atoi(argv[2]);
    int start[strlen(argv[3])];
    int new[game_size];

    //Checking that `time_steps` is not negative and `game_size` is not a nonpositive number
    if (time_steps < 0 || game_size < 1) {
        return 1;
    }

    //Loading the string in command line argument to the start and new array
    //Checking to ensure all inputs are 1 or 0
    for (int i = 0; i < game_size; i++) {
        if (argv[3][i] == '0') {
            start[i] = 0;
            new[i] = 0;
        }
        else if (argv[3][i] == '1') {
            start[i] = 1;
            new[i] = 1;
        }
        else {
            return 1;
        }
    }

    //Printing initial values or starting array
    printf("Initial value%-20c[", 's');
    for (int i = 0; i < game_size; ++i) {
        printf("%d", start[i]);
        if (i != (game_size - 1))
            printf(", ");
        else
            printf("]\n");
    }

    for (int i = 0; i < time_steps; ++i) {
        //After each time step, update the start array to hold the same values,
        //The start array will act as the original array before this step occurs
        for (int j = 0; j < game_size; ++j) {
            start[j] = new[j];
        }

        //First, check to see which cells should die based on the rules
        for (int k = 0; k < game_size; ++k) {
            if (shouldDie(start, k, game_size)) {
                new[k] = 0;
            }
        }

        //Next, check to see which cells should become alive based on the rules
        for (int l = 0; l < game_size; ++l) {
            if (isAlive(start, l, game_size) && !(shouldDie(start, l, game_size))) {
                if ((start[l-1]) == 0) {
                    new[l-1] = 1;
                }
                if ((start[l+1]) == 0) {
                    new[l+1] = 1;
                }
            }
        }

        //Printing values in the array after a given timestep
        printf("Values after timestep %-11d[", i + 1);
        for (int m = 0; m < game_size; ++m) {
            printf("%d", new[m]);
            if (m != (game_size - 1))
                printf(", ");
            else
                printf("]\n");
        }
    }

    return 0;
}
