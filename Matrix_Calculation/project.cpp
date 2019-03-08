/* program that reads a file into a 2D array using functions, doing different display operations and calculations using the array */
#include <stdio.h>

#define ROWS 5
#define COLS 5

//menu
int menu();
//read file that fills the file content into array
void readFile(FILE *fp, int arr[][COLS]);
//displays the matrix
void displayMatrix(int arr[][COLS]);
//displays the sum of minor diagonal
void displayMinorDiag(int arr[][COLS]);
//displays the average of major diagonal
void displayAvgMajor(int arr[][COLS]);
//takes row number from the user to find its max number
void displayMinOfGivenRow(int arr[][COLS]);
//takes col number from the user to find its max number
void displayMaxOfGivenCol(int arr[][COLS]);
//displays the sum and average of the matrix
void displaySumAndAvg(int arr[][COLS]);

int main(void)
{
	FILE *fp = fopen("Q2.txt", "r");

	if (fp == NULL)
		printf("The file Q2.txt couldn't be opened.\n");
	else
	{
		int choice, arr[ROWS][COLS];
		readFile(fp, arr);
		do
		{
			choice = menu();

			switch (choice)
			{
			case 1:
				displayMatrix(arr);
				break;
			case 2:
				displayMinorDiag(arr);
				break;
			case 3:
				displayAvgMajor(arr);
				break;
			case 4:
				displayMaxOfGivenCol(arr);
				break;
			case 5:
				displayMinOfGivenRow(arr);
				break;
			case 6:
				displaySumAndAvg(arr);
			}
		} while (choice != 7);
	}

	return 0;
}

int menu()
{
	int choice;

	printf("        Diplay the ... \n");
	printf("1.  Matrix\n");
	printf("2.  Sum of the minor diagonal\n");
	printf("3.  Average of the major diagonal\n");
	printf("4.  Maximum of the given column\n");
	printf("5.  Minimum of the given row\n");
	printf("6.  Sum and average of the matrix\n");
	printf("7.  Exit\n");

	do
	{

		printf("Enter your choice: ");
		scanf("%d", &choice);
		//simple validation
	} while (choice < 1 && choice > 7);

	return choice;
}

void readFile(FILE *fp, int arr[][COLS])
{
	//reads the file opened on fp pointer into the arr
	for (int i = 0; i < ROWS; i++)
		for (int y = 0; y < COLS; y++)
			fscanf(fp, "%d", &arr[i][y]);
}

//simple 2D array print out
void displayMatrix(int arr[][COLS])
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int k = 0; k < COLS; k++)
			printf("%4d", arr[i][k]);
		printf("\n");
	}
	printf("\n");
}

//the minor diagonal starts from the right most upper edge and goes towards the left most lower edge of the matrix; we want its sum of numbers
void displayMinorDiag(int arr[][COLS])
{
	int minor = 0, k;

	//2 index for loop example, can also be solved with simple while instead
	/*for (i, k; i < ROWS && k >= 0; i++, k--)
		minor += arr[i][k];
	alternative sol */

	for (k = 0; k < COLS; k++)
		minor += arr[k][COLS - 1 - k];
	printf("The sum of the minor diagonal in this matrix is: %d...\n\n", minor);
}

//major diagonal is from the left most upper edge to the right most lower edge of the matrix; we want its average here
void displayAvgMajor(int arr[][COLS])
{
	int major = 0, k = 0;

	for (k; k < COLS; k++)
		major += arr[k][k];

	printf("The average of the major diagonal in this matrix is: %0.1f...\n\n", 1.0*major / COLS);
}

//finds and displays the biggest number in a given row
void displayMinOfGivenRow(int arr[][COLS])
{
	int row, min, i = 0;

	printf("Please enter the row from which you want the minimum element: ");
	scanf("%d", &row);

	min = arr[row][i];
	for (i; i < ROWS; i++)
		if (min > arr[row][i])
			min = arr[row][i];

	printf("Minimum number within the row you have selected is %d.\n\n", min);
}

//finds and displays the biggest number in a given col
void displayMaxOfGivenCol(int arr[][COLS])
{
	int col, max, i = 0;

	printf("Please enter the column from which you want the maximum element: ");
	scanf("%d", &col);

	max = arr[i][col];
	for (i = 1; i < COLS; i++)
		if (max < arr[i][col])
			max = arr[i][col];

	printf("Maximum number within the column you have selected is %d.\n\n", max);
}

//finds the sum of all numbers in the array matrix as well as their average
void displaySumAndAvg(int arr[][COLS])
{
	double total = 0;
	int count = COLS * ROWS;

	for (int i = 0; i < ROWS; i++)
		for (int k = 0; k < COLS; k++)
			total += arr[i][k];

	printf("The sum of this matrix is %0.0f and its average is %0.2f\n\n", total, total / count);
}
