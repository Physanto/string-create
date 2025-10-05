#include <stdio.h>
#include <stdlib.h>
#include "../include/string.h"

/*
* Estructura que representa un string dinamico en el heap
* data: corresponde a la cadena de caracteres.
* length: corresponde a la longitud de la cadena contando el caracter nulo '\0'.
* buffer: representa el espacio total reservado para data, o sea que este representa el espacio total que se puede usar
* para almacenar una cadena.
* 
* Ejm: para la cadena "Hola".
* data: "Hola\0_____".
* length: 4.
* buffer: 10, o sea que puede ingresar una cadena de 5 caracteres mas a la cadena original. Ejm: "Hola\0_____".
*
* ACLARACION PARA TODO EL ARCHIVO: tener en cuenta que en el struct 'String' que esta ubicado en el heap cuando almacenamos el data y ponemos:
* "Hola\0_____" simplemente es una representacion grafica para mayor claridad.
*/
struct String{
    char* data;
    long length;
    long buffer;
};


// Definicion de prototipos para las funciones locales a este archivo
long strlength(const char* data);
void strcopy(char* dest, const char* src);

/*
* Esta funcion crea un struct 'String' en el heap.
*
* es importante aclarar que nuestro data no apunta al primer caracter de una cadena en el stack sino que reservamos espacio para almacenar
* toda la cadena en el heap (por eso pedimos espacio y luego usamos strcopy() para que data contenga toda la cadena en el heap).
* Ejm: data = "Hola\0".
*
* el buffer se le asigna un espacio inicial del doble de la longitud de la cadena de caracteres que se acaba de crear, esto lo hacemos para
* que no tengamos llamadas al sistema cada nada, asi que manejamos como una reserva del doble de la cadena inicial.
*
* la funcion retorna un puntero al struct 'String', es decir.
*
* stack                                                              heap
*   proof.c                                               |---->  struct 'String'
* |-------------------------------------------|           |    |------------------------|
* | string string_new = create_string("Hola") |-----------|    | data: "Hola\0_____"    |
* |-------------------------------------------|                |------------------------|
* |                                           |                | length: 4              |
* |-------------------------------------------|                |------------------------|
* |                                           |                | buffer: 10             |
* |-------------------------------------------|                |------------------------| 
*
*/
String* create_string(char* data){

    int length = strlength(data);
    int buffer = (length + 1) * 2;

    String* string = (String*) malloc(sizeof(String));
    if(string == NULL) return NULL;

    string->data = (char*) malloc(sizeof(buffer));
    if(string->data == NULL) return NULL;

    strcopy(string->data, data);

    string->length = length;
    string->buffer = buffer;

    return string;
}


/*
* Esta funcion se encarga de destruir todo el struct 'String' que se pasa por parametro que esta alojado en el heap.
*
* primero se libera el puntero que apunta al puntero que contiene la cadena de caracteres.
*
* despues se libera el puntero que apunta al struct en el heap.
*
* y por ultimo ponemos en NULL el struct que esta en el heap.
*
* con esto ya hacemos que el struct no consuma memoria.
*
* *Ejemplo de un flujo de ejecucion normal:
* 
* - llama a la funcion create_string() y esta le retorna un puntero donde se encuentra el struct 'String'.
*
* - Se llama a la funcion destroy_string() que se encargara de liberar el struct 'String' de la memoria ocupada en el heap:
*
* stack                                                heap
*                                                        |*******************************************************|
* |*********************************|                    | |---------------------------------------|             |
* |   proof.c                     | |                    | |  struct 'String'                      |             |
* | |-----------------------------| |                    | | |------------------------|            |             |
* | | destroy_string(&string_new) | |                    | | | data: "Hola\0_____"    |X: liberado |             |
* | |-----------------------------| |                    | | |------------------------|            | X: liberado |
* | |                             | |                    | | | length: 4              |            |             |
* | |-----------------------------| |                    | | |------------------------|            |             |
* | |                             | |                    | | | buffer: 10             |            |             |
* | |-----------------------------| |                    | | |------------------------|            |             |
* |                                 |                    | |---------------------------------------|             |
* |*********************************|                    |*******************************************************|
*
* - asi quedaria el puntero string_new que apunta al struct 'String':
*
* stack                                                heap
*                                                     |*******************************************************|
* |******************************|                    | |---------------------------------------|             |
* |   proof.c                    |     |----X---->    | |  struct 'String'                      |             |
* | |--------------------------| |     X              | | |------------------------|            |             |
* | | string_new = NULL    ----|-|-----|              | | | data: "Hola\0_____"    |X: liberado |             |
* | |--------------------------| |  deja de apuntar   | | |------------------------|            | X: liberado |
* | |                          | |                    | | | length: 4              |            |             |
* | |--------------------------| |                    | | |------------------------|            |             |
* | |                          | |                    | | | buffer: 10             |            |             |
* | |--------------------------| |                    | | |------------------------|            |             |
* |                            | |                    | |---------------------------------------|             |
* |******************************|                    |*******************************************************|
*
* y al final solo retorna un Status dependiendo de la entrada a la funcion.
*/
Status destroy_string(String** string){

    if(string == NULL) return ERR_NULL_PTR;    
    else if(*string == NULL) return ERR_NULL_PTR_STR;

    free((*string)->data);
    free(*string);
    *string = NULL;

    return OK;
}


