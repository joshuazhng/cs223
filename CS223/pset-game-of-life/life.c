#include "life.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool isAlive(int array[], size_t index, size_t size) {
    if (array[index] == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool shouldDie(int array[], size_t index, size_t size) {
    if (index == 0 || index == size - 1) {
        return false;
    }
    else {
        if (isAlive(array, index + 1, size) && isAlive(array, index - 1, size)) {
            return true;
        }
        else {
            return false;
        }
    }
}
