#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "libzahl/zahl.h"
#include "libutil/util.h"

void collatz(char* str, size_t len)
{
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

	cliterate(argc, argv, stdin, collatz);

	zunsetup();

	return 0;
}
