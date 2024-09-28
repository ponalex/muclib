#include "muclib_lmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG_IS_EMPTY 0
#define DEBUG_EXPAND_LINEARMAP 1
#define GET_ELEMENT 0
#define READ_ELEMENT 0


/*  _calc_position              :   40
 *  _find_empty_element         :   57
 *  create_linear_map           :   77
 *  create_linearmap_element    :   107
 *  del_linearmap_element       :   140
 *  is_empty_element            :   162
 *  write_data_to_linearmap     :   205
 *  write_element_to_linearmap  :   243
 *  add_data_to_linearmap       :   270
 *  add_element_to_linearmap    :   292
 *  get_data_from_linearmap     :   322
 *  get_element_from_linearmap  :   344
 *  read_data_linearmap         :   372
 *  read_element_linearmap      :   399
 *  calc_empty_number           :   430
 *  expand_linearmap            :   450
 *  shrink_linearmap            :   473
 *  clear_linearmap             :   504
 */

/*
 *  Function '_calc_position':
 *      takes: 'element_number' the size of array. (Taken from linear_map.array_size)
 *             'pointer' the interested number. It may be less then zero
 *                       (for addressing from ending of array).
 *      return the position(positive number)
 *             ERR_* - negative number
 *
 */
long int _calc_position(size_t element_number,long int pointer){
    long int position;
    if(pointer < 0 ){
        position = element_number + pointer;
    }else{
        if(pointer>= element_number){
            return ERR_INDEX;
        }
        position = pointer;
    }
    if (position < 0){
        position =  ERR_INDEX;
    }
    return position;
}

long int _find_empty_element(linear_map *list){
    long unsigned int result = 0;
    for (;result<list->array_size; result++ ){
        if(list->elements[result].data == NULL){
            break;
        }
    }
    return result;
}

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
long int create_linear_map(linear_map *new_map ,size_t linearmap_size){
    new_map->elements = calloc(linearmap_size, sizeof(linear_map));
    if(linearmap_size == 0){
        return ERR_SIZE;
    }
    if(new_map->elements == NULL ){
        perror("[create_linear_map] Can not allocate elements of linearmap. Calloc returned a null\n");
        return ERR_CALLOC;
    }
    new_map->array_size = linearmap_size;
    new_map->empty_elements = (uint)linearmap_size;
    return new_map->array_size;
}

/*
 *  Function 'create_linearmap_element' creates
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
        map_element **element,
        void *data,
        size_t data_len){
    if(data_len == 0){
        return ERR_SIZE;
    }
    *element = calloc(1, sizeof(map_element));
    if((*element)==NULL){
        perror("[create_linearmap_element] Can not create a map element. Calloc returned NULL\n");
        return ERR_CALLOC;
    }
    if((*element)->data!=NULL){
        return ERR_NONEMPTY;
    }
    (*element)->data = calloc(data_len, sizeof(void*));
    if((*element)->data==NULL){
        perror("[create_linearmap_element]Can not allocate data. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    memcpy((*element)->data, data, data_len);
    (*element)->data_len = data_len;
    return (*element)->data_len;
}

/*
 *  Function 'del_linearmap_element' deletes
 *      and set to NULL the linear map element.
 *  It takes:
 *      'element' - pointer to pointer of a
 *          linear map element;
 *  It returns: void. 
 */
