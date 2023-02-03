//Grammar:
//E->E+E
//E->E*E
//E->(E)
//E->id
//
//sample input:id+id*id

#include<stdio.h>
#include<string.h>

int k, c, z, i,j;
char stk[50], act[50], a[50], ac[50];

void check();

int main()
{
	printf("Enter the string:");
	gets_s(a,50);
	c = strlen(a);
	strcpy(act, "SHIFT->id");
	printf("%-15s%-15s%-15s", "Stack", "Input", "Action");
	for (k = 0, i = 0; j < c; k++, i++, j++)
	{
		if (a[j] == 'i' && a[j + 1] == 'd')
		{
			stk[i] = a[j];
			stk[i + 1] = a[j + 1];
			stk[i + 2] = '\0';
			a[j] =a[j+1] =' ';
			printf("\n%-15s%-15s%-15s", stk, a, act);
			check();
		}
		else
		{
			stk[i] = a[j];
			stk[i + 1] = '\0';
			a[j] = ' ';
			printf("\n%-15s%-15s%-15s", stk, a, act);
			check();
		}
	}
}

void check()
{
	strcpy(ac, "REDUCE to E");
	for(z=0;z<c;z++)
		if (stk[z] == 'i' && stk[z + 1] == 'd')
		{
			stk[z] = 'E';
			stk[z + 1] = '\0';
			printf("\n%-15s%-15s%-15s", stk, a,ac);
			j++;
		}
	for(z=0;z<c;z++)
		if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E')
		{
			stk[z + 1] =stk[z+2]= '\0';
			printf("\n%-15s%-15s%-15s", stk, a, ac);
			i = i - 2;
		}
	for (z = 0; z < c; z++)
		if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E')
		{
			stk[z + 1] = stk[z + 2] = '\0';
			printf("\n%-15s%-15s%-15s", stk, a, ac);
			i = i - 2;
		}
	for (z = 0; z < c; z++)
		if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')')
		{
			stk[z] = 'E';
			stk[z + 1] = stk[z + 2] = '\0';
			printf("\n%-15s%-15s%-15s", stk, a, ac);
			i = i - 2;
		}
}
