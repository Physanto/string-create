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

    String* information = (String*) malloc(sizeof(String));
    if(information == NULL) return NULL;

    information->data = (char*) malloc(sizeof(length));
    if(information->data == NULL) return NULL;

    strcopy(information->data, data);

    information->length = length;
    information->buffer = length * 2;

    return information;
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

    string->buffer = new_cap;
    return OK;
}

Status print_string(String* string){

    if(string == NULL) return ERR_NULL_PTR; 

    else if(strlength(string->data) == 0) return ERR_STR_EMPTY;

    printf("[");
    for(int i = 0; string->data[i] != '\0'; i++){

        if(string->data[i+1] == '\0'){ 
            printf("%c",string->data[i]);
            break;
        }
        printf("%c,",string->data[i]);
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

