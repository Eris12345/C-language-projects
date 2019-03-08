/*LG4_Q3 -> Calculates the fees of all attendees in all universities and display them on the screen*/

#include <stdio.h>
#include <string.h>

#define ATT 8
#define UNI 3

typedef struct
{
	int id;
	char name[10];
	int age, trainedYear;
	double fee;
} attendees_t;

typedef struct
{
	int univID;
	char univName[20], mArtsName[20];
	attendees_t attendees[ATT];
} univ_t;

void readFile(univ_t *dep, FILE *fp);
void calcFee(univ_t *univ);
void display(univ_t *univ);

void main()
{
	FILE *fp = fopen("mArtsDay.txt", "r");

	if (fp == NULL)
		printf("The file couldn't be opened.\n");
	else
	{
		univ_t univ[UNI];

		readFile(univ, fp);

		calcFee(univ);

		display(univ);
	}
}

void readFile(univ_t *univ, FILE *fp)
{
	char dummy;
	for (int i = 0; i < UNI; i++)
	{
		fscanf(fp, "%d %s %s", &(univ + i)->univID, (univ + i)->univName, (univ + i)->mArtsName);
		for (int j = 0; j < ATT; j++)
			fscanf(fp, "%d %s %d %d", &(univ + i)->attendees[j].id, (univ + i)->attendees[j].name, &(univ + i)->attendees[j].age, &(univ + i)->attendees[j].trainedYear);
	}
}

void calcFee(univ_t *univ)
{
	for (int j = 0; j < UNI; j++)
		for (int i = 0; i < ATT; i++)
		{
			if (univ[j].attendees[i].trainedYear <= 3)
				univ[j].attendees[i].fee = univ[j].attendees[i].trainedYear * 100;
			else if (univ[j].attendees[i].trainedYear <= 10)
				univ[j].attendees[i].fee = univ[j].attendees[i].trainedYear * 125;
			else
				univ[j].attendees[i].fee = ((univ[j].attendees[i].trainedYear - 10) * 25 + 125) * univ[j].attendees[i].trainedYear;
		}
}

void display(univ_t *univ)
{
	for (int j = 0; j < UNI; j++)
	{
		printf("%s\n\nMartial Art: %s\n\n", (univ + j)->univName, (univ + j)->mArtsName);

		printf("ID     NAME      AGE   Years Trained      Fee  \n");
		printf("*** ***********  ***   *************   *********\n");

		for (int i = 0; i < ATT; i++)
			printf("%3d %-11s %5d %7d %15.2fTL\n", (univ + j)->attendees[i].id, (univ + j)->attendees[i].name, (univ + j)->attendees[i].age, (univ + j)->attendees[i].trainedYear, (univ + j)->attendees[i].fee);

		printf("\n");
	}
}
