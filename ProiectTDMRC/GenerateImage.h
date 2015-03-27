#include "Direct_Access_Image.h"

class GenerateImage
{
public:
	/**
	Reads the image's dimensions and draws in the image a perlin noise map.
	@param result the image on which noise will be generated.
	*/
	static void perlinNoise(KImage *result);
};