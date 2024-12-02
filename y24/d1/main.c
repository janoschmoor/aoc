#include <stdio.h>
#include <stdlib.h>


void bubble(int *arr, int n) {
	int temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (arr[j] > arr[j+1]) {
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

int main() {
	
	FILE *file;
	int number;
	int other;

	int scores[100000] = {0};

	unsigned int size = 200;

	int *a = (int *)malloc(size * sizeof(int));
	int *b = (int *)malloc(size * sizeof(int));
	unsigned int i = 0;

	if (a == NULL || b == NULL) {
		perror("Error calling malloc");
		return 1;
	}

	file = fopen("input.txt", "r");
	if (file == NULL) {
		perror("Error opening file");
		return 1;
	}

	while(fscanf(file, "%d", &number) != EOF) {
		//printf("%d\n", number);
		if (i == size) {
			size *= 2;
			a = (int *)realloc(a, size * sizeof(int));
			b = (int *)realloc(b, size * sizeof(int));

			if (a == NULL || b == NULL) {
				perror("Error calling realloc");
				return 1;
			}
		}

		*(a+i) = number;
		
		fscanf(file, "%d", &other);
		*(b+i) = other;
		
		scores[other] += 1;

		++i;
	}
	size = i;

	bubble(a, size);
	bubble(b, size);

	int sum_dif = 0;
	int star2 = 0;

	for(int i = 0; i < size; i++) {

		sum_dif += abs(a[i] - b[i]);
		
		star2 += a[i] * scores[a[i]]; 
	}

	printf("%d %d\n", sum_dif, star2);

	fclose(file);
	return 0;
}
