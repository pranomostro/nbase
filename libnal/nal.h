/*
	nal-no arbitrary limits
*/

#define RESIZEFACTOR 2

char* nalread(char* in, size_t* len, FILE* input);
void* resize(void* data, size_t old, size_t new);
