#include <stdio.h>
#include <stdlib.h>

#define N (20000)
int mem[N * 10];

int main() {
	FILE *file = fopen("input.txt", "r");
	int c;
	int is_free = 0;
	int id = 0;
	int index = 0;

	while ((c = fgetc(file)) != EOF) {
		for (int i = 0; i < c - '0'; i++) {
			if (is_free) {
				mem[index] = '.';
			} else {
				mem[index] = id+'0';
			}

			index++;
		}

		id = (is_free) ? id : id+1;
		is_free = !is_free;
	}

	int *end = (mem + index - 1);
	int *start = mem;
	
	int *left = (mem + index - 1);
	int *right = (mem + index - 1);
	uint64_t answer = 0;

	// for (int i = 0; i < index; i++) {
	// 	printf("%c", mem[i]);
	// }
	// printf("\n");

	
	
	// while (start < end) {
	// 	if (*start == '.') {
	// 		*start = *end;
	// 		*end = '.';
	// 		end--;
	// 		start++;
	//
	// 		while (*end == '.') {
	// 			end--;
	// 		}
	// 		while (*start != '.') {
	// 			start++;
	// 		}
	// 	} else {
	// 		start++;
	// 	}
	// }
	
	while (left > start) {
		while (*left == '.') {
			left--;
		}
		right = left;
		while (*left == *right) {
			left--;
		}
		int size = (int) (right - left);
		c = *right;
		// if (c == '2') {
		// 	printf("TEST: %p %p\n", left, right);
		// }
		int *free_base = mem;
		int *free_end = mem;
		
		while (free_base < left) {
			while( *free_base != '.') {
				free_base++;
			}
			free_end = free_base;
			while (*free_end == *free_base) {
				free_end++;
			}
			
			if (free_base < left && size <= (int) (free_end - free_base)) {
				for (int i = 0; i < size; i++) {
					*(free_base+i) = *(left+1+i);
					*(left+1+i) = '.';
				}
				free_base = left;
			} else {
				free_base = free_end;
			}
		}

		// printf("%dx%c ",(int) (right - left), *right);
	}
	
	for (int i = 0; i < index; i++) {
		if (mem[i] == '.') continue;
		answer += i * (mem[i] - '0');
		// printf("%c", (mem[i]));
	}

	printf("\n%llu\n", answer);

	fclose(file);
	return 0;
}
