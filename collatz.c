#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

#include "libzahl/zahl.h"
#include "libutil/util.h"

z_t op;

void collatz(char* str, size_t len)
{
	char* nl=strchr(str, '\n');
	if(nl!=NULL)
		*nl='\0';

	if(zsets(op, str)<0)
		fprintf(stderr, "collatz: could not parse input line %s as number.\n", str);
}

int main(int argc, char** argv)
{
	jmp_buf env;

	if(setjmp(env))
	{
		perror(0);
		zunsetup();
		return 1;
	}

	zsetup(env);
	zinit(op);

	cliterate(argc, argv, stdin, collatz);

	zfree(op);
	zunsetup();

	return 0;
}
