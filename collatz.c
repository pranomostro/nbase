#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

#include "zahl.h"
#include "util.h"

z_t op1, op2;
struct line result;
char* argv0;

void collatz(char* str, size_t len)
{
	size_t resultsize;
	char* nl=strchr(str, '\n');

	if(nl!=NULL)
		*nl='\0';

	if(zsets(op1, str)<0)
	{
		fprintf(stderr, "%s: could not parse input line %s as number.\n", argv0, str);
		return;
	}
	if(zcmpi(op1, 1)==-1)
	{
		fprintf(stderr, "%s: the sequence only works with integers bigger than 0.\n", argv0);
		return;
	}

	while(zcmpi(op1, 1))
	{
		resultsize=zstr_length(op1, 10);
		result.data=zstr(op1, result.data, result.cap);
		if(resultsize+1>result.cap)
		{
			result.data=nalgrow(result.data, result.cap, resultsize+512);
			result.cap=resultsize+512;
		}
		printf("%s ", result.data);

		if(zeven(op1))
		{
			zseti(op2, 2);
			zdiv(op1, op1, op2);
		}
		else
		{
			zseti(op2, 3);
			zmul(op1, op1, op2);
			zseti(op2, 1);
			zadd(op1, op1, op2);
		}
	}
	printf("1\n");
}

int main(int argc, char* argv[])
{
	jmp_buf env;
	argv0=*argv;

	if(setjmp(env))
	{
		perror(0);
		zunsetup();
		exit(1);
	}

	result.cap=4096;
	result.data=calloc(result.cap, sizeof(char));

	zsetup(env);
	zinit(op1);
	zinit(op2);

	cliterate(argc, argv, stdin, collatz);

	zfree(op1);
	zfree(op2);
	zunsetup();

	return 0;
}
