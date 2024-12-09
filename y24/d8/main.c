#include <stdio.h>
#include <stdlib.h>

#define N (50)

int map[N][N + 1];

struct pos {
	int x;
	int y;
};
struct node {
	int c;
	struct node *next;
	struct pos *p;
};


struct node *lists[256] = {NULL};

int is_valid(struct pos *p) {

	// if (p->x == 3 && p->y == 1) {
	// 	printf("HEUREKA\n");
	// }

	return (p->x < 0 || p->x >= N || p->y < 0 || p->y >= N) ? 0 : 1;
}

void get_target(struct pos *a, struct pos *b, struct pos *target) {
	target->x = (a->x - b->x);
	target->y = (a->y - b->y);
	// printf("%d %d\n", target->x, target->y);
}

void place_anode(struct node *a, struct node *b, int *answer) {

	struct pos dir = {};
	get_target(a->p, b->p, &dir);
	struct pos target = {a->p->x, a->p->y};

	while (is_valid(&target)) {
		if (map[target.y][target.x] != '#') {
			map[target.y][target.x] = '#';
			*answer = (*answer) + 1;
		}
		target.x += dir.x;
		target.y += dir.y;
	}

	get_target(b->p, a->p, &dir);
	target.x = b->p->x;
	target.y = b->p->y;
	
	while (is_valid(&target)) {
		if (map[target.y][target.x] != '#') {
			map[target.y][target.x] = '#';
			*answer = (*answer) + 1;
		}
		target.x += dir.x;
		target.y += dir.y;
	}
}

void r_insert(struct node *n, struct node *new) {
	if (n->next == NULL) {
		n->next = new;
	} else {
		r_insert(n->next, new);
	}
}

void insert(int c, int x, int y) {
	struct node *new = malloc(sizeof(struct node));
	struct pos *p = malloc(sizeof(struct pos));

	new->c = c;
	new->next = NULL;
	new->p = p;
	p->x = x;
	p->y = y;

	if (lists[c] == NULL) {
		lists[c] = new;
	} else {
		r_insert(lists[c], new);
	}
}

int main() {
	FILE *file = fopen("input.txt", "r");
	if (file == NULL) {
		perror("unable to open file");
		return 1;
	}
	int c;
	int x = 0;
	int y = 0;
	int answer = 0;

	while ((c = fgetc(file)) != EOF) {

		map[y][x] = c;

		if (c != '.' && c != '\n') {
			insert(c, x, y);
		}

		x = (x+1) % (N+1);
		if (x == 0) {
			y++;
		}
	}

	// for (int i = 0; i < 256; i++) {
	// 	if (lists[i] == NULL) continue;
	// 	struct node *n = (lists[i]);
	// 	printf("\n%c: ", i);
	// 	
	// 	while (n != NULL) {
	// 		printf("(%c => %d %d -> %p), ", i, n->p->x, n->p->y, n->next); 
	// 		n = n->next;
	// 	}
	// }
	// printf("\n");

	for (int ci = 0; ci < 256; ci++) {
		
		if (lists[ci] == NULL) continue;

		struct node *n = (lists[ci]);
		struct node *other = n->next;

		while (n->next != NULL) {
			
			place_anode(n, other, &answer);
			
			// printf("(%d %d) ~ (%d %d)\n",n->p->x, n->p->y, other->p->x, other->p->y);

			if (other->next == NULL) {
				n = n->next;
				other = n->next;
			} else {
				other = other->next;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%c",map[i][j]);
		}
		printf("\n");
	}


	printf("%d\n", answer);

	fclose(file);
	return 0;
}



