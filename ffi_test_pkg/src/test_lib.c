#include <stdio.h>
#include <stdlib.h>

#include "test_lib.h"

typedef enum {
    TYPE_INT32 = 0,
    TYPE_INT64 = 1
} DataType;

#define MAX_ELEMENTS 10000000

/* Error codes (must stay in sync with README) */
#define ERR_SHAPE_SIZE         -1  /* shape_size <= 0 or an extent is <= 0 */
#define ERR_SIZE_OVERFLOW      -2  /* total number of elements would exceed MAX_ELEMENTS */
#define ERR_UNSUPPORTED_TYPE   -3  /* type is not supported */
#define ERR_NULL_BUFFER        -4  /* buffer == NULL */

/**
 * Populates `buffer` with consecutive values 0…N-1.
 *
 * @param type        0 = 32-bit ints, 1 = 64-bit ints
 * @param shape_size  Number of dimensions (must be >0)
 * @param shape       Array of `shape_size` extents (all >0)
 * @param buffer      Pre-allocated output buffer
 * @return            Number of elements written, or a negative error code
 */
int64_t dataRead(int32_t type, int32_t shape_size, int32_t* shape, void* buffer) {
    /* Validate pointers */
    if (buffer == NULL) {
        return ERR_NULL_BUFFER;
    }
    if (shape == NULL) {
        return ERR_SHAPE_SIZE;
    }

    /* Validate shape_size */
    if (shape_size <= 0) {
        return ERR_SHAPE_SIZE;
    }

    /* Calculate number of elements and validate each extent */
    int64_t num_elements = 1;
    for (int32_t i = 0; i < shape_size; i++) {
        if (shape[i] <= 0) {
            return ERR_SHAPE_SIZE;
        }
        num_elements *= shape[i];
        if (num_elements > MAX_ELEMENTS) {
            return ERR_SIZE_OVERFLOW;
        }
    }

    /* Populate buffer based on requested type */
    switch (type) {
        case TYPE_INT32: {
            int32_t* buffer_int32 = (int32_t*)buffer;
            for (int32_t i = 0; i < num_elements; i++) {
                buffer_int32[i] = i;
            }
            break;
        }
        case TYPE_INT64: {
            int64_t* buffer_int64 = (int64_t*)buffer;
            for (int64_t i = 0; i < num_elements; i++) {
                buffer_int64[i] = i;
            }
            break;
        }
        default:
            return ERR_UNSUPPORTED_TYPE;
    }

    return num_elements;
}

int main() {
    int32_t shape[] = {2, 3, 4};
    int32_t shape_size = 3;
    int32_t type = TYPE_INT32;
    int32_t buffer[24];
    int32_t num_elements = dataRead(type, shape_size, shape, buffer);
    printf("num_elements: %d\n", num_elements);
    for (int i = 0; i < 24; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
    return 0;
}