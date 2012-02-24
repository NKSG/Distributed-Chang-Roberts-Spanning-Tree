/*
 * CommunicationProtocol.h
 *
 *  Created on: Jan 25, 2012
 *      Author: dustevil
 */

#ifndef COMMUNICATIONPROTOCOL_H_
#define COMMUNICATIONPROTOCOL_H_

#include "DCRST.h"

typedef union EventHandler_Param_ {
	struct SelectParent_Param_ *sp_param;
        struct UCastEcho_Param_ *uce_param;
} EventHandler_Param;

typedef struct SelectParent_Param_ {
        List *selectorsNonSynchorizedList; 
        Mote *selector;
        Mote **selectorsParent;
	struct Message_ *probe_message;
} SelectParent_Param;

typedef struct UCastEcho_Param_ {
        List *sendersNonSynchronizedList;
        Mote *sender;
        Mote *receiver;
} UCastEcho_Param;

typedef enum {
        NOPE,
        SP,
        CPEE,
        HS        
} RtnVal;

//#define CP_TEST_H

#ifndef CP_TEST_H

typedef void (*EventHandler)(EventHandler_Param *param);

void initCommunicationProtocol();
void eventHandlerInvocation(const MoteState STATE, const MessageType INPUT, const EventHandler_Param *arg);
int unicastProbeMessage(const List *sendersNonSynchronizedList, const Mote *sender, const Mote *receiver);
void unicastEchoMessage(EventHandler_Param *arg);

#endif

#ifdef CP_TEST_H

typedef RtnVal (*EventHandler)(EventHandler_Param *param);

void initCommunicationProtocol();
RtnVal eventHandlerInvocation(const MoteState STATE, const MessageType INPUT, const EventHandler_Param *arg);

#endif

#endif /* COMMUNICATIONPROTOCOL_H_ */
