#include <stdbool.h>
#include <stdio.h>


int main()
{
	char c;
	bool isCorrect, toBeTerminated = false;
	int nl = 1;
	
	FILE* f = fopen("test.c", "r");
	
	while ((c = getc(f)) != EOF)
	{
		if (c == '(')
		{
			toBeTerminated = true;
			while ((c = getc(f)) != '\n')
			{
				if (c == ')')
				{
					toBeTerminated = false;
					break;
				}
			}
		}
		if (toBeTerminated)
		{
			printf("The parentheses should be closed on line %d\n", nl);
			break;
		}
		if (c == '\n')
			nl++;
	}
	
	if (!toBeTerminated)
		printf("Everything went fine!");
		
	fclose(f);
	return 0;
}
