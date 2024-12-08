#include <stdio.h>

#define N (130)

int main() {
	FILE *file = fopen("input.txt", "r");
	int mem[N][N+1];
	int c;
	
	int i = 0;
	int j = 0;

	int ppx;
	int ppy;
	int dx = 0;
	int dy = -1;

	while ((c = fgetc(file)) != EOF) {
		mem[i][j] = c;
		j = (j+1) % 131;
		if (j == 0) i++;

		if ( c == '^' ) {
			ppx = j-1;
			ppy = i;
		}
	}

	int r = 0;
	int exit = 0;
	int py = ppy;
	int px = ppx;

	while (!exit) {
		
		if (mem[py][px] == '.') {
			r++;
			mem[py][px] = 'X';
		}

		int dirok = 0;

		do {
			int npx = px+dx;
			int npy = py+dy;

			if (npx < 0 || npx >= N || npy < 0 || npy >= N) {
				exit = 1;
				break;
			}

			if (mem[npy][npx] == '#') {
				int tempx = dx;
				dx = -1*dy;
				dy = tempx;
			} else {
				dirok = 1;
				px = npx;
				py = npy;
			}
		} while (!dirok);
	}
	r++;



	r = 0;
	int test = 0;

	for (int i = 0; i < N; i++) {
	for (int j = 0; j < N; j++) {
	
	test++;


	if (mem[i][j] != 'X') continue;
	mem[i][j] = '#';

	py = ppy;
	px = ppx;
	dx = 0;
	dy = -1;
	// int h[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
	// int hindex = 1;
	exit = 0;
	int limit = 1000000;


	while (!exit) {

		int dirok = 0;
		limit--;
		if (limit == 1) {
			exit = 1;
			r++;
		}
		

		do {
			int npx = px+dx;
			int npy = py+dy;

			if (npx < 0 || npx >= N || npy < 0 || npy >= N) {
				exit = 1;
				break;
			}

			if (mem[npy][npx] == '#') {
				int tempx = dx;
				dx = -1*dy;
				dy = tempx;

				// int middle = (hindex+2) % 4;
				
				// if (h[hindex*2] == px && h[hindex*2+1] == py && h[middle*2] != px && h[middle*2+1] != py) {
					// r++;
					// exit = 1;
				// } else {
					// h[hindex*2] = px;
					// h[hindex*2+1] = py;
					// hindex = (hindex+1) % 4;
				// }
				
			} else {
				dirok = 1;
				px = npx;
				py = npy;
			}
		} while (!dirok);
	}

	mem[i][j] = 'X';

	}
	}


	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%c", mem[i][j]);
		}
		printf("\n");
	}



	printf("%d    %d\n", r, test);
	
	fclose(file);
	return 0;
}
