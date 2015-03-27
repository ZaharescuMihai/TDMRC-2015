class StudentCodec
{
public:
	static size_t compress(void *in, size_t in_size, void **out);

	static size_t decompress(void *in, size_t in_size, void **out);
};
