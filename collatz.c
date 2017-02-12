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
		weprintf("could not parse input line %s as number.\n", str);
		return;
	}
	if(zcmpi(op1, 1)==-1)
	{
		weprintf("the sequence only works with integers bigger than 0.\n");
		return;
	}

	while(zcmpi(op1, 1))
	{
		resultsize=zstr_length(op1, 10);
		if(resultsize+1>result.cap)
		{
			result.data=ereallocarray(result.data, resultsize+512, sizeof(result.data[0]));
			result.cap=resultsize+512;
		}
		result.data=zstr(op1, result.data, result.cap);
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
		zperror(argv0);
		zunsetup();
		exit(1);
	}

	result.cap=4096;
	result.data=ecalloc(result.cap, sizeof(char));

	zsetup(env);
	zinit(op1), zinit(op2);

	cliterate(argc, argv, stdin, collatz);

	zfree(op1), zfree(op2);
	zunsetup();
	free(result.data);

	return 0;
}
