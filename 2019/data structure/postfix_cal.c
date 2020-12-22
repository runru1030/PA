#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_STACK_SIZE 100
int evaluate();//���� ��
void infix_to_postfix();//���� ��ȯ
int precedence(char op);//�켱���� �Ǻ�
char read_input(char list[]);//����, ������ �Ǻ�

void push(char item);
char pop();//��ȯ���� ��
void push2(int item);
int pop2();//�򰡽��� ��


char expr[50];//��������
char output_exp[50];//��������

int top = -1;
int pos = 0;
int sym;

char stack[MAX_STACK_SIZE];//�������� ��ȯ�� ����
int stack2[MAX_STACK_SIZE];//�������� �򰡿� ����

void main()
{
	char expr2[50];//�Է�
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
	for (i = 0;i <= top;i++)printf("%c ", stack[i]);//���� ���
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
	for (i = 0;i <= top;i++)printf("%d ", stack2[i]);//�������
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
	for (i = 0;i < top;i++)printf("%c ", stack[i]);//�������
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
	for (i = 0;i < top;i++)printf("%d ", stack2[i]);//�������
	printf("\n");
	return stack2[top--];
}
void infix_to_postfix()
{
	char token;
	char post[50];
	char poptoken;//���ÿ��� ���� ������
	int i, j = 0;
	while ((token = expr[pos]) != '\0')
	{
		sym = read_input(expr);

		if (sym == 0) {
			post[j++] = token;
			if (read_input(expr + 1) != 0) post[j++] = ' ';
		}//�����϶�

		else if (sym == 1)
		{
			if (token == '(') 	push(token);
			else if (token == ')')
			{
				while ((poptoken = pop()) != '(') {

					post[j++] = poptoken;
					post[j++] = ' ';
				}//��ȣ ���� ������ ��� pop

			}
			else {

				while (precedence(stack[top]) >= precedence(token) && top != -1)
				{
					poptoken = pop();
					post[j++] = poptoken;
					post[j++] = ' ';
				}
				push(token);

			}//��ȣ�� �ƴ� ������ �� ���
		}//������ �� ��
		pos++;
	}
	while (top != -1)
	{
		poptoken = pop();
		post[j++] = poptoken;
		post[j++] = ' ';
	}//���ÿ� �����ִ� ������ pop
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
			}//�ڸ��� 
			if (i - count == 2 || i == 1) {
				push2(token - '0');

			}//���ڸ� �� ���
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
				}//int�� ���ڷ� ��ȯ
				push2(input);
				pos = i;

			}
			count = i;
		}//������ ���
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

			}//����
			count = pos + 1;

		}//������ �� ���
		pos++;
	}

	return stack2[top];//�� ��
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