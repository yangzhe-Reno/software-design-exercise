#define NPROC 9
#define SSIZE 1024

#define FREE   0
#define READY  1
#define SLEEP  2
#define ZOMBTE 3

typedef struct proc
{
    struct proc *next;
    int *ksp;
    int pid;
    int ppid;
    int status;
    int priority;
    int kstack[SSIZE];    
} Proc;
