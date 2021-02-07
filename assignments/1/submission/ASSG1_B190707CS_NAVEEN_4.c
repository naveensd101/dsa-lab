#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct node {
	struct tNode *treenode;
	struct node *next;
};
struct queue {
	struct node *head;
	struct node *tail;
};
int queueEmpty(struct queue *q) {
	return (q->head == NULL && q->tail == NULL ? 1 : 0);
}
struct node *CreateNode(struct tNode *k) {
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	(*newNode).treenode = k;
	(*newNode).next = NULL;

	return newNode;
}
void enqueue(struct queue *q, struct node *x) {
	if(queueEmpty(q)) q->head = x, q->tail = x;
	else q->tail->next = x, q->tail = x;
}
struct tNode *dequeue(struct queue *q) {
	if(queueEmpty(q)) return NULL;
	else {
		if(q->head == q->tail) {
			struct node *pointer = q->head;
			q->head = NULL;
			q->tail = NULL;

			pointer->next = NULL;
			struct tNode *tosend = pointer->treenode;
			free(pointer);
			return tosend;
		}
        else {
            struct node *pointer = q->head;
            q->head = q->head->next;
            pointer->next = NULL;
			struct tNode *tosend = pointer->treenode;
            free(pointer);
            return tosend;
        }
	}
	return NULL;
}


struct tNode {
    int key;
    int d;
    struct tNode *l;
    struct tNode *r;
    struct tNode *p;
};
struct tree {
    struct tNode *root;
};

struct tNode *createNode(int k) {
    struct tNode *newNode = (struct tNode *)malloc(sizeof(struct tNode));
    newNode->key = k;
    newNode->d = 0;
    newNode->l = NULL;
    newNode->r = NULL;
    newNode->p = NULL;
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
    z->p = y;
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
void transplant(struct tree *T, struct tNode *u, struct tNode *v) {
    if(u->p == NULL) T->root = v;
    else if(u == u->p->l) u->p->l = v;
    else u->p->r = v;
    if(v!=NULL) v->p = u->p;
}
struct tNode *treeMin(struct tNode *x) {
    while(x != NULL && x->l != NULL) x = x->l;
    return x;
}
struct tNode *treeMax(struct tNode *x) {
    while(x != NULL && x->r != NULL) x = x->r;
    return x;
}
void delete(struct tree *T, struct tNode *z) {
    struct tNode *y = NULL;
    if(z->l == NULL) transplant(T, z, z->r);
    else if(z->r == NULL) transplant(T, z, z->l);
    else {
        y = treeMin(z->r);
        if(y->p != z) {
            transplant(T,y,y->r);
            y->r = z->r;
            y->r->p = y;
        }
        transplant(T, z, y);
        y->l = z->l;
        y->l->p = y;
    }
   // printf("%d\n", z->key);
    free(z);
}
struct tNode *successor(struct tree *T, int k) {
    struct tNode *x = search(T, k);
    if(x == NULL) return NULL;
    if(x->r != NULL) return treeMin(x->r);
    struct tNode *y = x->p;
    while(y != NULL && x == y->r) {
        x = y;
        y = y->p;
    }
    return y;
}
struct tNode *predecessor(struct tree *T, int k) {
    struct tNode *x = search (T, k);
    if(x == NULL) return NULL;
    if(x->l != NULL) return treeMax(x->l);
    struct tNode *y = x->p;
    while(y != NULL && x == y->l) {
        x = y;
        y = y->p;
    }
    return y;
}


void BFS(struct tNode *root, struct tNode *source) {
    if(root == NULL || source == NULL) return;
    //this does a BFS and gives distance to all the nodes
    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    
    source->d = 1;
    enqueue(q, CreateNode(source));
    while(queueEmpty(q) == 0) {
        struct tNode *u = dequeue(q);
        if(u->l != NULL) {
            u->l->d = u->d+1;
            enqueue(q, CreateNode(u->l));
        }
        if(u->r != NULL) {
            u->r->d = u->d + 1;
            enqueue(q,CreateNode(u->r));
        }
    }
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

struct tree *combine(struct tree *T1, int k, struct tree *T2) {
    struct tree *res = (struct tree *)malloc(sizeof(struct tree));
    res->root = createNode(k);
    res->root->l = T1->root;
    res->root->r = T2->root;
    if(T1->root != NULL) T1->root->p = res->root;
    if(T2->root != NULL) T2->root->p = res->root;
    T1->root = NULL;
    T2->root = NULL;
    return res;
}

void main() {
    struct tree *T = (struct tree *)malloc(sizeof(struct tree));
    T->root = NULL;
    int canwe = 1;
    while(canwe) {
        char c = '#';
        scanf("%c", &c);
        switch(c) {
            case 'e': {
                canwe = 0;
                break;
            }
            case 'a': {
                int k;
                scanf("%d", &k);
                insert(T, createNode(k));
                break;
            }
            case 'd': {
                int k;
                scanf("%d", &k);
                struct tNode *ptr = search(T, k);
                if(ptr == NULL) printf("-1\n");
                else { 
                    printf("%d\n", ptr->key);
                    delete(T, ptr);
                }
                break;
            }
            case 's': {
                int k;
                scanf("%d", &k);
                struct tNode *ptr = search(T, k);
                if(ptr == NULL) printf("-1\n");
                else printf("1\n");
                break;
            }
            case 'i': {
                inorder(T);
                break;
            }
            case 'p': {
                preorder(T);
                break;
            }
            case 't': {
                postorder(T);
                break;
            }

            case 'm': {
                struct tNode *ptr = treeMin(T->root);
                if(ptr != NULL) printf("%d\n", ptr->key);
                break;
            }
            case 'x': {
                struct tNode *ptr = treeMax(T->root);
                if(ptr != NULL) printf("%d\n", ptr->key);
                break;
            }
            case 'u': {
                int k;
                scanf("%d", &k);
                struct tNode *ptr = successor(T, k);
                if(ptr == NULL) printf("-1\n");
                else printf("%d\n", ptr->key);
                break;
            }
            case 'r': {
                int k;
                scanf("%d", &k);
                struct tNode *ptr = predecessor(T, k);
                if(ptr == NULL) printf("-1\n");
                else printf("%d\n", ptr->key);
                break;
            }
            case 'l': {
                int k;
                scanf("%d", &k);
                BFS(T->root, T->root);
                struct tNode *ptr = search(T, k);
                if(ptr == NULL) printf("-1\n");
                else printf("%d\n", ptr->d);
                break;
            }
        }
    }
}