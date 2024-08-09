#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
};

char *get_string(const char *__restrict prompt);

int  *get_array(size_t size);

int min(int _count, ...);

int max(int _count, ...);

float float_min(int _count, ...);

float float_max(int _count, ...);

double double_min(int _count, ...);

double double_max(int _count, ...);

unsigned long factorial(int n);

void print_row(int *row, size_t size);

void print_matrix(int **mat, size_t size) ;

void append_to_array(int **arr, size_t *__size, int n);

void insert_to_array(int **arr, size_t *__size, int pos, int val);

void remove_from_array(int **arr, size_t *__size, int pos);

void append_to_list(struct Node *head, int val);

void remove_from_list(struct Node **head, int val);

int binary_search(int *arr, int val, int low, int high);


#endif // UTIL_H

