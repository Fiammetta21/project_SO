#include "./headers/msg.h"

static msg_t msgTable[MAXMESSAGES];
LIST_HEAD(msgFree_h);

void initMsgs() {
    INIT_LIST_HEAD(&msgFree_h) ; //inizializza la lista come vuota
    for(i = 0; i<MAXMESSAGES; i++) {
        list_add_tail(&msgTable[i].m_list, &msgFree_h) ; //aggiunge ogni elemento di msgTable alla lista msgFree_h
    }
}

void freeMsg(msg_t *m) {
    if(m != NULL) {
        if(list_empty(&msgFree_h)) {
            INIT_LIST_HEAD (&msgFree_h) ;
        }
        list_add(&m->m_list, &msgFree_h) ;
    }
}

msg_t *allocMsg() {
    if(list_empty(&msgFree_h)) {
        return NULL ;
    }

    struct list_head *msgNode = msgFree_h.next ;
    list_del(msgNode) ; //rimuove un elemento dalla lista msgFree_h

    msg_t *newMsg = container_of(msgNode, msg_t, m_list) ; //ottiene il puntatore al messaggio della struttura list_head

    newMsg->m_playload = 0 ;

    return newMsg ; //restituisce il puntatore al messaggio allocato
}

//Inizializza la lista messaggi vuota
void mkEmptyMessageQ(struct list_head *head) {
    INIT_LIST_HEAD(head);
}

//Verifica che la lista sia vuota
int emptyMessageQ(struct list_head *head) {
    return list_empty(head);
}

//Inserimento in coda della lista head
void insertMessage(struct list_head *head, msg_t *m) {
    list_add_tail(&m->m_list, head);
}

//Inserimento in testa della lista head
void pushMessage(struct list_head *head, msg_t *m) {
    list_add(&m->m_list, head);
}

//Rimozione messaggio dalla lista
msg_t *popMessage(struct list_head *head, pcb_t *p_ptr) {
    struct list_head *temp;

    list_for_each(temp, head) {
        msg_t *message = container_of(temp, msg_t, m_list);
        if (p_ptr == NULL || message->m_sender == p_ptr) {
            list_del(temp); // Rimuove il messaggio dalla lista dei messaggi
            return message; // Restituisce il messaggio trovato
        }
    }
    return NULL; //NULL se lista vuota o nessun messaggio dall'utente specificato
}

// Restituisce il primo messaggio in una coda di messaggi, senza rimuoverlo
msg_t *headMessage(struct list_head *head) {
    if (list_empty(head)) {
        return NULL; // Restituisce NULL se la lista è vuota
    } else {
        return container_of(head->next, msg_t, m_list); // Restituisce il primo messaggio
    }
}
