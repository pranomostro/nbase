/*
	utility functions
*/

/*
	This line is incompatible with sbase's struct line.
	Just in case you were wondering.
*/

#include <stdio.h>

struct line
{
	char* data;
	size_t cap;
};

extern char *argv0;

size_t nalread(char** in, size_t* len, FILE* input);
void cliterate(size_t argc, char** argv, FILE* input, void (*itf)(char*, size_t));

void *ecalloc(size_t, size_t);
void *emalloc(size_t);
void *erealloc(void *, size_t);
#undef reallocarray
void *reallocarray(void *, size_t, size_t);
void *ereallocarray(void *, size_t, size_t);
char *estrdup(const char *);
char *estrndup(const char *, size_t);
void *encalloc(int, size_t, size_t);
void *enmalloc(int, size_t);
void *enrealloc(int, void *, size_t);
char *enstrdup(int, const char *);
char *enstrndup(int, const char *, size_t);

void enprintf(int, const char *, ...);
void eprintf(const char *, ...);
void weprintf(const char *, ...);

void enfshut(int, FILE *, const char *);
void efshut(FILE *, const char *);
int  fshut(FILE *, const char *);

long long strtonum(const char *, long long, long long, const char **);
long long enstrtonum(int, const char *, long long, long long);
long long estrtonum(const char *, long long, long long);
