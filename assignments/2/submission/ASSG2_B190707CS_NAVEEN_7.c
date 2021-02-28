#include<stdio.h>
#include<stdlib.h>
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
struct tNode *createTNode(int k) {
    struct tNode *newNode = (struct tNode *)malloc(sizeof(struct tNode));
    newNode->key = k;
    newNode->d = 0;
    newNode->l = NULL;
    newNode->r = NULL;
    newNode->p = NULL;
    return newNode;
}
void inorder(struct tNode *r) {
	if(r != NULL) {
		inorder(r->l);
		printf("%d(%d) ", r->key, r->d);
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

struct tNode *make(int arr[], int l, int r) {
    if(l > r) return NULL;
    struct tNode *root = NULL;
    //int mid = l + (r-l)/2;
	int mid = (l+r+1)/2;
    root = createTNode(arr[mid]);
    struct tNode *left = make(arr, l, mid-1);
    struct tNode *right = make(arr, mid+1, r);
    if(left != NULL) left->p = root;
    if(right != NULL) right->p = root;
    root->l = left;
    root->r = right;
    return root;
}
int max(int a, int b) {
    if(a > b) return a;
    return b;
}
void BFS(struct tNode *root, struct tNode *source) {
    if(root == NULL || source == NULL) return;
    //this does a BFS and gives distance to all the nodes
    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    
    source->d = 0;
    enqueue(q, CreateNode(source));
    while(queueEmpty(q) == 0) {
        struct tNode *u = dequeue(q);
        if(u->l !=NULL) {
            u->l->d = u->d+1;
            enqueue(q, CreateNode(u->l));
        }
        if(u->r != NULL) {
            u->r->d = u->d + 1;
            enqueue(q,CreateNode(u->r));
        }
    }
}
void levelSum (struct tNode *root, int arr[], int *mx) {
    if(root == NULL) return;
    arr[root->d]+=root->key;
    (*mx) = max(*(mx), root->d);
    levelSum(root->l, arr, mx);
    levelSum(root->r, arr, mx);
}
int main() {
    int n;
    scanf("%d",&n);
    int *arr = (int *)malloc(n*sizeof(int));
    for(int i = 0; i < n; ++i) scanf("%d", &arr[i]);
    // for(int i = 0; i < n; ++i) printf("%d ", arr[i]);
    // printf("\n");
    struct tNode *root = make(arr, 0, n-1);
    BFS(root, root);
    printHelp(root);
    printf("\n");
    // inorder(root);
    // printf("\n");
    for(int i = 0; i < n; ++i) arr[i] = 0;
    int mx = 0;
    levelSum (root, arr, &mx);
    for(int i = 0; i < mx+1; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
 
