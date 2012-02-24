/*
 * CommunicationProtocol.c
 *
 *  Created on: Jan 25, 2012
 *      Author: dustevil
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "CommunicationProtocol.h"
#include "LinkedList.h"
#include "Queue.h"

#define STATE_COUNT 3
#define INPUT_COUNT 2

EventHandler communicationProtocolTable[STATE_COUNT][INPUT_COUNT];
extern pthread_mutex_t queue_locks[MAX_MOTE_COUNT];

//#define CP_TEST

#ifndef CP_TEST

static void nope(EventHandler_Param *arg);
static void selectParent(EventHandler_Param *arg);
static void communicationProtocolErrorException(EventHandler_Param *arg); 

void initCommunicationProtocol() {
    communicationProtocolTable[OFF][PROBE] = nope;
    communicationProtocolTable[OFF][ECHO] = nope;
    communicationProtocolTable[IDLE][PROBE] = selectParent;
    communicationProtocolTable[IDLE][ECHO] = communicationProtocolErrorException;
    communicationProtocolTable[WAITING][PROBE] = unicastEchoMessage;
    communicationProtocolTable[WAITING][ECHO] = nope;
}

void eventHandlerInvocation(const MoteState STATE, const MessageType INPUT, const EventHandler_Param *arg) {
    communicationProtocolTable[STATE][INPUT](arg);
}

void nope(EventHandler_Param *arg) {
    return;
}

void selectParent(EventHandler_Param *arg) {
    SelectParent_Param *sp_param = (SelectParent_Param *) arg->sp_param;
    *(sp_param->selectorsParent) = sp_param->probe_message->sender;
    sp_param->selector->state = WAITING;
    
    list_rem_elmt(sp_param->selectorsNonSynchorizedList, sp_param->probe_message->sender, NULL);
}

void communicationProtocolErrorException(EventHandler_Param *arg) {
    fprintf(stderr, "Warning: Error in communication!\n");
    exit(-1);
}
//TODO Protokolde hata var nonSynchronizedList i nerede modifiye edecegini ayarla
int unicastProbeMessage(const List *sendersNonSynchronizedList, const Mote *sender, const Mote *receiver) {
    Message *probe_message = (Message *)malloc(sizeof(Message));
    
    probe_message->mtype = PROBE;
    probe_message->sender = sender;
    
    pthread_mutex_lock(&queue_locks[receiver->ID]);
    if (queue_insert(receiver->message_queue, probe_message) < 0) {
        fprintf("An error occurred as inserting a probe message from mote %d to the message queue of mote %d!\n", sender->ID, receiver->ID);
        return -1;
    }
    pthread_mutex_unlock(&queue_locks[receiver->ID]);
 
    if(sendersNonSynchronizedList != NULL)
        list_rem_elmt(sendersNonSynchronizedList, receiver, NULL);
    return 0;
}

void unicastEchoMessage(EventHandler_Param *arg) {
    UCastEcho_Param *uce_param = (UCastEcho_Param *) arg->uce_param;
    Message *echo_message = (Message *)malloc(sizeof(Message));
    
    echo_message->mtype = ECHO;
    echo_message->sender = uce_param->sender;
    pthread_mutex_lock(&queue_locks[uce_param->receiver->ID]);
    if (queue_insert(uce_param->receiver->message_queue, echo_message) < 0)
        fprintf(stderr, "An error occurred as inserting a echo message from mote %d to the message queue of mote %d!\n", uce_param->sender->ID, uce_param->receiver->ID);
    pthread_mutex_unlock(&queue_locks[uce_param->receiver->ID]);
    
    if(uce_param->sendersNonSynchronizedList != NULL)
        list_rem_elmt(uce_param->sendersNonSynchronizedList, uce_param->receiver, NULL);
}

#endif

#ifdef CP_TEST

static RtnVal nope(EventHandler_Param *arg);
static RtnVal selectParent(EventHandler_Param *arg);
static RtnVal communicationProtocolErrorException(EventHandler_Param *arg);
static RtnVal handshaking(EventHandler_Param *arg);

void initCommunicationProtocol() {
    communicationProtocolTable[OFF][PROBE] = nope;
    communicationProtocolTable[OFF][ECHO] = nope;
    communicationProtocolTable[IDLE][PROBE] = selectParent;
    communicationProtocolTable[IDLE][ECHO] = communicationProtocolErrorException;
    communicationProtocolTable[WAITING][PROBE] = handshaking;
    communicationProtocolTable[WAITING][ECHO] = handshaking;
}

RtnVal eventHandlerInvocation(const MoteState STATE, const MessageType INPUT, const EventHandler_Param *arg) {
    return communicationProtocolTable[STATE][INPUT](arg);
}

RtnVal nope(EventHandler_Param *arg) {
    return NOPE;
}

RtnVal selectParent(EventHandler_Param *arg) {
    return SP;
}

RtnVal communicationProtocolErrorException(EventHandler_Param *arg) {
    return CPEE;
}

RtnVal handshaking(EventHandler_Param *arg) {
    return HS;
}

#endif