#ifndef COMUM_BMH_H
#define COMUM_BMH_H
#pragma once

//Cores Para Impressão No Terminal
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
 * @BMH_STRUCTURE_OK: Indicate the structure is ok and can be used
 * @BMH_STRUCTURE_CORRUPTED: Indicate the structure is corrupted and can
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
 * @BMH_STATUS_ERROR_WHEN_ALLOCATE_MEMORRY: Indicate when the method has an
 * error when allocate memory
 */
enum bmh_status {
    BMH_STATUS_OK,
    BMH_STATUS_FAILED,
    BMH_STATUS_STRUCTURE_EXIST,
    BMH_STATUS_STRUCTURE_DOESNT_EXIST,
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

#endif