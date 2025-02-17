#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0

enum mode {
	NORMAL_MODE,
	CHAR_MODE,
	STRING_MODE,
	ESCAPE_MODE,
	PREFIX_COMMENT_MODE,
	LINE_COMMENT_MODE,
	NONE_MODE,
	BLOCK_COMMENT_MODE
};

enum mode update_mode (char c, enum mode last_mode);
enum mode update_str_mode(enum mode prev_mode);
enum mode update_char_mode(enum mode prev_mode);
enum mode update_comment_mode(enum mode prev_mode);
enum mode update_escape_mode(enum mode prev_mode);
void update_row(char c);
void update_column();
void hanlde_error(char *error_location, char *message);
char* create_and_init_buffer(FILE *file, int buffer_size);
int processor(char *buffer, int index, char *end_str);
int expect_next_char(char c, int index, enum mode prev_mode, FILE *file);
