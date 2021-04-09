#include "tree.h"

typedef struct filesystem
{
    Node *root, *cwd;
    char dname[64], bname[64];
} FileSystem;

FileSystem* filesys;

#define SET_TEXT_BLUE "\033[1;36m"
#define RESET_TEXT "\033[0m"

void dbname(char *pathname){
    char temp[128]; 
    strcpy(temp, pathname);
    strcpy(filesys->dname, dirname(temp));
    strcpy(temp, pathname);
    strcpy(filesys->bname, basename(temp));
}

int initialize()
{
    filesys = (FileSystem *)malloc(sizeof(FileSystem));
    filesys->root = newNode("/",'D');
    filesys->cwd = filesys->root;
    return 0;
}
int isAbs(char* path)
{
    if(path[0] == '/')
        return 1;
    else
        return 0;
}

int mkdir(char* pathname)
{      
    Node *p;
    if (isAbs(pathname))
    {
        dbname(pathname);
        p = searchNode(filesys->root,filesys->dname);
        insertNode(p, filesys->bname,'D');
    }else{
        dbname(pathname);
        p = searchNode(filesys->cwd,filesys->dname);
        insertNode(p, filesys->bname,'D');
    }
    return 0;
}

int create(char* pathname)
{      
    Node *p;
    if (isAbs(pathname))
    {
        dbname(pathname);
        p = searchNode(filesys->root,filesys->dname);
        insertNode(p, filesys->bname,'F');
    }else{
        dbname(pathname);
        p = searchNode(filesys->cwd,filesys->dname);
        insertNode(p, filesys->bname,'F');
    }
    return 0;
}

int rmdir(char* pathname)
{
    Node *p;
    if (isAbs(pathname))
    {
        p = searchNode(filesys->root, pathname);
        deleteNode(p);
    }else{
        p = searchNode(filesys->cwd, pathname);
        deleteNode(p);
    }
    return 0;
}
int rm(char* pathname)
{
    Node *p;
    if (isAbs(pathname))
    {
        p = searchNode(filesys->root, pathname);
        if (p->type != 'F')
        {
            printf("file type error");
            return -1;
        }else{
            deleteNode(p);
        }
    }else{
        p = searchNode(filesys->cwd, pathname);
        if (p->type != 'F')
        {
            printf("file type error");
            return -1;
        }else{
            deleteNode(p);
        }
    }
    return 0;
}

int cd(char* pathname)
{
    Node *p = searchNode(filesys->root, pathname);
    if (p->type != 'D')
    {
       printf("please input a valid path");
       return -1;
    }
    filesys->cwd = p;
    return 0;
}

int pwd(Node *pcur)
{
    if (pcur == filesys->root)
    {
        printf("/");
        return 0;
    }else{
        pwd(pcur->parentPtr);
        if(pcur->parentPtr == filesys->root){
            printf("%s", pcur->name);
        }else{
            printf("/%s", pcur->name);
        }
    }
    return 0;
}

void print_node(Node *pcur){
    if(pcur->type == 'D'){
        printf(SET_TEXT_BLUE);
        printf("%s\n", pcur->name);
        printf(RESET_TEXT);
    }else{
        printf("%s\n", pcur->name);
    }
}

int ls(char* pathname)
{
    Node *p;
    if (!strcmp(pathname, ""))
    {
       p = filesys->cwd;
    }else{
        if (isAbs(pathname))
        {
            p = searchNode(filesys->root, pathname);
        }else{
            p = searchNode(filesys->cwd, pathname);
        }
    }
    p = p->childPtr;
    while (p)
    {
        print_node(p);
        p = p->siblingPtr;
    }
    
    
}

int menu(){
    printf("valid commands include: ls, pwd, menu, mkdir, rmdir, rm, creat, save, reload, & quit\n");
    return 0;
}