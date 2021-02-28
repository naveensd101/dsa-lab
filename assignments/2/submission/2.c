#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

int hash(char *a, int k) {
	//k is size of hash table
	//a is the string to be hashed
	int n = 0;
	for(int i = 0; a[i] != '\0'; ++i) n++;
	return (n*n)%k; 
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
	int i = hash(str, T->k);
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
	int i = hash(str, T->k);
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

int main() {
	struct table *T = (struct table *)malloc(sizeof(struct table));
	scanf("%d\n", &T->k);
	T->array = (struct node **)malloc(sizeof(struct node*)*(long unsigned int)(T->k));
	for(int i = 0; i < T->k; ++i) T->array[i] = NULL;
	//for(int i = 0; i < T->k; ++i) printf("%d: %p\n", i, (T->array[i]));


	char buffer[600];
	int buffersize = 0;
	while(1) {
		char c;
		scanf("%c", &c);
		if(c == '\n') {
			if(buffersize == 0) break;
			//printf("%s: %d\n", buffer, (int)strlen(buffer));
			if(search(T, buffer) == 0) insert(T, buffer);
			buffersize = 0;
			break;
		}
		else if(c == ' ') {
			if(buffersize == 0) continue;
			//printf("%s: %d\n", buffer, (int)strlen(buffer));
			if(search(T, buffer) == 0) insert(T, buffer);
			buffersize = 0;
		}
		else {
			buffer[buffersize++] = c;
			buffer[buffersize] = '\0';
		}
	}

	//for(int i = 0; i < T->k; ++i) printf("%d: %p\n", i, (T->array[i]));
	for(int i = 0; i < T->k; ++i) {
		printf("%d:", i);
		print(T->array[i]);	
	}
	return 0;
}
















