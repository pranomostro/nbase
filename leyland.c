#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>
#include <assert.h>

#include "arg.h"
#include "util.h"
#include "zahl.h"
#include "queue.h"

const int CAP=65536;

typedef unsigned long ulong;

TAILQ_HEAD(leyhead, leyland)head=TAILQ_HEAD_INITIALIZER(head);

typedef struct leyland
{
	size_t width;
	z_t val;
	TAILQ_ENTRY(leyland)next;
}leyland;

static void usage(char* progname)
{
	fprintf(stderr, "%s [-l LIM]\n", progname);
	exit(2);
}

void pbw(z_t res, ulong i, ulong j)
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
	char* argv0, * result_str;
	ulong lim, nflag, low, high, i, height;
	leyland* smallest, * tmp1, * tmp2;
	jmp_buf env;

	nflag=0;

	TAILQ_INIT(&head);
	result_str=calloc(CAP, sizeof(char));

	if(setjmp(env))
	{
		perror(0);
		zunsetup();
		exit(1);
	}

	zsetup(env);

	tmp1=calloc(1, sizeof(leyland));
	tmp1->width=2;
	zinit(tmp1->val);
	zseti(tmp1->val, 8);
	TAILQ_INSERT_HEAD(&head, tmp1, next);

	ARGBEGIN
	{
	case 'l':
		nflag=atoi(EARGF(usage(argv0)));
		break;
	default:
		usage(argv0);
	} ARGEND;

	for(low=high=2, lim=1; nflag==0||lim<=nflag; lim++)
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
		result_str=zstr(smallest->val, result_str, CAP);

		printf("%s %li %li\n", result_str, height, smallest->width);

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
			tmp1=calloc(1, sizeof(leyland));
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
	free(result_str);

	return 0;
}
