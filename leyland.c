#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <assert.h>

#include "arg.h"
#include "util.h"
#include "zahl.h"
#include "queue.h"

char* argv0;

TAILQ_HEAD(leyhead, leyland)head=TAILQ_HEAD_INITIALIZER(head);

typedef struct leyland
{
	size_t width;
	z_t val;
	TAILQ_ENTRY(leyland)next;
} leyland;

static void usage(void)
{
	eprintf("%s [-l lim]\n", argv0);
}

void pbw(z_t res, long i, long j)
{

	z_t op1, op2;

	zinit(op1), zinit(op2);

	zseti(op1, i), zseti(op2, j);

	zpow(res, op1, op2);
	zseti(op1, i);
	zseti(op2, j);
	zpow(op1, op2, op1);
	zadd(res, op1, res);

	zfree(op1), zfree(op2);
}

int main(int argc, char* argv[])
{
	struct line result;
	size_t resultsize;
	z_t lim, nflag, one;
	long i, low, high, height;
	leyland* smallest, * tmp1, * tmp2;
	jmp_buf env;

	if(setjmp(env))
	{
		zperror(argv0);
		zunsetup();
		exit(1);
	}
	zsetup(env);

	zinit(nflag);
	zseti(nflag, 0);

	ARGBEGIN
	{
	case 'l':
		zsets(nflag, EARGF(usage()));
		if(zcmpi(nflag, 0)<=0)
			usage();
		break;
	default:
		usage();
	} ARGEND;

	result.cap=4069;
	result.data=ecalloc(result.cap, sizeof(char));

	TAILQ_INIT(&head);

	zinit(one);
	zseti(one, 1);
	zinit(lim);
	zseti(lim, 1);
	tmp1=ecalloc(1, sizeof(leyland));
	tmp1->width=2;
	zinit(tmp1->val);
	zseti(tmp1->val, 8);
	TAILQ_INSERT_HEAD(&head, tmp1, next);

	for(low=high=2; zzero(nflag)||zcmp(lim, nflag)<=0; zadd(lim, lim, one))
	{
		smallest=TAILQ_FIRST(&head);
		i=low-1;
		TAILQ_FOREACH(tmp1, &head, next)
		{
			i++;
			if(zcmp(tmp1->val, smallest->val)<=0)
			{
				smallest=tmp1;
				height=i;
			}
		}
		resultsize=zstr_length(smallest->val, 10);
		if(resultsize+1>result.cap)
		{
			result.data=ereallocarray(result.data, resultsize+512, sizeof(result.data[0]));
			result.cap=resultsize+512;
		}
		result.data=zstr(smallest->val, result.data, result.cap);

		printf("%s %li %li\n", result.data, height, smallest->width);

		tmp1=TAILQ_FIRST(&head);
		if(tmp1->width>=low&&low==height)
		{
			TAILQ_REMOVE(&head, tmp1, next);
			zfree(tmp1->val);
			free(tmp1);
			low++;
		}
		if(!TAILQ_EMPTY(&head)&&height>=low)
		{
			smallest->width++;
			pbw(smallest->val, height, smallest->width);
		}
		if(TAILQ_EMPTY(&head)||TAILQ_LAST(&head, leyhead)->width>2)
		{
			high++;
			tmp1=ecalloc(1, sizeof(leyland));
			tmp1->width=2;
			zinit(tmp1->val);
			pbw(tmp1->val, high, tmp1->width);
			TAILQ_INSERT_TAIL(&head, tmp1, next);
		}
	}

	for(tmp2=TAILQ_FIRST(&head); tmp2; tmp2=tmp1)
	{
		tmp1=TAILQ_NEXT(tmp2, next);
		TAILQ_REMOVE(&head, tmp2, next);
		zfree(tmp2->val);
		free(tmp2);
	}

	zunsetup();
	free(result.data);

	return 0;
}
