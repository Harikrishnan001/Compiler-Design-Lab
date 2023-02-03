//E -> TE'
//E' -> +TE'  | NULL
//T ->FT'
//T' -> *FT' | NULL
//F -> (E) | id
//sample input: a+a*a
#include<stdio.h>
#include<string.h>

void E();
void T();
void F();
void Eds();
void Tds();
char input[100];
int i, error;

int main()
{
	printf("Enter the input:");
	scanf("%s", input);
	E();
	if (i == strlen(input) && !error)
	{
		printf("String is accepted!\n");
	}
	else {
		printf("String is rejected!\n");
	}
}

void E()
{
	T();
	Eds();
}

void T()
{
	F();
	Tds();
}

void Eds()
{
	if (input[i] == '+')
	{
		i++;
		T();
		Eds();
	}
}

void Tds()
{
	if (input[i] == '*')
	{
		i++;
		F();
		Tds();
	}
}

void F()
{
	if (input[i] == 'a')
	{
		i++;
	}
	else if (input[i] == '(')
	{
		i++;
		E();
		if (input[i] == ')')
		{
			i++;
		}
		else
		{
			error = 1;
		}
	}
	else
	{
		error = 1;
	}
}
