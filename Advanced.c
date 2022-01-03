/*********************************************************************/
/* Advanced.c: homework assignment #3, for EECS 22,  Winter 2020     */
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

#include "Advanced.h"
#include "Constants.h"


/* Noise function*/
void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    /* Randomize numbers based on time */
    srand(time(NULL));

    int x, y, i;
    int numberOfPixels = (n * WIDTH * HEIGHT) / 100;

    for (i = 0; i < numberOfPixels; i++)
    {
	/* generate random pixel */
    	x = rand() % WIDTH;
    	y = rand() % HEIGHT;
	
	R[x][y] = 255;
	G[x][y] = 255;
	B[x][y] = 255;
    }
}


/* Posterize function*/
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
   int x, y;
   int redOnes = 0, greenOnes = 0, blueOnes = 0;
   int i;
   int red, green, blue;

   /* Obtains ones for the lower bits */
   for (i = 1; i < rbits; i++)
   {
   	redOnes += pow(2,i-1);
   }

   for (i = 1; i < gbits; i++)
   {
   	greenOnes += pow(2,i-1);        
   }

   for (i = 1; i < bbits; i++)
   {
        blueOnes += pow(2,i-1);
   }

   /* Loops to shift the bits */
   for (x = 0; x < WIDTH; x++)
   {
        for (y = 0; y < HEIGHT; y++)
        {
	    /* Shifts out unnecessary bits */
	    red = R[x][y] >> rbits;
	    red = red << rbits;
	    green = G[x][y] >> gbits;
	    green = green << gbits;
            blue = B[x][y] >> bbits;
            blue = blue << bbits;
	  
	    /* Posterize */
 	    R[x][y] = (red | redOnes);
	    G[x][y] = (green | greenOnes);
	    B[x][y] = (blue | blueOnes);
        }
    }
}

/* Motion Blur function */
void MotionBlur(int BlurAmount, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
   int x, y, i;
   unsigned char r[WIDTH][HEIGHT], g[WIDTH][HEIGHT], b[WIDTH][HEIGHT];
   double red = 0, green = 0, blue = 0;
   
   /* Make temp arrays */
   for (x = 0; x < WIDTH; x++)
   {
        for (y = 0; y < HEIGHT; y++)
        {
            r[x][y] = 0;
            g[x][y] = 0;
            b[x][y] = 0;
	}
   }

   /* Alters image to blur */
   for (x = 0; x < WIDTH; x++)
   {
        for (y = 0; y < HEIGHT; y++)
        {   
	    red = 0;
	    blue = 0;
	    green = 0;
	    
	    /* Blurs pixels before bounds reached */
            if (y >= BlurAmount)
	    {
		for (i = 1; i <= BlurAmount; i++)
		{
		     red += R[x][y-i];
		     green += G[x][y-i];
	 	     blue += B[x][y-i];
		}
		
		/* Changes the temporary arrays to the average of the pixels until it reaches the boundary */
		r[x][y] = red * 0.5 / BlurAmount;
		g[x][y] = green * 0.5 / BlurAmount;
		b[x][y] = blue * 0.5 / BlurAmount;
	    }
	    
            /* Blurs pixels when blurAmount is greater than the pixel read */
	    if (y < BlurAmount)
	    {
		for (i = 1; i <= y; i++)
		{
		     red +=  R[x][y-i];
		     green += G[x][y-i];
		     blue += B[x][y-i];
		}
		
		/* Changes the temporary arrays to the average of the blur amount of pixels */
		r[x][y] = red * 0.5 / y;
                g[x][y] = green * 0.5 / y;
                b[x][y] = blue * 0.5 / y;
	    }
	    
	    /* Adds the temporary array and original pixel and obtains the average */
	    R[x][y] = r[x][y] + R[x][y] * 0.5;
            G[x][y] = g[x][y] + G[x][y] * 0.5;
            B[x][y] = b[x][y] + B[x][y] * 0.5;
        }
    }
}


