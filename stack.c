// C program to evaluate value of a postfix expression
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

int stack[max], top = -1;

void sum()
{
	int res, op1, op2;
	op1 = stack[top--];
	op2 = stack[top--];
	res = op1 + op2;
	stack[++top] = res;
}
void diff()
{
	int res, op1, op2;
	op1 = stack[top--];
	op2 = stack[top--];
	res = op1 - op2;
	stack[++top] = res;
}
void mul()
{
	int res, op1, op2;
	op1 = stack[top--];
	op2 = stack[top--];
	res = op1 * op2;
	stack[++top] = res;
}
void divi()
{
	int res, op1, op2;
	op1 = stack[top--];
	op2 = stack[top--];
	res = op1 / op2;
	stack[++top] = res;
}
void powr()
{
	int res, op1, op2;
	op1 = stack[top--];
	op2 = stack[top--];
	res = pow(op1, op2);
	stack[++top] = res;
}

void evaluate(char *st)
{
	int i;
	for (i = 0; st[i] != '\0'; i++)
	{
		if (st[i] != ' ')
		{
			switch (st[i])
			{
			case '+':
				sum();
				break;
			case '-':
				diff();
				break;
			case '*':
				mul();
				break;
			case '/':
				divi();
				break;
			case '^':
				powr();
				break;
			default:
				stack[++top] = st[i] - 48;
			}
		}
	}
}

int main()
{
	char str[max];
	printf("Enter any expression : ");
	scanf("%[^\n]s", str);
	evaluate(str);
	printf("\n The result is = %d", stack[top]);

	return 0;
}