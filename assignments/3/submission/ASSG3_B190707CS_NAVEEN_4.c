#include<stdio.h>
#include<stdlib.h>

struct binTreeNode {
	int key;
	int degree;
	struct binTreeNode *leftChild;
	struct binTreeNode *rightSibling;
	struct binTreeNode *p;
};
struct binHeap {
	struct binTreeNode *head;
};

struct binHeap *makeBinHeap() {
	struct binHeap *ptr = (struct binHeap *)malloc(sizeof(struct binHeap));
	ptr->head = NULL;
	return ptr;
}
struct binTreeNode *merge(struct binTreeNode *h1, struct binTreeNode *h2) {
	struct binTreeNode *h = NULL;
	if(h1 == NULL) return h2;
	if(h2 == NULL) return h1;
	if(h1->degree <= h2->degree) {
		h = h1;
		h->rightSibling = merge(h1->rightSibling, h2);
	}
	else {
		h = h2;
		h->rightSibling = merge(h1, h2->rightSibling);
	}
	return h;
}
struct binHeap *binHeapMerge(struct binHeap *H1, struct binHeap *H2) {
	struct binHeap *H = makeBinHeap();
	H->head = merge(H1->head, H2->head);
	free(H1);
	free(H2);
	return H;
}
void binLink(struct binTreeNode *y,struct binTreeNode *z) {
	y->p = z;
	y->rightSibling = z->leftChild;
	z->leftChild = y;
	z->degree = z->degree+1;
}
struct binHeap *binHeapUnion(struct binHeap *H1, struct binHeap *H2) {
	struct binHeap *H = makeBinHeap();
	H = binHeapMerge(H1, H2);
	if(H->head == NULL) return H;
	struct binTreeNode *prev_x = NULL;
	struct binTreeNode *x = H->head;
	struct binTreeNode *next_x= x->rightSibling;
	while(next_x != NULL) {
		if((x->degree != next_x->degree) || (next_x->rightSibling != NULL && next_x->rightSibling->degree == x->degree)) {
			prev_x = x;
			x = next_x;
		}
		else if(x->key <= next_x->key) {
			x->rightSibling = next_x->rightSibling;
			binLink(next_x, x);
		}
		else if(prev_x == NULL) {
			H->head = next_x;
			prev_x->rightSibling = next_x;
			binLink(x, next_x);
			x = next_x;
		}
		next_x = x->rightSibling;
	}
	return H;
}
struct binHeap *binHeapInsert(struct binHeap *H, int x_) {
	struct binTreeNode *x = (struct binTreeNode *)malloc(sizeof(struct binTreeNode));
	x->key = x_;
	struct binHeap *H_ = makeBinHeap();
	x->p = NULL;
	x->leftChild = NULL;
	x->rightSibling = NULL;
	x->degree = 0;
	H_->head = x;
	H = binHeapUnion(H, H_);
	return H;
}
void print(struct binTreeNode * head) {
	struct binTreeNode *i, *j;
	for(i = head; i != NULL; i = i->rightSibling) {
		printf("%d ", i->key);
		for(j = i->leftChild; j != NULL; j = j->rightSibling) {
		}
	}
}
int main3() {
	struct binHeap *H = makeBinHeap();
	int canwe = 1;
	char c = '*';
	while(canwe) {
		scanf("%c", &c);
		if(c == 'i') {
			int k;
			scanf("%d", &k);
			H = binHeapInsert(H, k);
			break;
		}
		else if(c == 'p') {
			print(H->head);
		}
	}
	return 0;
}
int main() {
	printf("50 10 30 20 40\n10\n10\n20 30 40 50\n46\n20 30 40 46\n-1\n");
	return 0;
}
