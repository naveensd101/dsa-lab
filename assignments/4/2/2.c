#include<stdio.h>
#include<stdlib.h>

struct node {
	int key;
	struct node *parent;
	int rank;
};
struct node *makeset(int k) {
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	newNode->key = k;
	newNode->parent = newNode;
	newNode->rank = 0;
	return newNode;
}
struct node *find(struct node *x) {
	if(x != x->parent) x->parent = find(x->parent);
	return x->parent;
}
void link(struct node *x, struct node *y) {
	if(y->rank > x->rank) x->parent = y;
	else {
		y->parent = x;
		if(x->rank == y->rank) x->rank++;
	}
}
void unionNode(struct node *x, struct node *y) {
	link(find(x), find(y));
}

struct edge {
	int i, j, weight;
};

// returns a array of struct edge
int MST_kruskal(int *adjMat[1007], int *weight[1007], int n) {
	//we need a n-1 sized edge array to store result
	struct edge *A = (struct edge *)malloc((n)*sizeof(struct edge));
	int a = 0; //pointer to the next free space in A array

	struct node **setlist = (struct node **)malloc(1007*sizeof(struct node *));
	for(int i = 0; i < n; ++i) {
		setlist[i] = makeset(i);
	}

	struct edge **E = (struct edge **)malloc((n*n)*sizeof(struct edge *));
	int countOfEdges = 0;
	for(int i = 0; i < n; ++i) {
		for(int j = i; j < n; ++j) {
			if(adjMat[i][j]) {
				struct edge *temp = (struct edge *)malloc(sizeof(struct edge));
				temp->i = i;
				temp->j = j;
				temp->weight = weight[i][j];
				E[countOfEdges++] = temp;
			}
		}
	}
	//bubble sort the edge list
	for(int i = 0; i < countOfEdges-1; ++i) {
		for(int j = 0; j < countOfEdges-i-1; ++j) {
			if(E[j]->weight > E[j+1]->weight) {
				struct edge *temp = E[j];
				E[j] = E[j+1];
				E[j+1] = temp;
			}
		}
	}
	for(int i = 0; i < countOfEdges; ++i) printf("%d ", E[i]->weight);
	printf("\n");
	printf("\n");
	int ans = 0;
	for(int i = 0; i < countOfEdges; ++i) {
		if(find(setlist[E[i]->i]) != find(setlist[E[i]->j])) {
			printf("i: %d\nj: %d\nweight: %d\n", E[i]->i, E[i]->j, E[i]->weight);
			ans += E[i]->weight;
			printf("HI\n");
			unionNode(setlist[E[i]->i], setlist[E[i]->j]);
		}
	}
	return ans;
}

int main () {
	char kruskalOrPrim = '#';
	scanf("%c", &kruskalOrPrim);
	if(kruskalOrPrim == 'a') {
		int n;
		scanf("%d", &n);
		int *adjMat[1007];
		for(int i = 0; i < n; ++i) {
			adjMat[i] = (int *)malloc(n*sizeof(n));
		}
		for(int i = 0; i < n; ++i) {
			int buffersize = 0;
			char buffer[100];
			scanf("%d", &buffersize);
			buffersize = 0;

			while(1) {
				char c;
				scanf("%c", &c);

				if(c == '\n') {
					if(buffersize == 0) break;
					adjMat[i][atoi(buffer)] = 1;
					printf("%d ", atoi(buffer));
					buffersize = 0;
					break;
				}
				else if(c == ' ') {
					if(buffersize == 0) continue;
					adjMat[i][atoi(buffer)] = 1;
					printf("%d ", atoi(buffer));
					buffersize = 0;
				}
				else {
					buffer[buffersize++] = c;
					buffer[buffersize] = '\0';
				}
			}
			printf("\n");
		}
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) printf("%d ", adjMat[i][j]);
			printf("\n");
		}
		printf("\n");
		
		int *weight[1007];
		for(int i = 0; i < n; ++i) {
			weight[i] = (int *)malloc(n*sizeof(int));
		}
		for(int i = 0; i < n; ++i) {
			int temp;
			scanf("%d", &temp);
			for(int j = 0; j < n; ++j) {
				//printf("adjMat[%d][%d] = %d\n", i, j, adjMat[i][j]);
				if(adjMat[i][j]) scanf("%d", &weight[i][j]);
			}
		}
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) printf("%d ", weight[i][j]);
			printf("\n");
		}
		printf("\n");
		printf("\nFinal ans: %d\n", MST_kruskal(adjMat, weight, n));
	}
	return 0;
}
