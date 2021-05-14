#include <stdbool.h>
#include <stdio.h>
#define ERRORLINESAMOUNT 10


int main()
{
	char c;
	bool isEverythingFine = true, parToBeTerminated = false;
	int bracesToBeTerminated = 0;
	int nl = 1, i = 0;					// i - to access errorlines[] array 
	int errorLines[ERRORLINESAMOUNT]; 	// array of integers representing lines where a curly brackets error occured
	
	
	FILE* f = fopen("test.c", "r");
	
	while ((c = getc(f)) != EOF)
	{
		switch(c)
		{
		case '(':
			parToBeTerminated = true;
			break;
			
		case ')':
			if (parToBeTerminated)
			{
				parToBeTerminated = false;
				break;
			}
			else 
			{
				printf("There isn't open round bracket on line %d\n", nl);
				isEverythingFine = false;
				break;
			}

		case '\n':
			if (parToBeTerminated)
			{
				printf("Round brackets should be closed on line %d\n", nl);
				isEverythingFine = false;
				parToBeTerminated = false;
			}
			nl++;
			break;
		
		case '{':
			bracesToBeTerminated++;
			errorLines[i] = nl;
			i++;
			break;
		
		case '}':
			if (bracesToBeTerminated)
			{
				bracesToBeTerminated--;
				i--;
				break;
			}
			else
			{
				printf("No matching open curly bracket on line %d\n", nl);
				isEverythingFine = false;
				break;
			}
			
		default:
			;
		}
	}
	
	if (bracesToBeTerminated)
	{
		isEverythingFine = false;
		for (int j = 0; j < i; j++)
			printf("No matching close curly bracket on line %d\n", errorLines[j]);
	}
	
	if (isEverythingFine)
		printf("Everything went fine!\n");
		
	fclose(f);
	return 0;
}
