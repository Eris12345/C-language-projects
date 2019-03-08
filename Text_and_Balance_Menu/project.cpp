#include <stdio.h>

# define SIZE 30

int
dispMenu()
{
	int option;

	//display menu
	printf("\n                MENU\n");
	printf("-------------------------------------\n");
	printf("1- List the accounts with zero balances\n");
	printf("2- Display the account which has the maximum balance\n");
	printf("3- Exit\n");

	do {
		//read and validate the user's choice
		printf("Enter your request: ");
		scanf("%d", &option);

	} while (option < 1 || option>3);
	
	return option;
}

//Display the list of accounts with zero balances
void
displayZeroBalances(int id[], double balance[], int size)
{
	int	i;

	for (i = 0; i < size; i++)
		if (balance[i] == 0)
			printf("%d	%6.2f\n", id[i], balance[i]);
}


//find the accounts which has the maximum balance
int
findMaxBalance(double balance[], int size)
{
	int	i, maxInd = 0;

	for (i = 1; i < size; i++)
		if (balance[i] > balance[maxInd])
			maxInd = i;

	return maxInd;
}

int
main(void)
{
	FILE *customers = fopen("customer.txt", "r");
	int	option,				//input-user's choice
		id[SIZE],			//input-keeps the id's of customers
		status,
		maxInd,
		i;					//loop control variable

	double balance[SIZE];	//input-keeps the balances of customers

	if (customers == NULL)
		printf("Error! File not found!\n");
	else
	{
		i = 0;
				
		//read id and balance information for each customer into the parallel arrays
		status = fscanf(customers, "%d %lf", &id[i], &balance[i]);

		while (status != EOF)
		{
			i++;
			status = fscanf(customers, "%d %lf", &id[i], &balance[i]);
		}
		fclose(customers);

		do {
			option = dispMenu();

			if (option != 3)
			{
				switch (option)
				{
				case 1:
					printf("\nAccounts with zero balances:\n");
					displayZeroBalances(id, balance, i);

					break;

				case 2:
					maxInd = findMaxBalance(balance, i);
					printf("\nAccount Info which has the maximum balance:\n");
					printf("%d	%6.2f\n", id[maxInd], balance[maxInd]);
					break;
				}
			}

		} while (option != 3);

	}
	return(0);
}
