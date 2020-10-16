/*
 * Task #2
 *
 * Azim Muradov, group #171
 */

#ifndef TASK_2_UTILS_H
#define TASK_2_UTILS_H

#include <stdio.h>

#define errprintf(...) fprintf(stderr, __VA_ARGS__)

int fprintf_array_ll(FILE *stream, long long *array, size_t array_size);

#endif // TASK_2_UTILS_H
