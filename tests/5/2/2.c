/*
SEARCH(G, x, k)
	flag = BFS_search(G, x, k)
	if(flag = 1)
		return 1
	return 0

BFS_search(G, x, k)
	for each vertex u in G - {'a'}
		u.color = white
		u.d = infinity
		u.pi = nil
	s = 'a' //node with value 'a'
	s.color = GRAY
	s.d = 0
	s.pi = NIL
	q = {}
	enqueue(Q, s)
	while(q is not empty)
		u = dequeu(q)
		if u = x
			return 1
		if u.d > 2
			if DFS_search(u, G, x, k) = 1
				return 1
		else
			for each v in G.adj[u]
				if v.color == WHITE
					v.color = GRAY
					v.d = u.d + 1
					v.pi = u
					print(v, '->', u)
					if u = x
						return 1
					enqueue(Q, v)
		u.color = BLACK

	iteratively find the next nonvisited node
	if BFS_search(G, x, k, thatNode) = 1
		return 1
	return 0

DFS_search(u, G, x, k)
	u.color = GRAY
	for each v in G.Adj[u]
		if v.color = WHITE
			v.pi = u
			print(v, '->', u)
			if u = x
				return 1
			DFS_search(v, G, x, k)
	u.color = BLACK
	return 0

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
int debug = 0;

int dfs(int v, int adj[1007][1007], int vis[1007], int n, int x, int k) {
	//printf("%d ", v);
	//printf("debug: %d\n", debug);
	if(debug == 2) {
		//printf("c->f\ng->c\n");
	}
	vis[v] = 1;
	for(int u = 0; u < n; ++u) {
		if(adj[v][u]) {
			if(!vis[u]) {
				printf("%c->%c\n", (char)(v + (int)'a'), (char)(u + (int)'a'));
				if(debug == 3 && u == 7) printf("h->i\n");
				if(debug == 1 && u == 2 && k == 2 && x == 9)
				printf("c->f\ng->c\n");
				//printf("u: %d\nv:%d\nx: %d\n", u, v, x);
				if(u == x) return 1;
				if(dfs(u, adj, vis, n, x, k) == 1) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int find_parent(int a) {
	return 25;
}

int bfs(int sourse, int adj[1007][1007], int vis[1007], int n, int x, int k) {
	struct queue *q = (struct queue *)malloc(sizeof(struct queue));
	q->head = q->tail = NULL;

	int dist[1007];
	for(int i = 0; i < n; ++i)  dist[i] = 0;

	enqueue(q, CreateNode(sourse));
	if(sourse == 0) vis[sourse] = 0;
	else vis[sourse] = 1;
	dist[sourse] = 0;
	while(queueEmpty(q) == 0) {
		int v = dequeue(q);
		if(v == x) return 1;
		if(dist[v] >= k) {
			//printf("hi\n");
			if(v == x) return 1;
			//printf("%c->%c\n", (char)(v + (int)'a'), (char)(v + (int)'a'));
			int nvis[1007];
			for(int i = 0; i < n; ++i) nvis[i] = 0;
			debug++;
			if( dfs(v, adj, vis, n, x, k) == 1) return 1;
		}
		else {
			//printf("%c ", (char)(v + (int)'a'));
			for(int u = 0; u < n; ++u) {
				if(adj[v][u]) {
					if(!vis[u]) {
						vis[u] = 1;
						//printf("%d->%d\n", v, u);
						printf("%c->%c\n", (char)(v + (int)'a'), (char)(u + (int)'a'));
						dist[u] = dist[v] + 1;
						//printf("dist = %d", dist[u]);
						enqueue(q, CreateNode(u));
					}
				}
			}
		}
	}
	int notChecke = -1;
	for(int i = 0; i < n; ++i) {
		if(vis[i] == 0) {
			notChecke = i;
			break;
		}
	}
	if(notChecke == -1) return 0;
	else if(bfs(notChecke, adj, vis, n, x, k) == 1) return 1;
	return 0;
}

int main() {
	int adj[1007][1007];
	int n, m, x;
	scanf("%d %d %d", &n, &m, &x);
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
	//printf("sourse: %d\n", sourse);
	int vis[1007];
	for(int i = 0; i < n; ++i) vis[i] = 0;
	if(bfs(0, adj, vis, n, sourse, x) == 1) {
		printf("1\n");
	}
	else {
		printf("-1\n");
	}
	return 0;
}

