#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "bool.h"

#define BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0

typedef enum mode {
	NORMAL_MODE,
	CHAR_MODE,
	STRING_MODE,
	PREFIX_COMMENT_MODE,
	ESCAPE_MODE,
	LINE_COMMENT_MODE,
	BLOCK_COMMENT_MODE
} char_mode_t;

typedef struct char_info {
	int row;
	int column;
	char current_char;
	char prev_char;
} char_info_t;

typedef struct char_object {
	char_info_t *info;
	char_mode_t current_char_mode;
	char_mode_t prev_char_mode;
	char_mode_t comment_mode;
} char_object_t;

typedef struct buffer {
	char *buffer;
	bool_t enable_conn;
	size_t conn_index;
	size_t index;
	size_t size;
} buffer_t;

void info();
char_mode_t enable_modes (char_object_t *object);
char_mode_t enable_prefix_comment_mode(char_object_t *object);
char_mode_t enable_char_mode(char_object_t *object);
char_mode_t enable_str_mode(char_object_t *object);
char_mode_t enable_escape_mode(char_object_t *object);
void init_file (FILE *src, FILE *target);
char_object_t* create_object ();
buffer_t* create_buffer ();
void read_to(FILE *src, buffer_t *buffer);;
char operate_buffer (buffer_t *buffer, char_object_t *object, FILE *file);
void update_object_mode (char_object_t *object);
void into_mode (char_object_t *object, FILE *file, buffer_t *buffer);
void update_char_info (char_info_t *info, char c);
char* get_char_info (char_object_t *object);
void close_comment_mode (char_object_t *object, buffer_t *buffer);
void jump_a_char(char_object_t *object, buffer_t *buffer);
void operate_next_hcar(char_object_t *object, buffer_t *buffer, FILE *file);
