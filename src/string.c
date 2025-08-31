#include <stdio.h>
#include <stdlib.h>

#include "../include/string.h"

// Definicion de prototipos para las funciones locales a este archivo
long strlength(char* data);
void strcopy(char* dest, const char* src);

/**
* @brief crea un string 
*
*
*/
String* create_string(char* data){

    int length = strlength(data) + 1;

    String* string = (String*) malloc(sizeof(String));
    if(string == NULL) return NULL;

    string->data = (char*) malloc(sizeof(length));
    if(string->data == NULL) return NULL;

    strcopy(string->data, data);

    string->length = length;
    string->buffer = length * 2;

    return string;
}

Status destroy_string(String** string){

    if(string == NULL) return ERR_NULL_PTR;    
    else if(*string == NULL) return ERR_NULL_PTR_STR;

    free((*string)->data);
    free(*string);
    *string = NULL;

    return OK;
}

Status reserve_string(String *string, long new_cap){

    if(string == NULL) return ERR_NULL_PTR;

    if(new_cap > string->buffer){

        char* ptr_string = realloc(string->data, new_cap);
        if(ptr_string == NULL) return ERR_NULL_PTR_MEMRY;

        string->data = ptr_string;
        string->buffer = new_cap;
    }

    return OK;
}

Status print_string(String* string){

    if(string == NULL) return ERR_NULL_PTR; 

    else if(strlength(string->data) == 0) return ERR_STR_EMPTY;

    int l = string->length;
    printf("la longitud de la cadena es: %d",l);

    printf("[");
    for(int i = 0; i < string->length; i++){
        printf("%c",string->data[i]);

        if(i + 1 < string->length) printf(",");
    } 
    printf("]\n");

    return OK;
}

Status length_string(String* string, long* ptr_length){ 

    if(string == NULL) return ERR_NULL_PTR;
    *ptr_length = string->length;

    if(*ptr_length == 1) *ptr_length = 0;

    return OK;
}

Status capacity_string(String *string, long *ptr_capacity){
    
    if(string == NULL) return ERR_NULL_PTR;
    *ptr_capacity = string->buffer;
    
    return OK;
}

Status clear_string(String* string){

    if(string == NULL) return ERR_NULL_PTR;
    else if(string->data == NULL) return ERR_NULL_PTR_STR;

    string->data[0] = '\0';

    return OK;
}

Status string_at(String* string, long index, char* c){
    
    if(string == NULL) return ERR_NULL_PTR;

    else if(string->length == 0 || string->length == 1) return ERR_STR_EMPTY;

    else if(index > string->length - 1) return ERR_INDEX_OUT_RANGE;

    *c = string->data[index];

    return OK;
}

Status string_set(String *string, long index, char c){ 

    if(string == NULL) return ERR_NULL_PTR;

    else if(string->length == 0 || string->length == 1) return ERR_STR_EMPTY;

    else if(index > string->length - 1) return ERR_INDEX_OUT_RANGE;

    string->data[index] = c;

    return OK;
}

Status string_append(String* string, char* data){

    if(string == NULL) return ERR_NULL_PTR;

    long length_data = strlength(data); // +1 para el '\0'
    long new_size = string->length + length_data;

    if(new_size+1 > string->buffer){ 

        long new_buffer = string->buffer * 2;
        Status reserve = reserve_string(string, new_buffer);
        if(reserve != OK) return ERR_NULL_PTR_MEMRY;
    }

    // mueve el puntero al final de la cadena
    strcopy(string->data + string->length, data);
    string->length = new_size;
    return OK;
}

/**
* @brief calcula la longitud de la cadena
*
* Calcula la longitud total de la cadena sin tomar la secuencia de escape'\0'.
*
* @param char* es la cadena que va ser leida para obtener su longitud
*
* @return long la longitud de la cadena*
*/
long strlength(char* data){ 
    long i = 0;
    for(i = 0; data[i] != '\0'; i++);
    return i;
}

/**
* @brief copia una cadena de caracteres a la variable destino
*
* coge caracter por caracter almacenado en el puntero fuente y
* lo copia al puntero destino, al final agrega el caracter '\0'
*
* @param char* es el puntero en donde va almacenar la cadena copiada
*
* @param const char* es el puntero donde esta almacenada la cadena
* que va ser copiada
*/
void strcopy(char* dest, const char* src){ 

    int i;
    for(i = 0; src[i] != '\0'; i++) dest[i] = src[i];
    dest[i++] = '\0';
}

