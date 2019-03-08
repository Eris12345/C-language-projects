#include<stdio.h>
#include<stdlib.h>

#define SIZE 15

enum record_status { EMPTY, DELETED, OCCUPIED };

typedef struct {
	int ct_id;
	char ct_name[20];
	char ct_department[20];
}candidate_t;

typedef struct {
	candidate_t info;
	enum record_status status;
}hash_t;

int hashFunction(int key)
{
	return (key % SIZE);
}

int searchFromHash(int key, hash_t hash_table[])
{
	int count, temp, position;
	temp = hashFunction(key);
	position = temp;
	for (count = 1; count != SIZE - 1; count++)
	{
		if (hash_table[position].status == EMPTY)
			return -1;
		if (hash_table[position].info.ct_id == key)
			return position;
		position = (temp + count) % SIZE;
	}
	return -1;
}

void insertIntoHash(candidate_t candidate, hash_t hash_table[])
{
	int count, position, temp, flag = 1;
	int key = candidate.ct_id;
	temp = hashFunction(key);
	position = temp;
	for (count = 1; count != SIZE - 1 && flag; count++)
	{
		if (hash_table[position].status == EMPTY || hash_table[position].status == DELETED)
		{
			hash_table[position].info = candidate;
			hash_table[position].status = OCCUPIED;
			printf("\nRecord Inserted into the Hash Table\n");
			flag = 0;
		}
		else if (hash_table[position].info.ct_id == key)
		{
			printf("\nDuplicate Record cannot be Inserted\n");
			flag = 0;;
		}
		else position = (temp + count) % SIZE; //linear probing
	}
	if (flag) printf("\nHash Table Limit Exceeded\n");
}

void displayHashContents(hash_t hash_table[])
{
	int count;
	printf("\nHash Table\n");
	for (count = 0; count < SIZE; count++)
	{
		printf("[%d]:\t", count);
		if (hash_table[count].status == OCCUPIED)
			printf("Occupied - ID: %d    Name: %s   Department: %s\n", hash_table[count].info.ct_id, hash_table[count].info.ct_name, hash_table[count].info.ct_department);
		else if (hash_table[count].status == DELETED)
			printf("Deleted\n");
		else
			printf("Empty\n");
	}
}

void deleteFromHash(int key, hash_t hash_table[])
{
	int position = searchFromHash(key, hash_table);
	if (position == -1)
		printf("\nId Not Found\n");
	else
	{
		hash_table[position].status = DELETED;
		printf("\nId deleted from the Hash Table\n");
	}
}

int
menu()
{
	int option;
	printf("\n     MENU\n");
	printf("*********************\n");
	printf("1. Insert a Candidate\n");
	printf("2. Delete a Candidate\n");
	printf("3. Search a Candidate\n");
	printf("4. Display All Candidates\n");
	printf("5. Exit\n");
	do {
		printf("Enter Your Option:\t");
		scanf("%d", &option);
	} while (option <1 || option >5);
	return option;
}

int main()
{
	int count, key, option;
	hash_t hash_table[SIZE];
	candidate_t candidate;
	for (count = 0; count <= SIZE - 1; count++)
		hash_table[count].status = EMPTY;
	do
	{
		option = menu();

		switch (option)
		{
		case 1: printf("\nEnter Candidate ID:\t");
			scanf("%d", &candidate.ct_id);

			printf("Enter Candidate Name:\t");
			scanf("%s", candidate.ct_name);

			printf("Enter Department of Candidate:\t");
			scanf("\n%[^\n]", candidate.ct_department);

			insertIntoHash(candidate, hash_table);
			break;

		case 2: printf("\nEnter the ID to Delete Candidate:\t");
			scanf("%d", &key);

			deleteFromHash(key, hash_table);
			break;

		case 3: printf("\nEnter the Id to Search Candidate:\t");
			scanf("%d", &key);

			count = searchFromHash(key, hash_table);

			if (count == -1)
				printf("\nId Not Found\n");
			else
			{
				printf("\nId Found at Index Position:\t%d\n", count);
				printf("ID: %d     Name : %s     Department : %s\n", hash_table[count].info.ct_id, hash_table[count].info.ct_name, hash_table[count].info.ct_department);
			}
			break;

		case 4: displayHashContents(hash_table);
			break;
		}
	} while (option != 5);
	return 0;
}

