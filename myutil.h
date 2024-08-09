#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct TreeNode {
    int val;

    struct TreeNode *left;
    struct TreeNode *right;
};

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
}MaxHeap;

typedef struct {
    int *data;
    size_t size;
    size_t capacity;
}MinHeap;

char *get_string(const char *__restrict prompt);

int  *get_array(size_t size);

int min(int _count, ...);

int max(int _count, ...);

float float_min(int _count, ...);

float float_max(int _count, ...);

double double_min(int _count, ...);

double double_max(int _count, ...);

unsigned long factorial(int n);

void print_array(int *arr, size_t __size);

void print_matrix(int **mat, size_t __size, size_t *column_size) ;

void append_to_array(int **arr, size_t *__size, int n);

void insert_to_array(int **arr, size_t *__size, int pos, int val);

void remove_from_array(int **arr, size_t *__size, int pos);

void append_to_list(struct ListNode *head, struct ListNode *node);

void remove_from_list(struct ListNode **head, int val);

int binary_search(int *arr, int val, int low, int high);

char *read_file(FILE *_file);

void write_to_file(const char *_filename, const char *_buf);

struct TreeNode *create_treeNode(int val);

void insert_to_BST(struct TreeNode **root, struct TreeNode *node);

void free_tree(struct TreeNode *root);

struct TreeNode *create_BST(int *arr, size_t __size);

struct TreeNode *search_BST(struct TreeNode *root, int n);

static void swap(int *x, int *y);

static void heapify_max(MaxHeap *heap, size_t index);

MaxHeap* create_max_heap(size_t capacity);

void insert_max_heap(MaxHeap *heap, int value);

int extract_max(MaxHeap *heap);

void destroy_max_heap(MaxHeap *heap);

void destroy_min_heap(MinHeap *heap);

static void heapify_min(MinHeap *heap, size_t index);

MinHeap* create_min_heap(size_t capacity);

void insert_min_heap(MinHeap *heap, int value);

int extract_min(MinHeap *heap);

void destroy_min_heap(MinHeap *heap);

#endif // UTIL_H

