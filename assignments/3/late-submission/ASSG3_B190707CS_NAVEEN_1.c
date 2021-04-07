#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>
//Structure declaration---------------------------------------------------------------------------------------------------------------------------------
struct avlNode {
	int key;
	struct avlNode* left;
	struct avlNode* right;
};
struct avlTree {
	struct avlNode *root;
};

//Min Nod and max node----------------------------------------------------------------------------------------------------------------------------------
struct avlNode *minNode(struct avlNode *T) {
	if(T == NULL) return NULL;
	while(T->left != NULL) T = T->left;
	return T;
}
struct avlNode *maxNode(struct avlNode *T) {
	if(T == NULL) return NULL;
	while(T->right != NULL) T = T->right;
	return T;
}
int abs(int a) {
	return (a < 0 ? -1*a : a);
}

//max and min and abs-----------------------------------------------------------------------------------------------------------------------------------
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

//Balance factor----------------------------------------------------------------------------------------------------------------------------------------
int bfHelper(struct avlNode *T) {
	if(T == NULL) return 0;
	return (height(T->left) - height(T->right));
}
int getBalance(struct avlTree *A, int k) {
	struct avlNode *ptr = search(A, k);
	return bfHelper(ptr);
}

//isAvl-------------------------------------------------------------------------------------------------------------------------------------------------
int isAvlHelper(struct avlNode * T) {
	if(T == NULL) return 1;
	if(abs(bfHelper(T)) > 1) return 0;
	if(isAvlHelper(T->left) && isAvlHelper(T->right)) return 1;
	return 0;
}
int isAvl(struct avlTree *A) {
	return isAvlHelper(A->root);
}

//Insert Functions--------------------------------------------------------------------------------------------------------------------------------------
struct avlNode *insertHelper(struct avlNode *T, int x) {
	if(T == NULL) {
		T = createAvlNode(x);
	}
	else if(T->key == x) return T;
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

//Delete------------------------------------------------------------------------------------------------------------------------------------------------
struct avlNode *deleteHelper(struct avlNode *T, int k) {
	if(T == NULL) return NULL;
	else if(k < T->key) T->left = deleteHelper(T->left, k);
	else if(k > T->key) T->right = deleteHelper(T->right, k);
	else { //T points the node to be deleted
		if(T->left == NULL) {
			struct avlNode *ptr = T->right;
			free(T);
			T = ptr;
		}
		else if(T->right == NULL) {
			struct avlNode *ptr = T->left;
			free(T);
			T = ptr;
		}
		else {
			struct avlNode *ptr = minNode(T->right);
			T->key = ptr->key;
			T->right = deleteHelper(T->right, T->key);
		}
	}
	int bf = bfHelper(T);
	if(abs(bf) > 1) {
		if(bf < -1) { //case 3
			if(bfHelper(T->right) <= 0) { //case 3a & 3b
				T = leftRotate(T);
			}
			else { //case 3c
				T->right = rightRotate(T->right);
				T = leftRotate(T);
			}
		}
		else if(bf > 1) { //case 3 mirror
			if(bfHelper(T->left) >= 0) { //case 3a & 3b mirror
				T = rightRotate(T);
			}
			else { //case 3c mirror
				T->left = leftRotate(T->left);
				T = rightRotate(T);
			}
		}
	}
	return T;
}
int deleteNode(struct avlTree *A, int k) {
	// returns 1 if we can delete k
	if(search(A, k) == NULL) return 0;
	A->root = deleteHelper(A->root, k);
	return 1;
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

int main() {
	struct avlTree *T = (struct avlTree *)malloc(sizeof(struct avlTree));
	T->root = NULL;
	int canwe = 1;
	char ch = '#';
	while(canwe) {
		scanf("%c", &ch);
		switch(ch) {
			case 'i': {
				int k;
				scanf("%d", &k);
				insert(T, k);
				break;
			}
			
			case 's': {
				int k;
				scanf("%d", &k);
				struct avlNode* ptr = search(T, k);
				if(ptr == NULL) printf("FALSE\n");
				else printf("TRUE\n");
				break;
			}

			case 'p': {
				printTree(T);
				break;
			}

			case 'e': {
				canwe = 0;
				break;
			}

			case 'd': {
				int k;
				scanf("%d", &k);
				if(deleteNode(T, k)) printf("%d\n", k);
				else printf("FALSE\n");
				break;
			}

			case 'b': {
				int k;
				scanf("%d", &k);
				if(search(T, k) == NULL) printf("FALSE\n");
				else {
					printf("%d\n", getBalance(T, k));
				}
				break;
			}
		}
	}
	return 0;
}







