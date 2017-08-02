#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

#include "zahl.h"
#include "util.h"

z_t in;
char* argv0;

void isprime(char* str, size_t len)
{
	char* nl=strchr(str, '\n');

	if(nl!=NULL)
		*nl='\0';

	if(zsets(in, str)<0)
	{
		weprintf("could not parse input line %s as number.\n", str);
		return;
	}

	switch(zptest(NULL, in, 10)) /* 10 taken from rosettacode, shady? */
	{
	case NONPRIME:
		printf("%s: nonprime\n", str);
		break;
	case PROBABLY_PRIME:
		printf("%s: probably prime\n", str);
		break;
	case PRIME:
		printf("%s: prime\n", str);
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[])
{
	jmp_buf env;
	argv0=*argv;

	if(setjmp(env))
	{
		zperror(argv0);
		zunsetup();
		exit(1);
	}

	zsetup(env);
	zinit(in);

	cliterate(argc, argv, stdin, isprime);

	zfree(in);
	zunsetup();

	return 0;
}
