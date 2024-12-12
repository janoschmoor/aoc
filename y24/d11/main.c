#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct node {
	struct node *next;
	long val;
};

void split_long(long num, long *first_half, long *second_half) {
	char num_str[21]; // Enough to store a 64-bit long number
	snprintf(num_str, sizeof(num_str), "%ld", num);

	int num_digits = strlen(num_str);
	int half_digits = num_digits / 2;

	char first_half_str[half_digits + 1];
	char second_half_str[half_digits + 1];

    strncpy(first_half_str, num_str, half_digits);
    first_half_str[half_digits] = '\0'; // Null-terminate
    strcpy(second_half_str, num_str + half_digits);

    *first_half = atol(first_half_str);
    *second_half = atol(second_half_str);
}

void r_insert(struct node *n, struct node *new) {
	if (n->next == NULL) {
		n->next = new;
	} else {
		r_insert(n->next, new);
	}
}
void insert(struct node *n, long value) {
	struct node *new = malloc(sizeof(struct node));
	new->val = value;
	new->next = NULL;

	r_insert(n, new);
}

void print(struct node *n, int i) {
	if (n == NULL) return;
	printf("(i:%d = val:%ld) -> \n", i, n->val);
	print(n->next, i+1);
	if (i == 0) {
		printf("\n");
	}
}

void blink(struct node *n, struct node *old) {
	if (n == old) return;
	if (n == NULL) return;

	// printf("val: %ld ", n->val);

	int num_digits = 0;
	long num = n->val;
	while(num > 0) {
		num /= 10;
		num_digits++;
	}

	if (n->val == 0) {
		n->val = 1;
	} else if (num_digits % 2 == 0) {
		num = n->val;
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
		// printf("%ld %ld - %ld  %ld\n", v1, v2, n->val, 1*((n->val) % 10));
		struct node *new = malloc(sizeof(struct node));
    		if (new == NULL) { 
   		     	perror("Failed to allocate memory");
   		     	exit(EXIT_FAILURE);
  		}
		n->val = v1;

 		new->val = v2;
 		new->next = n->next;
 		n->next = new;

		blink(new->next, n);
		return;
	} else {
		if (n->val >= 0x103091B51F5E1A) {
			printf("oops");
			return;
		}
		n->val *= 2024;
	}

	blink(n->next, n);
}

int main() {
	FILE *file = fopen("input.txt", "r");
	
	int size = 0;
	int c;
	struct node sentinel = {NULL, 0};

	c = fgetc(file);
	while ((c) != EOF) {
		long n = 0;
		while (c != ' ' && c != '\n' && c != EOF) {
			n = n * 10 + (c - '0');
			c = fgetc(file);
		}
		if (c != EOF) c = fgetc(file);
		insert(&sentinel, n);
	}

	// print(sentinel.next, 0);
	
	for (int i = 0; i < 25; i++) {
		blink(sentinel.next, &sentinel);
		// print(sentinel.next, 0);
	}

	// print(sentinel.next, 0);

	int answer = 0;
	struct node *n = sentinel.next;

	while (n!=NULL) {
		answer++;
		n = n->next;
	}

	printf("%d\n", answer);
	fclose(file);
	return 0;
}
