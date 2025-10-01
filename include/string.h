#ifndef STRING_H
#define STRING_H

/**
* @brief define un tipo de dato abstracto para una cadena dinamica 'string'
*
* Este tipo de dato se debe manipular a traves de las funciones provistas
* por la libreria que se le ofrece.
*
*/
typedef struct String String;

/**
* @brief define un alias para un puntero a 'String'.
*/
typedef String* string;

/**
* @brief define un enum 'Status' que representa los posibles codigos de error o exito
* de las funciones.
*/
typedef enum {
    OK, //ok: todo correcto
    ERR_NULL_PTR, //error: puntero nulo
    ERR_NULL_PTR_STR, //error: puntero al string nulo
    ERR_INDEX_OUT_RANGE, //error: tamano nulo
    ERR_STR_EMPTY, //error: string vacio
    ERR_NULL_PTR_MEMRY, //error: memory allocator fallo
    ERR_LEN_OUT_RANGE //error: longitud pasada de rango
} Status;

/**
* @brief crea un string dinamico en el heap
*
* Esta funcion crea un string en el heap, lo inicializa con el argumento pasado a la funcion (data)
* y termina la cadena con '\0'.
*
* @param char* data: representa la cadena (string) que va ser almacenada.
* @return string*: un puntero a un string con la cadena pasada por argumento.
*
* @note El usuario es responsable de liberar la memoria (string) con la funcion correspondiente
* destroy_string();
*/
String* create_string(char* data);

/**
* @brief esta funcion libera toda la memoria usada por la cadena dinamica (string).
*
* La funcion libera la memoria usada por el string.
*
* @param string* string: recibe un puntero al string el cual va ser liberado de la memoria dinamica.
*
* @return OK si la memoria fue liberada correctamente.
* @return ERR_NULL_PTR si el puntero al string pasado fue NULO.
*/
Status destroy_string(String** string);

/**
* @brief Esta funcion reserva memoria para un string mas grande.
*
* La funcion reserva memoria para un string mas grande.
* Ejm: tenemos un string "Hola" y esta cadena es de longitud 5, entonces si sabemos que la proxima cadena
* va ser "Hola, como estas el dia de hoy?" podemos asignar memoria previamente para asi evitar
* muchas llamadas al sistema de pedir memoria (buena practica).
*
* Para terminar, si tenemos "Hola" con longitud de 5 y reservamos 15
* entonces el string esta listo para almacenar ahora una cadena de 15 caracteres.
*
* @param string string: que va ser ampliado en el heap.
* @param long new_cap: representa la longitud de aumento para el string.
*
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return ERR_NULL_PTR_MEMRY si el realloc falla.
* @return OK si la reserva de memoria fue asignada correctamente.
*/
Status reserve_string(String* string, long new_cap);

/**
* @brief funcion que imprime un string
*
* Esta funcion se encarga de verificar si el string no esta vacio y si es asi entonces
* imprime el string pasado por argumento.
*
* @param string string: que quiere ser impreso.
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
*
* @return ERR_STR_EMPTY si el string pasado por argumento esta vacio.
* @return OK si imprime el string correctamente.
*/
Status print_string(String* string);

/**
* @brief funcion que calcula la longitud del string.
*
* Esta funcion calcula la longitud del string y lo asigna al puntero a un long pasado por argumento
* teniendo en cuenta que la longitud total es la cadena mas el caracter nulo de terminacion '\0'.
*
* @param string string: que se va a calcular la longitud.
* @param long* ptr_length: puntero a un long que le va ser asignado la longitud total de la cadena dinamica.
*
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return OK si fue asignado correctamente la longitud al puntero long pasado por argumento.
*/
Status length_string(String* string, long* ptr_length);

/**
* @brief funcion que calcula la capacidad que tiene el string en el momento de la consulta.
*
* Esta funcion calcula la capacidad del string y le asigna ese valor al puntero a un long pasado por argumento.
*
* @param string string: que se va a calcular la capacidad.
* @param long* ptr_capacity: puntero a un long el cual se le va asignar la capacidad calculada del string.
*
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return OK si fue asignado correctamente la capacidad al puntero long pasado por argumento.
*
*/
Status capacity_string(String* string, long* ptr_capacity);

