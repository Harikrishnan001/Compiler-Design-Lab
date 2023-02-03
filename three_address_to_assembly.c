#include<stdio.h>
#include<string.h>

//sample input:
//a=b+c
//b=e*f
//exit

int main()
{
	char icode[10][30], opr[10];
	int i = 0;
	puts("Enter the intermediate code(finish with exit):");
	do {
		scanf("%s", icode[i]);
	} while (strcmp(icode[i++], "exit"));
	for (int j = 0; j < i-1; j++)
	{
		switch (icode[j][3])
		{
		case '+':
			strcpy(opr, "ADD");
			break;
		case '-':
			strcpy(opr, "SUB");
			break;
		case '*':
			strcpy(opr, "MUL");
			break;
		case '/':
			strcpy(opr, "DIV");
			break;
		}
		printf("MOV %c,R0\n", icode[j][2]);
		printf("%s %c,R0\n", opr, icode[j][4]);
		printf("MOV R0,%c\n", icode[j][0]);
	}
}
