/*
 * File:   TestCommunicationProtocol.c
 * Author: sinansas
 *
 * Created on Jan 28, 2012, 4:35:47 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "CommunicationProtocol.h"
#include "DCRST.h"

/*
 * CUnit Test Suite
 */

int init_suite(void) {
    initializeNetwork("tryout");
    initCommunicationProtocol();
    return 0;
}

int clean_suite(void) {
    return 0;
}

void testEventHandlerInvocation() {
    Mote *selectedParent = NULL, *receiver = NULL;
    List nonSynchronizedList_Mote1 = {NULL, 0, NULL};
    Message *message = NULL;

    if (list_insert(&nonSynchronizedList_Mote1, getMote(0)))
        fprintf(stderr, "An error occurred as initializing the nonSynchronizedList_Mote1");
    if (list_insert(&nonSynchronizedList_Mote1, getMote(2)))
        fprintf(stderr, "An error occurred as initializing the nonSynchronizedList_Mote1");
    if (list_insert(&nonSynchronizedList_Mote1, getMote(7)))
        fprintf(stderr, "An error occurred as initializing the nonSynchronizedList_Mote1");
    
    unicastProbeMessage(NULL, getMote(0), getMote(1));
    queue_remove_first(getMote(1)->message_queue, &message);
    
    SelectParent_Param sp_param = {&nonSynchronizedList_Mote1, getMote(1), &selectedParent, message};
    EventHandler_Param arg = {NULL, NULL};
    
    arg.sp_param = &sp_param;
    eventHandlerInvocation(IDLE, PROBE, &arg);
     
    CU_ASSERT_EQUAL(0, selectedParent->ID);
    CU_ASSERT_EQUAL(WAITING, getMote(1)->state);
    
    unicastProbeMessage(&nonSynchronizedList_Mote1, getMote(1), getMote(2));
    
    queue_remove_first(getMote(2)->message_queue, &message);
    
    UCastEcho_Param uce_param = { NULL, getMote(2), getMote(1) };
    arg.uce_param = &uce_param;
    
    eventHandlerInvocation(WAITING, PROBE, &arg);
   
    queue_remove_first(getMote(1)->message_queue, &message);
    
    arg.sp_param = NULL;
    arg.uce_param = NULL;
    
    eventHandlerInvocation(WAITING, ECHO, &arg);
    
    if (nonSynchronizedList_Mote1.head->data->ID != 7)
        CU_ASSERT(0);
    if (nonSynchronizedList_Mote1.head->data->ID == 7)
        CU_ASSERT(1);
    CU_ASSERT_EQUAL(2, message->sender->ID);
    CU_ASSERT_EQUAL(ECHO, message->mtype);
    
    free(message);
  
    unicastProbeMessage(NULL, getMote(7), getMote(1));
    
    uce_param.sendersNonSynchronizedList = &nonSynchronizedList_Mote1;
    uce_param.sender = getMote(1);
    uce_param.receiver = getMote(7);
    arg.uce_param = &uce_param;
    eventHandlerInvocation(WAITING, PROBE, &arg);
    CU_ASSERT_EQUAL(0, list_size(&nonSynchronizedList_Mote1));
   
    queue_remove_first(getMote(7)->message_queue, &message);
    
    CU_ASSERT_EQUAL(1, message->sender->ID);
    CU_ASSERT_EQUAL(ECHO, message->mtype);
}

int main() {
    CU_pSuite pSuite = NULL;

    /* Initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* Add a suite to the registry */
    pSuite = CU_add_suite("TestCommunicationProtocol", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "testEventHandlerInvocation", testEventHandlerInvocation))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
