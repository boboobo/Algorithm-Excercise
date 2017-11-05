#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MESSAGE_LENGTH 55

unsigned int do_XOR(unsigned int c, unsigned int key)
{
	return c^key;		// return result of XOR 
}

char message[] = { "Welcome to Algorithm Practices, this is EoJun!" };

unsigned int encryption[MESSAGE_LENGTH];
char decryption[MESSAGE_LENGTH];


void main()
{
	int i = 0;
	char ch = 'a';
	unsigned int c;
	unsigned int key = 0x5;
	while (message[i] != NULL )
	{
		ch = message[i];
		c = (unsigned int)ch;
		encryption[i] = do_XOR(c, key);
		printf("%c", encryption[i]);
		i++;
	}
	printf("\n");
	
	i = 0;

	while (encryption[i] != NULL)
	{
		ch = encryption[i];
		c = (unsigned int)ch;
		decryption[i] = do_XOR(c, key);
		printf("%c", decryption[i]);
		i++;
	}
}