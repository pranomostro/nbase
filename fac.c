#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

#include "zahl.h"
#include "util.h"

z_t op1, op2, op3;
struct line result;
char* argv0;

void fac(char* str, size_t len)
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

	printf("%s: ", str);

	zsets(op1, str);
	zset(op2, op3);

	while(zcmpi(op1, 1))
	{
		zmul(op2, op2, op1);
		zsub(op1, op1, op3);
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
	zseti(op3, 1);

	cliterate(argc, argv, stdin, fac);

	zfree(op1);
	zfree(op2);
	zfree(op3);
	zunsetup();
	free(result.data);

	return 0;
}
