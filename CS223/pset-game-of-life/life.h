#include <stdlib.h>
#include <stdbool.h>

bool isAlive(int array[], size_t index, size_t size);
/* The `isAlive` function takes as arguments an array of `int`s called `array`, 
    an index `i`, and the size of the array (`size`).
    It returns `true` if the cell at position `i` is alive, otherwise returns `false`.
    Note that `bool`, `true` and `false` are not keywords in C, so you may `#include <stdbool.h>`, 
    which contains definitions for those two values and the type */


bool shouldDie(int array[], size_t index, size_t size);
// The `shouldDie` function takes as arguments an array of `int`s called `array`, 
// an index `i`, and the size of the array (`size`).
//     It returns `true` if cell `i` has two live neighbors; otherwise it returns `false`.
//     > **Hint**: Checking for neighbors that don’t exist (*e.g.*, things at index `-1` or at an index equal to `size`) will cause an error.
//     > Check your indexes before using them! 