/*
* La funcion reserva espacio adicional en el struct 'String' pasado por parametro para una cadena mas grande, esta se almacena
* en el campo buffer del struct 'String'.
*
* esto lo hace verificando primero si la capacidad nueva es mas grande que el buffer ya que sino es asi, el buffer sigue intacto
*
* Como podemos notar en la siguiente representacion grafica el campo buffer del struct 'String' crece y ademas lo que puede
* almacenar data ya es mas grande ya que el buffer crecio.
*
* Este es ejemplo de un ciclo de ejecucion normal, ahora tomaremos string str_new = "Hola":
*
* stack                                                heap
* |********************************|                   |********************************|
* |                                |                   | |----------------------------| |
* |   proof.c                      |           |-------|>|  struct 'String'           | |
* | |----------------------------| |           |       | | |------------------------| | |
* | | str_new = 0x01          ---|-|-----------|       | | | data: "Hola\0_______"  | | |
* | |----------------------------| |                   | | |------------------------| | |
* | | reserve_string(str_new, 12)| |                   | | | length: 4              | | |
* | |----------------------------| |                   | | |------------------------| | |
* | |                            | |                   | | | buffer: 12             | | |
* | |----------------------------| |                   | | |------------------------| | |
* |                                |                   | |----------------------------| |
* |********************************|                   |********************************|
*
* al final solo retorna un Status dependiendo de la entrada a la funcion.
*/
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


/*
* Esta funcion simplemente imprime toda la cadena de caracteres del 'String' pasado por parametro.
*
* retorna un Status dependiendo la entrada pasada a la funcion.
*/
Status print_string(String* string){

    if(string == NULL) return ERR_NULL_PTR; 

    else if(strlength(string->data) == 0) return ERR_STR_EMPTY;

    printf("[");
    for(int i = 0; i < string->length; i++){
        printf("%c",string->data[i]);

        if(i + 1 < string->length) printf(",");
    } 
    printf("]\n");

    return OK;
}

/*
* Esta funcion toma el 'String' pasado por parametro le consulta la longitud de la cadena y se la asigna
* al parametro recibido (ptr_length).
*
* retorna un Status dependiendo de la entrada que se le paso a la funcion.
*/
Status length_string(String* string, long* ptr_length){ 

    if(string == NULL) return ERR_NULL_PTR;
    *ptr_length = string->length;

    return OK;
}

/*
* Esta funcion toma el 'String' pasado por parametro le consulta el buffer y se la asigna al parametro recibido (ptr_capacity).
*
* retorna un Status dependiendo de la entrada a la funcion.
*/
Status capacity_string(String *string, long* ptr_capacity){
    
    if(string == NULL) return ERR_NULL_PTR;
    *ptr_capacity = string->buffer;
    
    return OK;
}


/*
* Esta funcion toma el 'String' pasado por parametro y limpia (vacia) la cadena de caracteres que se almacena en data del 'String'
*
* Veremos un ejemplo de ciclo de ejecucion:
*
*                                                      Heap
* Stack                                               |********************************|
* |******************************|                    | |----------------------------| |
* |   proof.c                    |          |---------|>|  struct 'String'           | |
* | |--------------------------| |          |         | | |------------------------| | |
* | | str_new = 0x01         --|-|----------|         | | | data: "\0ola\0_______" | | |
* | |--------------------------| |                    | | |------------------------| | |
* | | clear_string(str_new)    | |                    | | | length: 0              | | |
* | |--------------------------| |                    | | |------------------------| | |
* | |                          | |                    | | | buffer: 12             | | |
* | |--------------------------| |                    | | |------------------------| | |
* |                              |                    | |----------------------------| |
* |******************************|                    |********************************|
*
* cuando hablamos de limpiar el 'String' (vaciar) lo que verdaderamente hacemos es dejar string->data[0] = \0 ya que eso
* hablando logicamente es el final de la cadena, entonces se maneja de esta forma por simplicidad y eficiencia.
*
* notar que entonces la length ya pasaria hacer 0 y el buffer no se modifica.
*
* retorna un Status dependiendo de la entrada a la funcion.
*/
Status clear_string(String* string){

    if(string == NULL) return ERR_NULL_PTR;
    else if(string->data == NULL) return ERR_NULL_PTR_STR;
    
    string->length = 0;
    string->data[0] = '\0';

    return OK;
}


