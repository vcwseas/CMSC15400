#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
	int foo, endian;
	foo = 1 << ((sizeof(int) << 3) - 1);
	//reads the byte at the lowest address
	endian = ((unsigned char *) (&foo))[0];
	printf("%s\n", endian? "big" : "little" );

	int x = 0xDFFFFFFF;
	//At least one bit of x is 0
	int test1 = !!(x ^ -1);

	//At least one bit of x is 1
	int test2 = !!(x ^ 0);

	//Any of the bits in the most significant nibble of x is 0
	int test3 = !!( (x & 0xf << (((sizeof(int) << 1) - 1) << 2)) ^ (0xf << (((sizeof(int) << 1) - 1) << 2)));

	//Any of the bits in the least significant nibble of x is 1
	int test4 = !!(x & 0XF);

	//The most significant and the least significant byte are equal
	int test5 = ((unsigned char *) (&x))[0] == ((unsigned char *) (&x))[sizeof(int) - 1];

	//any even bit is 1
	int test6 = !!(x & 0X55555555);

	printf("input: %x\n", x);
	printf("test1: %d\n", test1);
	printf("test2: %d\n", test2);
	printf("test3: %d\n", test3);
	printf("test4: %d\n", test4);
	printf("test5: %d \t MSB: %x \t LSB: %x \n", test5, ((unsigned char *) (&x))[sizeof(int) - 1], ((unsigned char *) (&x))[0]);
	printf("test6: %d\n", test6);
}

