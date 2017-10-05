#include <iostream>
#include <string.h>

using namespace std;

float equation(char* _ch);
float mult(char* _ch);
float num_z(char* _ch);
float num(char* _ch);

float equation(char* _ch) {
	float eq = 0;
	
	eq += mult(_ch);
	
	while (*_ch != '\0') {
		if (*_ch == '+') {
			eq += mult(_ch + 2);
		}
		if (*_ch == '-' && *(_ch + 1) == ' ') {
			eq -= mult(_ch + 2);
		}
		_ch++;
	}
	return eq;
}
float mult(char* _ch) {
	float mul = 1;
	mul *= num_z(_ch);
	while (*_ch != '\0') {
		if (*_ch == '*') {
			mul *= num_z(_ch + 2);
		}
		if (*_ch == '/') {
			mul /= num_z(_ch + 2);
		}
		if (*_ch == '+' || *_ch == '-') {
			break;
		}
		_ch++;
	}
	return mul;
}
float num_z(char* _ch) {
	if (*_ch == '-') {
		return (-1 * num(_ch + 1));
	} else {
		return num(_ch);
	}
}
float num(char* _ch) {
	float n = 0;
	while (*_ch != '\0' && *_ch != ' ') {
		n = n * 10 + *_ch - '0';
		_ch++;
	}
	return n;
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf ("argc < 2\n");
		return 0;
	}
	char ch[255];
	int j;
	strcpy(ch, argv[1]);
	j = strlen(argv[1]);
	
	for (int i = 2; i < argc; i++) {
		ch[j++] = ' ';
		strcpy((char*)(ch + j), argv[i]);
		j += strlen(argv[i]);
	}
	printf("%s\n", ch);
	printf("%f\n", equation(ch));
	//printf("%c\n", argv[1][2]);
	//printf("%c\n", argv[1][5]);
	//printf("len = %d\n", strlen(argv[1]));
	//printf("%s\n", ch);
	//printf("len = %d\n", strlen(ch));
	
	
	
	/*
	int k;
	scanf("%d", &k);
	*/
	return 0; 
}
