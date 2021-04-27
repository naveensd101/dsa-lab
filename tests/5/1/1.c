/*
 * //store modified ascii values of charechters in adjMat
bfs(G, s)
	for each vertex u in G.V - {s}
		u.color = WHITE
		u.d = infinity
		u.pi = nil
	s.color = Gray
	s.d = 0
	s.pi = NIL
	Q = {}
	Enqueue(Q, s);
	while(Q is not empty)
		u = dequeue(Q)
		print(u)
		for each v in G.Adj[u]
			iterate and find the min vertex in adjlist that is not visited
			store it in mini
			//in matrix representation sequential travesal is enough
			mini.color = Gray
			mini.d = u.d + 1
			mini.pi = u
			enqueue(Q, mini)
		u.color = black

 */
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
		printf("%c ", (char)(v + (int)'a'));
		for(int u = 0; u < n; ++u) {
			if(adj[v][u]) {
				if(!vis[u]) {
					vis[u] = 1;
					enqueue(q, CreateNode(u));
				}
			}
			//int mini = 10000;
			//for(int _u = 0; _u < n; ++_u) {
			//	if(adj[v][_u]) {
			//		if(!vis[_u]) {
			//			if(mini > _u) mini = _u;
			//		}
			//	}
			//}
			//if(mini >= n) continue;
			//vis[mini] = 1;
			//enqueue(q, CreateNode(mini));
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
	char u, v;
	char str[100];
	for(int i = 0; i < m; ++i) {
		scanf("%s", str);
		u = str[0];
		scanf("%s", str);
		v = str[0];

		int a, b;
		a = (int)(u - 'a');
		b = (int)(v - 'a');
		adj[a][b] = 1;
		//adj[b][a] = 1;
	}
	char s[100];
	int sourse;
	scanf("%s", s);
	sourse = (int)(s[0] - 'a');
	bfs(sourse, adj, n);
	return 0;
}
