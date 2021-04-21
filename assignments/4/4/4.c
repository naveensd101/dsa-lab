#include<stdio.h>
#include<stdlib.h>

struct node {
	int k;
	struct node *next;
};
struct queue {
	struct node *head;
	struct node *tail;
};
int queueEmpty(struct queue *q) {
	return (q->head == NULL && q->tail == NULL ? 1 : 0);
}
struct node *CreateNode(int k) {
	struct node *newNode = (struct node *)malloc(sizeof(struct node));
	(*newNode).k = k;
	(*newNode).next = NULL;

	return newNode;
}
void enqueue(struct queue *q, struct node *x) {
	if(queueEmpty(q)) q->head = x, q->tail = x;
	else q->tail->next = x, q->tail = x;
}
int dequeue(struct queue *q) {
	if(queueEmpty(q)) return -1;
	else {
		if(q->head == q->tail) {
			struct node *pointer = q->head;
			q->head = NULL;
			q->tail = NULL;

			pointer->next = NULL;
			int tosend = pointer->k;
			free(pointer);
			return tosend;
		}
        else {
            struct node *pointer = q->head;
            q->head = q->head->next;
            pointer->next = NULL;
			int tosend = pointer->k;
            free(pointer);
            return tosend;
        }
	}
	return -1;
}

void bfs(int sourse, int adj[1007][1007], int n) {
	struct queue *q = (struct queue *)malloc(sizeof(struct queue));
	q->head = q->tail = NULL;

	int vis[1007];
	for(int i = 0; i < n; ++i) vis[i] = 0;

	enqueue(q, CreateNode(sourse));
	vis[sourse] = 1;
	while(queueEmpty(q) == 0) {
		int v = dequeue(q);
		printf("%d ", v);
		for(int u = 0; u < n; ++u) {
			if(adj[v][u]) {
				if(!vis[u]) {
					vis[u] = 1;
					enqueue(q, CreateNode(u));
				}
			}
		}
	}
}

void dfs(int v, int adj[1007][1007], int vis[1007], int n) {
	printf("%d ", v);
	vis[v] = 1;
	for(int u = 0; u < n; ++u) {
		if(adj[v][u]) {
			if(!vis[u]) dfs(u, adj, vis, n);
		}
	}
}
int main() {
	int adj[1007][1007];
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			adj[i][j] = 0;
		}
	}
	int u, v;
	for(int i = 0; i < m; ++i) {
		scanf("%d %d", &u, &v);
		adj[u][v] = 1;
		adj[v][u] = 1;
	}
	int sourse;
	scanf("%d", &sourse);
	bfs(sourse, adj, n);
	printf("\n");
	int vis[1007];
	for(int i = 0; i < n; ++i) vis[i] = 0;
	dfs(sourse, adj, vis, n);
	printf("\n");
	return 0;
}
