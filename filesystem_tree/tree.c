#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "tree.h"

Node* newNode(char* name, char type)
{
    Node* p = (Node *)malloc(sizeof(Node));
    p->type = type;
    strcpy(p->name, name);
    p->childPtr = p->childPtr = p->parentPtr = NULL;
    return p;
}

Node* searchNodefromLevel(Node *root, char* driname)
{
    Node *p;
    p = root->childPtr;
    if (!strcmp(p->name, (char *)dirname))
    {
        p = p->siblingPtr;
        while (!strcmp(p->name, (char *)dirname))
        {
            p = p->siblingPtr;
        }
        return p;
    }else{
        return p;
    }
}

Node* searchNode(Node *root, char* pathname)
{
    char *dirname;
    dirname = strtok(pathname, "/");
    while (dirname)
    {   
        root = searchNodefromLevel(root, dirname);
        if (root==NULL)
        {
            printf("Please provide a valid path\n");
            return NULL ;
        }
        
        dirname = strtok(NULL,"/");
    }
    return root;
}


int insertNode(Node *pcur, char* name, char type)
{
    Node *newchild = newNode(name, type);

    if (pcur->childPtr == NULL)
    {
        pcur->childPtr = newchild;
        newchild->parentPtr = pcur;
    }else{
        pcur = pcur->childPtr;
        while (pcur->siblingPtr)
        {
            pcur = pcur->siblingPtr;
        }
        pcur->siblingPtr = newchild;
        newchild->parentPtr = pcur->parentPtr;
    }
    return 0;
}

int deleteNode(Node *pcur)
{
    Node* parent = pcur->parentPtr;
    Node* temp;
    if(!strcmp(pcur->name, "/")){
        printf("STOP TRYING TO DELETE THE ROOT\n");
        return 0;
    }
    if (parent->childPtr == pcur)
    {
        if (pcur->siblingPtr == NULL)
        {
            free(pcur);
            parent->childPtr = NULL;
        }else{
            parent->childPtr = pcur->siblingPtr;
            free(pcur);
        }
    }else{
        temp = parent->childPtr;
        while (temp->siblingPtr != pcur)
        {
            temp = temp->siblingPtr;
        }
        temp->siblingPtr = pcur->siblingPtr;
        free(pcur);
    }
    return 0;
}