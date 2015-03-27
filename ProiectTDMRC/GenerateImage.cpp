#include "GenerateImage.h"
#include "simplexnoise1234.h"

void GenerateImage::perlinNoise(KImage *result)
{
	int w, h;
	w = result->GetWidth();
	h = result->GetHeight();

	result->BeginDirectAccess();

	unsigned char crt_color;

	for(int j=0;j<h;j++)
		for(int i=0;i<w;i++)
		{
			crt_color = (unsigned char) ( (SimplexNoise1234::noise(((float)i)/w, ((float)j)/h) + 1.0f) / 2.0f * 255.0f );
			result->Put8BPPPixel(i, j, crt_color);
		}

	result->EndDirectAccess();
}