#ifndef BMH_TREE
#define BMH_TREE

#include "bmh_commun.h"

/**
 * struct bmh_tree_node - An node from the tree
 * @data: The data from the node, contains the pointer and how much bytes are in it
 * @left: The left son from the node, can be used for smaller datas for example
 * @right: The right son from the node, can be used for bigger datas for example
 * @q_children: The quantity of children that node has
 */
struct bmh_binary_tree_node {
    struct bmh_data data;
    struct bmh_binary_tree_node *left;
    struct bmh_binary_tree_node *right;
    u_int32_t q_children;
};

/**
 * struct bmh_tree - An binary tree
 * @root_node: The node that the tree start
 * @status: Inidicate the status of the tree
 * @data_size: The size of the data stored in the tree
 * @height: The max height of the tree
 * @qty_of_nodes: The quantity of the nodes that the tree has
 */
struct bmh_binary_tree {
    struct bmh_binary_tree_node *root_node;
    enum bmh_structures_status status;
    size_t data_size;
    u_int32_t height;
    u_int32_t qty_of_nodes;
};

#endif