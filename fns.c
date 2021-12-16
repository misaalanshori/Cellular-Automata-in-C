#include "fns.h"
void upscaleCanvasArray(uint32_t source[], int sW, int sH, uint32_t target[], int tW, int tH, int mX, int mY) // Not sure what this kind of image scaling this is called, it just duplicates each pixels multiple times
{
    // Loop through the entire source array
	for (int cY = 0; cY < sH; cY++)
	{
		for (int cX = 0; cX < sW; cX++)
		{
            // Loop through and make a resized pixel
			for (int mmX = 0; mmX < mX; mmX++)
			{
				for (int mmY = 0; mmY < mY; mmY++)
				{
					target[(cX*mX+mmX)+(cY*mY+mmY)*tW] = source[cX+cY*sW];
				}
			}
		}
	}
}


void putInArray(uint32_t source[], int sW, int sH, uint32_t target[], int tW, int tH, int x, int y) // Puts the source array on the target array, I think its called "bliting" but I wasn't sure
{
	for (int cY = 0; cY < sH; cY++)
	{
		for (int cX = 0; cX < sW; cX++)
		{
			target[(cX+x)+(cY+y)*tW] = source[cX+cY*sW];
		}
	}
}