#include <stdio.h>
#include <stdlib.h>
	
int mat[100][100] = {0};

int legal(int first, int second) {
	return (mat[first][second] == -1) ? 0:1;
}

/*struct element {
	struct element *next;
	int value;
};

void insert(struct element *current, int value) {
	//printf("%d", value);
	struct element *next = current->next;
	int valid = 1;
	while (next != NULL) {
		if (!legal(current->value, next->value)) {
			valid = 0;
		}
		next = next->next;
	}
	if (valid) {
		struct element *new = malloc(sizeof(struct element));
		new->next = current->next;
		new->value = value;
		(*current).next = new;
	} else {
		insert(current->next, value);
	}
}

int find(struct element *current, int counter) {
	printf("%d ", current->value);
	if (counter == 0) {
		return current->value;
	}
	return find(current->next, counter-1);
}*/

int main() {
	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		perror("Cannot open file");
		return 1;
	}

	int line_buf[30];
	int valid;
	int i;
	int mpn_sum = 0;
	int nr2 = 0;
	char c;

	while ((c = (char) fgetc(file)) != '\n') {
		int a = (c-'0') * 10;
		a += (char) fgetc(file)-'0';
		fgetc(file); // |
		int b = ((char) fgetc(file) - '0') * 10;
		b += (char) fgetc(file) - '0';

		mat[a][b] = 1;
		mat[b][a] = -1;

		fgetc(file); // \n
	}
	
	//for (int i = 10; i < 100; i++) {
	//	for (int j = 10; j < 100; j++) {
	//		printf(" %s", (mat[i][j] == -1) ? "-1" : (mat[i][j] == 0) ? " 0" : " 1");
	//	}
	//	printf("\n");
	//}

	printf("check\n");
	i = 0;
	valid = 1;
	do {
		c = fgetc(file);

		if (c == EOF) {break;}

		int a = 10*(c - '0') + (fgetc(file) - '0');
		line_buf[i] = a;
		
		for (int j = 0; j < i; j++) {
			valid = valid && legal(line_buf[j], line_buf[i]);
		}
		
		c = fgetc(file);
		if (c == '\n') {
			if (valid) {
				int middle = i / 2;
				mpn_sum += line_buf[middle];
			} else {
				/*struct element sentinel = {
					NULL,
					0
				};
				for (int j = 0; j <= i; j++) {
					insert(&sentinel, line_buf[j]);
				}
				int middle = i/2;
				nr2 += find(&sentinel, middle+1);
				printf("\n");*/

				// printf("NEW\n");
				for (int q = 0; q <= i; q++) {
					printf("%d ", line_buf[q]);
				}
				// printf("\n");
				for (int j = 0; j < i; j++) {
					for (int k = j+1; k <= i; k++) {
						// printf("(%d, %d) ", j, k);
						if (!legal(line_buf[j], line_buf[k])) {
							// printf("->illegal ");
							int temp = line_buf[j];
							line_buf[j] = line_buf[k];
							line_buf[k] = temp;
						}
					}
				}
				// printf("\n");
				// for (int q = 0; q <= i; q++) {
					// printf("%d ", line_buf[q]);
				// }
				int middle = i / 2;
				nr2 += line_buf[middle];

			}
			valid = 1;
			i = 0;

		} else {
			i++;
		}

	} while (1);

	printf("%d %d\n", mpn_sum, nr2);

	fclose(file);
	return 0;
}
