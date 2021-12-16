#include <stdio.h>
#include <string.h>
#define windowX 768
#define windowY 640

#define simCanvasX 128
#define simCanvasY 128

#define canvasX 512
#define canvasY 512
#define multiplier 4

#define CNFG_IMPLEMENTATION
#include "rawdraw/CNFG.h"
int switchCanvas = 0;

uint32_t canvasA[simCanvasX*simCanvasY];
uint32_t canvasB[simCanvasX*simCanvasY];

uint32_t canvas4x[canvasX*canvasY];

#define t 0xffffffffL

uint32_t inputCanvas[32*32] = {
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

// uint32_t inputCanvas[16*16] = {
// 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 	0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0,
// 	0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, t, 0, t, 0, 0,
// 	0, 0, t, t, t, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0,
// 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 	0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 	0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 	0, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 	0, 0, 0, t, t, t, t, t, t, 0, 0, 0, 0, 0, 0, 0,
// 	0, 0, t, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0,
// 	0, 0, 0, 0, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0,
// 	0, 0, t, 0, 0, 0, 0, t, 0, 0, 0, 0, 0, 0, 0, 0,
// 	0, 0, 0, 0, t, t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
// 	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	
// };

#undef t

#define bignum 0xffffffffL

void upscaleCanvasArray(uint32_t source[], int sW, int sH, uint32_t target[], int tW, int tH, int mX, int mY) {
	for (int cY = 0; cY < sH; cY++)
	{
		for (int cX = 0; cX < sW; cX++)
		{
			for (int mmX = 0; mmX < mX; mmX++)
			{
				for (int mmY = 0; mmY < mY; mmY++)
				{
					target[(cX*mX+mmX)+(cY*mY+mmY)*tW] = source[cX+cY*sW];
					// printf("%d,%d,%lu|", mmX, mmY, source[cX+cY*sW]);
				}
				
			}
			// printf("\r");
			
		}
	}
	
}

void putInArray(uint32_t source[], int sW, int sH, uint32_t target[], int tW, int tH, int x, int y) {

	for (int cY = 0; cY < sH; cY++)
	{
		for (int cX = 0; cX < sW; cX++)
		{
			target[(cX+x)+(cY+y)*tW] = source[cX+cY*sW];

		}
		
	}
	
}

void calculateCGOL(uint32_t source[], uint32_t target[], int x, int y) {
	int totalNeighbors = 0;
	for (int cY = 0; cY < y; cY++)
	{
		for (int cX = 0; cX < x; cX++)
		{
			// Calculate the total neighors
			for (int nY = -1; nY <= 1; nY++)
			{
				for (int nX = -1; nX <= 1; nX++)
				{
					if (source[(cX + nX)+(cY + nY)*x] == bignum) {
						totalNeighbors += 1;
					}
				}
				
			}

			target[cX+cY*x] = 0;
			if (source[cX+cY*x] == bignum) {
				totalNeighbors -= 1;
				if (totalNeighbors == 3 | totalNeighbors == 2) {
					target[cX+cY*x] = bignum;
				} else {
					target[cX+cY*x] = 0;
				}
			} else {
				if (totalNeighbors == 3) {
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
void HandleButton( int x, int y, int button, int bDown ) {

 }	
void HandleMotion( int x, int y, int mask ) {

}
void HandleDestroy() { }



int buttonDown = 0;

int loop = 0;
int cvX = 0;
int cvY = 0;
int main() {
    CNFGSetup( "Hello World", windowX, windowY );
	putInArray(inputCanvas, 32, 32, canvasA, simCanvasX, simCanvasY, 0 , 0);
	putInArray(inputCanvas, 32, 32, canvasA, simCanvasX, simCanvasY, 32 , 32);
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
		// if (switchCanvas == 0) {
		// 	CNFGBlitImage(canvasB, 0, 0, simCanvasX, simCanvasY);
		// } else {

		// 	CNFGBlitImage(canvasA, 0, 0, simCanvasX, simCanvasY);
		// }

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