#include "error.h"

void handle_error(const char *location, const char *message) {
	printf("Error: In the %s\nMessage: %s\n", location, message);
	exit(1);
}
void is_null (const char *location, const void *pointer) {
	if (pointer == NULL) {
		handle_error(location, "Pointer is NULL");
	}
}
