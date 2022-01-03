/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Winter 2020     */
/*                                                                   */
/* Author: EECS 22 Team and <Vivian Lam>                             */
/* Date:   2/7/20                                                    */
/*                                                                   */
/* Comments: Enjoy Learning new things!:)                            */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>

#include "FileIO.h"
#include "Constants.h"
#include "DIPs.h"
#include "Advanced.h" 

void PrintMenu();

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);


int main() 
{
    unsigned char   R[WIDTH][HEIGHT];	/* use three 2-D arrays to store R, G, B components */
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];

    unsigned int rbits;
    unsigned int gbits;
    unsigned int bbits;

    int option;			/* user input option */
    char fname[SLEN];		/* input file name */

    srand(time(NULL));          /* Use current time for random number generator */
    
    int debugMode = 0;
    
    int rc = -1;                        /* return code of ReadImage() */
    int hue = 150;
    int noise, blur;
    
    /* Displays only AutoTest when Debug Mode is on */
    #ifdef DEBUG
	debugMode = 1;
	AutoTest(R, G, B);
        rc = SUCCESS;
        return 0;
    #endif 	

    assert(debugMode == 0);

    PrintMenu();
    scanf("%d", &option);

    while (option != EXIT)
    {
        if (option == 1)
        {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            rc = LoadImage(fname, R, G, B);
        }
        /* menu item 2 - 10 requires image is loaded first */
        else if (option >= 2 && option <= 10)
        {
            if (rc != SUCCESS)
            {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else
            {
                switch(option)
                {
                    case 2: /* Save Image */
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, R, G, B);
                        break;

                    case 3: /* Black and White filter to Image */
                        BlackNWhite(R, G, B);
                        printf("\"Black & White\" operation is done!\n");
                        break;

                    case 4: /* Sharpen Image */
                        Sharpen(R, G, B);
                        printf("\"Sharpen\" operation is done!\n");
                        break;

                    case 5: /* Hue Image */
                        printf("Please input the degree of changing hue: ");
                        scanf("%d", &hue);
                        Hue(R, G, B, hue);
                        printf("\"Hue\" operation is done!\n");
                        break;

		    case 6: /* Add Noise to Image */
			printf("Please input noise percentage: ");
			scanf("%d", &noise);
			Noise(noise, R, G, B);
			printf("\"Noise\" operation is done!\n");
			break;

		    case 7: /* Posterize Image */
			printf("Enter the number of posterization bits for R channel (1 to 8): ");
			scanf("%d", &rbits);
			printf("Enter the number of posterization bits for G channel (1 to 8): ");
			scanf("%d", &gbits);
			printf("Enter the number of posterization bits for B channel (1 to 8): ");
			scanf("%d", &bbits);
			Posterize(R, G, B, rbits, gbits, bbits);
			printf("\"Posterize\" operation is done!\n");
			break;

		    case 8: /* Blur Image */
			printf("Please input motion blur amount: ");
			scanf("%d", &blur);
			MotionBlur(blur, R, G, B);
			printf("\"Motion Blur\" operation is done!\n");
			break;

		    case 9: /* Auto Test */
			AutoTest(R, G, B);
			rc = SUCCESS;      /* set returned code SUCCESS,, since image is loaded */
			break;

		    case 10: /* EXIT */
			break;

                    default:
                        break;
                }
            }
        }
        else 
	{
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        scanf("%d", &option);
    }
 
    printf("You exit the program.\n\n");
    return 0;
}


/* Main Menu */
void PrintMenu()
{
    printf("\n-------------------------\n");
    printf("1: Load a PPM image\n");
    printf("2: Save the image in PPM and JPEG format\n");
    printf("3: Change the color image to black and white\n");
    printf("4: Sharpen the image\n");
    printf("5: Change the hue of image\n");
    printf("6: Add noise to the image\n");
    printf("7: Posterize an image\n");
    printf("8: Motion Blur\n");
    printf("9: Test all functions\n");
    printf("10: Exit\n");
    printf("--------------------------\n");
    printf("Please make your choice: ");
}


/* Test All Functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT] ,unsigned  char G[WIDTH][HEIGHT] ,unsigned char B[WIDTH][HEIGHT])
{
    char fname[SLEN] = "CrystalChurch";
    
    /* Black & White */
    LoadImage(fname, R, G, B);
    BlackNWhite(R, G, B);
    SaveImage("bw", R, G, B);
    printf("Black and White tested!\n\n");

    /* Sharpen */
    LoadImage(fname, R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B);
    printf("Sharpen tested!\n\n");

    /* Hue */
    LoadImage(fname, R, G, B);
    Hue(R, G, B, 150);
    SaveImage("hue", R, G, B);
    printf("Hue tested!\n\n");

    /* Noise */
    LoadImage(fname, R, G, B);
    Noise(30, R, G, B);
    SaveImage("noise", R, G, B);
    printf("Noise tested!\n\n");

    /* Posterize */
    LoadImage(fname, R, G, B);
    Posterize(R, G, B, 7, 7, 7);
    SaveImage("posterize", R, G, B);
    printf("Posterize tested!\n\n");

    /* Motion Blur */
    LoadImage(fname, R, G, B);
    MotionBlur(50, R, G, B);
    SaveImage("blur", R, G, B);
    printf("Motion Blur tested!\n\n");
}
