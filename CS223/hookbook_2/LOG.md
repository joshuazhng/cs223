# Author
Joshua Zhang
jez24

# Estimate of time to complete assignment
7 hours

# Actual time to complete assignment
| Date | Time Started | Time Spent | Work completed |
| :--: | -----------: | ---------: | :------------- |
| 3/07 |      11:00pm |       2:00 | read through the readme file and spec, copied over all files to hookbook_2 folder, and began expanding the pirate struct to account for the new profiles
| 3/08 |       3:00pm |       5:00 | wrote all code to implement functions that would print a pirate according to the spec and print the skills list. also added to the main function to read both of the files and parse through them, and extended list sort function. went through anomalies to catch various edge cases and ensured all resources were released. |
| 3/09 |       3:00pm |       1:00 | added comments to my code for clarity and updated LOG.md file |
|      |              |       8:00 |total time spent|

# Collaboration
I did not discuss my solution for this PSET with any peers.

# Discussion
Getting started with this PSET was uniquely challenging due to the organizational complexity of the program being designed. However, the single most challenging portion of extending the hookbook was reading through the files and figuring out a method to parse through each line, taking in the label and the value separately. I ultimately was able to use the strtok function in the string.h library to acccomplish this. It was also difficult to extend the pirate struct and ensure that I was keeping track of every point at which I was allocating memory on the heap. However, I combatted this by creating efficient functions for destroying each piece of memory that I called malloc for.
