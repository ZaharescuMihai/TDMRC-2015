#include "ElementalDust.h"
#include "QuickSort.h"

ElementalDust::ElementalDust()
{
	partiles_prt = NULL;
	nr_particles_int = 0;
}

ElementalDust::~ElementalDust()
{
	clear();
}

void ElementalDust::clear()
{
	if (partiles_prt)
		delete[] partiles_prt;

	partiles_prt = NULL;
	nr_particles_int = 0;
}

struct compare
{
	bool operator() (particle &a, particle &b)
	{
		if ( a.x != b.x )
		{
			return a.x < b.x;
		}
		else
		{
			return a.y < b.y;
		}
		return a.x < b.x;
	}
};

void ElementalDust::sortParticles()
{
	QuickSort<particle, compare>::quicksort(partiles_prt, nr_particles_int);
}

void ElementalDust::import(KImage *import, float multiplicator)
{
	clear();

	//read at most 255x255 from the image size
	int width = import->GetWidth();
	int height = import->GetHeight();

	if(width>255)
		width = 255;
	if(height>255)
		height = 255;

	//see how many particles we need
	nr_particles_int = 0;
	import ->BeginDirectAccess();
	unsigned int crt_color_uint;
	for (int j=0; j < height; j++)
		for (int i=0; i < width; i++)
		{
			crt_color_uint = import->Get8BPPPixel(i, j);
			nr_particles_int += crt_color_uint;
		}
	nr_particles_int = (int)(nr_particles_int * multiplicator);

	//place particles
	partiles_prt = new particle[nr_particles_int];

	unsigned int index=0;
	particle crt_particle;

	for (int j=0; j < height; j++)
		for (int i=0; i < width; i++)
		{
			crt_color_uint = (unsigned int)(import->Get8BPPPixel(i, j) * multiplicator);

			for (unsigned int k=0; k<crt_color_uint ; k++)
			{
				crt_particle.x = fixed_float(i + ((float)(rand()%1000))/1000);
				crt_particle.y = fixed_float(j + ((float)(rand()%1000))/1000);

				partiles_prt[index] = crt_particle;

				index++;
			}
		}

	import ->EndDirectAccess();
}

void ElementalDust::import(char *file_name)
{
	clear();

	FILE *fin;
	fopen_s(&fin, file_name, "rb");

	nr_particles_int = 0;

	fseek(fin, 0L, SEEK_END);
	unsigned int file_size_uint = ftell(fin);
	fseek(fin, 0L, SEEK_SET);

	nr_particles_int = file_size_uint/2;
	partiles_prt = new particle[nr_particles_int];

	unsigned char buffer[4];


	//TO DO: optimize: use buffer
	for(int i=0; i<this->nr_particles_int; i++)
	{
		fread(buffer, 4, 1, fin);

		partiles_prt[i].x = fixed_float(buffer[0], buffer[1]);
		partiles_prt[i].y = fixed_float(buffer[2], buffer[3]);
	}

	fclose (fin);
}

void ElementalDust::import(void *file_contents, size_t size)
{
	clear();

	nr_particles_int = size/4;
	partiles_prt = new particle[nr_particles_int];

	unsigned char *contents_uchar = (unsigned char*)file_contents;

	//TO DO: optimize: use buffer
	for(int i=0; i<this->nr_particles_int; i++)
	{
		partiles_prt[i].x = fixed_float(contents_uchar[i*4 + 0], contents_uchar[i*4 + 1]);
		partiles_prt[i].y = fixed_float(contents_uchar[i*4 + 2], contents_uchar[i*4 + 3]);
	}
}

void ElementalDust::SaveAs(char *file_name)
{
	FILE *fout;
	fopen_s(&fout, file_name, "wb");
	unsigned char buffer[4];

	//TO DO: optimize: use buffer
	for(int i=0; i<this->nr_particles_int; i++)
	{
		buffer[0] = partiles_prt[i].x.getIntegerBits();
		buffer[1] = partiles_prt[i].x.getFractionalBits();
		buffer[2] = partiles_prt[i].y.getIntegerBits();
		buffer[3] = partiles_prt[i].y.getFractionalBits();
		fwrite(buffer, sizeof(unsigned short), 2, fout);
	}

	fclose (fout);
}

void ElementalDust::SaveAs(KImage *import, float multiplicator)
{
	int width = import->GetWidth();
	int height = import->GetHeight();

	import->BeginDirectAccess();
	for (int j=0; j < height; j++)
		for (int i=0; i < width; i++)
		{
			import->Put8BPPPixel(i, j, 0);
		}

	int x, y;
	unsigned char crt_color_uchar;
	for(int i=0; i<this->nr_particles_int; i++)
	{
		float x_f = partiles_prt[i].x.getFloat();
		x = (int)(partiles_prt[i].x.getFloat() * multiplicator);
		y = (int)(partiles_prt[i].y.getFloat() * multiplicator);

		if(x>=width || y>=height)
			continue;

		crt_color_uchar = import->Get8BPPPixel(x, y);
		if(crt_color_uchar<254)
			import->Put8BPPPixel(x, y, crt_color_uchar+1);
	}

	import->EndDirectAccess();
}

ElementalDust& ElementalDust::operator= (ElementalDust b_ed)
{
	clear();

	nr_particles_int = b_ed.nr_particles_int;

	if(b_ed.partiles_prt)
	{
		partiles_prt = new particle[nr_particles_int];
		memcpy(partiles_prt, b_ed.partiles_prt, sizeof(particle)*nr_particles_int);
	}
	else
	{
		partiles_prt = NULL;
	}
	
	return *this;
}

bool ElementalDust::operator==(ElementalDust &b_flt)
{
	if(nr_particles_int != b_flt.nr_particles_int)
		return false;

	for( int i=0; i<nr_particles_int; i++)
		if((partiles_prt[i].x != b_flt.partiles_prt[i].x) || (partiles_prt[i].y != b_flt.partiles_prt[i].y))
			return false;

	return true;
}

bool ElementalDust::operator!=(ElementalDust &b_flt)
{
	return !(*this == b_flt);
}