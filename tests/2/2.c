#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

//-----------------------------------------------------------------------------------------------------------
struct node
{
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
    (*newNode).k = k;
    // printf("%d\n", k);
    (*newNode).next = NULL;

    return newNode;
}
//LIST-INSERT-FRONT(L, x)
void ListInsertFront(struct list *L, struct node *x)
{
    (*x).next = (*L).head;
    (*L).head = x;
}
//LIST-INSERT-TAIL(L, x)
void ListInsertTail(struct list *L, struct node *x)
{
    //empty then do this
    if ((*L).head == NULL)
    {
        (*L).head = x;
    }
    else
    {
        struct node *pointer = (*L).head;
        while ((*pointer).next != NULL)
            pointer = (*pointer).next;
        (*pointer).next = x;
    }
}
//LIST-SEARCH(L,k)
struct node *ListSearch(struct list *L, int k)
{
    struct node *pointer = (*L).head;
    //empty then do this
    if (pointer == NULL)
    {
        return NULL;
    }
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
//LIST-INSERT-AFTER(L, x, y)
void ListInsertAfter(struct list *L, struct node *x, struct node *y)
{
    if (y == NULL)
    {
        return;
    }
    x->next = y->next;
    y->next = x;
}
//LIST-INSERT-BEFOR(L, x, y)
void ListInsertBefor(struct list *L, struct node *x, struct node *y)
{
    if (y == NULL)
    {
        return;
    }
    struct node *pointer = L->head;
    while (pointer != NULL)
    {
        if (pointer == y) //this means first element is y
        {
            L->head = x;
            x->next = y;
            break;
        }
        if (pointer->next == y)
        {
            pointer->next = x;
            x->next = y;
            break;
        }
        pointer = pointer->next;
    }
}
//LIST-DELETE(L,x)
void ListDelete(struct list *L, struct node *x)
{
    if (x == NULL)
    {
        printf("-1\n");
        return;
    }
    struct node *pointer = L->head;
    if (L->head == x)
    {
        L->head = x->next;
        pointer->next = x->next;
        printf("%d\n", pointer->k);
        free(pointer);
        return;
    }
    while (pointer != NULL)
    {
        if (pointer->next == x)
        {
            pointer->next = x->next;
            printf("%d\n", x->k);
            free(x);
            return;
        }
        pointer = pointer->next;
    }
}
//LIST-DELETE-FIRST(L)
void ListDeleteFirst(struct list *L)
{
    if (L->head == NULL)
    {
        printf("-1\n");
        return;
    }
    else
    {
        ListDelete(L, L->head);
    }
}
//LIST-DELETE-LAST(L)
void ListDeleteLast(struct list *L)
{
    if (L->head == NULL)
    {
        printf("-1\n");
        return;
    }
    else
    {
        struct node *pointer = L->head;
        while (pointer != NULL)
        {
            if (pointer->next == NULL)
            {
                ListDelete(L, pointer);
                return;
            }
            pointer = pointer->next;
        }
    }
}
//-----------------------------------------------------------------------------------------------------------

int main23() {
    int array[100];
    int size = 0;
    char buffer[100];
    int buffersize = 0;
    while(1) {
        char c;
        scanf("%c", &c);

        if(c == '\n') {
            if(buffersize == 0) {
                break;
            }
            array[size++] = atoi(buffer);
            buffersize = 0;
            break;
        }
        else if(c == ' ') {
            array[size++] = atoi(buffer);
            buffersize = 0;
        }
        else {
            buffer[buffersize++] = c;
            buffer[buffersize] = '\0';
        }
    }
    printf("size: %d\n", size);
    for(int i = 0; i < size; ++i) printf("%d ",  array[i]);
    printf("\n");
    return 0;
}

struct node * kLast(struct node *head, int k) {
	struct node *ptr = head;
	int n = 0;
	while(ptr != NULL) {
		n++;
		ptr = ptr->next;
	}
	int index = n-k+1;
	if(index < 1 || index > n) return NULL;
	ptr = head;
	while(ptr != NULL) {
		index--;
		if(index == 0) return ptr;
		ptr = ptr -> next;
	}
	return NULL;
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

		if(c == '\n') {
			if(buffersize == 0) break;
			size++;
			ListInsertTail(L, CreateNode(atoi(buffer)));
			buffersize = 0;
			break;
		}
		else if(c == ' ') {
			size++;
			ListInsertTail(L, CreateNode(atoi(buffer)));
			buffersize = 0;
		}
		else {
			buffer[buffersize++] = c;
			buffer[buffersize] = '\0';
		}
	}
	/*
	struct node *ptr = L->head;
	while(ptr != NULL) {
		printf("%d ", ptr->k);
		ptr = ptr->next;
	}
	printf("\n");
	return 0;
	*/
	int k = 0;
	scanf("%d", &k);
	struct node *a = L->head;
	struct node *ptr = kLast(a,k);
	if(ptr == NULL) printf("-1\n");
	else printf("%d\n", ptr->k);
	return 0;
}
