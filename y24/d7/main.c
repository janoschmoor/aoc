#include <stdio.h>
#include <string.h>
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

	// printf("d%d: adding prev=%ld to input[%d]=%ld   => %ld\n", index, value, index, input[index], value+input[index]);
	int p = r(target, value + *(input + index), input, len, index+1);
	// printf("d%d: multiply prev=%ld to input[%d]=%ld   => %ld\n", index, value, index, input[index], value*input[index]);
	int m = r(target, value * *(input + index), input, len, index+1);
	
	char buffer[129]; // Ensure it’s large enough for both numbers and a null terminator.
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

		// printf("%ld\n", target);
		fgetc(file); // ommit leading space
		
		long value = 0;
		
		while ((c = fgetc(file)) != '\n') {
		
			if (c == ' ') {
				// printf("store %ld\n", value);
				input[len] = value;
				len++;
				value = 0;
			} else {
				value = (value * 10) + (c - '0');
			}
		}
		input[len] = value;
		len++;

		// for (int i = 0; i < len; i++) {
		// 	printf("%ld  ", input[i]);
		// }
		// printf("\n");

		if (r(&target, *(input), input, &len, 1) >= 1) {
			answer += target;
		}
		
	}
	
	printf("%ld\n", answer);
	
	fclose(file);
	return 0;
}