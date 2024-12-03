#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE *file;

	file = fopen("input.txt", "r");
	
	if (file == NULL) {
		perror("could not open file");
		return 1;
	}
	
	int c;
	// 0 == begin, 1 == m, 2 == mu, 3 == mul, 4 == mul(, 5 == mul(<a>,, 6 
	int state = 0;
	unsigned long sum = 0;
	int a;
	int b;

	int dont = 0;


	while ((c = fgetc(file)) != EOF) {
		
		switch(state) {
			case(0):
				if (c == 'm') state = 1;
				if (c == 'd') state = 10;
				break;
			case(1):
				if (c == 'm') state = 1;
				else if (c == 'd') state = 10;
				else state = (c == 'u') ? 2 : 0;
				break;
			case(2):
				if (c == 'm') state = 1;
				else if (c == 'd') state = 10;
				else state = (c == 'l') ? 3 : 0;
				break;
			case(3):
				a = 0;
				b = 0;
				if (c == 'm') state = 1;
				else if (c == 'd') state = 10;
				else state = (c == '(') ? 4 : 0;
				break;
			case(4):
				if (c == 'm') state = 1;
				else if (c == 'd') state = 10;
				else if (c - 48 >= 0 && c - 48 <= 9) {
					a *= 10;
					a += c-48;
				} else if (c == ',' && a <= 999 && a >= 1) {
					state = 5;
				} else {
					state = 0;
				}
				break;
			case(5):
				if (c == 'm') state = 1;
				else if (c - 48 >= 0 && c - 48 <= 9) {
					b *= 10;
					b += c-48;
				} else if (c == ')' && b <= 999 && b >= 1) {
					state = 0;
					if (dont == 0) {
						sum += a*b;
					}
				} else {
					state = 0;
				}
				break;
			

			case(10):
				if (c == 'd') state = 10;
				else if (c == 'm') state = 1;
				else if (c == 'o') state = 11;
				else state = 0;
				break;
			case(11):
				if (c == 'd') state = 10;
				else if (c == 'm') state = 1;
				else if (c == '(') state = 12;
				else if (c == 'n') state = 13;
				else state = 0;
				break;
			case(12):
				if (c == 'd') state = 10;
				else if (c == 'm') state = 1;
				else if (c == ')') {
					state = 0;
					dont = 0;
				}
				else state = 0;
				break;
			case(13):
				if (c == 'd') state = 10;
				else if (c == 'm') state = 1;
				else if (c == '\'') state = 14;
				else state = 0;
				break;
			case(14):
				if (c == 'd') state = 10;
				else if (c == 'm') state = 1;
				else if (c == 't') state = 15;
				else state = 0;
				break;
			case(15):
				if (c == 'd') state = 10;
				else if (c == 'm') state = 1;
				else if (c == '(') state = 16;
				else state = 0;
				break;
			case(16):
				if (c == 'd') state = 10;
				else if (c == 'm') state = 1;
				else if (c == ')') {
					state = 0;
					dont = 1;
				}
				else state = 0;
				break;
		}

	}
	
	printf("%lu", sum);

	fclose(file);
	return 0;

}
