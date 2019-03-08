#include <stdio.h>

#define ROW 5
#define COL 12

void main()
{
	/*read the numbers from text file*/
	FILE *file = fopen("words.txt", "r");

	if (file == NULL)
		printf("The file could not be opened.\n");
	else
	{
		/* create a two-dim array*/
		char arr[ROW][COL], word[5], dummy;
		int num_word, i = 0, j = 0;

		while (fscanf(file, "%c%c", &arr[i][j], &dummy) != EOF)
		{
			if (dummy == '\n')
			{
				i++;
				j = 0;
			}
			else
				j++;
		}

		
		fclose(file);

		printf("Which word do you want to display?\n");
		scanf("%d", &num_word);

		/* copy the word into a one-dim array */
		for (i = 0; i < ROW; i++)
			word[i] = arr[i][num_word - 1];

		printf("The word is ");
		for (i = 0; i < ROW; i++)
			printf("%c", word[i]);

		printf(".\n");
	}
}
