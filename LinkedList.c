/*
 * LinkedList.c
 *
 *  Created on: Jan 25, 2012
 *      Author: dustevil
 */

/*****************************************************************************
 *                                                                            *
 *  -------------------------------- list.c --------------------------------  *
 *                                                                            *
 *****************************************************************************/
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

/*****************************************************************************
 *                                                                            *
 *  ------------------------------- list_init ------------------------------  *
 *                                                                            *
 *****************************************************************************/
void list_init(struct List_ *list) {
    /*****************************************************************************
     *                                                                            *
     *  Initialize the list.                                                      *
     *                                                                            *
     *****************************************************************************/
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- list_ins_next ----------------------------  *
 *                                                                            *
 *****************************************************************************/
_Bool list_insert(List *list, const struct Mote_ *data) {
    ListElmt *new_element;

    /*****************************************************************************
     *                                                                            *
     *  Allocate storage for the element.                                         *
     *                                                                            *
     *****************************************************************************/
    if ((new_element = (ListElmt *) malloc(sizeof (ListElmt))) == NULL
            )
        return -1;
    new_element->data = data;
    /*****************************************************************************
     *                                                                            *
     *  Insert the element into the tail of the list.                                         *
     *                                                                            *
     *****************************************************************************/
    new_element->next = NULL;
    if (list->size == 0) {
        list->head = new_element;
        list->tail = new_element;
    } else {
        list->tail->next = new_element;
        list->tail = new_element;
    }

    /*****************************************************************************
     *                                                                            *
     *  Adjust the size of the list to account for the inserted element.          *
     *                                                                            *
     *****************************************************************************/
    list->size++;
    return 0;
}

/*****************************************************************************
 *                                                                            *
 *  ----------------------------- list_rem_elmt ----------------------------  *
 *                                                                            *
 *****************************************************************************/

int list_rem_elmt(List *list, Mote *element, Mote **data) {

    ListElmt *previous = NULL, *current = NULL;

    /*****************************************************************************
     *                                                                            *
     *  Do not allow removal from an empty list.                                  *
     *                                                                            *
     *****************************************************************************/

    if (list_size(list) == 0)
        return -1;

    /*****************************************************************************
     *                                                                            *
     *  Remove the element from the list.                                         *
     *                                                                            *
     *****************************************************************************/

    if (element == NULL) {
        current = list_head(list);

        if (current->next == NULL)
            list->tail = NULL;

        list->head = current->next;
        *data = current->data;
    } else {
        current = list_head(list);

        /**************************************************************************
         *                                                                         *
         *  Handle removal from the head                                                   *
         *                                                                         *
         **************************************************************************/

        if (current->data == element) {
            if (current->next == NULL)
                list->tail = previous;

            list->head = current->next;
        } else { // Handle removal from somewhere else        
            while (current != NULL && current->data != element) {
                previous = current;
                current = current->next;
            }
            if (current != NULL) {
                if (current->next == NULL)
                    list->tail = previous;

                previous->next = current->next;
            }
        }
    }

    /*****************************************************************************
     *                                                                            *
     *  Free the storage allocated by the abstract datatype.                      *
     *                                                                            *
     *****************************************************************************/
    if(current != NULL)
        free(current);

    /*****************************************************************************
     *                                                                            *
     *  Adjust the size of the list to account for the removed element.           *
     *                                                                            *
     *****************************************************************************/

    list->size--;

    return 0;

}