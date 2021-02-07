#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
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

struct tNode* make(char s[]) {
    if(strlen(s) <= 2) return NULL;
    
    //finding first number 
    char firstInt[50]; int index = 0;
    for(int i = 1; s[i] != '('; ++i) firstInt[index++] = s[i];
    firstInt[index] = '\0';

    int rootInt = atoi(firstInt);
    struct tNode *root = createTNode(rootInt);

    char ls[(int)1e4], rs[(int)1e4];
    int lsi = 0, rsi = 0;
    index = 2;
    int regbs = 0;
    for(index = 1; s[index] != '\0'; ++index) if(s[index] == '(') break;
    for(; s[index] != '\0'; ++index) {
        if(s[index] == '(') regbs++;
        if(s[index] == ')') regbs--;
        ls[lsi++] = s[index];
        if(regbs == 0) break;
    }
    ls[lsi] = '\0';
    regbs = 0;
    index++;
    for(; s[index] != '\0'; ++index) {
        if(s[index] == '(') regbs++;
        if(s[index] == ')') regbs--;
        rs[rsi++] = s[index];
        if(regbs == 0) break;
    }
    rs[rsi] = '\0';
    // printf("%s %d\n", ls, (int)strlen(ls));
    // printf("%s %d\n", rs, (int)strlen(rs));

    // struct tNode *root = createTNode(rootInt);

    struct tNode *left = make(ls);
    struct tNode *right = make(rs);
    if(left != NULL) {
        assert(root);
        assert(left);
        root->l = left;
        left->p = root;
    }
    if(right != NULL) {
        assert(root);
        assert(right);
        root->r = right;
        right->p = root;
    }
    return root;
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

void BFS(struct tNode *root, struct tNode *source) {
    struct queue *q = (struct queue *) malloc(sizeof(struct queue));
    q->head = NULL;
    q->tail = NULL;
    
    source->d = 0;
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

struct tNode * inorderFinder(struct tNode *root, int k) {
    if(root == NULL) return NULL;
    struct tNode *found = NULL;
    found = inorderFinder(root->l, k);
    if(found != NULL) return found;
    if(root->key == k) return root;
    found = inorderFinder(root->r, k);
    if(found != NULL) return found;
    return found;
}
void inorderPrinter(struct tNode *root, struct tNode *needed, int *count) {
    if(root != NULL) {
        inorderPrinter(root->l, needed, count);
        if(root->d == needed->d && root->p != needed->p) printf("%d ", root->key), (*count)++;
        inorderPrinter(root->r, needed, count);
    }
}
void cousines(struct tNode *root, int k) {
    struct tNode *needed = inorderFinder(root, k);
    if(needed == NULL) {
        printf("-1\n");
        return;
    }
    int count = 0;
    inorderPrinter(root, needed, &count);
    // printf("%d\n", count);
    if(count == 0) printf("-1");
    printf("\n");
}

struct tNode *treeMin(struct tNode *x) {
    while(x != NULL && x->l != NULL) x = x->l;
    return x;
}
struct tNode *successor(struct tree *T, struct tNode *x) {
    if(x == NULL) return NULL;
    if(x->r != NULL) return treeMin(x->r);
    struct tNode *y = x->p;
    while(y != NULL && x == y->r) {
        x = y;
        y = y->p;
    }
    return y;
}
int Ksmallest(struct tree *T, int k) {
    struct tNode *x = treeMin(T->root);
    if(k <= 0) return x->key;
    k--;
    if(k == 0) return x->key;
    while(k > 0) {
        x = successor(T, x);
        k--;
    }
    return x->key;
}

int main() {
    char copy[(int)1e4];
    fgets(copy, 1e4, stdin);
    char s[(int)1e4];
    int index = 0;
    for(int i = 0; i < (int)sizeof(copy); ++i) {
        if(copy[i] == ' ' || copy[i] == '\n') continue;
        s[index++] = copy[i];
    }
    s[index] = '\0';
    // printf("%s\n", s);
    struct tNode *root = make(s);
    struct tree *T = (struct tree *)malloc(sizeof(struct tree));
    T->root = root;
    int k = 1;
    scanf("%d", &k);
    int ans = Ksmallest(T, k);
    printf("%d\n", ans);

    return 0;
}
// gcc b.c -Wall -Wextra -pedantic -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector