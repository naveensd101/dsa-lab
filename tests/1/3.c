#include <stdio.h>
#include <stdlib.h>

struct stack{
    int n;
    int *arr;
    int top;
};
//return 1 if stack is full
int stack_full(struct stack *s){
    return (s->top >= s->n-1 ? 1 : 0);  
}
//return 1 if stack is empty
int stack_empty(struct stack *s){
    return(s->top <= -1? 1 : 0);
}

void push(struct stack *s, int k){
	int *newArr;
    if(stack_full(s)) {
		newArr = (int*)malloc((s->n)*2*sizeof(int));
		for(int i = 0; i < s->n; ++i) {
			newArr[i] = s->arr[i];
		}
		int *todel = s->arr;
		s->arr = newArr;
		s->n = 2*(s->n);
		free(todel);
	}

    s->top++;
    s->arr[s->top] = k;
}

void pop(struct stack *s){
    if(stack_empty(s)){
        printf("-1\n");
        return;
    }
    else{
        printf("%d\n", s->arr[s->top]);
        s->top--;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    struct stack s;
    s.arr = (int*)malloc(n*sizeof(int));
    s.top = -1;
    s.n = n;

    char c = '1';
    int canwe = 1;
    while(canwe){
        scanf("%c", &c);
        switch(c){
            case 'i':{
                int a;
                scanf("%d", &a);
				if(stack_full(&s)) {
					printf("1\n");
				}
                push(&s, a);
                break;
            }
            case 'd':{
                pop(&s);
                break;
            }
            case 'e':{
                stack_empty(&s) == 1 ? printf("-1\n") : printf("1\n");
                break;
            }
            case 't':{
                canwe = 0;
                break;
            }
        }
    }
    return 0;
}
