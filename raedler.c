#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "arg.h"
#include "libzahl/zahl.h"

const int CAP=65536;

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
	size_t ressize;
	unsigned long long count, nflag;
	unsigned short i, low, high, smallest;
	jmp_buf env;
	raedler res[CAP];

	nflag=0;
	ressize=CAP;
	resstr=(char*)calloc(ressize, sizeof(char));

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

	for(low=high=2, count=1; high<CAP; count++)
	{
		for(i=smallest=low; i<=high; i++)
			if(zcmp(res[i].val, res[smallest].val)<0)
				smallest=i;
		resstr=zstr(res[smallest].val, resstr, ressize);
		printf("%s %d %d\n", resstr, smallest, res[smallest].pos);

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
		{
			zfree(res[low].val);
			low++;
		}

		if(nflag!=0&&count>=nflag)
			break;
	}

	for(i=low; i<=high; i++)
		zfree(res[i].val);

	zfree(op1);
	zfree(op2);

	zunsetup();

	free(resstr);

	return 0;
}
