#include "comment_processor_in.h"
#include "comment_processor_out.h"
#include <stdio.h>

int row = 1;
int column = 1;
int enable_mode_conn = FALSE;
enum mode current_mode = NORMAL_MODE;
char current_char = '\0';
char comment_mode = LINE_COMMENT_MODE;

FILE* comment_processor(FILE *source_file) {
	FILE *ret = NULL;

	if (source_file == NULL) {
		printf("Error: In the comment_processor():\n");
		printf("Argment is null\n");
	} else {
		ret = fopen("target.c", "w");
		enum mode prev_mode = current_mode;

		while (1) {
			int i = 0;
			char *buffer = create_and_init_buffer(source_file, BUFFER_SIZE);

			for (; buffer[i] != '\0' && buffer[i] != EOF; i ++) {
				current_char = buffer[i];

				// 更新注释模式 -> 判断是否为line_comment or blick_comment
				// 是：跳过这个字符 || 否：执行P0
				prev_mode = current_mode;
				current_mode = update_mode(current_char, prev_mode);

				if (current_mode == PREFIX_COMMENT_MODE) {
					char next_char = buffer[i+1];
					i = expect_next_char(next_char, i, prev_mode, ret);
				} else if (current_mode == ESCAPE_MODE) {
					fputc(current_char, ret);
					char next_char = buffer[i+1];
					i = expect_next_char(next_char, i, prev_mode, ret);
				} else {
					fputc(current_char, ret);
				}

				// printf("In the (%d, %d): mode = %d: char = %c\n", row, column, current_mode, current_char);

				update_row(current_char);
				update_column();
			}

			if (buffer[i] == EOF) {
				free(buffer);
				break;
			}
			free(buffer);
		}
	}

	return ret;
}

enum mode update_mode (char c, enum mode prev_mode) {
	enum mode ret = NORMAL_MODE;

	switch (c) {
		case '\'' : {
			ret = update_str_mode(prev_mode);
			break;
		}
		case '"': {
			ret = update_char_mode(prev_mode);
			break;
		}
		case '\\' : {
			ret = update_escape_mode(prev_mode);
			break;
		}
		case '/': {
			ret = update_comment_mode(prev_mode);
			break;
		}
		default: ret = prev_mode;
	}

	return ret;
}
enum mode update_str_mode(enum mode prev_mode) {
	enum mode ret = NORMAL_MODE;

	if (prev_mode == NORMAL_MODE) {
		ret = STRING_MODE;
	} else if (prev_mode == CHAR_MODE) {
		ret = CHAR_MODE;
	} else if (prev_mode == STRING_MODE) {
		ret = NORMAL_MODE;
	} else {
		hanlde_error("In the update_str_mode", "Don't have in the nromal, char, string mode");
		exit(1);
	}

	return ret;
}

enum mode update_char_mode(enum mode prev_mode) {
	enum mode ret = NORMAL_MODE;

	if (prev_mode == NORMAL_MODE) {
		ret = CHAR_MODE;
	} else if (prev_mode == STRING_MODE) {
		ret = STRING_MODE;
	} else if(prev_mode == CHAR_MODE) {
		ret = NORMAL_MODE;
	} else {
		hanlde_error("In the update_char_mode", "Don't have nromal, char, string mode");
		exit(1);
	}

	return ret;
}

enum mode update_comment_mode(enum mode prev_mode) {
	enum mode ret = NORMAL_MODE;

	if (prev_mode == NORMAL_MODE) {
		ret = PREFIX_COMMENT_MODE;
	} else if (prev_mode == CHAR_MODE || prev_mode == STRING_MODE) {
		ret = prev_mode;
	} else {
		hanlde_error("In the update_comment_mode", "Don't have normla, char, string mode");
		exit(1);
	}

	return ret;
}

enum mode update_escape_mode(enum mode prev_mode) {
	enum mode ret = NORMAL_MODE;

	if (prev_mode == STRING_MODE || prev_mode == CHAR_MODE) {
		ret = ESCAPE_MODE;
	} else {
		hanlde_error("In the update_escape_mode", "Don't have in char or string mode");
	}

	return ret;
}

void update_row(char c) {
	if (c == '\n') {
		row ++;
		column = 1;
	}
}

void update_column() {
	column ++;
}
void hanlde_error(char *error_location, char *message) {
	printf("Error: %s:\n", error_location);
	printf("In the (%d, %d): mode = %d: char = %c\n", row, column, current_mode, current_char);
	printf("Message: %s\n", message);
	exit(1);

}

char* create_and_init_buffer(FILE *file, int buffer_size) {
	char *buffer = (char*) malloc (buffer_size * sizeof(char) + 1);

	if (buffer == NULL) {
		hanlde_error("In the create_and_init_buffer", "Malloc buffer failed");
	} else {
		for (int i = 0; i < buffer_size; i ++) {
			char c = fgetc(file);

			buffer[i] = c;

			if (c == EOF) {
				break;
			}
		}
		buffer[buffer_size] = '\0';
	}

	return buffer;
}

int expect_next_char(char c, int index, enum mode prev_mode, FILE *file) {
	int new_index = index;

	if (current_mode == ESCAPE_MODE) {
		switch (c) {
			case '\0':
			case EOF: {
				enable_mode_conn = 1;
				break;
			}
			default: {
				fputc(c, file);
				current_mode = prev_mode;
				new_index ++;
			}
		}
	} else if (current_mode == PREFIX_COMMENT_MODE) {
		switch (c) {
			case '/':{
				comment_mode = LINE_COMMENT_MODE;
				current_mode = prev_mode;
				new_index ++;
				break;
			}
			case '*': {
				comment_mode = BLOCK_COMMENT_MODE;
				current_mode = prev_mode;
				new_index ++;
				break;
			}
			case '\0':
			case EOF: {
				enable_mode_conn = TRUE;
				break;
			}
			default: fputc('/', file);
		}
	} else {
		hanlde_error("In the expect_next_char", "current_mode's value is error");
	}

	return new_index;
}
