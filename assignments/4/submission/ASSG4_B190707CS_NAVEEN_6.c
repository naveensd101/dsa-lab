#include<stdio.h>
#include<stdlib.h>

struct fibNode {
	struct fibNode *parent;
	int key;
	int mark; // 0 if not marked
	int degree;
	struct fibNode *left, *right, *child;
};

struct fibHeap {
	struct fibNode *min;
	int n; //num of nodes
};

struct fibHeap *MakeHeap() {
	struct fibHeap *newHeap = (struct fibHeap *)malloc(sizeof(struct fibHeap));
	newHeap->min = NULL;
	newHeap->n = 0;
	return newHeap;
}

struct fibNode *MakeNode(int k) {
	struct fibNode *newNode = (struct fibNode *)malloc(sizeof(struct fibNode));
	newNode->parent = NULL;
	newNode->key = k;
	newNode->mark = 0;
	newNode->degree = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->child = NULL;
	return newNode;
}

void insert(struct fibHeap *H, int k) {
	struct fibNode *x = MakeNode(k);
	x->degree = 0;
	x->parent = NULL;
	x->child = NULL;
	x->mark = 0; //FALSE
	if(H->min == NULL) {
		x->left = x;
		x->right = x;
		H->min = x;
	}
	else {
		x->left = H->min;
		x->right = H->min->right;
		H->min->right->left = x;
		H->min->right = x;
		if(x->key < H->min->key) {
			H->min = x;
		}
	}
	H->n += 1;
}

struct fibNode *minimum(struct fibHeap *H) {
	return H->min;
}

struct fibHeap *fibHeapUnion(struct fibHeap *H1, struct fibHeap *H2) {
	if(H1 == NULL || H1->min == NULL) return H2;
	if(H2 == NULL || H2->min == NULL) return H1;
	struct fibHeap *H = MakeHeap();
	H->min = H1->min;
	//Concatination start-------------------------------
	struct fibNode *t;
	t = H2->min->right;
	H2->min->right->left = H->min;
	H2->min->right = H->min->right;
	H->min->right->left = H2->min;
	H->min->right = t;
	//Concatination end---------------------------------
	if(H1->min == NULL || (H2->min != NULL && H2->min->key < H1->min->key))
		H->min = H2->min;
	H->n = H1->n + H2->n;
	return H;
}

void fibHeapLink(struct fibHeap *H, struct fibNode *y, struct fibNode *x) {
	//start Remover y from root list of H---------------
	y->left->right = y->right;
	y->right->left = y->left;
	//end Remover y from root list of H-----------------

	//start make y a child of x and x.degree++----------
	if(x->child == NULL) {
		x->child = y;
		y->parent = x;
	}
	else {
		y->left = x->child;
		y->right = x->child->right;
		x->child->right->left = y;
		x->child->right = y;
		y->parent = x;
	}
	x->degree++;
	//end make y a child of x and x.degree++------------

	y->mark = 0;
}

void consolidate(struct fibHeap *H) {
	if(H == NULL || H->min == NULL) return;
	int D = H->n;
	int logD = 32 - __builtin_clz(D) - 1;
	logD+=3;
	struct fibNode **A = (struct fibNode **)malloc(logD*sizeof(struct fibNode *));
	for(int i = 0; i < logD; ++i) {
		A[i] = NULL;
	}

	struct fibNode *w = H->min;
	struct fibNode *x, *y;
	do {
		x = w;
		int d = x->degree;
		while(A[d] != NULL) {
			y = A[d];
			if(x->key > y->key) {
				struct fibNode *t = x;
				x = y;
				y = t;
			}
			fibHeapLink(H, y, x);
			A[d] = NULL;
			d = d + 1;
		}
		A[d] = x;
		w = w->left;
	} while(w != H->min);
	H->min = NULL;
	for(int i = 0; i < logD; ++i) {
		if(A[i] != NULL) {
			if(H->min == NULL) {
				H->min = A[i];
			}
			else {
				//insert A[i] into H's root list
				A[i]->left = H->min;
				A[i]->right = H->min->right;
				H->min->right->left = A[i];
				H->min->right = A[i];
				if(A[i]->key < H->min->key) {
					H->min = A[i];
				}
			}
		}
	}
}

struct fibNode *fibHeapExtractMin(struct fibHeap *H) {
	struct fibNode *z = H->min;
	if(z != NULL) {
		struct fibNode *x = z->child;
		do {
			if(x == NULL) break;
			//add x to the root list of H
			struct fibNode *t = x->left;
			x->left = H->min;
			x->right = H->min->right;
			H->min->right->left = x;
			H->min->right = x;
			//end add x to root list of H
			x->parent = NULL;

			x = t;
		} while(x != H->min);
		//remove z from root list
		z->left->right = z->right;
		z->right->left = z->left;
		//end remover z from root list
		if(z == z->right) H->min = NULL;
		else {
			H->min = z->right;
			consolidate(H);
		}
		H->n = H->n - 1;
	}
	return z;
}

void printRootList(struct fibHeap *H) {
	if(H == NULL || H->min == NULL) return;
	struct fibNode *ptr = H->min;
	printf("%d ", ptr->key);
	ptr = ptr->left;
	while(ptr != H->min) {
		printf("%d ", ptr->key);
		ptr = ptr->left;
	}
	printf("\n");
	return;
}

void cut(struct fibHeap *H, struct fibNode *x, fibNode *y) {
	if(H == NULL || H->min == NULL || x == NULL || y == NULL) return;
	if(x == x->right) {
		y->child = NULL;
		x->parent = NULL;
	}
	else {
		y->child = x->right;
		x->right->left = x->left;
		x->left->right = x->right;
		x->parent = NULL;
	}
	x->left = H->min;
	x->right = H->min->right;
	H->min->right->left = x;
	H->min->right = x;
	x->parent = NULL;
	x->mark = 0;
}

void cascadingCut(struct fibHeap *H, struct fibNode *y) {
	if(H == NULL || H->min == NULL || y == NULL) return;
	struct fibNode *z = y->parent;
	if(z != NULL) {
		if(y->mark == 0) 
			y->mark = 1;
		else {
			cut(H, y, z);
			cascadingCut(H, z);
		}
	}
}


int main() {
	struct fibHeap *H = MakeHeap();
	char c = '#';
	int canwe = 1;
	while(canwe) {
		scanf("%c", &c);
		if(c == 'i') {
			int k;
			scanf("%d", &k);
			insert(H, k);
		}
		else if(c == 'p') {
			printRootList(H);
		}
		else if(c == 'e') {
			canwe = 0;
			break;
		}
		else if(c == 'm') {
			if(H->min == NULL || H == NULL) continue;
			printf("%d\n", minimum(H)->key);
		}
		else if(c == 'x') {
			struct fibNode *ptr = fibHeapExtractMin(H);
			printf("%d\n", ptr->key);
		}
	}
	return 0;
}









