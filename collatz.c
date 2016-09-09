#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <setjmp.h>

#include "zahl.h"
#include "util.h"

z_t op1, op2;

void collatz(char* str, size_t len)
{
	char* nl=strchr(str, '\n');
	char* resstr=NULL;

	if(nl!=NULL)
		*nl='\0';

	if(zsets(op1, str)<0)
		fprintf(stderr, "collatz: could not parse input line %s as number.\n", str);
	if(zcmpi(op1, 1)==-1)
		fprintf(stderr, "collatz: negative numbers are not allowed at the moment.\n");

	while(zcmpi(op1, 1))
	{
		printf("%s ", (resstr=zstr(op1, NULL, 0)));
		free(resstr);
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
	zinit(op1);
	zinit(op2);

	cliterate(argc, argv, stdin, collatz);

	zfree(op1);
	zfree(op2);
	zunsetup();

	return 0;
}
