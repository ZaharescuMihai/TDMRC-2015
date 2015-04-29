#include "stdafx.h"

#include "StudentCodec.h"
#include "utilities.h"

#include "QuickSort.h"
#include "GenerateImage.h"
#include "ElementalDust.h"
#include "StudentCodec.h"

int main(int argc, char *argv[])
{
	if(argc != 4)
	{
		std::cout<<"Usage: input_file {compress | decompress} output_file. Arguments offered:\n";

		for(int i=0;i<argc;i++)
			std::cout<<i<<": "<<argv[i]<<"\n";

		exit(-1);
	}

	void *input_file_contents, *output_file_contents;
	size_t input_file_size, output_file_size;

	try	{input_file_size = getFileContents(argv[1], &input_file_contents);}
	catch (std::string e) {std::cerr<<e.c_str(); exit(-1);}

	if(_strcmpi(argv[2], "compress") == 0)
		output_file_size = StudentCodec::compress(input_file_contents, input_file_size, &output_file_contents);
	else if(_strcmpi(argv[2], "decompress") == 0)
		output_file_size = StudentCodec::decompress(input_file_contents, input_file_size, &output_file_contents);
	else
	{
		std::cout<<"Unknown parameter: "<<argv[2];

		exit(-1);
	}

	try	{writeFileContents(argv[3], output_file_contents, output_file_size);}
	catch (std::string e) {std::cout<<e.c_str(); exit(-1);}


	return 0;
}