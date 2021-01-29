#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
//assuming distinct elements
//-----------------------------------------------------------------------------------------------------------
struct node
{
    struct node *prev;
    int k;
    struct node *next;
};

struct list
{
    struct node *head;
};
//-----------------------------------------------------------------------------------------------------------
//CREATE-NODE(k)
struct node *CreateNode(int k)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->k = k;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}
//LIST-INSERT-FRONT(L,x)
void ListInsertFront(struct list *l, struct node *x)
{
    if (l->head != NULL)
    {
        (l->head)->prev = x;
    }
    x->next = l->head;
    l->head = x;
}
//LIST-INSERT-TAIL(L,x)
void ListInsertTail(struct list *l, struct node *x)
{
    if (l->head == NULL)
        ListInsertFront(l, x);
    else
    {
        struct node *pointer = l->head;
        while (pointer->next != NULL)
            pointer = pointer->next;

        x->prev = pointer;
        pointer->next = x;
    }
}
//LIST-SEARCH(L, k)
struct node *ListSearch(struct list *l, int k)
{
    struct node *pointer = l->head;
    //empty then do this
    if (pointer == NULL)
        return NULL;
    else
    {
        while (pointer != NULL)
        {
            if (pointer->k == k)
            {
                return pointer;
            }
            pointer = pointer->next;
        }
    }
    return NULL;
}
//LIST-INSERT-AFTER(L,x,y)
void ListInsertAfter(struct list *l, struct node *x, struct node *y)
{
    if (y == NULL)
        return;
    x->next = y->next;
    x->prev = y;
    // assert(y->next);
    // assert(y->next->prev);
    (y->next) ? y->next->prev = x : 0;
    y->next = x;
}
//LIST-INSERT-BEFORE(l, x, y)
void ListInsertBefore(struct list *l, struct node *x, struct node *y)
{
    if (y == NULL)
        return;
    struct node *pointer = l->head;
    if (pointer == y)
        ListInsertFront(l, x);
    else
    {
        // printf("hi\n");
        x->prev = y->prev;
        x->next = y;
        y->prev->next = x;
        y->prev = x;
    }
}
//LIST-DELETE(L, x)
void ListDelete(struct list *l, struct node *x)
{
    if (x == NULL)
    {
        printf("-1\n");
        return;
    }
    struct node *prev = x->prev;
    struct node *next = x->next;
    if (prev == NULL && next == NULL)
    {
        //only one element
        l->head = NULL;
        printf("%d\n", x->k);
        free(x);
        return;
    }
    else if (prev == NULL && next != NULL)
    {
        //first element
        next->prev = NULL;
        l->head = next;

        x->next = NULL;
        printf("%d\n", x->k);
        free(x);
        return;
    }
    else if (next == NULL && prev != NULL)
    {
        //last element
        prev->next = NULL;

        x->prev = NULL;
        printf("%d\n", x->k);
        free(x);
        return;
    }
    else
    {
        //middle element
        prev->next = next;
        next->prev = prev;

        x->prev = NULL;
        x->next = NULL;
        printf("%d\n", x->k);
        free(x);
        return;
    }
}
//LIST-DELETE-FIRST(L)
void ListDeleteFirst(struct list *l)
{
    if (l->head == NULL)
    {
        printf("-1\n");
        return;
    }
    else
    {
        ListDelete(l, l->head);
    }
}
//LIST-DELETE-LAST(L)
void ListDeleteLast(struct list *l)
{
    if (l->head == NULL)
    {
        printf("-1\n");
        return;
    }
    else
    {
        struct node *pointer = l->head;
        while (pointer != NULL)
        {
            if (pointer->next == NULL)
            {
                ListDelete(l, pointer);
                return;
            }
            pointer = pointer->next;
        }
    }
}
//-----------------------------------------------------------------------------------------------------------

void f(struct list *l, int k) {
	struct node *ptr = l->head;
	int n = 0;
	while(ptr != NULL) {
		n++;
		ptr = ptr -> next;
	}
//	printf("N = %d\n", n);
	int index = (n&1 ? (n+1)/2 : n/2);
//	printf("i = %d\n", index);
	if(n == 0) {
		struct node *newPtr = CreateNode(k);
		l->head = newPtr;
		return;
	}
	ptr = l->head;
	while(ptr != NULL) {
		index--;
		if(index == 0) {
			if(n&1) {
				//n is odd
				ListInsertBefore(l, CreateNode(k), ptr);
			}
			else {
				ListInsertAfter(l, CreateNode(k), ptr);
			}
		}
		ptr = ptr->next;
	}
}
int main() {
	struct list *L = (struct list *) malloc(sizeof(struct list));
	(*L).head = NULL;

	int size = 0;
	char buffer[100];
	int buffersize = 0;
	while(1) {
		char c;
		scanf("%c", &c);

		if(c == 't') {
			if(buffersize == 0) break;
			size++;
			f(L, atoi(buffer));
			//ListInsertTail(L, CreateNode(atoi(buffer)));
			/*
			struct node *ptr = L->head;
			while(ptr != NULL) {
				printf("%d ", ptr->k);
				ptr = ptr->next;
				}
			printf("\n");
			*/
			buffersize = 0;
			break;
		}
		else if(c == '\n') {
			if(buffersize == 0) continue;
			size++;
			f(L, atoi(buffer));
			//ListInsertTail(L, CreateNode(atoi(buffer)));
			/*
			struct node *ptr = L->head;
			while(ptr != NULL) {
				printf("%d ", ptr->k);
				ptr = ptr->next;
				}
			printf("\n");
			*/
			buffersize = 0;
		}
		else {
			buffer[buffersize++] = c;
			buffer[buffersize] = '\0';
		}
	}
	struct node *ptr = L->head;
	while(ptr != NULL) {
		printf("%d ", ptr->k);
		ptr = ptr->next;
	}
	printf("\n");
	return 0;
}

