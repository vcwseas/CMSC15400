#include "cachelab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#define ADDRESS_SIZE 64;

/*
valid is either 0 or 1.
tag holds a max 64 bit tag.
*/
typedef struct line {
	long long tag;
	unsigned int lastUsed;
	unsigned char valid;
} line ;

//index of a set is given by position in array of cache
typedef struct set {
	line* line;
} set;

//omit B because it's unimportant for hit/miss
//all we need is the tag (t = m - s - b)
//and the set s
typedef struct cache {
	set* s;	
	unsigned int E;
	unsigned int S;
} cache; 

//for bits processing
int numSetBits;
int numTagBits;
int numBlockBits;
int associativity;




void nullPointerError(char* s, void* p)
{
	if (p == NULL)
	{
		fprintf(stderr, "%s\n", s);
		exit(0);
	}
}

//initialize a cache with S,E,B set and everything set to 0;
cache *initializeCache(unsigned int s, unsigned int E)
{
	cache *c = malloc(sizeof(cache));
	nullPointerError("initializeCache: Null Pointer Error", c);

	c->E = E;
	c->S = 1 << s;
	c->s = malloc(sizeof(set) * c->S);
	nullPointerError("initializeCache: Null Pointer Error", c->s);

	int i, j;
	for (i = 0; i < c->S; i++)
	{
		line* linePtr = c->s[i].line = malloc(sizeof(line) * E);
		nullPointerError("initializeCache: Null Pointer Error", linePtr);
		for (j = 0; j < c->E; j++)
		{
			linePtr->tag = 0;
			linePtr->valid = 0;
			linePtr->lastUsed = 0;
		}
	}
	return c;
}

//calculates set bits for 64 bit address
long long getSet(long long addr)
{
	long long mask = (~LLONG_MIN) >> (63 - numSetBits);
	addr >>= numBlockBits;
	return mask & addr;
}

//calculates tag bits for 64 bit address
long long getTag(long long addr)
{
	long long mask = ~((~LLONG_MIN) >> (numTagBits - 1));
	return (mask & addr) >> (numSetBits + numBlockBits);
}

void parseFile(char *filename) {
	char buf[100];
	char instruction;
	// long long addr;
	long long addr;
	FILE* file = fopen(filename, "r");
	if (file == NULL)
		fprintf(stderr, "%s\n", "error opening file");
	while(fgets(buf, 100, file) != NULL)
	{
		if (*buf == ' ')
		{
			buf[strlen(buf) - 3] = '\0';
			sscanf(buf, " %c %llx", &instruction, &addr);
			printf("%c\n", instruction);
			printf("%llx\n", addr);	
		}
	}
}





int main(int argc, char *argv[])
{
	//for getopt
	//trace file name
	char filename[2048];
	unsigned char numArgs = 0;
	char usage[] = "Usage: ./csim [-hv] -s <s> -E <E> -b <b> -t <tracefile>";
	char c;

	while((c = getopt(argc, argv, "hvs:E:b:t:")) != -1)
	{
		switch(c)
		{
			//TODO
			case 'v':
				break;
			case 's':
				numArgs++;
				numSetBits = atoi(optarg);
				break;
			case 'E':
				numArgs++;
				associativity = atoi(optarg);
				break;
			case 'b':
				numArgs++;
				numBlockBits = atoi(optarg);
				break;
			case 't':
				numArgs++;
				if (strlen(optarg) >= 2048)
				{
					fprintf(stderr, "%s\n", "tracefile name too long.");
					exit(1);
				}
				strcpy(filename, optarg);
				break;
			default: 
				printf("%s\n", usage);
				exit(0);
		}
	}
	//set tag bits
	numTagBits = ADDRESS_SIZE;
	numTagBits -= (numSetBits + numBlockBits);

	if (numArgs < 4)
	{
		printf("%s\n", usage);
		exit(0);
	}

	printf("tag: %d\n", numTagBits);
	printf("set: %d\n", numSetBits);
	printf("block: %d\n", numBlockBits);
	printf("E: %d\n", associativity);
	printf("%s\n", filename);


    // printSummary(0, 0, 0);
    // return 0;
}
