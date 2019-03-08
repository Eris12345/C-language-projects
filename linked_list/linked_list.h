#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXI 20

typedef struct node_s
{
	char data[MAXI];
	struct node_s *next;
} node_t;

node_t *getNode(void)
{
	node_t *node;
	node = (node_t *)malloc(sizeof(node_t));
	node->next = NULL;
	return (node);
}

void addAfter(node_t *p, char *item)
{
	node_t *newp;
	newp = getNode();
	strcpy(newp->data, item);
	newp->next = p->next;
	p->next = newp;
}

node_t *addBeginning(node_t *headp, char *item)
{
	node_t *newp;
	newp = getNode();
	strcpy(newp->data, item);
	newp->next = headp;
	return (newp);
}
