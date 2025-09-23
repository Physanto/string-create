#include <stdio.h>
#include <stdbool.h>
#include "include/string.h"

string proof_create_string(char*);
void proof_destroy_string(string*);
void proof_reserve_string(string);
void proof_print_string(string);
void proof_string_append(string, char*);
void proof_string_insert(string, long, char*);

int main(){

    // string new = proof_create_string("hola");
    // string new2 = proof_create_string("holas");
    // string new3 = proof_create_string("");
    // proof_print_string(new);
    // proof_print_string(new2);
    // proof_print_string(new3);
    string new4 = proof_create_string("hola ");
    proof_print_string(new4);
    proof_string_append(new4, "soy ");
    proof_print_string(new4);
    proof_string_insert(new4,9,"yo");
    proof_print_string(new4);

    string_delete(new4, 0, 14);
    print_string(new4);
    // proof_print_string(new4);
    // proof_string_insert(new4,4,"manuel");
    // proof_print_string(new4);
    //proof_destroy_string(&new);
    //proof_destroy_string(&new2);
    //proof_print_string(new2);
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
