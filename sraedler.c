#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LIMIT 140

int main(void)
{
	unsigned long long i, j;

	for(i=2; i<=LIMIT; i++)
		for(j=2; j<=i; j++)
			printf("%.0lf %llu %llu\n", pow(i, j)+pow(j, i), i, j);

	return 0;
}
