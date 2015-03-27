#include "StudentCodec.h"
#include "stdafx.h"


size_t StudentCodec::compress(void *in, size_t in_size, void **out)
{
	//TO DO: your compression code
	*out = new unsigned char[in_size];
	memcpy(*out, in, in_size);

	return in_size;
}

size_t StudentCodec::decompress(void *in, size_t in_size, void **out)
{
	//TO DO: your decompression code
	*out = new unsigned char[in_size];
	memcpy(*out, in, in_size);

	return in_size;
}
