#include "stdafx.h"


#include "Direct_Access_Image.h"
#include "GenerateImage.h"
#include "ElementalDust.h"

#include "StudentCodec.h"

#include "QuickSort.h"


size_t getFileContents(char *file_name, void **file_contents)
{
	FILE *fin;
	fopen_s(&fin, file_name, "rb");

	size_t file_size_uint = 0;

	fseek(fin, 0L, SEEK_END);
	file_size_uint = ftell(fin);
	fseek(fin, 0L, SEEK_SET);

	*file_contents = new unsigned char[file_size_uint];

	fread(*file_contents, sizeof(unsigned char), file_size_uint, fin);

	fclose (fin);

	return file_size_uint;
}

void writeFileContents(char *file_name, void *file_contents, size_t file_size_uint)
{
	FILE *fout;
	fopen_s(&fout, file_name, "wb");

	fwrite(file_contents, 1, file_size_uint, fout);

	fclose (fout);
}

/*const char* Compare(void *original_data_p, size_t original_size, void *decompressed_p, size_t decompressed_size)
{
	ElementalDust original, decompressed;

	original.import(original_data_p, original_size);
	original.sortParticles();
	decompressed.import(decompressed_p, decompressed_size);
	decompressed.sortParticles();

	if(original != decompressed)
		return "The buffer contents differ.\n";
	
	return "The buffers are identical.\n";
}*/

const char* Compare(void *original_data_p, size_t original_size, void *decompressed_p, size_t decompressed_size)
{
	unsigned int *original_intp = (unsigned int*)original_data_p;
	unsigned int *decompressed_intp = (unsigned int*)decompressed_p;

	if(original_size != decompressed_size)
		return "The buffer sizes differ.\n";

	int nr_ints = original_size/sizeof(unsigned int);

	QuickSort<unsigned int>::quicksort(original_intp, nr_ints);
	QuickSort<unsigned int>::quicksort(decompressed_intp, nr_ints);

	for(int i=0; i<nr_ints; i++)
		if(original_intp[i] != decompressed_intp[i])
			return "The buffer contents differ.\n";
	
	return "The buffers are identical.\n";
}

void test()
{
	//set image properties
	float km=4;	//scaling factor for the putput image (sqrt(km))
	int dim = 32;	//original image size

	//generate a image
	std::cout<<"Generating perlin_noise.tif ...\n";
	KImage *perlin_noise_img = new KImage(dim, dim, 8);
	GenerateImage::perlinNoise(perlin_noise_img);
	perlin_noise_img->SaveAs("perlin_noise.tif");
	delete perlin_noise_img;
	std::cout<<"DONE: Generating perlin_noise.tif\n\n";

	//open a image and convert it to edp
	std::cout<<"Converting perlin_noise.tif to perlin_noise.edp ...\n";
	KImage *dustmap_img = new KImage("perlin_noise.tif");
	ElementalDust ed = ElementalDust();
	ed.import(dustmap_img, km);
	ed.SaveAs("perlin_noise.edp");
	ed = ElementalDust();
	delete dustmap_img;
	std::cout<<"DONE: Converting perlin_noise.tif to perlin_noise.edp\n\n";

	//open an edp and compress to edpc
	std::cout<<"Compressing perlin_noise.edp to perlin_noise.edpc ...\n";
	void *original_data;
	size_t original_size;
	void *compressed;
	size_t compressed_size;
	original_size = getFileContents("perlin_noise.edp", &original_data);
	compressed_size = StudentCodec::compress(original_data, original_size, &compressed);
	writeFileContents("perlin_noise.edpc", compressed, compressed_size);
	delete[] compressed;
	delete[] original_data;
	std::cout<<"DONE: Compressing perlin_noise.edp to perlin_noise.edpc ...\n\n";

	//Open an edpc and decompress to edp
	std::cout<<"Decompressing perlin_noise.edpc to perlin_noise_decompressed.edp ...\n";
	void *decompressed;
	size_t decompressed_size;
	compressed_size = getFileContents("perlin_noise.edpc", &compressed);
	decompressed_size = StudentCodec::decompress(compressed, compressed_size, &decompressed);
	writeFileContents("perlin_noise_decompressed.edp", decompressed, decompressed_size);
	delete[] decompressed;
	delete[] compressed;
	std::cout<<"DONE: Decompressing perlin_noise.edpc to perlin_noise_decompressed.edp ...\n\n";
	
	//compare the two files
	std::cout<<"Compareing perlin_noise.edp with perlin_noise_decompressed.edp ...\n";
	original_size = getFileContents("perlin_noise.edp", &original_data);
	decompressed_size = getFileContents("perlin_noise_decompressed.edp", &decompressed);
	std::cout<<Compare(original_data, original_size, decompressed, decompressed_size);
	delete[] original_data;
	delete[] decompressed;
	std::cout<<"DONE: Compareing perlin_noise.edp with perlin_noise_decompressed.edp ...\n\n";

	//open the decompressed edpc and save it as an image
	std::cout<<"Converting perlin_noise_decompressed.edp to perlin_noise_decompressed.tif ...\n";
	ed.import("perlin_noise_decompressed.edp");
	KImage *perlin_noise_km_img = new KImage((int)(dim*sqrt(km)), (int)(dim*sqrt(km)), 8);
	ed.SaveAs(perlin_noise_km_img, sqrt(km));
	perlin_noise_km_img->SaveAs("perlin_noise_decompressed.tif");
	delete perlin_noise_km_img;
	ed = ElementalDust();
	std::cout<<"DONE: Converting perlin_noise_decompressed.edp to perlin_noise_decompressed.tif ...\n\n";
}

/*
struct compareX
{
	bool operator() (int &a, int &b)
	{
		return a > b;
	}
};

void test_sort()
{
	int ra[100];

	for(int i=0;i<100;i++)
		ra[i] = rand()%100;

	QuickSort<int, compareX>::quicksort(ra, 100);

	for(int i=0;i<100;i++)
		std::cout<<ra[i]<<"\t";
}
*/

int main()
{
	test();

	//test_sort();

	system("pause");



	return 0;
}