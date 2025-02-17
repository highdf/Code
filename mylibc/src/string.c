#include "string.h"

void str_init(string_t* str);

string_t* make_string(size_t length) {
    char* location = "string.c -> make_string()";

    if (length < 0) {
        handle_error(location, "Argment is invaled");
    }
    char* data = (char*)malloc(length * sizeof(char) + 1);
    string_t* str = (string_t*)malloc(sizeof(string_t));

    is_null(data, location);
    is_null(location, str);

    str->data = data;
    str->length = length;

    str_init(str);

    return str;
}

string_t* create_string(char* value) {
    char* location = "string.c -> create_string()";

    is_null(location, value);
    string_t* str = (string_t*)malloc(sizeof(string_t));
    is_null(location, str);

    size_t length = get_str_length(value);
    str->data = value;
    str->length = length;

    return str;
}

void str_init(string_t* str) {
    for (int i = 0; i < str->length; i++) {
        str->data[i] = '0';
    }
    str->data[str->length] = '\0';
}

char get_char(const string_t* str, size_t index) {
    if (index < 0 || index > str->length) {
        printf("index = %d\n", (int)index);
        handle_error("string.c -> get_char()", "Argment invaled");
    }

    return str_to_char_array(str)[index];
}

string_t* num_to_str(int number) {
    char* location = "string.c -> num_to_str()";

    if (num_to_str < 0) {
        handle_error(location, "Argment is invaled");
    }

    int length = get_number_length(number);
    string_t* str = make_string(length);

    int i = length - 1;
    do {
        int unit_digit = number % 10;
        str->data[i] = unit_digit + '0';

        number /= 10;
        i--;
    } while (number > 0);

    return str;
}

int get_number_length(int i) {
    int count = 0;

    i = (i >= 0) ? (i) : (-i);

    do {
        count++;
        i /= 10;
    } while (i > 0);

    return count;
}

string_t* str_concat(const string_t* str0, const string_t* str1) {
    char* location = "string.c -> str_concat()";

    int length0 = str0->length;
    int length1 = str1->length;

    string_t* new_str = make_string(length0 + length1);

    const char* src_str = str0->data;
    for (int i = 0, j = 0; get_char(new_str, i) != '\0'; i++, j++) {
        if (src_str[j] == '\0') {
            src_str = str1->data;
            j = 0;
        }
        new_str->data[i] = src_str[j];
    }

    return new_str;
}

int get_str_length(const char* str) {
    int lenght = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        lenght++;
    }

    return lenght;
}

char* str_to_char_array(const string_t* str) {
    is_null("string.c -> str_to_char_array()", str);

    return str->data;
}

bool_t str_equals(const string_t* str0, const string_t* str1) {
    bool_t ret = FALSE;
    size_t length0 = str0->length;
    size_t length1 = str1->length;

    if (length0 == length1) {
        int i = 0;

        do {
            char c0 = get_char(str0, i);
            char c1 = get_char(str1, i);
            if (c0 != c1) {
                break;
            }

            i++;
        } while (i < length0);

        ret = (i == length0) ? (TRUE) : (FALSE);
    }

    return ret;
}
