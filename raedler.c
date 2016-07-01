#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "arg.h"
#include "libnal/nal.h"
#include "libzahl/zahl.h"

const int CAP=4;

z_t op1, op2;

typedef struct raedler
{
	unsigned short pos;
	z_t val;
} raedler;

static void usage(char* progname)
{
	fprintf(stderr, "%s [-n LIM]\n", progname);
	exit(1);
}

void pbw(z_t res, short i, short j)
{
	zseti(op1, i);
	zseti(op2, j);

	zpow(res, op1, op2);
	zseti(op1, i);
	zseti(op2, j);
	zpow(op1, op2, op1);
	zadd(res, op1, res);
}

int main(int argc, char** argv)
{
	char* argv0, * resstr;
	size_t i, ressize, resstrsize, low, high, smallest;
	unsigned long long count, nflag;
	jmp_buf env;
	raedler* res;

	nflag=0;
	ressize=resstrsize=CAP;

	res=calloc(ressize, sizeof(raedler));
	resstr=calloc(resstrsize, sizeof(char));

	if(setjmp(env))
	{
		perror(0);
		zunsetup();
		return 1;
	}

	zsetup(env);

	res[2].pos=2;
	zinit(res[2].val);
	zseti(res[2].val, 8);

	zinit(op1);
	zinit(op2);

	ARGBEGIN
	{
	case 'n':
		nflag=atoi(EARGF(usage(argv0)));
		break;
	default:
		usage(argv0);
	} ARGEND;

	for(low=high=2, count=1; nflag==0||count<=nflag; count++)
	{
		for(i=smallest=low; i<=high; i++)
			if(zcmp(res[i].val, res[smallest].val)<0)
				smallest=i;

		if(zstr_length(res[smallest].val, 10)>=resstrsize-1)
		{
			resstr=resize(resstr, resstrsize*sizeof(char), 2*resstrsize*sizeof(char));
			resstrsize*=2;
		}
		resstr=zstr(res[smallest].val, resstr, ressize);
		printf("%s %ld %ld\n", resstr, smallest, res[smallest].pos);

		res[smallest].pos++;

		if(smallest==high)
		{
			high++;
			res[high].pos=2;
			zinit(res[high].val);
			pbw(res[high].val, res[high].pos, high);
		}

		pbw(res[smallest].val, res[smallest].pos, smallest);

		if(res[low].pos>low)
			low++;

		if(high>=ressize-1)
		{
			res=resize(res, ressize*sizeof(raedler), 2*ressize*sizeof(raedler));
			ressize*=2;
		}
	}

	for(i=low; i<=high; i++)
		zfree(res[i].val);

	zfree(op1);
	zfree(op2);

	zunsetup();

	free(res);
	free(resstr);

	return 0;
}
