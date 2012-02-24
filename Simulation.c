/* 
 * File:   Simulation.c
 * Author: sinansas
 *
 * Created on January 27, 2012, 8:09 AM
 */

/*
 * Simulation.c
 *
 *  Created on: Dec 26, 2011
 *      Author: dustevil
 */
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <error.h>

#include "DCRST.h"
#include "CommunicationProtocol.h"
#include "LinkedList.h"

#define STATE_COUNT 3
#define INPUT_COUNT 2
//#define DISPATCH_INTERVAL 5
//#define WAKEUP_INTERVAL 10

#define simulationDoneMessage() printf("The simulation is successfully completed.\n")

typedef struct alarm_t_ {
    int mote_id;
    pthread_t *timer_interupt;
} alarm_t;

static unsigned int vcount;
static EventHandler communicationProtocol[STATE_COUNT][INPUT_COUNT];
static pthread_t threads[MAX_MOTE_COUNT];
static unsigned int dispatchedList[MAX_MOTE_COUNT];
static unsigned int dispatchedListEnd = 0;
pthread_mutex_t queue_locks[MAX_MOTE_COUNT], printout_lock;
static unsigned int parentFoundCount = 0;

static void simulation();
static void root_dispatch();
static _Bool isNotInList(const int listEnd, const int list[], const int element);
static void thread_dispatch();
static void moteProcedure(void *rawMotePtr);
static void rootProcedure(void *rawRootPtr);

int main(int argc, char *argv[]) {
    //initilizeNetwork(argv[1]);
    initializeNetwork("tryout");
    vcount = getVCount();
    simulation();
    simulationDoneMessage();
    return 0;
}

void simulation() {
    int ctr;
    initCommunicationProtocol();

    for (ctr = 1; ctr < vcount; ctr++)
        thread_dispatch();

    root_dispatch();

    for (ctr = vcount - 1; ctr >= 0; ctr--)
        pthread_join(threads[ctr], NULL);

}

void root_dispatch() {
    getMote(0)->state = WAITING;
    pthread_create(&threads[0], NULL, rootProcedure, (void*) getMote(0));
    dispatchedList[dispatchedListEnd++] = 0;

    printf("Mote 1 is ONLINE!\n");
}

void thread_dispatch() {
    int index;
    _Bool toBreak = false;


    if (dispatchedListEnd < vcount) {
        srand(time(NULL));
        while (!toBreak) {
            index = (rand() % (vcount - 1)) + 1;
            toBreak = isNotInList(dispatchedListEnd, dispatchedList, index);
        }
        toBreak = false;

        getMote(index)->state = IDLE;
        dispatchedList[dispatchedListEnd++] = index;
        pthread_create(&threads[index], NULL, moteProcedure, (void *) getMote(index));

        printf("Mote %d is ONLINE!\n", index + 1);

        /*signal(SIGALRM, thread_dispatch);
        alarm(DISPATCH_INTERVAL);*/
    }

}

void moteProcedure(void *rawMotePtr) {
    const Mote *motePtr = (Mote *) rawMotePtr;
    Mote *parent = NULL, *receiver = NULL;
    int i;
    
    List *nonSynchorizedList = (List *) malloc(sizeof(List));
    nonSynchorizedList->size = 0;
    nonSynchorizedList->head = NULL;
    nonSynchorizedList->tail = NULL;
    
    Message *message = NULL;
    
    SelectParent_Param *sp_param = (SelectParent_Param *) malloc(sizeof(SelectParent_Param));
    sp_param->selectorsNonSynchorizedList = nonSynchorizedList;
    sp_param->selector = motePtr;
    sp_param->selectorsParent = &parent;
    sp_param->probe_message = NULL;
    
    EventHandler_Param *arg = (EventHandler_Param *) malloc(sizeof(EventHandler_Param)); 
    arg->sp_param = sp_param;
    
    // nonSynchronizedList initialization
    for (i = 0; i < motePtr->coveredMoteCount; i++)
        list_insert(nonSynchorizedList, motePtr->coverageArea[i]);

    while (motePtr->state == IDLE) {
        if (queue_size(motePtr->message_queue) > 0) {
            pthread_mutex_lock(&queue_locks[motePtr->ID]);
            queue_remove_first(motePtr->message_queue, &message);
            pthread_mutex_unlock(&queue_locks[motePtr->ID]);
            sp_param->probe_message = message;
            eventHandlerInvocation(motePtr->state, message->mtype, arg);
        }
    }

    UCastEcho_Param *uce_param = (UCastEcho_Param *) malloc(sizeof(UCastEcho_Param));
    uce_param->sendersNonSynchronizedList = nonSynchorizedList;
    uce_param->sender = motePtr;
    uce_param->receiver = NULL;
    
    arg->uce_param = uce_param;

    while (list_size(nonSynchorizedList) > 0) {
        while (queue_size(motePtr->message_queue) > 0) {
            pthread_mutex_lock(&queue_locks[motePtr->ID]);
            queue_remove_first(motePtr->message_queue, &message);
            pthread_mutex_unlock(&queue_locks[motePtr->ID]);
            uce_param->receiver = message->sender;
            eventHandlerInvocation(motePtr->state, message->mtype, arg);
        }

        if (list_size(nonSynchorizedList) > 0) {
            list_rem_elmt(nonSynchorizedList, NULL, &receiver);
            unicastProbeMessage(NULL, motePtr, receiver);
        }
    }

    uce_param->sendersNonSynchronizedList = NULL;
    uce_param->sender = motePtr;
    uce_param->receiver = parent;
    arg->uce_param = uce_param;

    unicastEchoMessage(arg);

    pthread_mutex_lock(&printout_lock);
    printf("The parent of mote %d is mote %d\n", motePtr->ID + 1, parent->ID + 1);
    pthread_mutex_unlock(&printout_lock);
}

void rootProcedure(void *rawRootPtr) {
    const Mote *rootPtr = (Mote *) rawRootPtr;
    int i;

    for (i = 0; i < rootPtr->coveredMoteCount; i++)
        unicastProbeMessage(NULL, rootPtr, rootPtr->coverageArea[i]);

}

_Bool isNotInList(const int listEnd, const int list[], const int element) {
    int i;

    for (i = 0; i < listEnd; i++) {
        if (list[i] == element)
            return false;
    }

    return true;
}