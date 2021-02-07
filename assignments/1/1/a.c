/*
(4(3(5()())(6()()))(9(1()())(8()()))) print this patter from the input below

i4
i3
i9
i5
i6
i1
i8
p
e

we have to use BFS
*/
#include<stdio.h>
#include<stdlib.h>

struct tNode {
    int key;
    struct tNode *l;
    struct tNode *r;
    struct tNode *p;
};
struct tree {
    struct tNode *root;
};
struct tNode *createTNode(int k) {
    struct tNode *newNode = (struct tNode *)malloc(sizeof(struct tNode));
    newNode->key = k;
    newNode->l = NULL;
    newNode->r = NULL;
    newNode->p = NULL;
    return newNode;
}
void inorder(struct tNode *r) {
	if(r != NULL) {
		inorder(r->l);
		printf("%d ", r->key);
		inorder(r->r);
	}
}

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

void insert(struct tree *T, int k) {
    struct queue *q = (struct queue *)malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    struct tNode *newPtr = createTNode(k);
    if(T->root == NULL) T->root = newPtr;
    else {
        enqueue(q, CreateNode(T->root));
        while(queueEmpty(q) == 0) {
            struct tNode *u = dequeue(q);
            //u->l
            if(u->l == NULL) {
                u->l = newPtr;
                newPtr->p = u;
                return;
            }
            else {
                enqueue(q, CreateNode(u->l));
            }
            //u->r
            if(u->r == NULL) {
                u->r = newPtr;
                newPtr->p = u;
                return;
            }
            else {
                enqueue(q, CreateNode(u->r));
            }
        }
    }
}

void printHelp(struct tNode *r) {
    if(r == NULL) {
        printf("( ) ");
        return;
    }
    printf("( ");
    printf("%d ", r->key);
    printHelp(r->l);
    printHelp(r->r);
    printf(") ");
} 
void print(struct tree *T) {
    printHelp(T->root);
    printf("\n");
}
int main3() {
    struct queue *q = (struct queue *)malloc (sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    enqueue(q, CreateNode(createTNode(1)));
    enqueue(q, CreateNode(createTNode(2)));
    enqueue(q, CreateNode(createTNode(3)));
    enqueue(q, CreateNode(createTNode(4)));
    enqueue(q, CreateNode(createTNode(5)));
    while(queueEmpty(q) == 0) {
        struct tNode *ptr = dequeue(q);
        printf("%d\n", ptr->key);
    }
    return 0;
}
int main() {
    struct tree *T = (struct tree *)malloc(sizeof(struct tree *));
    T->root = NULL;
    int canwe = 1;
    while(canwe) {
        char c = '#';
        scanf("%c", &c);
        if(c == 'e') {
            canwe = 0;
            break;
        }
        else if(c == 'i') {
            int k = 0;
            scanf("%d", &k);
            insert(T, k);
        }
        else if(c == 'p') {
            print(T);
        }
    }
    return 0;
}

