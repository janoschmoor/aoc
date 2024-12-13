#include <stdio.h>

#define N 1000
#define max_depth 75

long m[N][max_depth+1] = {{-1}};


long blink_smart(long value, int depth) {

	// printf("(%ld, %d): %ld\n", value, depth, m[value][depth]);
	
	if (depth == 0) {
		return 1;
	}
	if (value < N) {
		if (m[value][depth] != -1) {
			return m[value][depth];
		}
	}

	int num_digits = 0;
	long num = value;
	while(num > 0) {
		num /= 10;
		num_digits++;
	}

	if (value == 0) {
		long r = blink_smart(1, depth-1);
		if (value < N) {
			m[value][depth] = r;
		}
		return r;
	}  else if (num_digits % 2 == 0) {
		num = value;
		int i = 0;
		int middle = num_digits / 2;
		long v2 = 0;
		long v1 = 0;
		long pow = 1;
		while (i < middle) {
			v2 += pow * (num % 10);
			pow *= 10;
			num /= 10;
			i++;
		}
		i = 0;
		pow = 1;
		while (i < middle) {
			v1 += pow * (num % 10);
			pow *= 10;
			num /= 10;
			i++;
		}
		long r = blink_smart(v1, depth-1) + blink_smart(v2, depth-1);
		if (value < N) {
			m[value][depth] = r;
		}
		return r;
	} else {

		if (value * 2024 < value) {
			printf("OOPS\n");
		}

		long r = blink_smart(value*2024, depth-1);
		if (value < N) {
			m[value][depth] = r;
		}
		return r;
	}

}

int main() {
	FILE *file = fopen("input.txt", "r");
	
	int c;
	long answer = 0;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= max_depth; j++) {
			m[i][j] = -1;
		}
	}

	//answer = blink_smart(125, 6);
	c = fgetc(file);
	while ((c) != EOF) {
		long n = 0;
		while (c != ' ' && c != '\n' && c != EOF) {
			n = n * 10 + (c - '0');
			c = fgetc(file);
		}
		if (c != EOF) c = fgetc(file);
		answer += blink_smart(n, max_depth);
	}

	printf("%ld\n", answer);
	fclose(file);
	return 0;
}

