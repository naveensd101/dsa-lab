#include<stdio.h>
#include<stdlib.h>

int isPrime(int n) {
	/* Retruns 1 if n is prime */
	if(n < 2) return 0;
	for(int i = 2; i*i <= n; ++i) if(n%i == 0) return 0;
	return 1;
}
int h1(int k, int i, int c1, int c2, int m) {
	//Quadratic Probing
	return (k%m + c1*i + c2*i*i)%m;
}
int h2(int k, int i, int m, int R) {
	//Double Hashing
	int f = k%m;
	int s = R - (k%R);
	return (f + i*s)%m;
}

struct table {
	int m;          //size of the table
	int *array;     //the actual table
	int *flag;      //0 => notfilled, 1 => filled, 2 => deleted
	char aOrb;      //a => quadratic probbing, b => Double Hashing

	/* hash helpers */
	int c1, c2;     //constants for quadratic probbing
	int R;          //prime for double hashing
};

int *HashTable(int m) {
	/* Retrun pointer to a array */
	int *arr = (int *)malloc(m*sizeof(int));	
	for(int i = 0; i < m; ++i) arr[i] = 0;
	return arr;
}
void Insert(struct table *T, int k) {
	/* Inserts wit h1 or h2 accordingly (wrt variable aOrb) */
	for(int i = 0; i < T->m; ++i) {
		int j;
		if(T->aOrb == 'a') j = h1(k, i, T->c1, T->c2, T->m);
		else j = h2(k, i, T->m, T->R);
		//printf("\t[i: %d]\n", i);
		//printf("\t[j: %d]\n", j);
		if(T->flag[j] != 1) {
			T->array[j] = k;
			T->flag[j] = 1;
			return;
		}
	}
}
int Search(struct table *T, int k) {
	for(int i = 0; i < T->m; ++i) {
		int j;
		if(T->aOrb == 'a') j = h1(k, i, T->c1, T->c2, T->m);
		else j = h2(k, i, T->m, T->R);
		if(T->flag[j] == 0) return 0;
		else if(T->flag[j] == 1 && T->array[j] == k) return 1;
	}
	return 0;
}
void Delete(struct table *T, int k) {
	for(int i = 0; i < T->m; ++i) {
		int j;
		if(T->aOrb == 'a') j = h1(k, i, T->c1, T->c2, T->m);
		else j = h2(k, i, T->m, T->R);
		if(T->flag[j] == 1 && T->array[j] == k) T->flag[j] = 2;
	}
}

int main() {
	struct table *T = (struct table *)malloc(sizeof(struct table *));
	T->m = 0;
	T->array = NULL;
	T->flag = NULL;
	T->aOrb = '#';
	T->c1 = 0;
	T->c2 = 0;
	T->R = 0;

	scanf("%c", &T->aOrb);
	scanf("%d", &T->m);

	T->array = HashTable(T->m);
	T->flag = (int *)malloc(T->m*sizeof(int));
	for(int i = 0; i < T->m; ++i) T->flag[i] = 0;

	if(T->aOrb == 'a') scanf("%d %d", &T->c1, &T->c2);	
	else {
		for(int i = T->m-1; i >= 2; --i) {
			if(isPrime(i)) {
				T->R = i;
				break;
			}
		}
	}
	

	// printf("printing...\n");
	// printf("m: %d\n", T->m);
	// printf("arra: "); for(int i = 0; i < T->m; ++i) printf("%d ", T->array[i]);
	// printf("\n");
	// printf("flag: "); for(int i = 0; i < T->m; ++i) printf("%d ", T->flag[i]);
	// printf("\n");
	// printf("c1: %d\n", T->c1);
	// printf("c2: %d\n", T->c2);
	// printf("R: %d\n", T->R);
	
	char c = '#';
	int canwe = 1;
	while(canwe) {
		scanf("%c", &c);
		if(c == 't') {
			canwe = 0;
			break;
		}
		else if(c == 'i') {
			int x;
			scanf("%d", &x);
			Insert(T, x);
			continue;
		}
		else if(c == 's') {
			int x;
			scanf("%d", &x);
			if(Search(T, x)) printf("1\n");
			else printf("-1\n");
			continue;
		}
		else if(c == 'd') {
			int x;
			scanf("%d", &x);
			Delete(T, x);
			continue;
		}
		else if(c == 'p') {
			for(int i = 0; i < T->m; ++i) {
				printf("%d ", i);
				if(T->flag[i] == 1) printf("(%d)", T->array[i]);
				else printf("()");
				printf("\n");
			}
			continue;
		}
	}

	return 0;
}












