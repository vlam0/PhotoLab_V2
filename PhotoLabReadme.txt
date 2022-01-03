/*****************************************************************************/
/* PhotoLabReadme.txt: homework assignment #3, for EECS 22,  Winter 2020     */
/*                                                                           */
/* Author: <Vivian Lam>                                                      */
/* Date:   2/15/20                                                           */
/*                                                                           */
/*****************************************************************************/

Makefile
First was to define variable definitions in order to make the file more condensed and easier to alter when used for compiling files. Create a target to link DIPs.o and Advanced.o. Next was to make the targets such as all (compiles all object files in relation to PhotoLab), clean (removes all object files and removes the compiled file: PhotoLab), and PhotoLabTest (runs the PhotoLabTest with the debug option on). Lastly, was to make the compilation rules. Set each object file with the files in relation to the correlating file such as their .c and .h files used. For the file to run the programs, call upon all the object files that are accessed then set the compilation with all those object files to a runnable file. 

FileIO.c
FileIO.c is another file consisting of the Load Image and Save Image function. Since the functions were already made, there isn’t much that needs to be done. The only things that must be added are the #include .h files that correlate to this .c file and the include header files. 

FileIO.h
FileIO.h only declares the Load Image and Save Image functions. It also must have #include “Constants.h” since the global constants such as WIDTH and HEIGHT are used in this file. 

Constants.h
In the Constants.h file is where all the constants are defined 

DIPs.c
In the DIPs.c file, it is a copy of all the defined functions: Black & White, Sharpen, and Hue. The other things that must be added are: #include .h files that correlate to this .c file and the include header files.

DIPs.h
DIPs.h only declares the Black & White, Sharpen, and Hue functions. It also must have #include “Constants.h” since the global constants such as WIDTH and HEIGHT are used in this file. 

Advanced.c
Advanced.c includes the definition add Noise, Posterize, and Motion Blur function. For the Noise function, first was to set the random number based on the current time. With the user’s select of percentage of noise they want, the calculations to the number of pixels are obtained such that it equals to the percent times the WIDTH times HEIGHT. A loop was made until it reached to the number of pixels of noise. In that loop, it generates random values of the width and height of the image and changes that pixel to white. For the Posterize function: it obtains the level of most significant bit to set as 0 and the ones afterwards to set to 1’s. First was to calculate the decimal of the ones that need to alter based on user input. A loop was made in which it reads through each pixel’s color. For each pixel, we shift out the bits based on the user’s selected value then shift back to normal with the other values gone. We then set that for each color we get the ‘or’ values of the decimal 1’s and the shifted-out versions. For the Motion Blur function: it blurs the image upwards with the number of pixels based on user’s input. First, temporary arrays were made with the size of the image. Loops were made to obtain the image and alter the image. For the image when the height is greater than or equal to the blur amount, the colors of the above pixels are averaged and added to the temporary array. If the height is less than the blur amount, it does the same as when the height is greater than the blur amount, except it averages it with the number of pixels left from the current height. The image is altered by taking 50% of the original pixel’s value and %50 of the temporary array value and adding them together. 

Advanced.h
Advanced.h file is the declaration of Noise, Posterize, and Motion Blur function. It also must have #include “Constants.h” since the global constants such as WIDTH and HEIGHT are used in this file. 

PhotoLab.c
The only other functions in this file besides the main are PrintMenu which prints the menu options and AutoTest which tests all the functions. The AutoTest opens the main image and applies the function then saves the image to a new designated file correlating to the function. It does this for all the filters. In the beginning, all the .h files must be included. AutoTest and PrintMenu are declared. In the main function, first all the variable and arrays are declared. Next is to see if the debug mode is on or off. If the Debug mode is on, it runs the AutoTest function and exits the code. If debug mode is off, it prints menu and asks for the user’s input of selection. The user must open a file first in order to all user to do any alterations to the image. Next is to make a case statement with the correlating menu options. This repeats if the user does not choose to exit the option.  

