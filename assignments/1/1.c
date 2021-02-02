#include<stdio.h>
#include<stdlib.h>
---------------------------------------------------------------------------
---------------------------------------------------------------------------
struct tNode {
    int key;
    struct tNode *l;
    struct tNode *r;
    struct tNode *p;
};
--------------------------------------------------
struct tree {
    struct tNode *root;
};
--------------------------------------------------
struct tNode *createTNode(int k) {
    struct tNode *newNode = (struct tNode *)malloc(sizeof(struct tNode));
    newNode->key = k;
    newNode->l = NULL;
    newNode->r = NULL;
    newNode->p = NULL;
    return newNode;
}
---------------------------------------------------------------------------
---------------------------------------------------------------------------
struct node {
	struct tNode *n;
	struct node *next;
};
--------------------------------------------------
struct queue {
	struct node *head;
	struct node *tail;
};
--------------------------------------------------
int queueEmpty(struct queue *q) {
	return (q->head == NULL && q->tail == NULL ? 1 : 0);
}
--------------------------------------------------
struct node *CreateNode(struct tNode *k) {
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	(*newNode).n = k;
	(*newNode).next = NULL;

	return newNode;
}
--------------------------------------------------
void enqueue(struct queue *q, struct node *x) {
	if(queueEmpty(q)) q->head = x, q->tail = x;
	else q->tail->next = x, q->tail = x;
}
--------------------------------------------------
struct node *dequeue(struct queue *q) {
	if(queueEmpty(q)) return NULL;
	else {
		if(q->head == q->tail) {
			struct node *pointer = q->head;
			q->head = NULL;
			q->tail = NULL;

			pointer->next = NULL;
			//here still there is stuff to do
		}
	}
}
---------------------------------------------------------------------------
---------------------------------------------------------------------------
