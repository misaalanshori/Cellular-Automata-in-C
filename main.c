#include <stdio.h>
#include <string.h>
#include "fns.h"

#define CNFG_IMPLEMENTATION
#include "rawdraw/CNFG.h"


#define windowX 768
#define windowY 640

#define simCanvasX 128
#define simCanvasY 128

#define canvasX 512
#define canvasY 512
#define multiplier 4


int switchCanvas = 0;

// Canvas A and B for storing the pixels
uint32_t canvasA[simCanvasX*simCanvasY];
uint32_t canvasB[simCanvasX*simCanvasY];

// This canvas is for storing the upscaled pixels
uint32_t canvas4x[canvasX*canvasY];

#define t 0xffffffffL

uint32_t inputCanvas[32*32] = { // NOTE: temporary solution, in the future read input from stdin or something.
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, t, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, t, 0, 0, 0, 0, 0, t, t, t, 0, 0, 0, 0, 0, 0, t, t, t, t, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, t, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, t, t, t, t, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, t, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, t, 0, 0, 0, t, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, t, t, t, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, t, t, t, t, t,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, t,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, t, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, t, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, t, t, 0, 0, t, t, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, t,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0, 0, t, t, 0, 0, t, t, t,
	
};

#undef t

#define bignum 0xffffffffL

void calculateCGOL(uint32_t source[], uint32_t target[], int x, int y) {
	int totalNeighbors = 0;
	// Loop through all pixels
	for (int cY = 0; cY < y; cY++)
	{
		for (int cX = 0; cX < x; cX++)
		{
			// Loop Through the neighbors and calculate the total
			for (int nY = -1; nY <= 1; nY++)
			{
				for (int nX = -1; nX <= 1; nX++)
				{
					if (source[(cX + nX)+(cY + nY)*x] == bignum) {
						totalNeighbors += 1;
					}
				}
			}

			target[cX+cY*x] = 0; // Make sure the current target pixel is 0

			if (source[cX+cY*x] == bignum) {
				totalNeighbors -= 1; // this excludes the current pixel from the neighbor count
				if (totalNeighbors == 3 | totalNeighbors == 2) { // If has 2/3 neighbors than it stays alive, else it dies
					target[cX+cY*x] = bignum;
				} else {
					target[cX+cY*x] = 0;
				}
			} else {
				if (totalNeighbors == 3) { // if total neighbors is 3, set current pixel to alive
					target[cX+cY*x] = bignum;
				}
			}
			totalNeighbors = 0;
		}
	}
}



void HandleKey( int keycode, int bDown )
{
	if( keycode == 27 ) exit( 0 );
	if( keycode == 8 && bDown == 0 ) {
		
	};
	printf( "Key: %d -> %d\n", keycode, bDown );

}
void HandleButton( int x, int y, int button, int bDown ) { }	
void HandleMotion( int x, int y, int mask ) { }
void HandleDestroy() { }



int buttonDown = 0;

int loop = 0;
int cvX = 0;
int cvY = 0;
int main() {
    CNFGSetup( "Hello World", windowX, windowY );
	// Puts the input array to the main canvas (canvas)
	putInArray(inputCanvas, 32, 32, canvasA, simCanvasX, simCanvasY, 0 , 0);
	putInArray(inputCanvas, 32, 32, canvasA, simCanvasX, simCanvasY, 80 , 80);
    while(CNFGHandleInput())
	{
        CNFGBGColor = 0x3333bbff; //Dark Blue Background

		short w, h;
		// CNFGClearFrame();
		CNFGGetDimensions( &w, &h );

		//Change color to white.
		CNFGColor( 0xffbbaaff ); 
		CNFGClearFrame();

		// Run every 30 loops
		if (loop == 30){
			// printf("Calculate\n");
			if (switchCanvas == 0) {
				calculateCGOL(canvasA, canvasB, simCanvasX, simCanvasY);
				switchCanvas = 1;
				upscaleCanvasArray(canvasB, simCanvasX, simCanvasY, canvas4x, canvasX, canvasY, multiplier, multiplier);
				
			} else {
				calculateCGOL(canvasB, canvasA, simCanvasX, simCanvasY);
				switchCanvas = 0;
				upscaleCanvasArray(canvasA, simCanvasX, simCanvasY, canvas4x, canvasX, canvasY, multiplier, multiplier);
			}
			loop = 0;
		}
		loop++;

		// Calculates where the canvas should be for it to be centered
		if (w > canvasX) {
			cvX = (w - canvasX)/2;
		} else cvX = 0;
		if (h > canvasY) {
			cvY = (h - canvasY)/2;
		} else cvY = 0;

		CNFGBlitImage(canvas4x, cvX, cvY, 512, 512);
		//Display the image and wait for time to display next frame.
		CNFGSwapBuffers();
    }

    return 0;
}