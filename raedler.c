#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "arg.h"
#include "libnal/nal.h"
#include "libzahl/zahl.h"

const int CAP=4;

typedef struct raedler
{
	size_t pos;
	z_t val;
} raedler;

static void usage(char* progname)
{
	fprintf(stderr, "%s [-n LIM]\n", progname);
	exit(1);
}

void pbw(z_t res, size_t i, size_t j)
{
	z_t op1, op2;

	zinit(op1);
	zinit(op2)

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
		printf("%s %li %li\n", resstr, smallest, res[smallest].pos);

		res[smallest].pos++;
		if(smallest>=high&&res[high].pos!=2)
		{
			high++;
			res[high].pos=2;
			zinit(res[high].val);
			fprintf(stderr, "initialized res[%li].\n", high);
			fprintf(stderr, "high: computing with %li, %li.\n", high, res[high].pos);
			pbw(res[high].val, high, res[high].pos);
		}

		if(res[smallest].pos<smallest)
		{
			res[smallest].pos++;
			fprintf(stderr, "nonhigh: computing with %li, %li.\n", smallest, res[smallest].pos);
			pbw(res[smallest].val, smallest, res[smallest].pos);
		}

		if(res[low].pos>low)
		{
			zfree(res[low].val);
			low++;
		}

		if(high>=ressize-1)
		{
			res=resize(res, ressize*sizeof(raedler), 2*ressize*sizeof(raedler));
			ressize*=2;
		}
	}

	for(i=low; i<=high; i++)
		zfree(res[i].val);

	zunsetup();

	free(res);
	free(resstr);

	return 0;
}
