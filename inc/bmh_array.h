#ifndef BMH_ARRAY
#define BMH_ARRAY

#include "bmh_commun.h"

/** 
 * define BMH_LIST_INIT_CAP - It defines the initial size of the array
*/
#define BMH_ARRAY_INIT_CAP 0

/** 
 * define BMH_ARRAY_GROWTH_FACOTR - It defines the growth factor of the array
*/
#define BMH_ARRAY_GROWTH_FACTOR 0

/**
 * struct bmh_array - An dynamic array that store one type of data
 * @array: It stores the pointer to the adress of memory and how much bytes are in
 * @status: Indicate the status of the array
 * @data_size: The size of the data that is stored in the array
 * @len: How much elements are in the arrray
 * @cap: The capacity of the array or how much data it can store
 */
struct bmh_array {
    struct bmh_data array;
    enum bmh_structures_status status;
    size_t data_size;
    u_int32_t len;
    u_int32_t cap;
};

enum bmh_status bmh_array_init(struct bmh_array **p_array, size_t data_size);
enum bmh_status bmh_array_finish(struct bmh_array **p_array, bmh_destroyer d_method);
enum bmh_status bmh_array_append(struct bmh_array **p_array, void *data);
enum bmh_status bmh_array_remove_by_index(struct bmh_array **p_array, u_int32_t index);
enum bmh_status bmh_array_remove_by_data(struct bmh_array **p_array, void *data, bmh_comparison c_method);
void *bmh_array_linear_serach(struct bmh_array *array, void *data, bmh_comparison c_method);
void *bmh_array_binary_serach(struct bmh_array *array, void *data, bmh_comparison c_method);
enum bmh_status bmh_array_sort(struct bmh_array **p_array, bmh_comparison c_method);

#endif