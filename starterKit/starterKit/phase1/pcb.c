#include "./headers/pcb.h"

static pcb_t pcbTable[MAXPROC];
LIST_HEAD(pcbFree_h);
static int next_pid = 1;

void initPcbs() {
}

void freePcb(pcb_t *p) {
}

pcb_t *allocPcb() {
}

void mkEmptyProcQ(struct list_head *head) {
}

int emptyProcQ(struct list_head *head) {
}

void insertProcQ(struct list_head *head, pcb_t *p) {
}

pcb_t *headProcQ(struct list_head *head) {
}

pcb_t *removeProcQ(struct list_head *head) {
}

pcb_t *outProcQ(struct list_head *head, pcb_t *p) {
}

int emptyChild(pcb_t *p) {
    //verifica se la lista
    return (p->p_child.next == &p->p_child) && (p->p_child.prev == &p->p_child) ? 1:0;
}

void insertChild(pcb_t *prnt, pcb_t *p) {
    //imposta il genitore del PCB p
    p->p_parent = prnt;

    //aggiungi il PCB p alla lista dei figli di prnt
    if(list_empty(&prnt->p_child)){
        //la lista dei figli è vuota, quindi p diventa l'unico figlio
        INIT_LIST_HEAD(&p->p_child);
        list_add(&p->p_child, &prnt->p_child);}
        else{
            //La lista dei figli non è vuota, aggiungi p alla fine della lista
            list_add_tail(&p->p_child, &prnt->p_child);
        }
    }
}

pcb_t *removeChild(pcb_t *p) {
    //verifica se lisya dei figli è vuota
    if(list_empty(&p->p_child)){
        //non ci sono figli, reztituisci NULL
        return NULL;
    }

    //ottieni il primo figlio
    pcb_t *first_child = list_first_entry(&p->p_child, pcb_t, p_child);

    //rimuovi il primo figlio dalla lista dei figli
    list_del(&first_child->p_child);

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
    list_del(&p->p_child);

    // Rimuovi il riferimento al genitore nel PCB p
    p->p_parent = NULL;

    // Restituisci il puntatore al PCB p
    return p;

}