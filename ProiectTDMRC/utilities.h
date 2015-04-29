#ifndef UTILITIESH
#define UTILITIESH

size_t getFileContents(char *file_name, void **file_contents);

void writeFileContents(char *file_name, void *file_contents, size_t file_size_uint);

const char* Compare(void *original_data_p, size_t original_size, void *decompressed_p, size_t decompressed_size);

void shuffle(unsigned int *arr, size_t n);

void test();

#endif