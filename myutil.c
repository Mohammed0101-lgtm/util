//
// Implementation of the myutil library functions
//

#include "myutil.h"

#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


// get input string from stdin via a prompt
char *get_string(const char *__restrict prompt) {
    printf(prompt);
    
    // allocate memory for input, REMEMBER to free it later
    char *input = (char *)malloc(MAX_INPUT * sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return NULL;
    } 

    // MAX_INPUT expands to 1024 character , this is a relatively
    // large amount of storage for most use cases, including '\0' 
    if (fgets(input, MAX_INPUT, stdin) != NULL) {
        // strip newline character
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        return input;
    }

    // if reading input failed 
    free(input);
    fprintf(stderr, "Failed to read stdin\n");
    
    return NULL;
}

// get array data from stdin
int *get_array(size_t size) {
    if (size <= 0) return NULL;

    // allocate memory for the array
    int *arr = (int *)malloc(size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return NULL;
    }

    // scan each element on a seperate line
    for (size_t i = 0; i < size; i++) {
        scanf("%i", &arr[i]);
    }

    return arr;
}

// get the minimum element from 
// any given list of numbers
int min(int _count, ...) { 
    // get the list of arguments provided
    va_list arg_ptr;
    va_start(arg_ptr, _count);

    // set the minimum to the highest value
    // possible for comparison
    int minimum = INT_MAX;
    int next; // store the next argument in the list

    for (int i = 0; i < _count; i++) {
        next = va_arg(arg_ptr, int);
        // update the minimum if a new min is found
        if (next <= minimum) {
            minimum = next;
        }
    }    

    return minimum; 
}

// same logic for min() but reversed to get the maximum
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

// get minimum floating number from a list of floats
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

// get maximum floating number from list of floats
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


// get minimum double
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

// get maximum double
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

// get the factorial of a number
// example : 
// factorial(3) = 3! 
//              = 3 x 2 x 1 = 6
unsigned long factorial(int n) {
    if (n < 0) return 0; 
    if (n == 0) return 1;

    return n * factorial(n - 1); // multiply n with n - 1 recursively
}


// this prints an array in a more oranized way to stdout
// example : 1 2 3 -> [1, 2, 3]
void print_array(int *arr, size_t __size) {
    // please don't provide a ghost array
    if (arr == NULL) return;
    
    printf("["); // open bracket
    if (__size == 0) {
        // if size of array is 0 then print : []
        printf("]"); 
        return; 
    } else if (__size == 1) {
        // if size of array is 1 then print : [arr[0]]
        printf("%i]", arr[0]);
        return;
    }

    // if array has more than one element than print 
    // each element followed with comma like : [1, 2, 3]
    for (size_t i = 0; i < __size; i++) {
        if (i == __size - 1) {
            // if at the last element then print the 
            // element followed by a closing bracket
            printf("%i]", arr[i]);
            return;
        }

        // print an element followed by a comma
        print("%i, ", arr[i]);
    }
}

// print a matrix aka 2D array
// let's just print each row as an array 
void print_matrix(int **mat, size_t __size, size_t *column_size) {
    // please do not provide a ghost matrix
    if (mat == NULL) return;
    if (__size <= 0) return;

    for (int i = 0; i < __size; i++) {
        print_array(mat[i], column_size[i]);
        printf("\n");
    }
}

// add a new element at the last position in the array
void append_to_array(int **arr, size_t *__size, int n) {
    // please do not provide a ghost element
    if (arr  == NULL || *arr == NULL || __size == NULL) return;

    // reallocate memory for the array to account for our new guest
    // assign the reallocation to a temp so we don't destroy the original
    // array in case the reallocation fails, hopefuly you don't have less
    // than one byte of available memory left :)
    int *temp = (int *)realloc(*arr, (*__size + 1) * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return;
    } 

    *arr = temp; // realloc success so we reassing 'arr'
    (*arr)[*__size] = n; // append the element 
    (*__size)++; // increment the original size
}

// insert a new element at any given index within the array
void insert_to_array(int **arr, size_t *__size, int pos, int val) {
    if (arr == NULL || *arr == NULL || __size == NULL) return;
    // the given position should be within the array boundaries
    if (pos < 0 || pos > *__size) return;
    // if the position is at the very end the append the element
    if (pos == *__size) {
        append_to_array(arr, __size, val);
    }

    // reallocate memory for the array to account for the new element
    int *temp = (int *)realloc(*arr, (*__size + 1) * sizeof(int));
    if (temp == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return;
    }

    *arr = temp;
    (*__size)++; // increment size

    // start from the position and shift all 
    // the following elements  to the next 
    // index to make room for our guest
    for (int i = pos + 1; i < *__size; i++) {
        (*arr)[i] = (*arr)[i - 1];  
    }

    (*arr)[pos] = val; // voila
}


