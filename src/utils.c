/*
 * Task #2
 *
 * Azim Muradov, group #171
 */

#include "utils.h"

void fprintf_array_ll(FILE *stream, long long *array, size_t array_size) {
    for (size_t i = 0; i < array_size; ++i) {
        fprintf(stream, "%lld ", array[i]);
    }
}
