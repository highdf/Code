#include "main.h"

int main() {
	FILE *file = fopen("c/comment_processor.c", "r");

	if (file != NULL) {
		FILE *output = comment_processor(file);

	} else {
		printf("Opne source.c faled\n");
	}

	return 0;
}
