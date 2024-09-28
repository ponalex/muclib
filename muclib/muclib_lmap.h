#include<stdlib.h>
#include<string.h>

#define OK      1
#define ZERO    0
#define ERR_CALLOC -1
#define ERR_NONEMPTY -2
#define ERR_EMPTY -3
#define ERR_INDEX -4
#define ERR_SIZE  -5
#define ERR_OTHER -127

typedef struct map_element{
    void *data;
    size_t data_len;
}map_element;

typedef struct linear_map{
     map_element* elements;
     size_t array_size;
     uint empty_elements;
}linear_map;

/*
 *  Function 'create_linear_map' initializes
 *      a empty linear map.
 *  It takes:
 *      'new_map' - pointer to a linear_map;
 *      'linearmap_size'- size of array;
 *  It returns: 
 *      if positive - the number of elements;
 *      if negative - error;
 */
long int create_linear_map(
        linear_map* new_map,
        size_t map_size
        );

/*
 *  Function 'create_linearmap_elements' creates
 *      and initializes a linear map element.
 *  It takes:
 *      'element' - pointer to pointer of a new
 *          linear map element;
 *      'data' - pointer to a data to add data
 *          to the new element;
 *      'data_len' - the length in bytes of
 *          stored elements;
 *  It returns: 
 *      if positive - the length in bytes of
 *          stored elements(should be equal
 *          data_len);
 *      if negative - error
 */
long int create_linearmap_element(
        map_element** element,
        void* data,
        size_t data_len
        );

/*
 *  Function 'del_linearmap_element' deallocates
 *      and set to zero element.
 *  It takes:
 *      'element' - pointer to pointer of the
 *          linear map element;
 *  It returns: void.
 */
void del_linearmap_element(map_element** element);

/*
 *  Function 'write_data_to_linearmap' writes
 *      data to the given position. If element
 *      is not empty, the new value will replace
 *      old one.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *      'element_number'- the position of
 *          interested element.It can take
 *          negative number to count in back
 *          order;
 *      'data' - pointer to new data
 *      'data_len' - the length in bytes of
 *          stored data;
 *  It returns: 
 *      if positive or zero - the number of empty
 *          elements;
 *      if negative - error;
 */
long int write_data_to_linearmap(
        linear_map *array,
        long int element_number,
        void *data,
        size_t data_len
        );

/*
 *  Function 'write_element_to_linearmap' copies
 *      element to the given position.
 *      If element in linear map is not empty,
 *      the new value will replace old one.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *      'element_number'- the position of
 *          interested element.It can take
 *          negative number to count in back
 *          order;
 *      'element' - pointer to the a new element;
 *  It returns:
 *      if positive or zero - the number of empty
 *          elements;
 *      if negative - error;
 */
long int write_element_to_linearmap(
        linear_map *array,
        long int element_number,
        map_element* element
        );

/*
 *  Function 'add_data_to_linearmap' copy data to
 *          the least position and return the
 *          number of position.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *      'data'  - pointer to new data;
 *      'data_len' - the length in bytes of
 *          stored data;
 *  It returns:
 *      if positive or zero - the number of empty
 *          elements;
 *      if negative - error;
 */
long int add_data_to_linearmap(
        linear_map *array,
        void *data,
        size_t data_len
        );

/*
 *  Function 'add_element_to_linearmap' copy data to
 *          the least position and return the
 *          number of position.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *      'element'  - pointer to element with
 *          new data;
 *  It returns:
 *      if positive or zero - the number of inserted element
 *          elements;
 *      if negative - error;
 */
long int add_element_to_linearmap(
        linear_map *array,
        map_element *element
        );

/*
 *  Function 'get_element_from_linearmap' extract
 *          element from the position number and
 *          delete data at this position.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *      'element_number'  - pointer to element
 *          with new data. It can take negative
 *          number to count in back order;
 *  It returns:
 *      pointer to the new linear map element
 *      NULL if there is error;
 */
map_element* get_element_from_linearmap(
        linear_map* array,
        long int element_number
        );

/*
 *  Function 'get_data_from_linearmap' extract
 *          data from the position number and
 *          delete data at this position.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *      'element_number' - pointer to element
 *          with data.It may take a negative
 *          number to count in back order.
 *      'data' - pointer to pointer where data
 *          will be copied.
 *      'data_len' - pointer where the length of
 *          data will be stored.
 *  It returns:
 *      zero or positive - the number of empty
 *          elements;
 *      negative - error;
 */
long int get_data_from_linearmap(
        linear_map* array,
        long int element_number,
        void** data,
        size_t *data_len
        );

/*
 *  Function 'read_data_linearmap' read
 *          data from the position number and
 *          does not delete it.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *      'element_number' - pointer to element
 *          with data.It may take a negative
 *          number to count in back order.
 *      'data' - pointer to pointer where data
 *          will be copied.
 *      'data_len' - pointer where the length of
 *          data will be stored.
 *  It returns:
 *      positive - number of bytes stored in this
 *          element;
 *      negative - error;
 */
long int read_data_linearmap(
        linear_map *array,
        long int element_number,
        void** data,
        size_t* data_len
        );

/*
 *  Function 'read_element_linearmap' copy data
 *      to the element.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *      'element_number' - pointer to element
 *          with data.It may take a negative
 *          number to count in back order.
 *      'map_element' - pointer to the element
 *          where data will be copied.
 *  It returns:
 *      positive - number of bytes stored in this
 *          element;
 *      negative - error;
 */
long int read_element_linearmap(
        linear_map* array,
        long int element_number,
        map_element* element
        );

/*
 *  Function 'calc_empty_number' calculate the
 *      number of empty elements.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *  It returns:
 *      positive or zero - number of bytes stored
 *          in array;
 *      negative - error;
 */
long int calc_empty_number(
        linear_map* array
        );

/*
 *  Function 'expand_linearmap' expands array
 *      and copy to the new array from old one.
 *  It takes:
 *      'old_array' - pointer to a linear_map;
 *      'new_size' - new size of array.
 *  It returns:
 *      positive - number of empty elements 
 *      negative - error;
 */
long int expand_linearmap(
        linear_map* old_array,
        uint new_size
        );

/*
 *  Function 'shrink_linearmap' reduce array
 *      and copy to the new array from old one.
 *      Old data or data at the end of an old
 *      array will be erased.
 *  It takes:
 *      'old_array' - pointer to a linear_map;
 *      'new_size' - new size of array.
 *  It returns:
 *      positive - number of empty elements 
 *      negative - error;
 */
long int shrink_linearmap(
        linear_map* old_array,
        uint new_size
        );

/*
 *  Function 'clear_linearmap' deallocates
 *      and set to zero all data in linear map.
 *  It takes:
 *      'element' - pointer the linear map;
 *  It returns: number of elements in deleted
 *          array.
 */
int clear_linearmap(linear_map* array);

/*
 *  Function 'is_empty_element' checks if the
 *      given position is empty.
 *  It takes:
 *      'array' - pointer to a linear_map;
 *      'element_number'- the position of
 *          interested element.It can take
 *          negative number to count in back
 *          order;
 *  It returns: 
 *      if zero - the element is empty;
 *      if positive - the length of stored data
 *          in bytes;
 *      if negative - error;
 */
long int is_empty_element(linear_map* array, long int element_number);

