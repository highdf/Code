#include "main.h"

int main() {
	// FILE *file = fopen("c/comment_processor.c", "r");
	FILE *file = fopen("main.c", "r");

	/* ksfjakjsdddd
	*/
	if (file != NULL) {
		FILE *output = comment_processor(file);

	} else {
		printf("Opne source.c faled\n");
	}

	return 0;
}
