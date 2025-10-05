#include <stdio.h>
#include <stdbool.h>
#include "include/string.h"

string proof_create_string(char*);
void proof_destroy_string(string*);
void proof_reserve_string(string);
void proof_print_string(string);
void proof_length_string(string);
void proof_capacity_string(string);
void proof_clear_string(string);
void proof_string_at(string, long);
void proof_string_set(string, long, char);
void proof_string_append(string, char*);
void proof_string_insert(string, long, char*);
void proof_string_delete(string, long, long);
void proof_string_convert_char(string, char*);

int main(){

    string str_new = proof_create_string("Hola");
    proof_print_string(str_new);
    proof_length_string(str_new);

    printf("-----------------\n\n");
    proof_string_append(str_new, " amigo");
    proof_print_string(str_new);
    proof_length_string(str_new);
    
    return 0;
}

string proof_create_string(char* data){
    return create_string(data);
}

void proof_destroy_string(string* data){ 

    Status status = destroy_string(data);
    if(status == ERR_NULL_PTR) printf("ERROR: puntero nulo\n");
    else if(status == ERR_NULL_PTR_STR) printf("ERROR: puntero al string nulo\n");
    else printf("OK: string liberado\n");
}

void proof_print_string(string data){

    Status status = print_string(data);

    if(status == ERR_NULL_PTR) printf("ERROR: no se puede imprimir ya que el puntero es nulo\n");
    else if(status == ERR_STR_EMPTY) printf("ERROR: el string esta vacio\n");
}

void proof_length_string(string data){

    long length = 0;

    Status status = length_string(data, &length);

    if(status == ERR_NULL_PTR) printf("ERROR: puntero al string nulo\n");
    else printf("OK: longitud de la cadena: %ld\n",length);
}

void proof_capacity_string(string data){
    
    long ptr_capacity = 0;
    Status status = capacity_string(data, &ptr_capacity);

    if(status == ERR_NULL_PTR) printf("ERROR: puntero al string nulo\n");
    else printf("OK: la capacidad del string es: %ld\n", ptr_capacity);
}

void proof_clear_string(string data){

    Status status = clear_string(data);

    if(status == ERR_NULL_PTR) printf("ERROR: puntero al string nulo\n");
    else if(status == ERR_NULL_PTR_STR) printf("ERROR: fallo el memory allocator\n");
    else printf("OK: string limpiado correctamente\n");
}

void proof_string_at(string data, long index){
    
    char c;
    Status status = string_at(data, index, &c);

    if(status == ERR_NULL_PTR) printf("ERROR: puntero al string nulo\n");
    else if(status == ERR_STR_EMPTY) printf("ERROR: string vacio\n");
    else if(status == ERR_INDEX_OUT_RANGE) printf("ERROR: el indice pasado por argumento esta fuera de rango\n");
    else printf("OK: Este es el caracter en la posicion pasada por argumento: %c\n",c);
}

void proof_string_set(string data, long index, char c){

    Status status = string_set(data, index, c);

    if(status == ERR_NULL_PTR) printf("ERROR: puntero al string nulo\n");
    else if(status == ERR_STR_EMPTY) printf("ERROR: string vacio\n");
    else if(status == ERR_INDEX_OUT_RANGE) printf("ERROR: el indice pasado por argumento esta fuera de rango\n");
    else printf("OK: El caracter pasado por argumento se modifico correctamente en la cadena\n");

}

void proof_string_append(string string, char* data){

    Status append = string_append(string, data);

    if(append == ERR_NULL_PTR) printf("ERROR: puntero al string nulo\n");
    else if(append == ERR_NULL_PTR_MEMRY) printf("ERROR: fallo del realloc\n");
    else printf("OK: string concatenado\n");
}

void proof_string_insert(string string, long index, char* data){
    
    Status insert = string_insert(string, index, data);

    if(insert == ERR_NULL_PTR) printf("ERROR: puntero al string nulo\n");
    else if(insert == ERR_NULL_PTR_MEMRY) printf("ERROR: fallo del realloc\n");
    else if(insert == ERR_INDEX_OUT_RANGE) printf("ERROR: index no es correcto\n");
    else printf("OK: string insertado\n");
}

void proof_string_delete(string data, long index, long length){

    Status status = string_delete(data, index, length);

    if(status == ERR_NULL_PTR) printf("ERROR: puntero al string nulo\n");
    else if(status == ERR_INDEX_OUT_RANGE) printf("ERROR: index no es correcto\n");
    else if(status == ERR_LEN_OUT_RANGE) printf("ERROR: la longitud pasada por argumento esta fuera de rango\n");
    else printf("OK: string eliminado correctamente en la posicion indicada\n");
}

void proof_string_convert_char(string string, char* string_converted){
    
    Status status = string_convert_char(string, string_converted);

    if(status == ERR_NULL_PTR) printf("ERROR: puntero al string nulo\n");
    else printf("OK: string convertido a char*");
}
