#include "./headers/msg.h"

static msg_t msgTable[MAXMESSAGES];
LIST_HEAD(msgFree_h);

void initMsgs() {
#define MAXMESSAGES 40 //dimensione massima definita da Renzo
    typedef struct msg_t {
        int data ;
        struct msg_t *next ; //puntatore al prossimo elemento nella lista
    } msg_t ;

    typedef struct {
        msg_t *head ;
    } msgFreeList ;

    void initMsgFreeList(msgFreeList *list) {
        list->head = NULL ;
    }

    void insertMsgFree(msgFreeList *list, msg_t *msg) {
        msg->next = list->head ;
        list->head = msg ;
    }

    //Funzione per inizializzare la lista msgFree con gli
    void initMsgs(msgFreeList *msgFree, msg_t *msgArray, size_t arraySize) {
        initMsgFreeList(msgFree) ; //inizializza la lista msgFree

        //inserisce gli elemento dell'array nella lista
        for (size_t i = 0; i < arraySize; i++) {
            insertMsgFree(msgFree, &msgArray[i])
        }
}

void freeMsg(msg_t *m) {
        //Struttura del messaggio
        typedef struct msg_t {
        int data ;
        struct msg_t *next ; //puntatore al prossimo elemento nella lista
    } msg_t ;

    //Definisco la struttura della lista
    typedef struct {
        msg_t *head ; //puntatore alla testa della lista
    } msgFreeList ;

    //Funzione per inizializzare la lista
    void initMsgFreeList(msgFreeList *list) {
        list->head = NULL ; //inizializza la testa della lista a NULL
    }

    //Funzione per inserire un elemento in testa alla lista
    void insertMsgFree(msgFreeList *list, msg_t *msg) {
        msg->next = list->head ; //il prossimo elemento del messaggio è l'attuale testa della lista
        list->head = msg ; //aggiorna la testa della lista con il nuovo messaggio
    }

    //Funzione per liberare un messaggio e inserirlo nella lista
    void freeMsg(msgFreeList *msgFree, msg_t *msg) {
     insertMsgFree(msgFree, msg) ; //inserisce il messaggio nella lista
    }
}


msg_t *allocMsg() {
    typedef struct msg_t {
        int dati ;
        struct msg_t *next ; //puntatore al prossimo elemento nella lista
    } msg_t;

    //Struttura della lista
    typedef struct {
        msg_t *head
    } msgFreeList ;


    void initMsgFreeList(msgFreeList *list) {
        list->head = NULL ; //inizializza la testa della lista a NULL
    }

    //Funzione per inserire un elemento in testa alla lista
    void insertMsgFree(msgFreeList *list, msg_t *msg) {
        msg->next = list->head ; //il prossimo elemento del messaggio è l'attuale testa della lista
        list->head = msg ; //aggiorna la testa della lista con il nuovo messaggio
    }

    //Funzione per allocare un messaggio
    msg_t *allocMsg(msgFreeList *msgFree) {
        if (msgFree == NULL) {
            return NULL ; //se la lista msgFree è vuota ritorna NULL
    }

    //Rimozione di un elemento dalla lista msgFree
    msg_t *allocatedMsg = msgFree->head ;
    msgFree->head = allocatedMsg->next ;

    //Inizializzazione dei campi del messaggio
    allocatedMsg->data = 0 ; //valore iniziale campo dati
    allocatedMsg->next = NULL ; //resetta il puntatore successivo

    return allocatedMsg ;
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
