

#include "linkedList.h"

node_t *createList(FILE *inp);
void displayList(node_t *headp);
void displayRec(node_t *headp, char *str);

int main()
{
	node_t *headp;
	char str[MAXI];
	FILE *words;

	words = fopen("words.txt", "r");

	if (words == NULL)
		printf("The file couldn't be opened.\n");
	else
	{
		//create the list
		headp = createList(words);
		fclose(words);

		if (headp != NULL)
		{	//display the list
			printf("Word List\n");
			printf("*********\n");
			displayList(headp);

			printf("\nEnter a string (\"??\" to stop): ");
			scanf("%s", str);

			while (strcmp(str, "??") != 0)
			{
				printf("\nWords starting or ending with \"%s\"\n", str);
				printf("**********************************\n");
				displayRec(headp, str);
				printf("\nEnter another string (\"??\" to stop): ");
				scanf("%s", str);
			}
		}
		else
			printf("\nThe List is empty.\n");
	}

	return 0;
}

node_t *createList(FILE *inp)
{
	node_t *headp = NULL, *p;
	char word[MAXI];

	if (fscanf(inp, " %s", word) != EOF)
	{
		headp = addBeginning(headp, word);
		p = headp;

		while (fscanf(inp, " %s", word) != EOF)
		{
			addAfter(p, word);
			p = p->next;
		}
	}
	return headp;
}

void displayList(node_t *headp)
{
	node_t *p;

	if (headp == NULL)
		printf("\nThe List is empty.\n");
	else
	{
		p = headp;
		while (p != NULL)
		{
			printf("%s\n", p->data);
			p = p->next;
		}
	}
}

void displayRec(node_t *headp, char *str)
{
	int len, lenstr;
	if (headp != NULL)
	{
		len = strlen(headp->data);
		lenstr = strlen(str);
		if (strncmp(headp->data, str, lenstr) == 0 || strncmp(headp->data + len - lenstr, str, lenstr) == 0)
			printf("%s\n", headp->data);
		displayRec(headp->next, str);
	}
}
