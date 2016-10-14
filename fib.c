#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

#include "zahl.h"
#include "util.h"

z_t op1, op2, op3, op4, op5;
struct line result;
char* argv0;

void fib(char* str, size_t len)
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
		weprintf("factorial only works with integers bigger than 0.\n");
		return;
	}

	zsets(op1, str);
	zseti(op2, 1);
	zseti(op3, 1);

	while(zcmpi(op1, 2)==1)
	{
		zset(op5, op2);
		zadd(op2, op2, op3);
		zset(op3, op5);
		zsub(op1, op1, op4);
	}
	resultsize=zstr_length(op2, 10);
	if(resultsize+1>result.cap)
	{
		result.data=ereallocarray(result.data, resultsize+512, sizeof(result.data[0]));
		result.cap=resultsize+512;
	}
	result.data=zstr(op2, result.data, result.cap);
	printf("%s\n", result.data);
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
	zinit(op3);
	zinit(op4);
	zinit(op5);
	zseti(op4, 1);

	cliterate(argc, argv, stdin, fib);

	zfree(op1);
	zfree(op2);
	zfree(op3);
	zfree(op4);
	zfree(op5);
	zunsetup();
	free(result.data);

	return 0;
}
