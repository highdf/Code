#include "batch_test.h"
#include <stdio.h>

int main(int argc, char **args) {
	char *location = "batch_test.c -> main()";
	if (argc != 2) {
		handle_error(location, "Usage: ./out [unit or batch]");
	}

	string_t *arg = create_string(args[1]);
	string_t *value0 = create_string("unit");
	string_t *value1  = create_string("batch");

	if (str_equals (arg, value0) == TRUE) {
		unit ("test/testfiles/0");
	} if (str_equals(arg, value1) == TRUE) {
		batch_test();
	}

	return 0;
}

void unit (const char *file_name) {
	FILE *file = fopen(file_name, "r");
	FILE *target = fopen("test/target.c", "w");

	comment_processor(file, target);
}
bool_t equals_file(FILE *file0, FILE *file1) {
	char *locaton = "batch_test -> equals_file()";
	is_null(locaton, file0);
	is_null(locaton, file1);

	freopen(NULL, "r", file0);
	freopen(NULL, "r", file1);
	bool_t ret = FALSE;
	char c0 = fgetc(file0);
	char c1 = fgetc(file1);
	int row = 1;
	int column = 1;


	do {
		if (c0 != c1) {
			printf("row = %d, column = %d\n", row, column);
			printf("c0 = %c, c1 = %c\n", c0, c1);
			break;
		}
		if (c0 == '\n') {
			row ++;
			column  = 1;
		}
		column ++;
		c0 = fgetc(file0);
		c1 = fgetc(file1);
	} while (c0 != EOF && c1 != EOF);

	if (c0 == EOF && c1 == EOF) {
		ret = TRUE;
	}

	return ret;
}
void unit_test (FILE *src_file, FILE *target_file) {
	comment_processor(src_file, target_file);
}
void batch_test () {
	string_t *base_test_dir = create_string("test/testfiles/");
	string_t *base_expect_dir_name = create_string("test/expectfiles/");
	int error_number = 0;
	char *location = "batch_test.c -> main()";

	FILE *target = fopen("test/target.c", "w");
	is_null(location, target);

	for (int i = 0; i < TEST_FILE_NUMBER; i ++) {
		string_t *file_number = num_to_str(i);
		string_t *test_path = str_concat(base_test_dir, file_number);
		string_t *expect_path = str_concat(base_expect_dir_name, file_number);

		FILE *test_file = fopen(str_to_char_array(test_path), "r");
		FILE *expect_file = fopen(str_to_char_array(expect_path), "r");
		is_null(location, test_file);
		is_null(location, expect_file);

		unit_test(test_file, target);

		if (equals_file(expect_file, target) == FALSE) {
			error_number ++;
		}

		fclose(test_file);
		fclose(expect_file);
	}

	printf("[[ INFO ]]: test_example %d, error_number %d\n", TEST_FILE_NUMBER, error_number);
	fclose(target);
}
