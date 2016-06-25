#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "arg.h"
#include "deps/libzahl/zahl.h"
#include "deps/liblist/list.h"

static void usage(char* progname)
{
	fprintf(stderr, "%s [-N LIM]\n", progname);
	exit(1);
}

int main(int argc, char** argv)
{
	char* argv0, * resstr;
	size_t ressize;
	unsigned long long i, j, nflag, count;
	z_t res, op1, op2;

	nflag=0;
	ressize=65536;
	resstr=calloc(ressize, sizeof(char));

	ARGBEGIN
	{
	case 'n':
		nflag=atoi(EARGF(usage(argv0)));
		break;
	default:
		usage(argv0);
	} ARGEND;

	jmp_buf env;

	if(setjmp(env))
	{
		perror(0);
		zunsetup();
		return 1;
	}

	zsetup(env);

	zinit(res);
	zinit(op1);
	zinit(op2);

	for(i=2, count=1;; i++)
		for(j=2; j<=i; j++)
		{
			zseti(op1, i);
			zseti(op2, j);
			zpow(res, op1, op2);
			zseti(op1, i);
			zseti(op2, j);
			zpow(op1, op2, op1);
			zadd(res, op1, res);

			if(zstr_length(res, 10)>ressize)
			{
				ressize*=2;
				resstr=realloc(resstr, ressize);
			}

			resstr=zstr(res, resstr, ressize);
			printf("%s %llu %llu\n", resstr, i, j);
			if(nflag>0&&count++>=nflag)
				goto end;
		}
	end:

	zfree(res);
	zfree(op1);
	zfree(op2);
	zunsetup();

	free(resstr);

	return 0;
}
