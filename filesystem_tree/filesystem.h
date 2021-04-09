#include "tree.h"

typedef struct filesystem
{
    Node *root, *cwd;
    char dname[64], bname[64];
} FileSystem;

FileSystem* filesys;


int initialize();
int mkdir(char* pathname);
int rmdir(char* pathname);
int cd(char* pathname);
int pwd(Node *pcur);
int ls(char* pathname);
int rm(char* pathname);
int create(char* pathname);