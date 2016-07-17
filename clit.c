#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "libnal/nal.h"

void cliterate(int argc, char** argv, FILE* input, void (*itf)(char*, size_t))
{
	char* line;
	size_t linelen;

	if(argc>=1)
		while(argc-->0)
			itf(argv[argc], strlen(argv[argc]));
	else
	{
		line=calloc((linelen=LINE_MAX), sizeof(char));
		while((line=nalread(line, &linelen, input))!=NULL)
			itf(line, linelen);
	}
}
