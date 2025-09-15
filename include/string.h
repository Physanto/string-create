
#ifndef STRING

/**
* @brief define la estructura principal que representa un 'String'
*
*
*/
typedef struct {
    char* data;
    long length;
    long buffer;
} String;

typedef String* string;

typedef enum {
    OK, // todo correcto
    ERR_NULL_PTR, // error: puntero nulo
    ERR_NULL_PTR_STR, //error: puntero al string nulo
    ERR_INDEX_OUT_RANGE, //error: tamano nulo
    ERR_STR_EMPTY, // error: string vacio
    ERR_NULL_PTR_MEMRY
} Status;

/**
* @brief crea un string
*
* crea un s
*
*
*/
String* create_string(char* data);
Status destroy_string(String** string);
Status reserve_string(String* string, long new_cap);
Status print_string(String* string);
Status length_string(String* string, long* ptr_length);
Status capacity_string(String* string, long* ptr_capacity);
Status clear_string(String* string);
Status string_at(String* string, long index, char* c);
Status string_set(String* string, long index, const char c);
Status string_append(String* string, const char* data);
Status string_insert(String* string, long index, const char* string_add);

#endif
