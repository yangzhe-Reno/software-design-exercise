#include <stdio.h>
#include "type.h"

Proc proc[NPROC];
Proc *freeList;
Proc *readyQueue;
Proc *running;

#include "queue.c"

int init()
{
    Proc *p;
    int i;
    for (i = 0; i < NPROC; i++)
    {
        p = &proc[i];
        p->pid = i;
        p->status = FREE;
        p->priority = 0;
        p->next = p+1;
    }
    proc[NPROC-1].next = NULL;
    freeList = &proc[0];
    readyQueue = NULL;

    running = dequeue(&freeList);
    p = running;
    p->status = READY;
    p->ppid = 0;
    printList("freeList:", freeList);
    printf("init complete: P0 running\n");
}

int body()
{
    int c;
    printf("proc %d starts from body()\n", running->pid);
    while (1)
    {
       printf("*********************************\n");
       printf("proc %d running: parent=%d\n", running->pid, running->ppid);
       printf("enter a key [f|s|q] :");
       c = getchar();getchar();
       switch (c)
       {
       case 'f': do_kfork();
           break;
       case 's': do_switch();
           break;
        case 'q': do_exit();
           break;
       default:
           break;
       }
    } 
}

int kfork()
{
    int i;
    Proc *p = dequeue(&freeList);
    if(!p)
    {
        printf("no more proc\n");
        return -1;
    }
    p->status = READY;
    p->priority = 1;
    p->ppid = running->pid;
    for(i = 0;i < 10 ;i++)
        p->kstack[SSIZE-i] = 0;
    p->kstack[SSIZE-1] = (int)body;
    p->ksp = &(p->kstack[SSIZE - 9]);
    enqueue(&readyQueue, p);
    return p->pid;
}

int kexit()
{
    running->status = FREE;
    running->priority = 0;
    enqueue(&freeList, running);
    printList("freeList", freeList);
    tswitch();
}

int do_kfork()
{
    int child = kfork();
    if (child < 0 )
    {
        printf("kfork failed\n");
    }else{
        printf("proc %d kforked a child = %d\n", running->pid, child);
        printList("readQueue", readyQueue);
    }
    return child;
}

int do_switch()
{
    tswitch();
}

int do_exit()
{
    kexit();
}

int scheduler()
{
    printf("proc %d in schduler()\n", running->pid);
    if (running->status == READY)
    {
        enqueue(&readyQueue, running);
    }
    printList("readyQueue", readyQueue);
    running = dequeue(&readyQueue);
    printf("next running = %d\n", running->pid);
    return 0;
}



int main()
{
    printf("Welcome to the MT Multitasking System\n");
    init();
    kfork();
    while (1)
    {
        printf("P0: switch process\n");
        printList("readyQueue", readyQueue);
        if (readyQueue)
        {
           tswitch();
        }
    }
    
    return 0;
}