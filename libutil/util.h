/*
	utility functions
*/

char* nalread(char* in, size_t* len, FILE* input);
void* nalgrow(void* data, size_t old, size_t new);
void cliterate(int argc, char** argv, FILE* input, void (*itf)(char*, size_t));
