#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<limits.h>

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
		else {
			if(x->key <= next_x->key) {
				x->rightSibling = next_x->rightSibling;
				binLink(next_x, x);
			}
			else {
				if(prev_x == NULL) {
					H->head = next_x;
				}
				else {
					prev_x->rightSibling = next_x;
				}
				binLink(x, next_x);
				x = next_x;
			}
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

int levelHelper(struct binTreeNode *ptr) {
	int level = -1;
	while(ptr != NULL) {
		level++;
		ptr = ptr->p;
	}
	return level;
}
void dfs(struct binTreeNode *root, int level) {
	if(root == NULL) return;
	while(root != NULL) {
		if(level == levelHelper(root)) printf("%d ", root->key);
		if(root->leftChild != NULL) dfs(root->leftChild, level);
		root = root->rightSibling;
	}
}
void printThisLevel(struct binTreeNode *root, int level) {
	if(root == NULL) return;
	if(level == 0) {
		printf("%d ", root->key);
		return;
	}
	else {
		dfs(root->leftChild, level);
	}
}
void printTree(struct binTreeNode *root) {
	int maxLevel = -1;
	struct binTreeNode *ptr = root;
	while(ptr != NULL) {
		maxLevel++;
		ptr = ptr->leftChild;
	}
	for(int level = 0; level <= maxLevel; ++level) {
		printThisLevel(root, level);
	}
}
void print(struct binTreeNode *root) {
	struct binTreeNode *ptr = root;
	while(ptr != NULL) {
		printTree(ptr);
		ptr = ptr->rightSibling;
	}
	printf("\n");
}
struct binTreeNode *binHeapMinimum(struct binHeap *H) {
	struct binTreeNode *y = NULL;
	struct binTreeNode *x = H->head;
	int min = INT_MAX;
	while(x != NULL) {
		if(x->key < min) {
			min = x->key;
			y = x;
		}
		x = x->rightSibling;
	}
	return y;
}
struct binTreeNode *reverse(struct binTreeNode *prev, struct binTreeNode *ptr, struct binTreeNode *next) {
	if(next == NULL) {
		ptr->p = NULL;
		ptr->rightSibling = prev;
		return ptr;
	}
	ptr->p = NULL;
	ptr->rightSibling = prev;
	prev = ptr;
	ptr = next;
	next = ptr->rightSibling;
	return reverse(prev, ptr, next);
}
struct binHeap *binHeapExtractMin(struct binHeap *H, int flag) {
	if(H == NULL) return NULL;
	struct binTreeNode *x = binHeapMinimum(H);
	struct binTreeNode *ptr = H->head;
	if(ptr == NULL) return NULL;
	if(ptr == x) H->head = x->rightSibling;
	else {
		while(ptr != NULL) {
			if(ptr->rightSibling == x) {
				ptr->rightSibling = x->rightSibling;
				break;
			}
			ptr = ptr->rightSibling;
		}
	}
	/* x contains the root of the binomial tree
	 * x should be deleted
	 * and the rest of the tree has to be unioned with the heap
	 */
	struct binHeap *H_ = makeBinHeap();
	struct binTreeNode *y = x->leftChild;
	if(y != NULL) y = reverse(NULL, y, y->rightSibling);
	H_->head = y;
	H = binHeapUnion(H, H_);
	if(flag) printf("%d\n", x->key);
	free(x);
	return H;
}
struct binTreeNode *searchDFS(struct binTreeNode *root, int k) {
	if(root == NULL) return NULL;
	while(root != NULL) {
		if(root->key == k) return root;
		if(root->leftChild != NULL) {
			if(searchDFS(root->leftChild, k) != NULL) 
				return searchDFS(root->leftChild, k);
		}
		root = root->rightSibling;
	}
	return NULL;
}
int binHeapDecreaseKey(struct binHeap *H, struct binTreeNode *x, int k) {
	if(x->key < k) return -1;
	x->key -= k;
	int ans = x->key;
	struct binTreeNode *y = x;
	struct binTreeNode *z = y->p;
	struct binTreeNode *temp = (struct binTreeNode *)malloc(sizeof(struct binTreeNode));
	while(z != NULL && y->key < z->key) {
		temp->key = y->key;

		y->key = z->key;

		z->key = temp->key;

		y = z;
		z = y->p;
	}
	return ans;
}
struct binHeap *binHeapDelete(struct binHeap *H, struct binTreeNode *x) {
	binHeapDecreaseKey(H, x, x->key);
	H = binHeapExtractMin(H, 0);
	return H;
}
int main() {
	struct binHeap *H = makeBinHeap();
	int canwe = 1;
	char c = '*';
	while(canwe) {
		scanf("%c", &c);
		if(c == 'i') {
			int k;
			scanf("%d", &k);
			H = binHeapInsert(H, k);
		}
		else if(c == 'p') {
			print(H->head);
		}
		else if(c == 'm') {
			struct binTreeNode *ptr = binHeapMinimum(H);
			if(ptr != NULL) printf("%d\n", ptr->key);
		}
		else if(c == 'x') {
			H = binHeapExtractMin(H, 1);
		}
		else if(c == 'r') {
			int y, z;
			scanf("%d %d", &y, &z);
			struct binTreeNode *ptr = searchDFS(H->head , y);
			if(ptr == NULL) printf("-1\n");
			else if(ptr->key < z) printf("-1\n");
			else printf("%d\n", binHeapDecreaseKey(H, ptr, z));
		}
		else if(c == 'd') {
			int k;
			scanf("%d", &k);
			struct binTreeNode *ptr = searchDFS(H->head, k);
			if(ptr == NULL) printf("-1\n");
			else {
				H = binHeapDelete(H, ptr);
				printf("%d\n", k);
			}
		}
		else if(c == 'e') {
			canwe = 0;
			break;
		}
	}
	return 0;
}
