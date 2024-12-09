#include <stdio.h>
#include <stdlib.h>

int r(long *target, long value, long *input, int *len, int index) {
	if (index == *len) {
		// printf("%ld\n", value);
		return (value == *target) ? 1 : 0;
	}
	if (*target < value || value < 0) {
		// printf("abort\n");
		return 0;
	}

	int p = r(target, value + *(input + index), input, len, index+1);
	int m = r(target, value * *(input + index), input, len, index+1);
	
	char buffer[129];
	snprintf(buffer, sizeof(buffer), "%ld%ld", value, input[index]);

	long concatenated = atol(buffer);

	int c = r(target, concatenated, input, len, index+1);

	return p+m+c;
}

int main() {

	FILE *file = fopen("input.txt", "r");
	
	long answer = 0;
	long target = 0;
	long c;

	while((c = fgetc(file)) != EOF) {

		long input[20];
		int len = 0;

		target = c - '0';
		while ((c = fgetc(file)) != ':') {
			target = target * 10 + (c - '0');
		}

		fgetc(file); // ommit leading space
		
		long value = 0;
		
		while ((c = fgetc(file)) != '\n') {
		
			if (c == ' ') {
				input[len] = value;
				len++;
				value = 0;
			} else {
				value = (value * 10) + (c - '0');
			}
		}
		input[len] = value;
		len++;

		if (r(&target, *(input), input, &len, 1) >= 1) {
			answer += target;
		}
		
	}
	
	printf("%ld\n", answer);
	
	fclose(file);
	return 0;
}
