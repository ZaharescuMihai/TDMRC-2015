#include "StudentCodec.h"
#include "stdafx.h"

void shuffle(unsigned int *arr, size_t n)
{
    if (n > 1) 
    {
        size_t i, j;
		unsigned int t;
        for (i = 0; i < n - 1; i++) 
        {
          j = rand();
          t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

size_t StudentCodec::compress(void *in, size_t in_size, void **out)
{
	//TO DO: your compression code
	*out = new unsigned char[in_size];
	memcpy(*out, in, in_size);

	shuffle((unsigned int*)(*out), in_size/sizeof(unsigned int));

	return in_size;
}

size_t StudentCodec::decompress(void *in, size_t in_size, void **out)
{
	//TO DO: your decompression code
	*out = new unsigned char[in_size];
	memcpy(*out, in, in_size);

	return in_size;
}
