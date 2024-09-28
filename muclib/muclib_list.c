#include "muclib_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int init_linked_list(linked_list *list){
    list->first_element= NULL;
    list->last_element = NULL;
    list->list_size = 0;
    return OK;
}

int clear_list(linked_list *list){
    linked_list_element *temp_first_element;
    for(long int i = 0 ; i < list->list_size ; i++ ){
        if(list->first_element->next_element !=NULL){
            temp_first_element = list->first_element->next_element;
        }
        free(list->first_element->line);
        list->first_element->line=NULL;
        list->first_element->array_len=0;
        free(list->first_element);
        list->first_element = temp_first_element;
    }
    return OK;
}

long int append_list(linked_list *list, void *data, size_t array_len){
    linked_list_element *new_element = calloc(1, sizeof(linked_list_element));
    if(new_element==NULL){
        perror("[append_list]Can not add an element. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    new_element->line = calloc(array_len, sizeof(void*));
    if(new_element->line==NULL){
        free(new_element);
        perror("[append_list]Can not add e data to the element. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    memcpy(new_element->line, data, array_len);
    new_element->array_len = array_len;
    if(list->list_size == 0){
        list->first_element = new_element;
        list->last_element  = new_element;
        list->list_size=1;
    }else{
        list->list_size++;
        list->last_element->next_element = new_element;
        list->last_element = new_element;
    }
    return list->list_size;
}

long int pop_from_list(linked_list *list, void **data, size_t *array_len){
    linked_list_element *temp_last_element ;
    if(list->list_size==0){
        return ERR_EMPTY;
    }
    *data = calloc(list->first_element->array_len, sizeof(void*));
    if(*data==NULL){
        perror("[pop_from_list]Can not pop data from a list. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    memcpy(*data, list->first_element->line, list->first_element->array_len);
    free(list->first_element->line);
    list->first_element->line=NULL;
    
    temp_last_element = list->first_element->next_element;
    free(list->first_element);
    list->first_element = temp_last_element;
    list->list_size--;
    if(list->list_size == 0){
        list->last_element = NULL;
    }
    return list->list_size;
}

long int push_to_list(linked_list* list, void *data, size_t array_len){
    linked_list_element *new_element = calloc(1, sizeof(linked_list_element));
    if(new_element == NULL){
        perror("[push_to_list]Can not add a new element list. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    new_element->line = calloc(array_len, sizeof(void*));
    if(new_element->line == NULL){
        free(new_element);
        perror("[push_to_list]Can not add data. Calloc returned NULL.\n");
        return ERR_CALLOC;
    }
    memcpy(new_element->line, data, array_len);
    new_element->array_len = array_len;
    new_element->next_element = list->first_element;
    list->first_element = new_element;
    list->list_size++; 
    if((list->list_size) ==1){
        list->last_element = new_element;
    }
    return list->list_size;
}

linked_list_element* get_element_number(linked_list *list, uint element_number){
    linked_list_element *element = list->first_element;
    if(element_number >= list->list_size){
        return NULL;
    }
    for(uint i = 0 ; i<list->list_size ; i++){
        if(i == element_number){
           break;
        }
        if(element->next_element == NULL){
            return NULL;
        }
        element = element->next_element;
    }
    return element;
}

long int write_element_number(linked_list *list,
                        uint element_number,
                        void *data,
                        size_t data_len){
    long int result  = 0;
    linked_list_element *element; 
    element = get_element_number(list, element_number);
    free(element->line);
    element->line = calloc(data_len, sizeof(void*));
    if(element->line == NULL ){
        result = ERR_CALLOC;
    }
    memcpy(element->line, data, data_len);
    element->array_len = data_len;
    result = data_len;
    return result;
}
