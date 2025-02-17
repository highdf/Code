#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "error.h"
#include "bool.h"
#include "c/comment_processor_out.h"

#define TEST_FILE_NUMBER 1
#define COMMAND_SIZE 256

bool_t equals_file(FILE *file0, FILE *file1);
void unit_test (FILE *src_file, FILE *target_file);
void batch_test ();
void unit (const char *file_name);
