#include <stdio.h>
#include <stdlib.h>

struct stack{
    int n;
    char *arr;
    int top;
};

void push(struct stack *s, char c)
{
    s->top++;
    s->arr[s->top] = c;
}
char pop(struct stack *s)
{
    char c = s->arr[s->top];
    s->top--;
    return c;
}
int isPalindrome(struct stack *s)
{
    char rev[s->n];
    for(int i = 0; i < s->n; ++i)
    {
        rev[i] = pop(s);
    }
    for(int i = 0; i < s-> n; ++i)
    {
        if(rev[i] != s->arr[i])
        return 0;
    }
    return 1;
}
int main()
{
    char str[100]; 
    scanf("%s", str);
    struct stack p;
    
    int count = 0;
    for(int i= 0; str[i]!= '\0'; ++i)
    {
        count++;
    }
    p.arr = (char*)malloc(count*sizeof(char));
    p.n = count;
    p.top = -1;
    for(int i = 0; i < p.n; ++i)
    {
        push(&p,str[i]);
    }
	for(int i = 0; i < p.n; ++i) {
		printf("%c", pop(&p));
	}
	printf("\n");
}
