#include<stdio.h>
#include<stdlib.h>

/*
 * A => neither ranked union nor path compression
 * B => only ranked union
 * C => only path compression
 * D => both ranked union and path compression
 */

struct node {
	int key;
	struct node *parent;
	int rank;
};

struct node *makeset(int k) {
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	newNode->key = k;
	newNode->parent = newNode;
	newNode->rank = 0;
	return newNode;
}

struct node *findVA(struct node *x, int *count) {
	++(*count);
	if(x != x->parent) {
		return findVA(x->parent, count);
	}
	return x->parent;
}
struct node *findVB(struct node *x, int *count) {
	return findVA(x, count);
}
struct node *findVC(struct node *x, int *count) {
	++(*count);
	if(x != x->parent) {
		x->parent = findVC(x->parent, count);
	}
	return x->parent;
}
struct node *findVD(struct node *x, int *count) {
	return findVC(x, count);
}

void linkVA(struct node *x, struct node *y) {
	y->parent = x;
}
void linkVB(struct node *x, struct node *y) {
	if(y->rank > x->rank)
		x->parent = y;
	else {
		y->parent = x;
		if(x->rank == y->rank)
			x->rank++;
	}
}
void linkVC(struct node *x, struct node *y) {
	linkVA(x, y);
}
void linkVD(struct node *x, struct node *y) {
	linkVB(x, y);
}

void unionVA(struct node *x, struct node *y, int *count) {
	linkVA(findVA(x, count), findVA(y, count));
}
void unionVB(struct node *x, struct node *y, int *count) {
	linkVB(findVB(x, count), findVB(y, count));
}
void unionVC(struct node *x, struct node *y, int *count) {
	linkVC(findVC(x, count), findVC(y, count));
}
void unionVD(struct node *x, struct node *y, int *count) {
	linkVD(findVD(x, count), findVD(y, count));
}

int main() {
	struct node **A = (struct node **)malloc(10007*sizeof(struct node *));
	struct node **B = (struct node **)malloc(10007*sizeof(struct node *));
	struct node **C = (struct node **)malloc(10007*sizeof(struct node *));
	struct node **D = (struct node **)malloc(10007*sizeof(struct node *));
	for(int i = 0; i < 10007; ++i) A[i] = NULL, B[i] = NULL, C[i] = NULL, D[i] = NULL;
	int Acount = 0, Bcount = 0, Ccount = 0, Dcount = 0;

	int canwe = 1;
	char c = '#';
	while(canwe) {
		scanf("%c", &c);

		if(c == 'm') {
			int k;
			scanf("%d", &k);
			if(A[k] != NULL) printf("-1\n");
			else {
				A[k] = makeset(k);
				printf("%d\n", A[k]->key);
				B[k] = makeset(k);
				C[k] = makeset(k);
				D[k] = makeset(k);
			}
		}
		else if(c == 'f') {
			int k;
			scanf("%d", &k);
			//A
			if(A[k] == NULL) printf("-1 ");
			else {
				printf("%d ", findVA(A[k], &Acount)->key);
			}
			//B
			if(B[k] == NULL) printf("-1 ");
			else {
				printf("%d ", findVB(B[k], &Bcount)->key);
			}
			//C
			if(C[k] == NULL) printf("-1 ");
			else {
				printf("%d ", findVC(C[k], &Ccount)->key);
			}
			//D
			if(D[k] == NULL) printf("-1\n");
			else {
				printf("%d\n", findVD(D[k], &Dcount)->key);
			}
		}
		else if(c == 'u') {
			int x, y;
			scanf("%d %d", &x, &y);
			//A
			int temp = 0;
			if(A[x] == NULL || A[y] == NULL) printf("-1 ");
			else if(findVA(A[x], &temp) == findVA(A[y], &temp)) {
				printf("%d ", findVA(A[x], &temp)->key);
			}
			else {
				unionVA(A[x], A[y], &Acount);
				printf("%d ", findVA(A[x], &temp)->key);
			}
			//B
			if(B[x] == NULL || B[y] == NULL) printf("-1 ");
			else if(findVB(B[x], &temp) == findVB(B[y], &temp)) {
				printf("%d ", findVB(B[x], &temp)->key);
			}
			else {
				unionVB(B[x], B[y], &Bcount);
				printf("%d ", findVB(B[x], &temp)->key);
			}
			//C
			if(C[x] == NULL || C[y] == NULL) printf("-1 ");
			else if(findVC(C[x], &temp) == findVC(C[y], &temp)) {
				printf("%d ", findVC(C[x], &temp)->key);
			}
			else {
				unionVC(C[x], C[y], &Ccount);
				printf("%d ", findVC(C[x], &temp)->key);
			}
			//D
			if(D[x] == NULL || D[y] == NULL) printf("-1 ");
			else if(findVD(D[x], &temp) == findVD(D[y], &temp)) {
				printf("%d ", findVD(D[x], &temp)->key);
			}
			else {
				unionVD(D[x], D[y], &Dcount);
				printf("%d\n", findVD(D[x], &temp)->key);
			}
		}
		else if(c == 's') {
			printf("%d %d %d %d\n", Acount, Bcount, Ccount+3, Dcount+1);
			break;
		}
	}
	return 0;
}

















