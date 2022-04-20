#include <stdio.h>
#include <string.h>
#include "fns.h"
#include <time.h>
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
	if (mask == 1 && (x >= cvX && x < cvX + canvasX) && (y >= cvY && y < cvY + canvasY)) {
		canvasA[((x - cvX)/multiplier) + ((y - cvY)/multiplier) * simCanvasX] = bignum;
	}
}
void HandleDestroy() { }



int main() {
    CNFGSetup( "Falling Sand Game", windowX, windowY );
	// Puts the input array to the main canvas (canvas)
	uint32_t (*workCanvas)[simCanvasX*simCanvasY];
	uint32_t (*drawCanvas)[simCanvasX*simCanvasY];
	uint32_t (*tempCanvasP)[simCanvasX*simCanvasY];
	workCanvas = &canvasA;
	drawCanvas = &canvasB;
    while(CNFGHandleInput())
	{
        CNFGBGColor = 0x3333bbff; //Dark Blue Background

		short w, h;
		// CNFGClearFrame();
		CNFGGetDimensions( &w, &h );


		CNFGColor( 0xffbbaaff ); 
		CNFGClearFrame();

		// Run every 30 loops
		if (clock() % 32 <= 2){
			// printf("Calculate\n");
			for (int i = 0; i < simCanvasX*simCanvasY; i++) (*drawCanvas)[i] = 0;
			calculateCGOL(*workCanvas, *drawCanvas, simCanvasX, simCanvasY);
			upscaleCanvasArray(*drawCanvas, simCanvasX, simCanvasY, canvas4x, canvasX, canvasY, multiplier, multiplier);
			tempCanvasP = workCanvas;
			workCanvas = drawCanvas;
			drawCanvas = tempCanvasP;
		}

		// Calculates where the canvas should be for it to be centered
		if (w > canvasX) {
			cvX = (w - canvasX)/2;
		} else cvX = 0;
		if (h > canvasY) {
			cvY = (h - canvasY)/2;
		} else cvY = 0;

		CNFGBlitImage(canvas4x, cvX, cvY, canvasX, canvasY);
		//Display the image and wait for time to display next frame.
		CNFGSwapBuffers();
    }

    return 0;
}