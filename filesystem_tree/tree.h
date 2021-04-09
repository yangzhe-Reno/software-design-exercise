#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

typedef struct node
{
    char name[64];
    char type;
    struct node *childPtr, *siblingPtr, *parentPtr;
} Node;

Node* newNode(char* name, char type);
Node* searchNode(Node *root, char* pathname);
int insertNode(Node *pcur, char* name, char type);
int deleteNode(Node *pcur);