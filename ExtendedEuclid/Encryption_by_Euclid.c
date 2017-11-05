#define _CRT_SECURE_NO_WARNINGS
#define MESSAGE_LENGTH 35
#include <stdio.h>
#include <stdlib.h>



char message[] = { 'H','e','l','l','o',',',' ','P','l','e','a','s','e',
' ','l','o','v','e',' ','W','o','o','n','g','s','u','p','!','!',
'!','\0' };

unsigned int encryption[MESSAGE_LENGTH];	// encryption�� ������ �迭�� ����
char decryption[MESSAGE_LENGTH];	// decryption�� ������ �迭�� ����

struct _node {		// d ���� ���ϱ� ���� extended_Euclid �Լ� ����� ���� ����ü
	int x;
	int y;
	int d;
};


// �־��� p,q,e ���� ������ private key�� d ���� ���Ѵ�. 
// ���ϴ� ����� ���� 1�� extended_Euclid �Լ��� �����Ͽ� ������ d ���� ����ϵ��� �ϸ� 
// extended_Euclid�� a�� b�� ���� e�� (p-1)��(q-1) �� �ǹ��Ѵ�. �� d���� ������ ������ // ��찡 ���� ������ d ���� ������ ������ ��� N�� ���ؼ� d���� ���� ������ �������� �ؾ� ��// ��.

struct _node *extended_Euclid(int a, int b)
{
	struct _node *n;

	struct _node *n1, *n2;

	if (b == 0) {
		n = (struct _node *)malloc(sizeof(struct _node));
		n->x = 1;
		n->y = 0;
		n->d = a;

		return n;
	}

	n1 = extended_Euclid(b, a%b);

	printf("%d\n", n1->x);
	printf("%d\n", n1->y);


	n2 = (struct _node *)malloc(sizeof(struct _node));
	n2->x = n1->y;
	n2->y = (n1->x) - (a / b)*(n1->y);
	n2->d = n1->d;

	return n2;


}



// ckey mod  N ���� ���Ѵ�.
//
// ���⼭ key ���� ��ȣȭ�� ���� public key (e,N)�� e ���� �ְ� ��ȣȭ �� ���� 
// private key (d, N)�� d���� �ش�.
unsigned int do_exp(int c, int key, int N) {
	// do_exp()�� ckey mod N ���� ���� �����Ѵ�.
	// �� c�� key �� ���ϰ� �Ǹ� �� ���� ���������� ������ �� ���� ������ Ŀ���Ƿ�
	// c�� ������ �� ���� mod ���� (%����)�� �����Ͽ� �� ���� ����� ���� ������ 
	// ������ų �ʿ䰡 �ִ�. ���� �����ð��� ��� ������ �����Ͽ� ckey mod N �� ���� 
	// ���� �ִ�.
	// ��) prod = prod * c; prod = prod % N;

	
	unsigned int prod = 1;
	
	for (int i = 0; i < key; i++)
	{
		prod = prod * c;
		prod = prod % N;
	}


	return prod;		// ckey mod N�� ���� 
}

// encryption �迭�� ���������� �Ǿ� �����Ƿ� �Ʒ� �Լ��� ����Ͽ� ����ϵ��� �Ѵ�.
void print_encryption(int e[]) {
	for (int i = 0; i < MESSAGE_LENGTH; i++)
		printf("%d", e[i]);
	printf("\n");
}

void main(void) 
{

	// �־��� ������ extended_euclid�Լ��� ����Ͽ� ���Ű�� ��´�.
	int p = 11;
	int q = 17;
	int e = 3;
	int N = p*q;
	int d = 0;
	int i = 0;
	int c;
	char ch;



	struct _node *n;
	n = extended_Euclid( (p - 1)*(q - 1), e);

	while (n->y < 0) {
		n->y = n->y + (p - 1)*(q - 1);
	}
	d = n->y;

	printf("***p: %d, q = %d, N = %d, e = %d, d = %d ***\n\n\n", p, q, N, e, d);
		
	
	while (message[i] != '\0')
	{
		ch = message[i];
		c = (unsigned int)ch;
		encryption[i] = do_exp(c, e, N);
		i++;
	}
	print_encryption(encryption);
	printf("\n");


		//	1.	���ڿ� message[i]�� ���ڸ� ch�� �����Ѵ�.
		//	2.	c = (unsigned int)ch; // ch�� ���������� ��ȯ�Ѵ�.
		//	3.	c�� public key�� ���� ��ȣȭ(do_exp(c, e, N) ������ ��)�� �� �̸� encryption[i]�� �����Ѵ�.

		//	print_encryption()�Լ��� ����Ͽ� ��ȣȭ�� �����迭 encryption�� ������ ����Ѵ�.

	i = 0;

	while (encryption[i] != '\0')
	{
		c = encryption[i];
		decryption[i] = (char)do_exp(c, d, N);
		printf("%c", decryption[i]);
		i++;
	}
		//	1.	encryption�� ���ڸ� �ϳ��� �о� ���� c�� �����Ѵ�.
		//	2.	c�� private key�� ���� ��ȣȭ(do_exp(c, d, N) ������ ��) �� ��, �̸� decryption[i]�� �ϳ��� �����Ѵ�.�� decryption�� ��� ������ �迭�̹Ƿ� ����ȯ�� �����Ѵ�. (��, decryption[i] = (char)do_exp(...);)

		//	��ȣȭ�� ���ڿ� decryption�� ������ ����Ѵ�.

	int j = 0;
	scanf("%d", j);
}
