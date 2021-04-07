#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

struct RBNode {
	int key;
	char color;//red = 'r', black = 'b'
	struct RBNode *left;
	struct RBNode *right;
};
struct RBTree {
	struct RBNode *root;
};

char colorHelper(struct RBNode *x) {
	if(x == NULL) return 'b';
	return x->color;
}
struct RBNode *leftRotate(struct RBNode *n) {
	struct RBNode *p = n->right;
	n->right = p->left;
	p->left = n;
	n = p;
	return n;
}
struct RBNode *rightRotate(struct RBNode *n) {
	struct RBNode *p = n->left;
	n->left = p->right;
	p->right = n;
	n = p;
	return n;
}
struct RBNode *createRBNode(int k) {
	struct RBNode *ptr = (struct RBNode *)malloc(sizeof(struct RBNode));
	ptr->key = k;
	ptr->color = 'r';
	ptr->left = NULL;
	ptr->right = NULL;
	return ptr;
}

struct RBNode *rbTreeInsert(struct RBNode *r, struct RBNode *x) {
	if(r == NULL) return x;
	else if(r->key < x->key) {
		r->right = rbTreeInsert(r->right, x);
		if(colorHelper(r->right) == 'b') return r;
		else {
			if(colorHelper(r->right->left) == 'r' || colorHelper(r->right->right) == 'r') {
				if(colorHelper(r->left) == 'r') { //case 1: uncle is red
					r->left->color = 'b';
					r->right->color = 'b';
					r->color = 'r';
					return r;
				}
				else { //case 2: uncle is black
					if(colorHelper(r->right->left) == 'r') { //case 3
						//converting case 3 to case 2
						r->right = rightRotate(r->right);
					}
					//case 2 continues
					struct RBNode *y = leftRotate(r);
					y->left->color = 'r';
					y->color = 'b';
					return y;
				}
			}
		}
	}
	else if(r->key > x->key) {
		r->left = rbTreeInsert(r->left, x);
		if(colorHelper(r->left) == 'b') return r;
		else {
			if(colorHelper(r->left->left) == 'r' || colorHelper(r->left->right) == 'r') {
				if(colorHelper(r->right) == 'r') { // case 1: uncle is red
					r->right->color = 'b';
					r->left->color = 'b';
					r->color = 'r';
					return r;
				}
				else { // case 2: uncle is black
					if(colorHelper(r->left->right) == 'r') { //case 3
						//converting case 3 to case 2
						r->left = leftRotate(r->left);
					}
					//case 2 continues
					struct RBNode *y = rightRotate(r);
					y->right->color = 'r';
					y->color = 'b';
					return y;
				}
			}
		}
	}
	return r;
}
struct RBNode *InsertRedBlack(struct RBNode *root, int k) {
	struct RBNode *x = createRBNode(k);
	x->color = 'r';
	return rbTreeInsert(root, x);
}
void RBTreeInsert(struct RBTree *T, int k) {
	T->root = InsertRedBlack(T->root, k);
	if(T->root->color == 'r') T->root->color = 'b';
}
void printer(struct RBNode *r) {
	if(r == NULL) {
		printf("( ) ");
		return;
	}
	printf("( ");
	printf("%d %c ", r->key, (r->color == 'r' ? 'R' : 'B'));
	printer(r->left);
	printer(r->right);
	printf(") ");
}

int main() {
	struct RBTree *T = (struct RBTree *)malloc(sizeof(struct RBTree));
	T->root = NULL;

	char buffer[100];
	int buffersize = 0;
	char c;
	while(1) {
		scanf("%c", &c);
		if(c == 't') break;
		else if(c == '\n') {
			if(buffersize == 0) continue;
			RBTreeInsert(T, atoi(buffer));
			printer(T->root);
			printf("\n");
			buffersize = 0;
		}
		else {
			buffer[buffersize++] = c;
			buffer[buffersize] = '\0';
		}
	}

	return 0;
}
