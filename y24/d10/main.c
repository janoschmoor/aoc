#include <stdio.h>

#define N 60 // 60

int m[N][N+1];

int search(int h, int i, int j, int *id) {
	if (i < 0 || j < 0 || i >= N || j >= N) {
		return 0;
	}
	if (m[i][j] != h && !(h == 9 && m[i][j] >= 9)) {
		return 0;
	}
	if (m[i][j] >= 9) {
		if (m[i][j] != *id) {
			//m[i][j] = *id;
			// printf("%d %d\n", i, j);
			return 1;
		}
		return 0;
	}

	int r = search(h+1, i+1, j, id);
	r += search(h+1, i-1, j, id);
	r += search(h+1, i, j+1, id);
	r += search(h+1, i, j-1, id);

	return r;
}

int main() {

	FILE *file = fopen("input.txt", "r");
	int c;
	int answer = 0;
	int index = 0;
	int id = 100;

	while ((c = fgetc(file)) != EOF) {
		m[0][index] = c - '0';
		index++;
	}

	

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			if (m[i][j] == 0) {
				answer += search(0, i, j, &id);
				id++;
			}

		}
	}
	
	printf("%d\n", answer);

	fclose(file);
	return 0;
}
