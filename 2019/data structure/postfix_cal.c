#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100
int evaluate();//수식 평가
void infix_to_postfix();//수식 변환
int precedence(char op);//우선순위 판별
char read_input(char list[]);//숫자, 연산자 판별

void push(char item);
char pop();//변환스택 용
void push2(int item);
int pop2();//평가스택 용


char expr[50];//중위수식
char output_exp[50];//후위수식

int top = -1;
int pos = 0;
int sym;

char stack[MAX_STACK_SIZE];//후위수식 변환용 스택
int stack2[MAX_STACK_SIZE];//후위수식 평가용 스택

void main()
{
	char expr2[50];//입력
	printf("input an infix notation to convert : ");
	fflush(stdin);
	gets(expr2);

	printf("\ninfix = ");
	puts(expr2);
	printf("\n");

	strcpy(expr, expr2);

	infix_to_postfix();

	printf("\nCorrepinding Postfix notation is ");
	printf("\npostfix = %s\n", output_exp);
	printf("\nevaluation of %s = %d\n", output_exp, evaluate());
	system("pause");
}

void push(char item)
{
	int i;
	if (top >= MAX_STACK_SIZE - 1)
	{
		printf("stack full");
		return;

	}
	stack[++top] = item;
	printf("\nstack : ");
	for (i = 0;i <= top;i++)printf("%c ", stack[i]);//스택 출력
	printf("\n");

}
void push2(int item)
{
	int i;
	if (top >= MAX_STACK_SIZE - 1)
	{
		printf("stack full");
		return;

	}
	stack2[++top] = item;
	printf("\nstack : ");
	for (i = 0;i <= top;i++)printf("%d ", stack2[i]);//스택출력
	printf("\n");

}
char pop()
{
	int i;
	if (top < 0)
	{
		printf("stack empty");
		return-999;
	}
	printf("\nstack : ");
	for (i = 0;i < top;i++)printf("%c ", stack[i]);//스택출력
	printf("\n");
	return stack[top--];
}
int pop2()
{
	int i;
	if (top < 0)
	{
		printf("stack empty");
		return-999;
	}
	printf("\nstack : ");
	for (i = 0;i < top;i++)printf("%d ", stack2[i]);//스택출력
	printf("\n");
	return stack2[top--];
}
void infix_to_postfix()
{
	char token;
	char post[50];
	char poptoken;//스택에서 꺼낸 연산자
	int i, j = 0;
	while ((token = expr[pos]) != '\0')
	{
		sym = read_input(expr);

		if (sym == 0) {
			post[j++] = token;
			if (read_input(expr + 1) != 0) post[j++] = ' ';
		}//숫자일때

		else if (sym == 1)
		{
			if (token == '(') 	push(token);
			else if (token == ')')
			{
				while ((poptoken = pop()) != '(') {

					post[j++] = poptoken;
					post[j++] = ' ';
				}//괄호 내의 연산자 모두 pop

			}
			else {

				while (precedence(stack[top]) >= precedence(token) && top != -1)
				{
					poptoken = pop();
					post[j++] = poptoken;
					post[j++] = ' ';
				}
				push(token);

			}//괄호가 아닌 연사자 일 경우
		}//연산자 일 때
		pos++;
	}
	while (top != -1)
	{
		poptoken = pop();
		post[j++] = poptoken;
		post[j++] = ' ';
	}//스택에 남아있는 연산자 pop
	post[--j] = '\0';
	strcpy(output_exp, post);
}
int evaluate() {
	char token;
	int i, sym, input, input2;
	int count = -1;
	int op1, op2;
	pos = 0;
	while ((token = output_exp[pos]) != '\0')
	{
		sym = read_input(output_exp);
		if (sym == 0) {
			for (i = pos; i < 50;i++)
			{
				if (output_exp[i] == ' ')
					break;
			}//자릿수 
			if (i - count == 2 || i == 1) {
				push2(token - '0');

			}//한자리 일 경우
			else
			{
				int a = 1;
				int b = 1;
				input = 0;
				for (;a < i - count;a++) {
					input2 = input;
					input = output_exp[count + a] - '0';
					for (b = 1;b < i - count - a;b++)
					{
						input *= 10;
					}
					input += input2;
				}//int형 숫자로 변환
				push2(input);
				pos = i;

			}
			count = i;
		}//숫자일 경우
		else if (sym == 1)
		{
			op1 = pop2();

			op2 = pop2();

			switch (output_exp[pos]) {
			case '+': push2(op2 + op1);
				break;
			case '-': push2(op2 - op1);
				break;
			case '*': push2(op2 * op1);
				break;
			case '/': push2(op2 / op1);
				break;
			case '%': push2(op2 % op1);
				break;

			}//연산
			count = pos + 1;

		}//연산자 일 경우
		pos++;
	}

	return stack2[top];//평가 값
}
char read_input(char list[])
{
	switch (list[pos])
	{
	case'+': sym = 1;
		break;
	case'-': sym = 1;
		break;
	case'*': sym = 1;
		break;
	case'/': sym = 1;
		break;
	case'%':  sym = 1;
		break;
	case'(':  sym = 1;
		break;
	case')':  sym = 1;
		break;
	case' ': sym = -1;
		break;
	case'\0': sym = -1;
		break;
	default: sym = 0;
	}

	return sym;
}
int precedence(char op) {
	if (op == '(')
		return 0;
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/' || op == '%')
		return 2;
}