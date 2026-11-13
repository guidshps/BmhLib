#ifndef BMH_NODE_H
#define BMH_NODE_H

#include "bmh_commun.h"

/**
* struct bmh_node - Generic node that can have arbitrary number of sons
* @bmh_data: Struct that stores an pointer and the quantity of bytes in it
* @next: Pointer to the children of the node 
* @status: The status of the node, indicate wheter it's ok or corrupted
* @qty_of_sons: Number of children the node has
*/
struct bmh_node {
    struct bmh_data data;
    struct bmh_node **next; 
    enum bmh_structures_status status;
    size_t qty_of_sons;
};

#endif