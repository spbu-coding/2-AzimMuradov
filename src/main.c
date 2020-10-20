/*
 * Task #2
 *
 * Azim Muradov, group #171
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"
#include "utils.h"

enum task_2_err_codes {
    TASK_2_ERR_NO_CL_ARGS = -1,
    TASK_2_ERR_TOO_MANY_CL_ARGS = -2,
    TASK_2_ERR_DUPLICATE_CL_ARGS = -3,
    TASK_2_ERR_WRONG_CL_ARGS = -4,
    TASK_2_ERR_OTHER = -5
};

enum arg_type {
    ARG_T_INVALID,
    ARG_T_FROM,
    ARG_T_TO
};

static const char *const FROM = "--from=";
static const char *const TO = "--to=";


enum arg_type get_argument_type(char *argument);

int set_parameter(long long **from, long long **to, char *argument, enum arg_type type);


int parse_and_validate_arguments(long long **from, long long **to, char **arguments, size_t arguments_number) {
    if (arguments_number < 1) return TASK_2_ERR_NO_CL_ARGS;
    if (arguments_number > 2) return TASK_2_ERR_TOO_MANY_CL_ARGS;


    char *arg0 = arguments_number >= 1 ? arguments[0] : NULL;
    char *arg1 = arguments_number >= 2 ? arguments[1] : NULL;

    enum arg_type arg0_type = get_argument_type(arg0);
    enum arg_type arg1_type = get_argument_type(arg1);

    if (arg0_type == ARG_T_INVALID && arg1_type == ARG_T_INVALID) return TASK_2_ERR_WRONG_CL_ARGS;
    if (arg0_type == arg1_type) return TASK_2_ERR_DUPLICATE_CL_ARGS;


    int return_codes_sum = 0;
    return_codes_sum += set_parameter(from, to, arg0, arg0_type);
    return_codes_sum += set_parameter(from, to, arg1, arg1_type);
    if (return_codes_sum != 0) {
        if (*from != NULL) {
            free(*from);
            *from = NULL;
        }
        if (*to != NULL) {
            free(*to);
            *to = NULL;
        }

        return TASK_2_ERR_OTHER;
    }

    return 0;
}

int scan_numbers(long long *numbers) {
    char delimiter;
    int size = 0;

    do {
        if (scanf("%lld%c", &numbers[size++], &delimiter) != 2) {
            errprintf("Cannot read from stdin\n");
            return -1;
        }
    } while (isblank(delimiter));

    return size;
}


int reduce_numbers(long long *reduced, long long *numbers, size_t numbers_size, long long *from, long long *to) {
    long long too_small[numbers_size];
    long long too_big[numbers_size];
    size_t too_small_size = 0;
    size_t reduced_size = 0;
    size_t too_big_size = 0;

    long long num;
    bool is_big_enough, is_small_enough;
    for (size_t i = 0; i < numbers_size; ++i) {
        num = numbers[i];
        is_big_enough = from == NULL || *from < num;
        is_small_enough = to == NULL || num < *to;

        if (!is_big_enough) too_small[too_small_size++] = num;
        if (!is_small_enough) too_big[too_big_size++] = num;
        if (is_big_enough && is_small_enough) reduced[reduced_size++] = num;
    }

    if (fprintf_array_ll(stdout, too_small, too_small_size) < 0) return -1;
    if (fprintf_array_ll(stderr, too_big, too_big_size) < 0) return -1;

    return reduced_size;
}

int run_app(long long *numbers, size_t numbers_size, long long *from, long long *to) {
    long long reduced[numbers_size];
    int reduced_size = reduce_numbers(reduced, numbers, numbers_size, from, to);
    if (reduced_size == -1) return TASK_2_ERR_OTHER;

    if (reduced_size == 0) return 0;

    long long sorted[reduced_size];
    memcpy(sorted, reduced, sizeof(long long) * reduced_size);

    sort(sorted, reduced_size);

    int diff_counter = 0;
    for (int i = 0; i < reduced_size; ++i) {
        if (reduced[i] != sorted[i]) diff_counter += 1;
    }

    return diff_counter;
}


int main(int argc, char *argv[]) {
    long long *from = NULL;
    long long *to = NULL;

    int return_code = parse_and_validate_arguments(&from, &to, argv + 1, argc - 1);
    if (return_code != 0) return return_code;

    long long numbers[100];
    int numbers_size = scan_numbers(numbers);
    if (numbers_size == -1) return TASK_2_ERR_OTHER;

    int app_result = run_app(numbers, numbers_size, from, to);

    if (from != NULL) free(from);
    if (to != NULL) free(to);

    return app_result;
}


enum arg_type get_argument_type(char *argument) {
    if (argument == NULL) return ARG_T_INVALID;
    if (strstr(argument, FROM) == argument) return ARG_T_FROM;
    if (strstr(argument, TO) == argument) return ARG_T_TO;
    return ARG_T_INVALID;
}

int set_parameter(long long **from, long long **to, char *argument, enum arg_type type) {
    const long long FROM_LEN = strlen(FROM);
    const long long TO_LEN = strlen(TO);

    switch (type) {
        case ARG_T_FROM:
            *from = malloc(sizeof **from);
            if (*from == NULL) {
                errprintf("Cannot allocate memory for `from` parameter\n");
                return -1;
            }
            **from = strtoll(argument + FROM_LEN, NULL, 10);
            break;
        case ARG_T_TO:
            *to = malloc(sizeof **to);
            if (*to == NULL) {
                errprintf("Cannot allocate memory for `to` parameter\n");
                return -1;
            }
            **to = strtoll(argument + TO_LEN, NULL, 10);
            break;
        case ARG_T_INVALID:
            break;
    }

    return 0;
}


