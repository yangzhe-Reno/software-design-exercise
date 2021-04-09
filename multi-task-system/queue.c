int enqueue(Proc **queue, Proc *p)
{
    Proc *q = *queue;
    if (q == 0 || p->priority > q->priority)
    {
       *queue = p;
       p->next = q;
    }else{
        while (q->next && p->priority <= q->next->priority)
        {
            q = q->next;
        }
        p->next = q->next;
        q->next = p;
    }
}

Proc* dequeue(Proc **queue)
{
    Proc *p = *queue;
    if (p)
    {
       *queue = (*queue)->next;
    }
    return p;
}

int printList(char* name, Proc *p)
{
    printf("%s = ", name);
    while (p)
    {
        printf("[%d %d]->", p->pid, p->priority);
        p = p->next;
    }
    printf("NULL\n");
}