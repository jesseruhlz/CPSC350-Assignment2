# CPSC350-Assignment2
#Jesse Ruhl
#2363770
#Known Issues
# 1. For an unknown reason, the "Output" mode
#   has an issue where it will change some 0's to a '-' on the main screen
#   and add a 1 next to the '-' within the same index.
#   the program outputs this index to be full and places an  'X' .  
#   However in the calculations to create the next generation, while it registers
#   the index as a 0 still, it displays an 'X' although the 'X' does not affect the calculations
# 2. make realclean is not working
# after doing make all. using make realclean gives :
#Try 'find --help' for more information.
#Makefile:24: recipe for target 'realclean' failed
#make: *** [realclean] Error 1

#Works Cited
# Bhargav, Skanda. GeeksForGeeks. https://ide.geeksforgeeks.org/iVA9hRlmD8
# Software_Designer. "How to append file in c++ using fstream? [duplicate]". Stack Overflow. https://stackoverflow.com/questions/23615975/how-to-append-file-in-c-using-fstream
# "C++ Sleep: How To Use The Sleep Function In C++ Programs". Software Testing Help. https://www.softwaretestinghelp.com/cpp-sleep/
# adrei985 "How to add a border around a matrix?". StackOverflow. https://stackoverflow.com/questions/26952358/how-to-add-a-border-around-a-matrix
