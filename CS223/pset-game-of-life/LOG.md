# Author
Joshua Zhang
jez24

# Estimate of time to complete assignment
5 hours

# Actual time to complete assignment
| Date | Time Started | Time Spent | Work completed |
| :--: | -----------: | ---------: | :------------- |
| 2/07 |      11:00pm |       1:00 | read through the readme file, set up and created all files for this pset, declared the functions in life.h and wrote the implementation of the two functions in life.c
| 2/08 |       8:00pm |       3:00 | created the framework of main.c and examined all edge cases or tricky test cases, spent time debugging when errors arose
|      |              |            |                |
|      |              |       5:00 |total time spent|

# Collaboration
I did not discuss my solution for this PSET with any peers.

# Discussion
Getting started with the project at the beginning was quite difficult as it was a little overwhelming trying to see where to start. I chose to begin with the two functions in life.c as they seemed to be smaller tasks that I could first focus on, rather than jumping immediately into the big picture. Additionally, I faced some trouble implementing the second rule of the game, which is that if a live cell $i$ does not have two live neighbors, then any dead neighbors of cell $i$ will become alive. This is because I forgot to check if the cell itself was live first.