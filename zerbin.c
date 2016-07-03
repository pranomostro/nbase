#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>

#include "arg.h"
#include "libnal/nal.h"
#include "libzahl/zahl.h"

const int CAP=65536;

typedef struct zerbin
{
	size_t pos;
	z_t val;
} zerbin;

static void usage(char* progname)
{
	fprintf(stderr, "%s [-n LIM]\n", progname);
	exit(1);
}

void pbw(z_t res, size_t i, size_t j)
{
	z_t op1, op2, op3;

	zinit(op1);
	zinit(op2);
	zinit(op3);

	zseti(op1, i);
	zseti(op2, j);
	zseti(op3, 2);

	zpow(op1, op1, op3);
	zpow(op2, op2, op3);
	zsub(res, op1, op2);

	zfree(op1);
	zfree(op2);
	zfree(op3);
}

int main(int argc, char** argv)
{
	char* argv0, * resstr;
	size_t i, low, high, smallest;
	unsigned long long count, nflag;
	jmp_buf env;
	zerbin res[CAP];

	nflag=0;
	resstr=calloc(CAP, sizeof(char));

	if(setjmp(env))
	{
		perror(0);
		zunsetup();
		return 1;
	}

	zsetup(env);

	res[3].pos=2;
	zinit(res[3].val);
	zseti(res[3].val, 5);

	ARGBEGIN
	{
	case 'n':
		nflag=atoi(EARGF(usage(argv0)));
		break;
	default:
		usage(argv0);
	} ARGEND;

	for(low=high=3, count=1; nflag==0||count<=nflag; count++)
	{
		for(i=smallest=low; i<=high; i++)
			if(zcmp(res[i].val, res[smallest].val)<0)
				smallest=i;

		resstr=zstr(res[smallest].val, resstr, CAP);

		printf("%s %li %li\n", resstr, smallest, res[smallest].pos);

		if(res[low].pos==2&&smallest==low)
		{
			zfree(res[low].val);
			low++;
		}
		if(res[smallest].pos>2&&smallest>=low)
		{
			res[smallest].pos--;
			pbw(res[smallest].val, smallest, res[smallest].pos);
		}
		if(res[high].pos!=high-1||high==3)
		{
			high++;
			res[high].pos=high-1;
			zinit(res[high].val);
			pbw(res[high].val, high, res[high].pos);
		}
	}

	zunsetup();

	free(resstr);

	return 0;
}
