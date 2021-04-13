#include<stdio.h>
#include<stdlib.h>


struct table {
	int m;          //size of the table
	int *flag;      //1 if filled 0 if not filled
	int *array;     //the actual table
	int t1ort2;     //1 if t1 and 2 if t2
};

int *HashTable(int m) {
	/* Retrun pointer to a array */
	int *arr = (int *)malloc(m*sizeof(int));	
	for(int i = 0; i < m; ++i) arr[i] = 0;
	return arr;
}
int *flagSetter(int m) {
	int *flag = (int *)malloc(m*sizeof(int));
	for(int i = 0; i < m; ++i) {
		flag[i] = 0;
	}
	return flag;
}
int f(struct table *T, int x) {
	if(T->t1ort2 == 1) {
		return x%(T->m);
	}
	else {
		return ((x+(T->m)-1)/(T->m)) % (T->m);
	}
}
int insert(int x, struct table* T1, struct table *T2, int fx, int gx, int count) {
	if(count > T1->m) return -1;
	int index1 = f(T1, x);
	int index2 = f(T2, x);
	if(T1->flag[index1] == 0) {
		T1->array[index1] = x;
		T1->flag[index1] = 1;
		return 1;
	}
	else {
		int temp = T1->array[index1];
		if(insert(temp, T2, T1, 1, 1, ++count) == -1) {
			return -1;
		}
		else {
			T1->array[f(T1, x)] = x;
			T1->flag[f(T1, x)] = 1;
			return 1;
		}
	}
	return -1;
}
void print(struct table *T1) {
	for(int i = 0; i < T1->m; ++i) {
		if(T1->flag[i] == 1) printf("%d ", T1->array[i]);
		else printf("NIL ");
	}
	printf("\n");
}
int main() {
	int n;
	scanf("%d", &n);
	struct table *T1 = (struct table *)malloc(sizeof(struct table *));
	T1->m = n;
	T1->array = NULL;
	T1->flag = flagSetter(n);
	T1->t1ort2 = 1;
	T1->array = HashTable(n);

	struct table *T2 = (struct table *)malloc(sizeof(struct table *));
	T2->m = n;
	T2->array = NULL;
	T2->flag = flagSetter(n);
	T2->t1ort2 = 2;
	T2->array = HashTable(T2->m);

	char c = '#';
	int canwe = 1;
	while(canwe) {
		scanf("%c", &c);
		if(c == 't') {
			canwe = 0;
			break;
		}
		else if(c == 'i') {
			int k;
			scanf("%d", &k);
			insert(k, T1, T2, 1, 1, 1);
			continue;
		}
		else if(c == 'p') {
			int k;
			scanf("%d", &k);
			if(k == 1) {
				print(T1);
			}
			else print(T2);
			continue;
		}
	}

	return 0;
}

