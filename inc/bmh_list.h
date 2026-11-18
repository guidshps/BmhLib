#ifndef BMH_LIST_H
#define BMH_LIST_H

#include "bmh_commun.h"

/** 
 * define BMH_LIST_INIT_CAP - It defines the initial size of the list
*/
#define BMH_LIST_INIT_CAP 0
/** 
 * define BMH_LIST_GROWTH_FACOTR - It defines the growth factor of the list
*/
#define BMH_LIST_GROWTH_FACTOR 0

/** struct bmh_list - An dynamic list that can store any type of data
 * @list: An array that stores all the pointers that have an data
 * @status: Indicate the status of the list
 * @len: The quantity of data stored
 * @cap: The capacity of the list (How much data can store in it)
 */
struct bmh_list {
    struct bmh_data *list;
    enum bmh_structures_status status;
    u_int32_t len;
    u_int32_t cap;
};

#endif