/*
 * Task #2
 *
 * Azim Muradov, group #171
 */

#include "utils.h"

int fprintf_array_ll(FILE *stream, long long *array, size_t array_size) {
    if (array_size > 0) {
        if (fprintf(stream, "%lld", array[0]) < 0) return -1;
    }
    for (size_t i = 1; i < array_size; ++i) {
        if (fprintf(stream, " %lld", array[i]) < 0) return -1;
    }
    if (array_size > 0) {
        if (fprintf(stream, "\n") < 0) return -1;
    }

    return 0;
}
