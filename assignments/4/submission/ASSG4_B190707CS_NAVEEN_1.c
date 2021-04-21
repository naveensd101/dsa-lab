#include<stdio.h>
#include<stdlib.h>

int main() {
	int n;
	int adjMat[1005][1005];
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &adjMat[i][j]);
		}
	}
	for(int i = 0; i < n; ++i) {
		printf("%d ", i);
		for(int j = 0; j < n; ++j) {
			if(adjMat[i][j]) printf("%d ", j);
		}
		printf("\n");
	}
	return 0;
}
