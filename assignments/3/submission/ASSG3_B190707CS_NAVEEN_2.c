#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>
//Structure declaration---------------------------------------------------------------------------------------------------------------------------------
struct avlNode {
	int key;
	int count;
	struct avlNode* left;
	struct avlNode* right;
};
struct avlTree {
	struct avlNode *root;
};
//max and min-------------------------------------------------------------------------------------------------------------------------------------------
int max(int a, int b) {
	return ( a > b ? a : b);
}
int min(int a, int b) {
	return (a < b ? a : b);
}

//Height finding helper---------------------------------------------------------------------------------------------------------------------------------
int height(struct avlNode *node) {
	/* I'm maintaing null nodes height as 0
	 * if there is a single node then its height is 1
	 * 1
	 *  \
	 *   2
	 * here 1's height is 2 and 2's height is 1
	 *
	 * CAUTION: I'm finding height of a node ins O(lg n), but you can do it in O(1), i am lazy to do case work
	 */
	if(node == NULL) return 0;
	return max(height(node->left), height(node->right)) + 1;
}

//Create Avl node with key k----------------------------------------------------------------------------------------------------------------------------
struct avlNode *createAvlNode(int k) {
	struct avlNode *ptr = (struct avlNode *)malloc(sizeof(struct avlNode));
	ptr->key = k;
	ptr->count = 1;
	ptr->left = NULL;
	ptr->right = NULL;
	return ptr;
}

//Single Rotate functions-------------------------------------------------------------------------------------------------------------------------------
struct avlNode *leftRotate(struct avlNode *n) {
	struct avlNode *p = n->right;
	n->right = p->left;
	p->left = n;
	n = p;
	return n;
}
struct avlNode *rightRotate(struct avlNode *n) {
	struct avlNode *p = n->left;
	n->left = p->right;
	p->right = n;
	n = p;
	return n;
}

//Search------------------------------------------------------------------------------------------------------------------------------------------------
struct avlNode* searchHelper(struct avlNode *T, int k) {
	if(T == NULL) return NULL;
	if(T->key == k) return T;
	if(T->key < k) return searchHelper(T->right, k);
	return searchHelper(T->left, k);
}
struct avlNode* search(struct avlTree *A, int k) {
	return searchHelper(A->root, k);
}

//Insert Functions--------------------------------------------------------------------------------------------------------------------------------------
struct avlNode *insertHelper(struct avlNode *T, int x) {
	if(T == NULL) {
		T = createAvlNode(x);
	}
	else if(T->key == x) {
		(T->count)++;
		return T;
	}
	else if(T->key > x) {
		T->left = insertHelper(T->left, x);
		if(height(T->left) - height(T->right) == 2) {
			if(T->left->key > x) {
				T = rightRotate(T);
			}
			else {
				T->left = leftRotate(T->left);
				T = rightRotate(T);
			}
		}
	}
	else {
		T->right = insertHelper(T->right, x);
		if(height(T->right) - height(T->left) == 2) {
			if(T->right->key < x) T = leftRotate(T);
			else {
				T->right = rightRotate(T->right);
				T = leftRotate(T);
			}
		}
	}
	//T->height = max(height(T->left), height(T->right)) + 1;
	return T;
}
void insert(struct avlTree *A, int k) {
	A->root = insertHelper(A->root, k);
}

//Print Parenthesis form--------------------------------------------------------------------------------------------------------------------------------
void printTreeHelper(struct avlNode *T) {
	if(T == NULL) {
		printf("( ) ");
		return;
	}
	printf("( ");
	//printf("%d(%d) ", T->key, height(T));
	printf("%d ", T->key);
	printTreeHelper(T->left);
	printTreeHelper(T->right);
	printf(") ");
}
void printTree(struct avlTree *A) {
	printTreeHelper(A->root);
	printf("\n");
}

//Pring Sorted form-------------------------------------------------------------------------------------------------------------------------------------
void printSortHelper(struct avlNode *T) {
	if(T == NULL) return;
	printSortHelper(T->left);
	for(int i = 0; i < T->count; ++i) printf("%d ", T->key);
	printSortHelper(T->right);
}
void printSort(struct avlTree *A) {
	printSortHelper(A->root);
	printf("\n");
}

int main() {
	struct avlTree *T = (struct avlTree *)malloc(sizeof(struct avlTree));
	T->root = NULL;
	int n = 0;
	scanf("%d", &n);
	int k;
	for(int i = 0; i < n; ++i) {
		scanf("%d", &k);
		insert(T, k);
	}
	printSort(T);
	return 0;
}








