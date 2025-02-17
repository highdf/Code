#include "string.h"

void info (string_t *str0, string_t *str1);

int main() {
	string_t *str1 = create_string("Hello");
	string_t *str2 = create_string("hello");
	string_t *str3 = create_string("hello");

	info(str1, str2);
	info(str2, str3);
	
	return 0;
}

void info (string_t *str0, string_t *str1) {
	if (str_equals(str0, str1) == TRUE) {
		printf("str1 == str2\n");
	} else {
		printf("str1 != str2\n");
	}
}
