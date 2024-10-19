#include <stdlib.h>

#define NULL_LEVEL      4
#define ERROR_LEVEL     0
#define WARNING_LEVEL   1
#define INFO_LEVEL      2
#define DEBUG_LEVEL     3


#define OK      1
#define ZERO    0
#define ERR_CALLOC -1
#define ERR_NONEMPTY -2
#define ERR_EMPTY -3
#define ERR_INDEX -4
#define ERR_OTHER -127

/*
 *  Typicall error:
 *  -1  - Operating system did not allocate the memory
 *  -2  - Pointer points to nonempty element
 *  -3  - Pointer points to empty element
 *  -127- Other error
 */

/*
 * Structure containes:
 *      void array - line
 *      size of void array - array_len
 *      pointer to the next element of the list
*/
typedef struct linked_list_element{
    void *line;
    size_t array_len;
    struct linked_list_element *next_element;
} linked_list_element;

typedef struct linked_list{
    linked_list_element *first_element;
    linked_list_element *last_element;
    size_t list_size;
}linked_list;


int init_linked_list(linked_list *list);

/*
 * clear_list   - deallocates an empty list or containing one element.
 * returns      - negative element if there is anothere element in the list
 *              - zero if operation was succesfull
 */
int clear_list(linked_list* elements);

/*
 *  Function    - 'get_last' itterate through the all elements of the list
 *              and return the pointer to the last element
 *  takes:  
 *      a pointer to the element of list.
 */
linked_list_element *get_last(linked_list elements);

/*
 *  Function    - 'append_list' add a new element at the end of the list
 *  takes       - pointer to pointer of the element of array(you may pass the last element)(**elements)
 *                pointer to the array data casted to void type(*data).
 *                size of array data(array_len).
 *  returns     - positive number: everything is ok. element was added to the end.
 *              - zero: operating system did allocate a memory.
 *              - negative_number: other kind of error.
 */
long int append_list(linked_list *elements, void* data, size_t array_len);

/*
 *  Function    - 'push_list' add a new element at the begining of the list
 *  takes       - pointer to pointer of the element of array(you may pass the last element)(**elements)
 *                pointer to the array data casted to void type(*data).
 *                size of array data(array_len).
 *  returns     - positive number: everything is ok. element was added to the end.
 *              - zero: operating system did allocate a memory.
 *              - negative_number: other kind of error.
 */
long int push_to_list(linked_list* list, void* data, size_t array_len);

/*
 *  Function    - 'pop_from_list' pop data to data variable.
 *  takes       - pointer to pointer of the element of array(you may pass the last element)(**elements)
 *                pointer to the array data casted to void type(*data).
 *                size of array data(array_len).
 *  returns     - positive number: everything is ok. element was added to the end.
 *              - zero: operating system did allocate a memory.
 *              - negative_number: other kind of error.
 */
long int pop_from_list(linked_list* elements, void** data, size_t* array_len);

/*
 *  Function    -  'get_element_number'
 *  takes       -  pointer to linked_list
 *              -  element_number number of element for reading
 *              -  pointer to pointer 'data' for extracting data
 *              -  pointer to extract size of readed element
 *  returns     - 
 *
 */
linked_list_element *get_element_number(linked_list* list, uint element_number);

long int write_element_number(linked_list* list, uint element_number, void* data, size_t data_len);
