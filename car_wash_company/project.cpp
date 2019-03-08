#define SIZE 8

#include <stdio.h>
#include <string.h>
#include "stack_str.h"
#include "queue_str.h"

void displayStack(stack_t stackp);

void displayQueue(queue_t q);

void carWash(stack_t *stck, queue_t *que, char kod, char *plate);

int main(void)
{
	FILE *fptr;
	int	status;
	char	code, plate[20] = "";
	stack_t	lane;
	queue_t	park;

	initialize_s(&lane);
	initialize_q(&park);
	push(&lane, "45NMH69");
	push(&lane, "35FDG63");
	push(&lane, "15DER12");// all lanes have cars

	fptr = fopen("car_wash.txt", "r");
	if (fptr == NULL)
		printf("File con not be opened!!");
	else
	{

		status = fscanf(fptr, "%c %[^\n]", &code, plate);
		while (status != EOF)
		{

			carWash(&lane, &park, code, plate);
			status = fscanf(fptr, " %c %[^\n]", &code, plate);
		}
		fclose(fptr);
	}
	return (0);
}

void displayStack(stack_t stackp)
{
	char plate[SIZE];
	while (!is_empty_s(&stackp))
	{
		strcpy(plate, pop(&stackp));
		printf("%s\n", plate);
	}
}

void displayQueue(queue_t q)
{
	char plate[SIZE];

	while (!is_empty_q(&q))
	{
		strcpy(plate, remove(&q));
		printf("%s\n", plate);
	}
}

void carWash(stack_t *stck, queue_t *que, char kod, char *plate)
{
	stack_t	temp;
	char temp_plate[20];

	if (kod == 'A')
		insert(que, plate);
	else if (kod == 'D')
	{
		initialize_s(&temp);
		strcpy(temp_plate, pop(stck));
		while (strcmp(temp_plate, plate) != 0 && !is_empty_s(stck))
		{
			push(&temp, temp_plate);
			strcpy(temp_plate, pop(stck));
		}

		while (!is_empty_s(&temp))
		{
			strcpy(temp_plate, pop(&temp));
			push(stck, temp_plate);
		}

		//a waiting car will be moved into the washing lane
		strcpy(temp_plate, remove(que));
		push(stck, temp_plate);
	}
	else
		printf("\nInvalid code!");
	
	printf("The washing lanes:\n");
	displayStack(*stck);printf("\n");

	printf("The car Queue:\n");
	displayQueue(*que);

	printf("*****************\n");
}