// remove an element from the array given its pos
// I was tempted to make another one that removes the 
// element based on it's value , but that would cause 
// problems with duplicate elements so you 
// don't know wich one you should remove
void remove_from_array(int **arr, size_t *__size, int pos) {
    if (arr == NULL || *arr == NULL || __size == NULL) return;

    // overwrite the element by shifting all the
    // next elements to their previous position 
    for (int i = pos; i < *__size - 1; i++) {
        (*arr)[i] = (*arr)[i + 1];
    }

    (*__size)--; // decrement the size
}


// create a node of a singly linked list 
// given the value it should hold
struct ListNode *create_listNode(int val) {
    // allocate memory for a new node
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (node == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return NULL;
    }

    node->val = val; // set the val
    // remain agnostic to 
    // the next element
    node->next = NULL; 

    return node; 
}

// free a singly linked list
void freeList(struct ListNode *head) {
    // if head is null then there is nothing to free
    if (head == NULL) return;

    // this pointer acts as a walker 
    // that points to the current 
    // position in the list
    struct ListNode *ptr = head;
   
    // while the pointer is not NULL 
    while (ptr) {
        // save the current position before 
        // updating ptr so to not 'orphin' 
        // the current index
        struct ListNode *temp = ptr;
        // go to the next position
        ptr = ptr->next; 
        // free temp (previous of ptr)
        free(temp); 
    }
    
    // free the head and 
    // wash your hands
    free(head);
}


// convert an array to a singly linked list
struct ListNode *create_list(int *arr, size_t __size) {
    // typical checking
    if (arr == NULL || __size == 0) return NULL;

    // head of list
    struct ListNode *list = NULL; 

    // for each element in 'arr'
    for (int i = 0; i < __size;i++) {
        // make a new node
        struct ListNode *node = create_listNode(arr[i]);
        // if node creation failed then free 
        // memory allocated thus far and return 
        if (node == NULL) {
            freeList(list);
            return NULL;
        }

        // append new node to the end of list
        append_to_list(list, node);
    }
    
    // return head of list
    return list; 
}

// append the given node at the end of the list
void append_to_list(struct ListNode *head, struct ListNode *node) {
    // no valid node ?! seriously 
    if (node == NULL) return;
    
    // if the list is empty (we 
    // assume so if head points 
    // to NULL) then push node 
    // to top of list and return
    if (head == NULL) {
        head = node;
        return;
    }

    // walk to the end
    struct ListNode *ptr = head;
    while (ptr) {
        ptr = ptr->next;
    }

    // link the new node
    ptr->next = node; 
}

// remove an entry based on it's value
// duplicates are not accounted for
void remove_from_list(struct ListNode **head, int val) {
    // check for validity
    if (head == NULL || *head == NULL) return;

    // if it is the head that we shall remove
    if ((*head)->val == val) {
        // keep track of head temporarily
        struct ListNode *temp = *head;
        // unlink head
        *head = (*head)->next;  
        // free memory assigned to head
        free(temp); 
        return;
    }

    // walk till you find a node 
    // that has the target value
    struct ListNode *ptr = *head;
    while (ptr->next && ptr->next->val != val) {
        ptr = ptr->next;
    }
    
    // unlink node with similar logic to head
    if (ptr->next && ptr->next->val == val) {
        struct ListNode *temp = ptr->next;
        ptr->next = ptr->next->next;
        free(temp);
    }
}


// basic binary search
// so you don't have to keep typing it all over every time
int binary_search(int *arr, int val, int low, int high) {
    if (low > high) return -1;

    int mid = low + (high - low) / 2;

    if (arr[mid] == val) return mid;
    else if (arr[mid] < val) 
        return binary_search(arr, val, mid + 1, high);
    else 
        return binary_search(arr, val, low, mid - 1);
}

// get the content of a text file 
char *read_file(FILE *_file) {
    // the file should be already open 
    if (_file == NULL) return NULL;

    // seek the end of the file to get it's size later
    if (fseek(_file, 0, SEEK_END) != 0) return NULL;

    // get the size of file 
    long f_size = ftell(_file);
    
    // ftell returns -1L when failed
    if (f_size == -1L) return NULL;
    
    // reset to the beginning of the file
    if (fseek(_file, 0, SEEK_SET) != 0) return NULL;
    if (f_size < 0) return NULL;

    // allocate memory for buffer, it is 
    // your resposability to free it later
    char *buf = (char *)malloc((f_size + 1) * sizeof(char));
    if (buf == NULL) {
        fprintf(stderr, "Malloc failed\n");
        return NULL;
    }

    // this reads the file to buffer, and 
    // returns the file size when success
    size_t read_size = fread(buf, sizeof(char), (size_t)f_size, _file);
    // if fread failed 
    if (read_size != (size_t)f_size) {
        // free memory preamptively 
        free(buf);
        // check failure reason 
        // useful when debugging
        if (feof(_file)) {
            fprintf(stderr, "Unexpected end of file\n");
        } else if (ferror(_file)) {
            fprintf(stderr, "fread failed\n");
        }

        return NULL;
    }

    buf[f_size] = '\0'; // nul terminate
    return buf;
}

