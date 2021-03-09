#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct node {
	int key1, key2;
	struct node *left;
	struct node *middle;
	struct node *right;
};
struct node *create(int key) {
	struct node *newnode = (struct node*)malloc(sizeof(struct node));
	newnode->key1 = key;
	newnode->key2 = INT_MIN;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->middle = NULL;
	return newnode;
}
struct node* insert(struct node *r, int key) {
	if(r == NULL) {
		r = create(key);
		return r;
	}
	//else {
	//	if(r->key2 == INT_MIN) {
	//		r->left = insert(r->left, key);
	//		return r;
	//	}
	//	else if(r->key1 == INT_MIN) { //key1 is empty
	//			r->right = insert(r->right, key);
	//			return r;
	//		}
	//	else { //key1 and key2 are occupied
	//		if(r->key1 > key) {
	//			r->left = insert(r->left, key);
	//			return r;
	//		}
	//		else if(r->key1 < key && r->key2 < key) {
	//			r->middle = insert(r->middle, key);
	//			return r;
	//		}
	//		else {
	//			r->right = insert(r->right, key);
	//			return r;
	//		}
	//	}
	//}
	if(r->key2 == INT_MIN && r->key1 < key) r->key2 = key;
	else if(key < r->key1) r->left = insert(r->left, key);
	else if(key > r->key1 && key < r->key2) r->middle = insert(r->middle, key);
	else if(key > r->key2) r->right = insert(r->right, key);
	return r;
}
void preorder(struct node *r) {
	//printf("hibefr\n");
	if(r != NULL) {
		//printf("hi\n");
		if(r->key1 != INT_MIN) printf("%d ", r->key1);
		if(r->key2 != INT_MIN) printf("%d ", r->key2);
		preorder(r->left);
		preorder(r->middle);
		preorder(r->right);
	}
}
int main() {
	struct node *r = NULL;
	char c = '#';
	int canwe = 1;
	while(canwe) {
		scanf("%c", &c);
		if(c == 'p') {
			preorder(r);
			continue;
		}
		else if(c == 't') {
			canwe = 0;
			break;
		}
		else if(c == 'i') {
			//printf("hi\n");
			int k;
			scanf("%d", &k);
			r = insert(r, k);
			continue;
		}
	}
	return 0;
}
