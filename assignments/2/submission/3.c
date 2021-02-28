#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

int hash(char *a) {
	//a is the string to be hashed
	//a b c d e f g h
	//0 1 2 3 4 5 6 7 <- correspoinding n value 
	int flag[8];
	int rv = 0;
	for(int i = 0; i < 8; ++i) flag[i] = 0;
	for(int i = 0; a[i] != '\0'; ++i) {
		int n = (int)a[i] - (int)'a';
		if(flag[n] == 1) continue;
		flag[n] = 1;
		rv += (1<<n);
	}
	return rv;
}
struct node {
	char *word;
	struct node *next;
};
struct node *createNode(char *str) {
	struct node *newptr = (struct node*)malloc(sizeof(struct node*));
	newptr->word = (char *)malloc(strlen(str));
	strcpy(newptr->word, str);
	newptr->next = NULL;
	return newptr;
}
struct table {
	int k;					//size of table
	struct node **array;	//array of head pointers to node
};
void insert(struct table *T, char *str) {
	int i = hash(str);
	if(T->array[i] == NULL) {
		struct node *newptr = createNode(str);
		T->array[i] = newptr;
	}
	else {
		struct node *newptr = createNode(str);
		struct node *ptr = T->array[i];
		while(ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = newptr;
	}
}
int search(struct table *T, char *str) {
	int i = hash(str);
	if(T->array[i] == NULL) return 0;
	else {
		struct node *ptr = T->array[i];
		while(ptr != NULL) {
			if(strcmp(ptr->word, str) == 0) return 1;
			ptr = ptr->next;
		}
	}
	return 0;
}
void print(struct node *ptr) {
	if(ptr == NULL) printf("null");
	else {
		printf("%s", ptr->word);
		ptr = ptr->next;
		while(ptr != NULL) {
			printf("-%s", ptr->word);
			ptr = ptr->next;
		}
	}
	printf("\n");	
}
void swap(struct node *ptr1, struct node *ptr2) {
	char *t = (char *)malloc(sizeof(ptr1->word));
	strcpy(t, ptr1->word);
	free(ptr1->word);
	ptr1->word = (char*)malloc(sizeof(ptr2->word));
	strcpy(ptr1->word, ptr2->word);
	free(ptr2->word);
	ptr2->word = (char*)malloc(sizeof(t));
	strcpy(ptr2->word, t);
	free(t);
}
void prindNew(struct node *ptr) {
	if(ptr == NULL) return;
	int n = 0;
	struct node *p = ptr;
	while(p != NULL) n++, p = p->next;
	struct node *ptrj = NULL;
	struct node *ptrjplus = NULL;
	int i, j;
	for(i = 0; i < n-1; ++i) {
		ptrj = ptr;
		for(j = 0; j < n-i-1; ++j, ptrj = ptrj->next) {
			ptrjplus = ptrj->next;
			if(strcmp(ptrj->word, ptrjplus->word) > 0) swap(ptrj, ptrjplus);
		}
	}
	p = ptr;
	while(p != NULL) {
		printf("%s ", p->word);
		p = p->next;
	}
	printf("\n");
}

int main() {
	struct table *T = (struct table *)malloc(sizeof(struct table));
	T->k = 256;
	T->array = (struct node **)malloc(sizeof(struct node*)*(long unsigned int)(T->k));
	for(int i = 0; i < T->k; ++i) T->array[i] = NULL;
	//for(int i = 0; i < T->k; ++i) printf("%d: %p\n", i, (T->array[i]));
	int n;
	scanf("%d", &n);
	char str[100];
	for(int i = 0; i < n; ++i) {
		scanf("%s", str);
		insert(T, str);
	}
	//for(int i = 0; i < T->k; ++i) if(T->array[i] != NULL) printf("%d: %p\n", i, (T->array[i]));
	for(int i = 0; i < T->k; ++i) {
		if(T->array[i] != NULL) prindNew(T->array[i]);
	}
	return 0;
}

















