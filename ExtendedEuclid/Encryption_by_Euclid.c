#define _CRT_SECURE_NO_WARNINGS
#define MESSAGE_LENGTH 35
#include <stdio.h>
#include <stdlib.h>



char message[] = { 'H','e','l','l','o',',',' ','P','l','e','a','s','e',
' ','l','o','v','e',' ','W','o','o','n','g','s','u','p','!','!',
'!','\0' };

unsigned int encryption[MESSAGE_LENGTH];	// encryption은 정수형 배열로 선언
char decryption[MESSAGE_LENGTH];	// decryption은 문자형 배열로 선언

struct _node {		// d 값을 구하기 위한 extended_Euclid 함수 사용을 위한 구조체
	int x;
	int y;
	int d;
};


// 주어진 p,q,e 값을 가지고 private key의 d 값을 구한다. 
// 구하는 방법은 예제 1의 extended_Euclid 함수를 적용하여 구해진 d 값을 사용하도록 하며 
// extended_Euclid의 a와 b는 각각 e와 (p-1)×(q-1) 를 의미한다. 단 d값이 음수를 가지는 // 경우가 많기 때문에 d 값이 음수를 가지는 경우 N을 더해서 d값이 양의 정수를 가지도록 해야 한// 다.

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



// ckey mod  N 값을 구한다.
//
// 여기서 key 값은 암호화할 때는 public key (e,N)의 e 값을 주고 복호화 할 때는 
// private key (d, N)의 d값을 준다.
unsigned int do_exp(int c, int key, int N) {
	// do_exp()는 ckey mod N 해준 값을 리턴한다.
	// 단 c를 key 번 곱하게 되면 그 값이 정수형으로 감당할 수 없을 정도로 커지므로
	// c를 곱해줄 때 마다 mod 연산 (%연산)을 구행하여 그 값을 충분히 작은 값으로 
	// 유지시킬 필요가 있다. 물론 수업시간에 배운 내용을 적용하여 ckey mod N 을 구할 
	// 수도 있다.
	// 예) prod = prod * c; prod = prod % N;

	
	unsigned int prod = 1;
	
	for (int i = 0; i < key; i++)
	{
		prod = prod * c;
		prod = prod % N;
	}


	return prod;		// ckey mod N을 리턴 
}

// encryption 배열은 정수형으로 되어 있으므로 아래 함수를 사용하여 출력하도록 한다.
void print_encryption(int e[]) {
	for (int i = 0; i < MESSAGE_LENGTH; i++)
		printf("%d", e[i]);
	printf("\n");
}

void main(void) 
{

	// 주어진 값으로 extended_euclid함수를 사용하여 비밀키는 얻는다.
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


		//	1.	문자열 message[i]의 문자를 ch에 저장한다.
		//	2.	c = (unsigned int)ch; // ch를 정수형으로 변환한다.
		//	3.	c를 public key에 따라 암호화(do_exp(c, e, N) 참고할 것)한 후 이를 encryption[i]에 저장한다.

		//	print_encryption()함수를 사용하여 암호화된 정수배열 encryption의 내용을 출력한다.

	i = 0;

	while (encryption[i] != '\0')
	{
		c = encryption[i];
		decryption[i] = (char)do_exp(c, d, N);
		printf("%c", decryption[i]);
		i++;
	}
		//	1.	encryption의 문자를 하나씩 읽어 정수 c에 저장한다.
		//	2.	c를 private key에 따라 복호화(do_exp(c, d, N) 참고할 것) 한 후, 이를 decryption[i]에 하나씩 저장한다.단 decryption의 경우 문자형 배열이므로 형변환후 저장한다. (예, decryption[i] = (char)do_exp(...);)

		//	복호화된 문자열 decryption의 내용을 출력한다.

	int j = 0;
	scanf("%d", j);
}
