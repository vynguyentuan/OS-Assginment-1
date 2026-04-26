#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
        if (q == NULL)
                return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc) {
    if (q == NULL || proc == NULL) return;
    
    if (q->size >= MAX_QUEUE_SIZE) {
        printf("ERROR: Queue is full. Cannot enqueue PID %d\n", proc->pid);
        return; 
    }
    
    q->proc[q->size] = proc;
    q->size++;
}

struct pcb_t *dequeue(struct queue_t *q) {
    if (q == NULL || empty(q)) return NULL;
    
    struct pcb_t *top_proc = q->proc[0];
    for (int i = 0; i < q->size - 1; i++) {
        q->proc[i] = q->proc[i + 1];
    }
    q->proc[q->size - 1] = NULL;
    q->size--;
    
    return top_proc;
}
struct pcb_t *purgequeue(struct queue_t *q, struct pcb_t *proc) {
    if (q == NULL || proc == NULL || empty(q)) return NULL;
    
    int target = -1;
    for (int i = 0; i < q->size; i++) {
        if (q->proc[i] == proc) {
            target = i;
            break;
        }
    }
    
    if (target == -1) return NULL;
    
    struct pcb_t *removed_proc = q->proc[target];
    for (int i = target; i < q->size - 1; i++) {
        q->proc[i] = q->proc[i + 1];
    }
    q->proc[q->size - 1] = NULL;
    q->size--;
    
    return removed_proc;
}