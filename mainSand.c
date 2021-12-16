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

int buttonDown = 0;

int loop = 0;
int cvX = 0;
int cvY = 0;
// Canvas A and B for storing the pixels
uint32_t canvasA[simCanvasX*simCanvasY];
uint32_t canvasB[simCanvasX*simCanvasY];

// This canvas is for storing the upscaled pixels
uint32_t canvas4x[canvasX*canvasY];

#define bignum 0xffffffffL

void calculateCGOL(uint32_t source[], uint32_t target[], int x, int y) {

	// Loop through all pixels
	
	for (int cY = 0; cY < y; cY++)
	{
		for (int cX = 0; cX < x; cX++)
		{

			if (source[cX+cY*x] == bignum) {
				if ((cY + 1) == y) {
					target[cX+cY*x] = bignum;
				} else {
					if (source[cX+(cY + 1)*x] != bignum)
					{
						target[cX+(cY + 1)*x] = bignum;
					} 
					else if ((source[(cX-1)+(cY + 1)*x] != bignum) &&  !((cX - 1) < 0))
					{
						target[(cX-1)+(cY + 1)*x] = bignum;
					} 
					else if ((source[(cX+1)+(cY + 1)*x] != bignum) &&  !((cX + 1) == x))
					{
						target[(cX+1)+(cY + 1)*x] = bignum;
					} 
					else
					{
						target[cX+cY*x] = bignum;
					}
				}
			}

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
void HandleButton( int x, int y, int button, int bDown ) {
 }	
void HandleMotion( int x, int y, int mask ) { 
	if (mask == 1) {
		canvasA[((x - cvX)/multiplier) + ((y - cvY)/multiplier) * simCanvasX] = bignum;
	}
}
void HandleDestroy() { }



int main() {
    CNFGSetup( "Hello World", windowX, windowY );
	// Puts the input array to the main canvas (canvas)
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
		if (loop == 10){
			// printf("Calculate\n");
			if (switchCanvas == 0) {
				for (int i = 0; i < simCanvasX*simCanvasY; i++) canvasB[i] = 0;
				calculateCGOL(canvasA, canvasB, simCanvasX, simCanvasY);
				switchCanvas = 1;
				upscaleCanvasArray(canvasB, simCanvasX, simCanvasY, canvas4x, canvasX, canvasY, multiplier, multiplier);
				
				
			} else {
				for (int i = 0; i < simCanvasX*simCanvasY; i++) canvasA[i] = 0;
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