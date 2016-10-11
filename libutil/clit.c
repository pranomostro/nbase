#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../util.h"

void cliterate(size_t argc, char** argv, FILE* input, void (*itf)(char*, size_t))
{
	char* line, * rp;
	size_t linelen, i;

	if(argc>1)
		for(i=1; i<argc; i++)
			itf(argv[i], strlen(argv[i]));
	else
	{
		line=calloc((linelen=BUFSIZ), sizeof(char));
		while((rp=nalread(line, &linelen, input))!=NULL)
		{
			line=rp;
			itf(line, linelen);
		}
		free(line);
	}
}