/*
* Esta funcion toma del 'String' pasado por parametro un caracter especifico y se lo asigna a un ptr_c que tambien es pasado
* por parametro.
*
* retorna un Status dependiendo de la entrada a la funcion.
*/
Status string_at(String* string, long index, char* c){
    
    if(string == NULL) return ERR_NULL_PTR;

    else if(string->length == 0) return ERR_STR_EMPTY;

    else if(index > string->length) return ERR_INDEX_OUT_RANGE;

    *c = string->data[index];

    return OK;
}


/*
* Esta funcion toma el 'String' pasado por parametro y le asigna en una posicion especifica un caracter.
*
* retorna un Status dependiendo de la entrada a la funcion.
*/
Status string_set(String *string, long index, const char c){ 

    if(string == NULL) return ERR_NULL_PTR;

    else if(string->length == 0) return ERR_STR_EMPTY;

    else if(index > string->length) return ERR_INDEX_OUT_RANGE;

    string->data[index] = c;

    return OK;
}


/*
* Esta funcion toma el 'String' pasado por parametro y le agrega a data una cadena de caracteres al final cambiando el
* caracter nulo al final de la nueva cadena.
*
* Ahora tomaremos que str_nw = "Hola".
*
Stack                                                        |********************************|
* |*************************************|                    | |----------------------------| |
* |   proof.c                           |          |---------|>|  struct 'String'           | |
* | |---------------------------------| |          |         | | |------------------------| | |
* | | str_nw = 0x01               ----|-|----------|         | | | data: "Hola amigo\0_"  | | |
* | |---------------------------------| |                    | | |------------------------| | |
* | | string_append(str_nw, " amigo") | |                    | | | length: 10             | | |
* | |---------------------------------| |                    | | |------------------------| | |
* | |                                 | |                    | | | buffer: 12             | | |
* | |---------------------------------| |                    | | |------------------------| | |
* |                                     |                    | |----------------------------| |
* |*************************************|                    |********************************|*
*
* retorna un Status dependiendo de la entrada a la funcion.
*/
Status string_append(String* string, const char* data){

    if(string == NULL) return ERR_NULL_PTR;

    long length_data = strlength(data);
    long new_size = string->length + length_data;

    if(new_size > string->buffer){ 
        long new_buffer = string->buffer * 2;
        Status reserve = reserve_string(string, new_buffer);
        if(reserve != OK) return ERR_NULL_PTR_MEMRY;
    }

    // mueve el puntero al final de la cadena
    strcopy(string->data + string->length, data);
    string->length = new_size;
    return OK;
}

Status string_insert(String* string, long index, const char* string_add){

    if(string == NULL) return ERR_NULL_PTR;
    if(index >= string->length) return ERR_INDEX_OUT_RANGE;    

    long string_length = strlength(string_add);
    long new_length = string_length + index + 1; //+1 del '\0'

    if(new_length > string->buffer){
        printf("aqui estoy\n");
        long new_buffer = string->buffer * 2;
        Status reserve = reserve_string(string, new_buffer);
        if(reserve != OK) return ERR_NULL_PTR_MEMRY;        
    }

    strcopy(string->data + index, string_add);
    string->length = new_length;
    return OK;
}

Status string_delete(String *string, long index, long length){

    if(string == NULL) return ERR_NULL_PTR;

    if(index >= string->length) return ERR_INDEX_OUT_RANGE;

    if(length > (string->length - index - 1)) return ERR_LEN_OUT_RANGE;
    
    char string_aux[length+1];
    strcopy(string_aux, string->data + (index + length));

    strcopy(string->data + index, string_aux);

    string->length = string->length - length;

    return OK;
}

Status string_convert_char(String* string, char* string_converted){
    
    if(string == NULL) return ERR_NULL_PTR;

    strcopy(string_converted, string->data);

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
long strlength(const char* data){ 
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


