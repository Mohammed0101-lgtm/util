#include "util.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


char *get_string(const char *__restrict prompt) {
    printf(prompt);
    
    char *input = (char *)malloc(MAX_INPUT * sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return NULL;
    } 

    if (fgets(input, MAX_INPUT, stdin) != NULL) {
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        return input;
    }

    free(input);
    fprintf(stderr, "Failed to read stdin\n");
    
    return NULL;
}


int *get_array(size_t size) {
    if (size <= 0) return NULL;

    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return NULL;
    }

    for (size_t i = 0; i < size; i++) {
        scanf("%i ", &arr[i]);
    }

    return arr;
}


int min(int _count, ...) { 
    va_list arg_ptr;
    va_start(arg_ptr, _count);

    int minimum = INT_MAX;
    int next;

    for (int i = 0; i < _count; i++) {
        next = va_arg(arg_ptr, int);
        if (next <= minimum) {
            minimum = next;
        }
    }    

    return minimum; 
}


int max(int _count, ...) {  
    va_list arg_ptr;
    va_start(arg_ptr, _count);

    int maximum = INT_MIN;
    int next;

    for (int i = 0; i < _count; i++) {
        next = va_arg(arg_ptr, int);
        if (next >= maximum) {
            maximum = next;
        }
    }

    return maximum;
}


float float_min(int _count, ...) { 
    va_list arg_ptr;
    va_start(arg_ptr, _count);

    float minimum = __FLT_MAX__;
    int next;

    for (int i = 0; i < _count; i++) {
        next = va_arg(arg_ptr, float);
        if (next <= minimum) {
            minimum = next;
        }
    }    

    return minimum; 
}


float float_max(int _count, ...) { 
    va_list arg_ptr;
    va_start(arg_ptr, _count);

    float maximum = __FLT_MIN__;
    int next;

    for (int i = 0; i < _count; i++) {
        next = va_arg(arg_ptr, float);
        if (next >= maximum) {
            maximum = next;
        }
    }

    return maximum;
}


double double_min(int _count, ...) { 
    va_list arg_ptr;
    va_start(arg_ptr, _count);

    double minimum = __DBL_MAX__;
    int next;

    for (int i = 0; i < _count; i++) {
        next = va_arg(arg_ptr, double);
        if (next <= minimum) {
            minimum = next;
        }
    }

    return minimum;
}


double double_max(int _count, ...) { 
    va_list arg_ptr;
    va_start(arg_ptr, _count);

    double maximum = __DBL_MIN__;
    int next;

    for (int i = 0; i < _count; i++) {
        next = va_arg(arg_ptr, double);
        if (next >= maximum) {
            maximum = next;
        }
    }

    return maximum; 
}


unsigned long factorial(int n) {
    if (n < 0)  return 0; 
    if (n == 0) return 1;

    return n * factorial(n - 1);
}


void print_row(int *row, size_t size) {
    if (row == NULL) return;
    
    printf("[");
    if (size == 0) {
        printf("]");
        return;
    } else if (size == 1) {
        printf("%i]", row[0]);
        return;
    }

    for (size_t i = 0; i < size; i++) {
        if (i == size - 1) {
            printf("%i]", row[i]);
            return;
        }

        print("%i, ", row[i]);
    }
}


void print_matrix(int **mat, size_t size) {
    if (mat == NULL) return;
    if (size == 0)   return;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%i ", mat[i][j]);
        }

        printf("\n");
    }
}


void append_to_array(int **arr, size_t *__size, int n) {
    if (arr  == NULL || *arr == NULL || __size == NULL)   return;

    int *temp = (int *)realloc(*arr, (*__size + 1) * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return;
    } 

    *arr = temp;
    (*arr)[*__size] = n;
    (*__size)++;
}


void insert_to_array(int **arr, size_t *__size, int pos, int val) {
    if (arr == NULL || *arr == NULL || __size == NULL) return;

    int *temp = (int *)realloc(*arr, (*__size + 1) * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return;
    }

    *arr = temp;
    (*__size)++;

    for (int i = pos + 1; i < *__size; i++) {
        (*arr)[i] = (*arr)[i - 1];  
    }

    (*arr)[pos] = val;
}


void remove_from_array(int **arr, size_t *__size, int pos) {
    if (arr == NULL || *arr == NULL || __size == NULL) return;

    for (int i = pos; i < *__size - 1; i++) {
        (*arr)[i] = (*arr)[i + 1];
    }

    (*__size)--;
}


void append_to_list(struct Node *head, int val) {
    if (head == NULL) return;

    struct Node *node = (struct Node *)malloc(sizeof(struct Node *));
    if (node == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return;
    }

    node->val = val;
    node->next = NULL;

    struct Node *ptr = head;
    while (ptr) {
        ptr = ptr->next;
    }

    ptr->next = node;
}


void remove_from_list(struct Node **head, int val) {
    if (head == NULL || *head == NULL) return;

    if ((*head)->val == val) {
        struct Node *temp = *head;
        *head = (*head)->next;  
        free(temp);
        return;
    }

    struct Node *ptr = *head;
    while (ptr->next && ptr->next->val != val) {
        ptr = ptr->next;
    }
    
    if (ptr->next && ptr->next->val == val) {
        struct Node *temp = ptr->next;
        ptr->next = ptr->next->next;
        free(temp);
    }
}


int binary_search(int *arr, int val, int low, int high) {
    if (low > high) return -1;

    int mid = low + (high - low) / 2;

    if (arr[mid] == val) return mid;
    else if (arr[mid] < val) 
        return binary_search(arr, val, mid + 1, high);
    else 
        return binary_search(arr, val, low, mid - 1);
}

