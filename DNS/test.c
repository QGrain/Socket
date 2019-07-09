#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char *c = malloc(10);

	memset(c, 97, 10);
	printf("string c = %s\n", c);
	printf("sizeof(c) = %d\nstrlen(c) = %d\n", sizeof(c), strlen(c));
	free(c);
	return 0;
}
