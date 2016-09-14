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
	size_t pos;
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
	fprintf(stderr, "setting to %li, %li\n", i, j);

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
	ulong count, nflag, pos, low, high;
	leyland* smallest, * r, * t;
	jmp_buf env;

	nflag=0;

	TAILQ_INIT(&head);
	resstr=calloc(CAP, sizeof(char));

	if(setjmp(env))
	{
		perror(0);
		zunsetup();
		exit(1);
	}

	zsetup(env);

	t=calloc(1, sizeof(leyland));
	t->pos=2;
	zinit(t->val);
	zseti(t->val, 8);
	TAILQ_INSERT_HEAD(&head, t, next);

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
		smallest=TAILQ_FIRST(&head);
		pos=low-1;
		TAILQ_FOREACH(t, &head, next)
		{
			if(zcmp(t->val, smallest->val)<0)
			{
				fprintf(stderr, "found new smallest at pos %li\n", pos);
				smallest=t;
			}
			pos++;
		}
		assert(pos>=low);
		resstr=zstr(smallest->val, resstr, CAP);

		printf("%s %li %li\n", resstr, pos, smallest->pos);

		t=TAILQ_FIRST(&head);
		if(t->pos>=low&&low==pos)
		{
			fprintf(stderr, "removing head\n");
			TAILQ_REMOVE(&head, t, next);
			zfree(t->val);
			free(t);
			low++;
		}
		if(!TAILQ_EMPTY(&head)&&pos>=low)
		{
			fprintf(stderr, "increasing pos of smallest\n");
			smallest->pos++;
			fprintf(stderr, "smallest->pos: %li\n",smallest->pos);
			pbw(smallest->val, pos, smallest->pos);
		}
		if(TAILQ_EMPTY(&head)||TAILQ_LAST(&head, leyhead)->pos>2)
		{
			fprintf(stderr, "adding to tail\n");
			high++;
			fprintf(stderr, "high: %li\n", high);
			t=calloc(1, sizeof(leyland));
			t->pos=2;
			zinit(t->val);
			pbw(t->val, high, t->pos);
			TAILQ_INSERT_TAIL(&head, t, next);
		}
	}

	for(r=TAILQ_FIRST(&head); r; r=t)
	{
		t=TAILQ_NEXT(r, next);
		TAILQ_REMOVE(&head, r, next);
		zfree(r->val);
		free(r);
	}
	zunsetup();
	free(resstr);

	return 0;
}
