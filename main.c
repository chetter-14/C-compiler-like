#include <stdbool.h>
#include <stdio.h>
#define ERRORLINESAMOUNT 10


int main()
{
	char c;
	bool isEverythingFine = true;
	bool parToBeClosed = false, squareToBeClosed = false;
	bool singleQuoteWasMet = false, doubleQuoteWasMet = false;
	int bracesToBeClosed = 0;
	int nl = 1, i = 0;					// i - to access errorlines[] array 
	int errorLines[ERRORLINESAMOUNT]; 	// array of integers representing lines where a curly brackets error occured
	
	
	FILE* f = fopen("test.c", "r");
	
	while ((c = getc(f)) != EOF)
	{
		switch(c)
		{
		case '(':
			parToBeClosed = true;
			break;
			
		case ')':
			if (parToBeClosed)
			{
				parToBeClosed = false;
				break;
			}
			else 
			{
				printf("There isn't open round bracket on line %d\n", nl);
				isEverythingFine = false;
				break;
			}

		case '\n':
			if (parToBeClosed)
			{
				printf("Round brackets should be closed on line %d\n", nl);
				isEverythingFine = false;
				parToBeClosed = false;
			}
			if (singleQuoteWasMet)
			{
				printf("Single quotes should be closed on line %d\n", nl);
				isEverythingFine = false;
				singleQuoteWasMet = false;
			}
			if (doubleQuoteWasMet)
			{
				printf("Double quotes should be closed on line %d\n", nl);
				isEverythingFine = false;
				doubleQuoteWasMet = false;
			}
			nl++;
			break;
		
		case '{':
			bracesToBeClosed++;
			errorLines[i] = nl;
			i++;
			break;
		
		case '}':
			if (bracesToBeClosed)
			{
				bracesToBeClosed--;
				i--;
				break;
			}
			else
			{
				printf("No matching open curly bracket on line %d\n", nl);
				isEverythingFine = false;
				break;
			}
		
		//the same logic as with round brackets only add ';' case
		case '[':
			squareToBeClosed = true;
			break;
			
		case ']':
			if (squareToBeClosed)
			{
				squareToBeClosed = false;
				break;
			}
			else 
			{
				printf("There isn't open square bracket on line %d\n", nl);
				isEverythingFine = false;
				break;
			}

		case ';':
			if (squareToBeClosed)
			{
				printf("Square brackets should be closed on line %d\n", nl);
				isEverythingFine = false;
				squareToBeClosed = false;
			}
			break;
			
		case '\'':
			if (singleQuoteWasMet)
				singleQuoteWasMet = false;
			else
				singleQuoteWasMet = true;
			break;
		
		case '\"':
			if (doubleQuoteWasMet)
				doubleQuoteWasMet = false;
			else
				doubleQuoteWasMet = true;
			break;
		
		default:
			;
		}
	}
	
	if (bracesToBeClosed)
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
