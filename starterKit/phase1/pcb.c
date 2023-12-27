#include "./headers/pcb.h"

static pcb_t pcbTable[MAXPROC];
LIST_HEAD(pcbFree_h);
static int next_pid = 1;

void initPcbs() {

	INIT_LIST_HEAD(&pcbFree_h);
	
	for(int i = MAXPROC - 1; i >= 0; i--) {
		list_add()
	}
}

void freePcb(pcb_t *p) {
/*if pcbFree is empty initialize it*/
	if(list_empty(&pcbFree_h)) {
		INIT_LIST_HEAD(&pcbFree_h);
	} else {
		list_add(&p->p_list, &pcbFree_h);	
	}	
}


pcb_t *allocPcb() {

	// return NULL if the pcbFree list is empty
	if (list_empty(&pcbFree_h)) {
		return NULL;

	} else {

		// get the first element
		struct list_head *head = pcbFree_h.next;
		// remove it from the free list
		list_del(head);

		// return a pointer to the removed element
		pcb_t *p = container_of(head, pcb_t, p_list);

		// initial values for all PCB fields
		.p_list
		.p_parent
		.p_child
		.p_sib


	}
}


void mkEmptyProcQ(struct list_head *head) 
{
	INIT_LIST_HEAD(head);
}

int emptyProcQ(struct list_head *head) 
{
	return list_empty(head);
}

void insertProcQ(struct list_head *head, pcb_t *p) 
{
	list_add_tail(&p->p_list, head);
}

pcb_t *headProcQ(struct list_head *head) 
{
	if (emptyProcQ) {
		return NULL;
	}
	else {
		return container_of(head->next, pcb_t, p_list);
	}
}

pcb_t *removeProcQ(struct list_head *head) {
	if (emptyProcQ(head)) {
		return NULL;
	} else {
		pcb_t *removed = headProcQ(head);
		list_del(&removed->p_list);
		return removed;
	}
}

pcb_t *outProcQ(struct list_head *head, pcb_t *p) {
    // check if the queue is empty or if p is NULL
    if (emptyProcQ(head) || !p) {
        return NULL;
    }

    struct list_head *iter;
    list_for_each(iter, head) {
        struct pcb_t *current_pcb = list_entry(iter, pcb_t, p_list);
        if (current_pcb == p) {
            list_del(iter);
            return p;
        }
    }
    return NULL;
}


int emptyChild(pcb_t *p) {
    return list_empty(&p->p_child); 
}

void insertChild(pcb_t *prnt, pcb_t *p) {
    //imposta il genitore del PCB p
    p->p_parent = prnt;

    //aggiungi il PCB p alla lista dei figli di prnt
    list_add_tail(&p->p_sib, &prnt->p_child);
}


pcb_t *removeChild(pcb_t *p) {
    //verifica se lisya dei figli è vuota
    if(list_empty(&p->p_child)){
        //non ci sono figli, restituisci NULL
        return NULL;
    }

    //ottieni il primo figlio
    pcb_t *first_child = container_of(p->p_child.next, pcb_t, p_sib);

    //rimuovi il primo figlio dalla lista dei figli
    list_del(&first_child->p_sib);

    //rimuovi il riferimento al genitore nel PCB del figlio rimosso
    first_child->p_parent = NULL;
    
    //restituisci il puntatore al PCB del figlio rimosso
    return fist_child;
}

pcb_t *outChild(pcb_t *p) {
    // Verifica se il PCB ha un genitore
    if (p->p_parent == NULL) {
        // Se p non ha un genitore, restituisci NULL
        return NULL;
    }

    // Rimuovi p dalla lista dei figli del suo genitore
    list_del(&p->p_sib);

    // Rimuovi il riferimento al genitore nel PCB p
    p->p_parent = NULL;

    // Restituisci il puntatore al PCB p
    return p;

}