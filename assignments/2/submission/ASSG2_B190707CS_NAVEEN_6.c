#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

struct tNode {
    int key;
    struct tNode *l;
    struct tNode *r;
};
struct tree {
    struct tNode *root;
};

struct tNode *createNode(int k) {
    struct tNode *newNode = (struct tNode *)malloc(sizeof(struct tNode));
    newNode->key = k;
    newNode->l = NULL;
    newNode->r = NULL;
    return newNode;
}
void insert(struct tree *t, struct tNode *z) {
    struct tNode *y = NULL;
    struct tNode *x = t->root;

    while(x != NULL) {
        y = x;
        if(z->key < x->key) x = x->l;
        else x = x->r; 
    }
    /** y stores the parrent node inside the loop 
     * if y is null that implies that 
     * z should be the root node 
     * since root is the only place where parent in null
    **/
    if(y == NULL) t->root = z;// tree was empty
    else if(z->key < y->key) y->l = z;
    else y->r = z;
}
struct tNode *search(struct tree *t, int k) {
    struct tNode *x = t->root;
    while(x!= NULL && k!=x->key) {
        if(k < x->key) x = x->l;
        else x = x->r;
    }
    return x;
}

struct tNode *treeMin(struct tNode *x) {
    while(x != NULL && x->l != NULL) x = x->l;
    return x;
}

void inorderHelp(struct tNode *r) {
    if(r != NULL) {
        inorderHelp(r->l);
        printf("%d ", r->key);
        inorderHelp(r->r);
    }
}
void inorder (struct tree *t) {
    inorderHelp(t->root);
    printf("\n");
}
void preorderHelp(struct tNode *r) {
    if(r != NULL) {
        printf("%d ", r->key);
        preorderHelp(r->l);
        preorderHelp(r->r);
    }
}
void preorder(struct tree *T) {
    preorderHelp(T->root);
    printf("\n");
}
void postorderHelp(struct tNode *r) {
    if(r!=NULL) {
        postorderHelp(r->l);
        postorderHelp(r->r);
        printf("%d ", r->key);
    }
}
void postorder(struct tree *T) {
    postorderHelp(T->root);
    printf("\n");
}

struct tNode *treeMax(struct tNode *r) {
	struct tNode *ptr = r;
	while(ptr->r != NULL) {
		ptr = ptr->r;
	}
	if(ptr == NULL) return NULL;
	return ptr;
}
int maxPath(struct tNode *root, int a, int b) {
	//first finding the common ancestor
	struct tNode *ptr = root;
	if(ptr == NULL) return INT_MIN;
	if(a > b) {
		int t = a;
		a = b;
		b = t;
	}
	while(ptr != NULL && !(a <= ptr->key && ptr->key <= b)) {
		if( a < ptr->key && b < ptr->key) ptr = ptr->l;
		if( a > ptr->key && b > ptr->key) ptr = ptr->r;
	}
	int maxelem = INT_MIN;
	struct tNode *commonMOMorDAD = ptr;
	// a
	while(ptr != NULL && ptr->key != a) {
		if(maxelem < ptr->key && ptr->key != a && ptr->key != b) maxelem = ptr->key;
		if(a < ptr->key) ptr = ptr->l;
		else ptr = ptr->r;
	}
	// b
	ptr = commonMOMorDAD;
	while(ptr != NULL && ptr->key != b) {
		if(maxelem < ptr->key && ptr->key != b && ptr->key != a) maxelem = ptr->key;
		if(b < ptr->key) ptr = ptr->l;
		else ptr = ptr->r;
	}
	return maxelem;
}
int main() {
	struct tree *T = (struct tree *)malloc(sizeof(struct tree));
	T->root = NULL;

	char buffer[100];
	int buffersize = 0;
	while(1) {
		char c;
		scanf("%c", &c);

		if(c == '\n') {
			if(buffersize == 0) break;
			// printf("%d\n", atoi(buffer));
			insert(T, createNode(atoi(buffer)));
			buffersize = 0;
			break;
		}
		else if(c == ' ') {
			// printf("%d\n", atoi(buffer));
			insert(T, createNode(atoi(buffer)));
			buffersize = 0;
		}
		else {
			buffer[buffersize++] = c;
			buffer[buffersize] = '\0';
		}
	}
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d\n", maxPath(T->root, a, b)); 
	return 0;
}