// write text to file given the file path
void write_to_file(const char *_filename, const char* _buf) {
    // check for NULL
    if (_buf == NULL || _filename == NULL) return;

    // open file in appending mode 
    // so not to overwite current data
    FILE *fp = fopen(_filename, "a");
    if (fp == NULL)  return;

    fprintf(fp, "%s", _buf); // write
    fclose(fp); // close
}


// create a new tree node, your typical 'new' in c++
struct TreeNode *create_treeNode(int val) {
    // allocate memory for new node
    struct TreeNode *node = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Malloc failed");
        return NULL;
    }

    // initialize node
    node->val = val;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// insert a node to a binary search tree
void insert_to_BST(struct TreeNode **root, struct TreeNode *node) {
    // we assume the tree is empty and 
    // not that the caller just messed up
    if (*root == NULL) {
        // let the node be the root and return
        *root = node;
        return;
    }

    // recursion breaking condition
    if ((*root)->val == node->val) return; 

    // recursively look for the right place to 
    // insert, I assume you know how a BST work
    if ((*root)->val < node->val) {
        insert_to_BST(&(*root)->right, node);
    } else {
        insert_to_BST(&(*root)->left, node);
    }
}


// free the tree struct
void free_tree(struct TreeNode *root) {
    if (root == NULL) return;

    free_BST(root->right);
    free_BST(root->left);

    free(root);    
}

// convert an array to abinary search tree 
struct TreeNode *create_BST(int *arr, size_t __size) {
    if (arr == NULL || __size == 0) return NULL;

    // create the root node with the first val
    struct TreeNode *root = create_treeNode(arr[0]);
    if (root == NULL) return NULL;

    // create a node for each element in 
    // the array and insert it in the tree
    for (int i = 1; i < __size; i++) {
        struct TreeNode *node = create_treeNode(arr[i]);
        if (node == NULL) {
            free_tree(root);
            return NULL;
        }

        insert_to_BST(&root, node);
    }

    return root;
}

// search a binary search tree
// useful for performance cases
struct TreeNode *search_BST(struct TreeNode *root, int n) {
    // if the root is empty return null
    if (root == NULL) return NULL;

    // breaking case for recursion
    if (root->val == n) return root;

    // go right or left based 
    // on value comparison
    else if (root->val < n) 
        return search_BST(root->right, n);
    else 
        return search_BST(root->left, n);
}

// swap two elements in an array
static void swap(int *x, int *y) {
    int temp = *x; 
    *x = *y;
    *y = temp;
}

// make a maximum heap that prioritises the maximum elements 
static void heapify_max(MaxHeap *heap, size_t index) {
    size_t largest = index;

    size_t left  = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left  < heap->size && heap->data[left]  > heap->data[largest]) { largest = left;  }
    if (right < heap->size && heap->data[right] > heap->data[largest]) { largest = right; }
    
    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapify(heap, largest);
    }
}

MaxHeap* create_max_heap(size_t capacity) {
    MaxHeap *heap = malloc(sizeof(MaxHeap));
    heap->data = malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insert_max_heap(MaxHeap *heap, int value) {
    if (heap->size >= heap->capacity) {
        fprintf(stderr, "Heap is full\n");
        return;
    }
    size_t index = heap->size++;
    heap->data[index] = value;

    while (index != 0 && heap->data[(index - 1) / 2] < heap->data[index]) {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int extract_max(MaxHeap *heap) {
    if (heap->size <= 0) return -1; 
    if (heap->size == 1) return heap->data[--heap->size];

    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify(heap, 0);

    return root;
}

void destroy_max_heap(MaxHeap *heap) {
    free(heap->data);
    free(heap);
}


static void heapify_min(MinHeap *heap, size_t index) {
    size_t smallest = index;
    size_t left = 2 * index + 1;
    size_t right = 2 * index + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        heapify(heap, smallest);
    }
}

MinHeap* create_min_heap(size_t capacity) {
    MinHeap *heap = malloc(sizeof(MinHeap));
    heap->data = malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void insert_min_heap(MinHeap *heap, int value) {
    if (heap->size >= heap->capacity) {
        fprintf(stderr, "Heap is full\n");
        return;
    }
    size_t index = heap->size++;
    heap->data[index] = value;

    while (index != 0 && heap->data[(index - 1) / 2] > heap->data[index]) {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

int extract_min(MinHeap *heap) {
    if (heap->size <= 0) return -1; 
    if (heap->size == 1) return heap->data[--heap->size];

    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapify(heap, 0);

    return root;
}

void destroy_min_heap(MinHeap *heap) {
    free(heap->data);
    free(heap);
}


