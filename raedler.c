#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "arg.h"
#include "deps/libzahl/zahl.h"

const int CAP=65536;

typedef struct raedler
{
	unsigned short pos;
	z_t val;
} raedler;

static void usage(char* progname)
{
	fprintf(stderr, "%s [-N LIM]\n", progname);
	exit(1);
}

void pbw(z_t res, short i, short j)
{
	z_t op1, op2;
	zinit(op1);
	zinit(op2);

	zseti(op1, i);
	zseti(op2, j);

	zpow(res, op1, op2);
	zseti(op1, i);
	zseti(op2, j);
	zpow(op1, op2, op1);
	zadd(res, op1, res);

	zfree(op1);
	zfree(op2);
}

int main(int argc, char** argv)
{
	char* argv0, * resstr;
	size_t ressize;
	unsigned long long count, nflag;
	unsigned short i, low, high, smallest;
	raedler res[CAP];

	nflag=0;
	ressize=CAP;
	resstr=calloc(ressize, sizeof(char));

	res[2].pos=2;
	zinit(res[2].val);
	zseti(res[2].val, 8);

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

	for(low=high=2, count=1; high<CAP; count++)
	{
		for(i=smallest=low; i<=high; i++)
			if(zcmp(res[i].val, res[smallest].val)<0)
				smallest=i;
		if(zstr_length(res[smallest].val, 10)>ressize)
		{
			ressize*=2;
			resstr=realloc(resstr, ressize);
		}
		resstr=zstr(res[smallest].val, resstr, ressize);
		printf("%s %d %d\n", resstr, smallest, res[smallest].pos);

		res[smallest].pos++;
		if(res[low].pos>low)
			low++;
		if(smallest==high)
		{
			high++;
			res[high].pos=2;
			zinit(res[high].val);
			pbw(res[high].val, res[high].pos, high);
		}
		pbw(res[smallest].val, res[smallest].pos, smallest);

		if(nflag!=0&&count>=nflag)
			break;
	}

	for(i=0; i<=high; i++)
		zfree(res[i].val);

	zunsetup();

	free(resstr);

	return 0;
}
