/*
	utility functions
*/

/*
	This line is incompatible with sbase's struct line.
	Just in case you were wondering.
*/

struct line
{
	char* data;
	size_t len;
	size_t cap;
};

char* nalread(char* in, size_t* len, FILE* input);
void* nalgrow(void* data, size_t old, size_t new);
void cliterate(size_t argc, char** argv, FILE* input, void (*itf)(char*, size_t));
