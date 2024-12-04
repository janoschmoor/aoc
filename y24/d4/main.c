#include <stdio.h>
#include <stdlib.h>

struct dir {
	int i;
	int j;
};

struct dir d[8] = {
	{1,0},
	{1,1},
	{0,1},
	{-1,1},
	{-1,0},
	{-1,-1},
	{0,-1},
	{1,-1},
};
#define n (140)
int mem[n][n+1];


int isValid(struct dir t) {
	return (int) (t.i >= 0 && t.i < n && t.j >= 0 && t.j < n);
}

int search(int i, int j) {
	int res = 0;

	//if (i == 0 && j == 5) {
	
	for (int k = 0; k < 8; k++) {
		int success = 1;
		struct dir t = {d[k].i+i, d[k].j+j};
		if (!(isValid(t) == 1 && mem[t.i][t.j] == 'M')) {
			success = 0;	
		}
		//printf("%d %d %c  ", t.i, t.j, (char) mem[t.i][t.j]);
		t.i = d[k].i*2+i; 
		t.j = d[k].j*2+j;
		if (!(isValid(t) == 1 && mem[t.i][t.j] == 'A')) {
			success = 0;	
		}
		//printf("%d %d %c  ", t.i, t.j, (char) mem[t.i][t.j]);
		t.i = d[k].i*3+i;
		t.j = d[k].j*3+j;
		if (!(isValid(t) == 1 && mem[t.i][t.j] == 'S')) {
			success = 0;	
		}
		//printf("%d %d %c\n", t.i, t.j, (char) mem[t.i][t.j]);

		res += success;
	//}

	}
	return res;
}

int search2(int i, int j) {
	
	struct dir a = {1+i, 1+j};
	struct dir b = {-1+i, -1+j};

	if (!(isValid(a) == 1 && isValid(b) == 1 && ((mem[a.i][a.j] == 'S' && mem[b.i][b.j] == 'M') || (mem[a.i][a.j] == 'M' && mem[b.i][b.j] == 'S')))) {
		return 0;	
	}
	//printf("%d %d %c  ", t.i, t.j, (char) mem[t.i][t.j]);
	a.i = 1+i; 
	a.j = -1+j;
	b.i = -1+i;
	b.j = 1+j;
	if (!(isValid(a) == 1 && isValid(b) == 1 && ((mem[a.i][a.j] == 'S' && mem[b.i][b.j] == 'M') || (mem[a.i][a.j] == 'M' && mem[b.i][b.j] == 'S')))) {
		return 0;	
	}
	return 1;
}


int main() {
	int c;
	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		perror("Unable to open file");
		return 1;
	}
	
	int check = 0;

	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n+1; j++) {
			c = fgetc(file);
			mem[i][j] = c;
			check++;
		}
	}

	int sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (mem[i][j] == 'A') {
				sum += search2(i, j);
			}
			//printf("%c", (char) mem[i][j]);
		}
	}

	printf("%d", sum);

	fclose(file);
	return 0;
}

// 000 001 010 011 100 101 110 111
//
// | / -- \
