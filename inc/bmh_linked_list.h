#ifndef BMH_LINKED_LIST_H
#define BMH_LINKED_LIST_H

#include "bmh_commun.h"

/**
 * struct bmh_linked_list_node - The node that belongs to the linked list
 * @data: Stores an pointer and the quantity of bytes in it 
 * @next: Points to the next son of the node
 */
struct bmh_linked_list_node {
    struct bmh_data data;
    struct bmh_linked_list_node *next;
};

/**
 * struct bmh_linked_list - An linked list that can stores any type of data
 * @i_node: The initial node from the linked list
 * @f_node: The final node from the linked list
 * @len: The length/quantity of data of the linked list
 * @data_size: The size of the data of one element stored in the linked list
 * @status: The status of the linked list, indicate wheter it's ok or corrupted
 */
struct bmh_linked_list {
    struct bmh_node *i_node;
    struct bmh_node *f_node; 
    enum bmh_structures_status status;
    u_int32_t len; 
    size_t data_size;
};

#endif