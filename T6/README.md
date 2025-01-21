# epfu24W-103-D-penguins

This project was made to house the Penguin board game for Programming fundamental class. The project is done and managed by group D, consisting of: Nguyen Huynh Gia Bao, Priyanshu Rajput and Damian Piechocki.

This project is divided ito 6 Major Tasks i.e. T1 to T6. Each of the tasks has a specified work.
We will create files for the each of the tasks and will showcase the team's progress via Gitlab.

T1 : For the following task, We have used the flowchart drawn by Nguyen Huynh Gia Bao and we organised our work for individuals.The preliminary code has the functions to be used later for the full code by void functions and return random values to mimic what the functions will return to output the results of the game.

T2 : For this task we prepared preliminary code in accordance with the flowchart for interactive game mode. The program expects user input and in some complex functions, to be done in later parts of the project, random values are returned.  In this part of the task we have already managed to create key variables and the main loop of the prgram. Some of the most important functions are already in place.The program compiles. 

T3 : For this assignment, we divided our main.c file into other files with meaningful names that store appropriate functions. We created header files of newly created .c files and linked them accordingly. In the header files we have written basic comments regarding function's variables and purpose. We also managed to fill out the functions for previously created preliminary code. At this point the interactive game mode is nearly finished, pending finishing touches.

T4 : For this part, we have changed the comments in the header files to doxygen format and implemented structures. We have converted from static memory allocation to dynamic memory allocation for both Player and Board structures. We have added a feature allowing multiple users(at most 4) to play the game together. We made stylistic change of denoting player's penguins by letters(A,B,C,D's) instead of numbers(6,7,8,9). During the meeting we presented our program, it works when appropriate data is inputted, only the mismatched types in input fields are not being handled yet.

T5 : For this assignment, we completed the error handling for Interactive game mode, with that being said the Interactive game mode is now fully finished. We completed the grand majority of the Autnomous mode, thus far the program reads file, saves data to appropriate structures, handles player addition, has the ability to make placements/movements and write the output to specified file, while handling some important errors. We want to include some more error handling for the following meeting, that is the only aspect which may be considered lacking.The program correctly accepts command line parameters. We added some helper-functions to handle respective cases.

T6 :


Contributions list:

-Damian Piechocki: interactive placement phase, file reading, handling player addition and id assignment, accepting command line parameters, converted static board matrix to a Board structure, printing player name to the screen, preliminary code for both interactive and autonomous game modes, manual testing.

-Nguyen Huynh Gia Bao: Interactive movement phase, autonomous movement phase, player score distribution, interactive summerization (game end), handling interpret values for both read and write txt files, formating the files (code blocks, syntax, naming conventions, camelCase, snake_case), generating documentation, adding Doxygen comments to functions.

-Priyanshu Rajput: fixation of errors throughout the project, additional checks to terminate, taking inputs from the user utils.c , unit testing, assignment of doxygen styled comments in few functions.