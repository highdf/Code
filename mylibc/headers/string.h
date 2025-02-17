#include <stdio.h>
#include "error.h"
#include <stddef.h>
#include <stdlib.h>
#include "bool.h"

typedef struct string {
	char *data;
	size_t length;
}string_t;

string_t* create_string (char *value);
string_t* make_string (size_t length);
char get_char (const string_t *str, size_t index);
int get_str_length (const char *str);
string_t *str_concat (const string_t *str0, const string_t *str1);
int get_number_length (int i);
string_t *num_to_str(int number);
char get_char (const string_t *str, size_t index);
char* str_to_char_array (const string_t *str);
bool_t str_equals (const string_t *str0, const string_t *str1);
