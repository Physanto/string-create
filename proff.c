#include <stdio.h>
#include <stdbool.h>
#include "include/string.h"

string proof_create_string(char*);
void proof_destroy_string(string*);
void proof_reserve_string(string*);
void proof_print_string(string);

int main(){

    string new = proof_create_string("hola");
    string new2 = proof_create_string("holas");
    string new3 = proof_create_string("");
    proof_print_string(new);
    proof_print_string(new2);
    proof_print_string(new3);
    proof_destroy_string(&new);
    proof_destroy_string(&new2);
    proof_print_string(new2);

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
