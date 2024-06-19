#include <stdlib.h>

#define NULL_LEVEL      4
#define ERROR_LEVEL     0
#define WARNING_LEVEL   1
#define INFO_LEVEL      2
#define DEBUG_LEVEL     3

typedef struct list_element{
    void *line;
    size_t array_len;
    struct list_element *next_element;
} list_element;

enum numbers{
    null = 0,
    one  = 1,
    four = 4,
    eight= 8
};

list_element* create_empty_list();
int clear_list(list_element* elements);
/*
 *  Function append returns a pointer at the last element of the array
 *  obtaines:
 *      a pointer to the array,
 *      pointer to the data,
 *      size of data in bytes.
 */
list_element *get_last(list_element *elements);

/*
 *  Push to begining of the list
 *  Obtaines:
 *      pointer to begining of the list
 *      data pointer
 *      size of data
 * */
int append_list(list_element** elements, void* data, size_t);
int push_to_list(list_element** elements, void* data, size_t array_len);

/*
 * pop_from_list returns the next element of list.
 * obtains:
 *      pointer to the  start of list
 *      pointer to save the length of poped data
 *      pointer to pointer to data
 */
int pop_from_list(list_element** elements, size_t* array_len, void** data);