/** 
* @brief funcion que limpia el string.
*
* Esta funcion limpia el string pasado por argumento es decir, deja al string vacio.
*
* @param string string: que va ser limpiado.
*
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return OK si el string fue vaciado completamente.
*/
Status clear_string(String* string);

/**
* @brief funcion que extrae un caracter en la posicion especificada.
*
* Esta funcion extrae un caracter del string en una posicion especifica pasada
* por argumento y lo asigna al argumento pasado a la funcion.
*
* @param string string: donde va ser extraido el caracter.
* @param long index: representa el indice dentro del string donde se esta ubicado el caracter.
* @param char* c: es donde va ser asignado el caracter extraido.
*
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return ERR_STR_EMPTY si el string pasado por argumento esta vacio.
* @return ERR_INDEX_OUT_RANGE si el indice pasado por argumento esta fuera de rango del string.
*/
Status string_at(String* string, long index, char* c);

/**
* @brief funcion que inserta un caracter en la posicion especificada.
*
*
* Esta funcion inserta un caracter dentro del string en la posicion
* especifica que es pasada por argumento es decir, el caracter que envian es que el va reemplazar
* el que esta en la posicion especificada dentro del string.
*
* @param string string: donde va ser reemplazado caracter.
* @param long index: representa el indice dentro del string donde va ser reemplazado el caracter.
* @param const char c: caracter que ser puesto en el indice especificado dentro del string.
*
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return ERR_STR_EMPTY si el string pasado por argumento esta vacio.
* @return ERR_INDEX_OUT_RANGE si el indice pasado por argumento esta fuera de rango del string.
*/

Status string_set(String* string, long index, const char c);

/**
* @brief funcion que agrega una cadena de caracteres al final del string.
*
* Esta funcion inserta una cadena de caracteres que es pasada por argumento al final del string
* y pone el caracter nulo '\0' al final de la cadena recien agregada.
*
* @param string string: donde va ser agregada la cadena de caracteres.
* @param const char* data: representa la cadena que va ser agregada al final del string.
* 
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return ERR_NULL_PTR_MEMRY si el realloc falla.
* @return OK si la cadena de caracteres fue insertada al final del string correctamente.
*/
Status string_append(String* string, const char* data);

/**
* @brief funcion que inserta una cadena de caracteres desde la posicion especificada.
*
* Esta funcion inserta una cadena de caracteres que es pasada por argumento en la posicion
* especificada y pone el caracter nulo '\0' al final de la cadena recien agregada.
*
* @param string string: donde va ser agregada la cadena de caracteres.
* @param long index: representa el indice dentro del string donde va iniciar la insercion
* de la cadena de caracteres.
* @param const char* data: representa la cadena que va ser agregada al string.
* 
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return ERR_INDEX_OUT_RANGE si el indice pasado por argumento esta fuera de rango del string.
* @return ERR_NULL_PTR_MEMRY si el realloc falla.
* @return OK si la cadena de caracteres fue insertada al final del string correctamente.
*/

Status string_insert(String* string, long index, const char* string_add);

/**
* @brief funcion que elimina un rango de caracteres.
*
* Esta funcion elimina un rango de caracteres dentro del string, este rango se relacion como:
* inicio y cantidad de caracteres a eliminar.
*
* @param string string: representa el string donde se va eliminar los caracteres.
* @param long index: representa el indice dentro del string donde va empezar a eliminar.
* @param long length: representa la cantidad de caracteres que va eliminar empezando desde
* el indice pasado por argumento.
*
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return ERR_INDEX_OUT_RANGE si el indice pasado por argumento esta fuera de rango del string.
* @return ERR_LEN_OUT_RANGE si la longitud pasada por argumento excede la cantidad de caracteres
* es decir, length > (string.length - index).
* @return OK si elimina la cantidad de caracteres especificado. 
*/
Status string_delete(String* string, long index, long length);

/**
* @brief funcion que convierte un string en un puntero a char de caracteres.
*
* @param string string: es el que se a convertir a char*
* @param char* string_converted: sera asignado el string convertido.
*
* @return ERR_NULL_PTR si el string pasado por argumento es NULO.
* @return OK si convierte el string a char* correctamente.
*/
Status string_convert_char(String* string, char* string_converted);

#endif
