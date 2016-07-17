#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "arg.h"
#include "libutil/util.h"
#include "libzahl/zahl.h"

const int CAP=65536;

typedef struct raedler
{
	size_t pos;
	z_t val;
} raedler;

static void usage(char* progname)
{
	fprintf(stderr, "%s [-l LIM]\n", progname);
	exit(1);
}

void pbw(z_t res, size_t i, size_t j)
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
	size_t i, low, high, smallest;
	unsigned long long count, nflag;
	jmp_buf env;
	raedler res[CAP];

	nflag=0;

	resstr=calloc(CAP, sizeof(char));

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
	case 'l':
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
		resstr=zstr(res[smallest].val, resstr, CAP);

		printf("%s %li %li\n", resstr, smallest, res[smallest].pos);

		if(res[low].pos>=low&&smallest==low)
		{
			zfree(res[low].val);
			low++;
		}
		if(res[smallest].pos<smallest&&smallest>=low)
		{
			res[smallest].pos++;
			pbw(res[smallest].val, smallest, res[smallest].pos);
		}
		if(res[high].pos!=2||high==2)
		{
			high++;
			res[high].pos=2;
			zinit(res[high].val);
			pbw(res[high].val, high, res[high].pos);
		}
	}

	zunsetup();

	free(resstr);

	return 0;
}