void del_linearmap_element(map_element **element){
    free((*element)->data);
    (*element)->data = NULL;
    (*element)->data_len = 0;
    free(*element);
}

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
long int is_empty_element(linear_map *array,long int element_number){
    long int result = 0;
    long int a_size = array->array_size;
    long int position = _calc_position(a_size, element_number);
//  Error from get position
    if(position<0){
        return position;
    }
    if( array->elements[position].data==NULL){
        if(array->elements[position].data_len == 0){
            result = 0;
        }else{
            result = ERR_EMPTY;
        }
    }else{
        if(array->elements[position].data_len == 0){
            result = ERR_NONEMPTY;
        }else{
            result = array->elements[position].data_len;
        }
    }
    return result;
}

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
        ){
    if(data_len == 0){
        return ERR_SIZE;
    }
    long number = _calc_position(array->array_size, element_number);
    if(number<0){
        // Index exceeded the number of elements.
        return ERR_INDEX;
    }
    if(array->elements[number].data != NULL){
        if(array->elements[number].data_len!=0){
            free(array->elements[number].data);
            array->elements[number].data_len=0;
            ++array->empty_elements;
        }else{
            return ERR_OTHER;
        }
    }
    array->elements[number].data = calloc(data_len, sizeof(void*));
    if(array->elements[number].data==NULL){
        perror("[write_data_to_linearmap]Can not allocate an element. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    array->elements[number].data_len = data_len;
    memcpy(array->elements[number].data, data, data_len);
    return --array->empty_elements;
}

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
            long element_number, 
            map_element *element){
    long int number = _calc_position(array->array_size, element_number);
    if(number < 0){
        return ERR_INDEX;
    }
    if(array->elements[number].data!=NULL){
        if(array->elements[number].data_len!=0){
            free(array->elements[number].data);
            array->elements[number].data_len=0;
            ++array->empty_elements;
        }else{
            return ERR_OTHER;
        }
    }
    array->elements[number].data = calloc(element->data_len, sizeof(void*));
    if(array->elements[number].data==NULL){
        perror("[write_element_to_linearmap]Can not allocate memory for data. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    memcpy(array->elements[number].data, element->data, element->data_len);
    array->elements[number].data_len = element->data_len;
    return --array->empty_elements;
}

long int add_data_to_linearmap(linear_map *array,
            void *data,
            size_t data_len){
    long int result = 0;
    if(array->empty_elements!=0){
        result = _find_empty_element(array);
        array->elements[result].data = calloc(data_len, sizeof(void*));
        if(array->elements[result].data != NULL){
            memcpy(array->elements[result].data, data, data_len);
            array->elements[result].data_len = data_len;
            array->empty_elements--;
            result = array->empty_elements;
        }else{
            perror("[add_data_to_linearmap] Can not store data. Calloc returned NULL.\n");
            result = ERR_CALLOC;
        }
    }else{
        result = ERR_NONEMPTY;
    }
    return result;
}

long int add_element_to_linearmap(linear_map *array, map_element *element){
    long int result = 0;
    if(array->empty_elements == 0){
        return ERR_NONEMPTY;
    }
    long int element_number = _find_empty_element(array);
    if(element_number < 0){
        return element_number;
    }
    array->elements[element_number].data = calloc(element->data_len, sizeof(void*));
    if(array->elements[element_number].data == NULL){
        perror("[add_element_to_linearmap]Can not copy data. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    array->elements[element_number].data_len = element->data_len;
    --array->empty_elements;
    result = element_number;
    return result;
}

/*
 *  Function 'get_data_from_linearmap' extracts data(cell will be free) from map 
 *      takes:  'array' - pointer to linear map
 *              'element_number' - number element for storing data
 *              'data'  - pointer at pointer where data will be stored
 *              'data_len' - pointer where size data will be stored
 *      returnes:
 *              negative number if there is error
 *              positive or zero - number of empty element
 */
long int get_data_from_linearmap(linear_map *array,
                            long int element_number,
                            void **data,
                            size_t *data_len){
    long int position = _calc_position(array->array_size, element_number);
    if(position< 0 ){
        return position;
    }
    *data = calloc(array->elements[position].data_len, sizeof(void*));
    if(*data == NULL){
        perror("[get_data_from_linearmap]Can not allocate data. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    memcpy(*data, array->elements[position].data, array->elements[position].data_len);
    *data_len = array->elements[position].data_len;
    free(array->elements[position].data);
    array->elements[position].data = NULL;
    array->elements[position].data_len = 0;
    return ++array->empty_elements;
}

map_element *get_element_from_linearmap(linear_map *array, long int element_number){
    map_element *result;
    long int number = _calc_position(array->array_size, element_number);
#if GET_ELEMENT
    printf("[get_element_from_linearmap] DEBUG: number: %ld", number);
#endif
    if(number < 0 ){
        return NULL;
    }
    result = calloc(1, sizeof(map_element));
    if(result == NULL){
        perror("[get_element_from_linearmap] Can not create an element. Calloc returned NULL.\n");
        return NULL;
    }
    result->data = calloc(array->elements[number].data_len, sizeof(void*));
    if(result->data==NULL){
        perror("[get_element_from_linearmap] Can not copy data to a new element. Calloc returned NULL.\n");
       return NULL; 
    }
    memcpy(result->data, array->elements[number].data, array->elements[number].data_len);
    result->data_len = array->elements[number].data_len;
    free(array->elements[number].data);
    array->elements[number].data = NULL;
    array->elements[number].data_len = 0;
    ++array->empty_elements;
    return result;
}

long int read_data_linearmap(
                linear_map *array,
                long element_number,
                void **data,
                size_t *data_len){
    long int number = _calc_position(array->array_size, element_number);
    void *temp;
    if(number<0){
        return ERR_INDEX;
    }
    if(is_empty_element(array, number)==0){
        return ERR_EMPTY;
    }
    temp = calloc(array->elements[number].data_len, sizeof(void*));
    if(temp == NULL){
        perror("[read_data_linearmap] Can not create temp element for copying. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    memcpy(temp, array->elements[number].data, array->elements[number].data_len);
    if(*data != NULL){
        free(*data);
    }
    *data=temp;
    *data_len = array->elements[number].data_len;
    return array->elements[number].data_len;
}

long int read_element_linearmap(
                linear_map *array,
                long element_number,
                map_element *element){
    long int result = 0;
    void *new_element;
    long int number = _calc_position(array->array_size, element_number);
    if(number<0){
        return ERR_INDEX;
    }
    if(is_empty_element(array, number)==0){
        return ERR_EMPTY;
    }
    new_element = calloc(array->elements[number].data_len, sizeof(void*));
#if READ_ELEMENT
    printf("[read_element_linearmap] DEBUG: Address element: %p\n", new_element);
#endif
    if(new_element == NULL){
        perror("[read_element_linearmap] Can not create temp element for copying. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    if(element->data != NULL){
        free(element->data);
    }
    element->data = new_element;
    memcpy(element->data, array->elements[number].data, array->elements[number].data_len);
    element->data_len = array->elements[number].data_len;
    return element->data_len;
}

// OK version
long int calc_empty_number(linear_map *array){
    long int result = array->array_size;
    for(long int i = 0 ; i < array->array_size ; ++i){
        if(array->elements[i].data_len == 0){
            if(array->elements[i].data == NULL){
                --result;
            }else{
                result = ERR_OTHER;
                break;
            }
        }else{
            if(array->elements[i].data == NULL){
                result = ERR_OTHER;
                break;
            }
        } 
    }
    return result;
}

long int expand_linearmap(linear_map *array, uint new_size){
    if(new_size <= array->array_size){
        return ERR_SIZE;
    }
    map_element *new_array = calloc(new_size, sizeof(map_element));
    if(new_array == NULL){
        perror("[expand_linearmap]Can not copy an array. Calloc  returned NULL.\n");
        return ERR_CALLOC;
    }
    memcpy(new_array, array->elements, array->array_size*sizeof(map_element));
    for(long i = 0 ; i < array->array_size; ++i){
        free(array->elements[i].data);
        array->elements[i].data = NULL;
        array->elements[i].data_len = 0;
    }
    free(array->elements);
    array->elements = new_array;
    array->array_size = new_size;
    array->empty_elements = calc_empty_number(array);
    return array->empty_elements;
}

long int shrink_linearmap(linear_map *array, uint new_size){
    long int result = 0;
    if(new_size >= array->array_size){
        return ERR_SIZE;
    }
    map_element *new_array = calloc(new_size, sizeof(map_element));
    if(new_array == NULL){
        perror("[shrink_linearmap]Can not copy an array. Calloc  returned NULL.\n");
        return ERR_CALLOC;
    }
    memcpy(new_array, array->elements, new_size*sizeof(map_element));
    for(long i = 0 ; i < array->array_size; ++i){
        free(array->elements[i].data);
        array->elements[i].data = NULL;
        array->elements[i].data_len = 0;
    }
    free(array->elements);
    array->elements = new_array;
    array->array_size = new_size;
    array->empty_elements = calc_empty_number(array);
    return result;
}

/*
 *  Function 'clear_linearmap' clears all map data
 *      takes:  pointer to linear_map element
 *      returns:
 *              negative 
 *              positive
 *
 */
int clear_linearmap(linear_map* array){
    int result = array->array_size;
    for(int i= 0 ; i< result; i++){
        if(array->elements[i].data!=NULL){
            free(array->elements[i].data);
            array->elements[i].data=NULL;
        }
    }
    free(array->elements);
    array->elements = NULL;
    array->array_size = 0;
    array->empty_elements=0;
    return result;
}
