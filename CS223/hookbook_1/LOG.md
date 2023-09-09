# Author
Joshua Zhang
jez24

# Estimate of time to complete assignment
7 hours

# Actual time to complete assignment
| Date | Time Started | Time Spent | Work completed |
| :--: | -----------: | ---------: | :------------- |
| 2/21 |      10:00pm |       1:00 | read through the readme file, set up and created all files for this pset, and wrote the implementation struct as well as the list_create() function |
| 2/23 |       3:00pm |       1:00 | wrote the implementation of four functions in pirate_list.c |
| 3/06 |      11:00pm |       1:00 | wrote the implementation of the five remaining functions in pirate_list.c |
| 3/07 |       7:00pm |       4:00 | defined pirate struct in pirate.c and created  |
|      |              |       7:00 |total time spent|

# Collaboration
I did not discuss my solution for this PSET with any peers.

# Discussion
Part 1 of the Hookbook PSET was quite challenging for me at various points. It was very difficult to understand how the structs were organized, specifically in realizing that the pirate_list struct contains a pointer to an array of pointers to pirates. At the same time, upon knowing this, it was nonetheless difficult to keep track of the types of every variable I was creating in my pirate_list functions. It was also very challenging to debug an issue regarding memory in my pirate.c file as well as in the hookbook.c file. I forgot to add 1 to the strlen when using malloc for the name of each pirate and also forgot to close the file after reading it.
