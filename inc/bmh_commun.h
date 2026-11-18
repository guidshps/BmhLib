#ifndef COMUM_BMH_H
#define COMUM_BMH_H
#pragma once

#define BMH_RED "\033[31m"
#define BMH_GREEN "\033[32m"
#define BMH_YELLOW "\033[33m"
#define BMH_BLUE "\033[34m"
#define BMH_MAGENTA "\033[35m"
#define BMH_CIAN "\033[36m"
#define BMH_WHITE "\033[37m"
#define BMH_RESET "\033[0m"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#ifdef BMH_DEBUG
    #define bmh_log_sucess(msg) \
        fprintf(stderr, BMH_BLUE "[BMH DEBUG] " "%s" BMH_RESET "\n", msg)
    #define bmh_log_error(msg) \
        fprintf(stderr, BMH_RED "[BMH DEBUG] " "%s" BMH_RESET "\n", msg)
    #define bmh_log_warn(msg) \
        fprintf(stderr, BMH_YELLOW "[BMH DEBUG: WARN] " "%s" BMH_RESET "\n", msg)
#else
    #define bmh_log_sucess(msg) ((void)0)
    #define bmh_log_error(msg) ((void)0)
    #define bmh_log_warn(msg) ((void)0)
#endif

#define bmh_calloc calloc ////Nickname for the function calloc
#define bmh_malloc malloc //Nickname for the function malloc
#define bmh_realloc realloc //Nickname for the function realloc
#define bmh_free free //Nickname for the function free

/**
 * enum bmh_structures_status - Status from the data structures
 * @BMH_STRUCTURE_OK: Indicate if the structure is ok and can be used
 * @BMH_STRUCTURE_CORRUPTED: Indicate if the structure is corrupted and can
 * not be used
 * @BMH_STRUCTURE_NOT_STARTED: Indicate that structure has not started yet.
 */
enum bmh_structures_status {
    BMH_STRUCTURE_OK,
    BMH_STRUCTURE_CORRUPTED,
    BMH_STRUCTURE_NOT_STARTED,
};

/**
 * enum bmh_status - Status returned by the methods of the structures
 * @BMH_STATUS_OK: Indicate that method were done sucefully
 * @BMH_STATUS_FAILED: Indicate that methor were not done sucefully
 * @BMH_STRUCTURES_EXIST: Indicate that the method  has find an structure 
 * that exist
 * @BMH_STATUS_STRUCTURE_DOESNT_EXIST: Indicate that method has find an 
 * structure that does not exist 
 * BMH_STATUS_PARAMETER_IS_INVALID: Indicate that parameter is invalid
 * @BMH_STATUS_ERROR_WHEN_ALLOCATE_MEMORRY: Indicate when the method has an
 * error when allocate memory
 */
enum bmh_status {
    BMH_STATUS_OK,
    BMH_STATUS_FAILED,
    BMH_STATUS_STRUCTURE_EXIST,
    BMH_STATUS_STRUCTURE_DOESNT_EXIST,
    BMH_STATUS_PARAMETER_IS_INVALID,
    BMH_STATUS_ERROR_WHEN_ALLOCATE_MEMORRY,
};

/**
 * struct bmh_data - Store an adress and the quantity of bytes in it
 * @ptr: Pointer that store the adress from the data stored
 * @size: The quantity of the data stored in the adress stored in pointer
 */
struct bmh_data {
    void *ptr;
    size_t size;
};

/**
 * typedef bmh_comparison - Function that compares two datas
 * 
 * It compares the first data in relation to the second dat If the first data
 * is bigger than the second, the result will be bigger than zero and if the
 * second data is bigger than the first data the result will be smaller than zero
 */
typedef int(bmh_comparison)(void *, void *);

/**
 * typedef bmh_destroyer - Function that clean the data of an pointer
 * 
 * It destroy a pointer from an specific data type, used for generalize any
 * function that to clean some data that are not used
 */
typedef enum bmh_status(bmh_destroyer)(void *);

/**
 * typedef bmh_byte - Represents an single byte
 */
typedef unsigned char bmh_byte;

enum bmh_status create_bmh_data(struct bmh_data *dest, void *src, size_t d_size);
enum bmh_status destroy_bmh_data(struct bmh_data *dest, bmh_destroyer data_destroyer);

#endif