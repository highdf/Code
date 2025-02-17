#include "comment_processor_in.h"
#include "comment_processor_out.h"

void comment_processor(FILE *source_file, FILE *targe_file) {

	if (source_file == NULL || targe_file == NULL) {
		printf("Error: In the comment_processor():\n");
		printf("Argment is null\n");
	} else {
		init_file(source_file, targe_file);
		char_object_t *object = create_object();
		buffer_t *buffer = create_buffer ();

		while (1) {
			read_to (source_file, buffer);
			char c = operate_buffer(buffer, object, targe_file);
			if (c == EOF) {
				break;
			}
		}

		free(object);
		free(buffer);
	}
}

char operate_buffer (buffer_t *buffer, char_object_t *object, FILE *file) {
	char ret = '\0';
	buffer -> index = 0;

	while (buffer -> index < buffer -> size) {
		char current_char = buffer -> buffer[buffer -> index];

		if (current_char == EOF) {
			ret = EOF;
			break;
		}

		update_char_info(object -> info, current_char);
		close_comment_mode(object, buffer);
		if (object -> comment_mode == NORMAL_MODE) {
			update_object_mode(object);
			into_mode (object, file, buffer);
		}
		buffer -> index ++;
	}

	return ret;
}

void into_mode (char_object_t *object, FILE *file, buffer_t *buffer) {
	if (object -> current_char_mode == PREFIX_COMMENT_MODE || object -> current_char_mode == ESCAPE_MODE) {
		operate_next_hcar(object, buffer, file);
	} else {
		fputc(object -> info -> current_char, file);
	}
}

void operate_next_hcar(char_object_t *object, buffer_t *buffer, FILE *file) {
	int next_char_index = buffer -> index + 1;

	if (next_char_index == buffer -> size) {
		buffer -> enable_conn = TRUE;
		buffer -> buffer[0] = object -> info -> current_char;
		buffer -> conn_index = 1;
		object -> current_char_mode = object -> prev_char_mode;
	} else if(next_char_index < buffer -> size && object -> current_char_mode == PREFIX_COMMENT_MODE) {
		char next_char = buffer -> buffer[next_char_index];
		switch (next_char) {
			case '/':{
				object -> comment_mode = LINE_COMMENT_MODE;
				object -> current_char_mode = object -> prev_char_mode;
				break;
			}
			case '*':{
				object -> comment_mode = BLOCK_COMMENT_MODE;
				object -> current_char_mode = object -> prev_char_mode;
				break;
			}
			default: {
				fputc(object -> info -> current_char, file);
			}
		}
	} else if(next_char_index < buffer -> size && object -> current_char_mode == ESCAPE_MODE) {
		char next_char = buffer -> buffer[next_char_index];
		fputc(object -> info -> current_char, file);

		buffer -> index ++;
		update_char_info(object -> info, next_char);
		fputc(next_char, file);
		object -> current_char_mode = object -> prev_char_mode;
	}
}
void close_comment_mode (char_object_t *object, buffer_t *buffer) {
	char_mode_t comment_mode = object -> comment_mode;
	char current_char = object -> info -> current_char;
	char prev_char = object -> info -> prev_char;

	if (comment_mode == LINE_COMMENT_MODE) {
		if (current_char == '\n') {
			object -> comment_mode = NORMAL_MODE;
		}
	} else if (comment_mode == BLOCK_COMMENT_MODE) {
		if (current_char == '/' && prev_char == '*') {
			object -> comment_mode = NORMAL_MODE;
			jump_a_char(object, buffer);
		}
	} else if (comment_mode != NORMAL_MODE) {
		char *str = get_char_info(object);
		sprintf(str, "close_comment_mode %s", str);
		handle_error(str, "comment_mode is invalid");
	}
}

void jump_a_char(char_object_t *object, buffer_t *buffer) {
	buffer -> index ++;
	char current_char = buffer -> buffer[buffer -> index];
	update_char_info(object -> info, current_char);
}

void update_object_mode (char_object_t *object) {

	object -> prev_char_mode = object -> current_char_mode;
	object -> current_char_mode = enable_modes (
		object
	);
}

void update_char_info (char_info_t *info, char c) {
	info -> prev_char = info -> current_char;
	info -> current_char = c;

	if (info -> current_char == '\n') {
		info -> row ++;
		info -> column = 0;
	} else {
		info -> column ++;
	}
}

char_object_t* create_object () {
	char_object_t *ret = (char_object_t*) malloc (sizeof(char_object_t));
	char_info_t *info = (char_info_t*) malloc (sizeof(char_info_t));

	is_null("comment_processor.c -> create_object()", ret);	
	is_null("comment_processor.c -> create_object()", info);	

	info -> row = 1;
	info -> column = 0;
	info -> current_char = '\0';
	info -> prev_char = '\0';

	ret -> info = info;
	ret -> current_char_mode = NORMAL_MODE;
	ret -> prev_char_mode = NORMAL_MODE;
	ret -> comment_mode = NORMAL_MODE;

	return ret;
}

void read_to(FILE *src, buffer_t *buffer) {
	int i = (buffer -> enable_conn == TRUE)? (buffer -> enable_conn = FALSE, buffer -> conn_index): (0);

	for (; i < buffer -> size; i ++) {
		char c = fgetc(src);
		buffer -> buffer[i] = c;

		if (c == EOF) {
			break;
		}
	}
}
buffer_t* create_buffer () {
	buffer_t *ret = (buffer_t*) malloc (sizeof(buffer_t));
	ret -> buffer = (char*) malloc (BUFFER_SIZE * sizeof(char));

	is_null("comment_processor.c -> create_buffer()", ret);
	is_null("comment_processor.c -> create_buffer()", ret -> buffer);

	ret -> index = 0;
	ret -> enable_conn = FALSE;
	ret -> size = BUFFER_SIZE;
	ret -> conn_index = 0;

	return ret;
}

char* get_char_info (char_object_t *object) {
	char* str = (char*) malloc (sizeof(char) * 256);

	sprintf(str, "[%d, %d] char = %c, mode = %d",
		 object -> info -> row,
		 object -> info -> column,
		 object -> info -> current_char, 
		 object -> current_char_mode
	);

	return str;
}
char_mode_t enable_modes (char_object_t *object) {
	char_mode_t ret = NORMAL_MODE;
	char c = object -> info -> current_char;
	char_mode_t prev_mode = object -> current_char_mode;

	switch (c) {
		case '\'' : {
			ret = enable_char_mode(object);
			break;
		}
		case '"': {
			ret = enable_str_mode(object);
			break;
		}
		case '/': {
			ret = enable_prefix_comment_mode(object);
			break;
		}
		case '\\': {
			ret = enable_escape_mode(object);
			break;
		}
		default: ret = prev_mode;
	}

	return ret;
}
char_mode_t enable_escape_mode(char_object_t *object) {
	char_mode_t ret = NORMAL_MODE;
	char_mode_t prev_mode = object -> current_char_mode;

	if (prev_mode == STRING_MODE || prev_mode == CHAR_MODE) {
		ret = ESCAPE_MODE;	
	} else {
		char *str = get_char_info(object);
		sprintf(str, "update_escape_mode: %s", str);
		handle_error(str, "Don't have in the normal, char, string mode");
	}

	return ret;
}

char_mode_t enable_str_mode(char_object_t *object) {
	char_mode_t ret = NORMAL_MODE;
	char_mode_t prev_mode = object -> current_char_mode;

	if (prev_mode == NORMAL_MODE) {
		ret = STRING_MODE;
	} else if (prev_mode == CHAR_MODE) {
		ret = CHAR_MODE;
	} else if (prev_mode != STRING_MODE) {
		char *str = get_char_info(object);
		sprintf(str, "update_str_mode: %s", str);
		handle_error(str, "Don't have in the normal, char, string mode");
	}

	return ret;
}

char_mode_t enable_char_mode(char_object_t *object) {
	char_mode_t ret = NORMAL_MODE;
	char_mode_t prev_mode = object -> current_char_mode;

	if (prev_mode == NORMAL_MODE) {
		ret = CHAR_MODE;
	} else if (prev_mode == STRING_MODE) {
		ret = STRING_MODE;
	} else if (prev_mode != CHAR_MODE) {
		char *str = get_char_info(object);
		sprintf(str, "update_char_mode: %s", str);
		handle_error(str, "Don't have in the normal, char, string mode");
	}

	return ret;
}

/*
	*
	*
	*
	*
	*
	*
	*
	*
*/
char_mode_t enable_prefix_comment_mode(char_object_t *object) {
	char_mode_t ret = NORMAL_MODE;
	char_mode_t prev_mode = object -> current_char_mode;

	if (prev_mode == NORMAL_MODE) {
		ret = PREFIX_COMMENT_MODE;
	} else if (prev_mode == CHAR_MODE || prev_mode == STRING_MODE) {
		ret = prev_mode;
	} else {
		char *str = get_char_info(object);
		sprintf(str, "update_prefix_comment_mode: %s", str);
		handle_error(str, "Don't have in the normal, char, string mode");
	}

	return ret;
}

// void update_comment_mode(char *buffer) {
// 	if (comment_mode == LINE_COMMENT_MODE && current_char == '\n') {
// 		comment_mode = NORMAL_MODE;
// 	} else if (comment_mode == BLOCK_COMMENT_MODE && current_char == '/') {
// 		switch (prev_char) {
// 			case '*': {
// 				comment_mode = NONE_MODE;
// 				update_current_char(buffer, ++ buffer_i);
// 				break;
// 			}
// 			default:{
// 				printf("char = %c\n", prev_char);
// 			}
//
// 		}
// 	}
// }

// void update_current_char(char *buffer, int index) {
// 	current_char = buffer[index];
// }

// void update_row() {
// 	if (current_char == '\n') {
// 		row ++;
// 	}
// }

// void update_column() {
// 	if (current_char == '\n') {
// 		column = 1;
// 	} else {
// 		column ++;
// 	}
// }

// char* create_and_init_buffer(FILE *file, int buffer_size) {
// 	char *buffer = (char*) malloc (buffer_size * sizeof(char) + 1);
//
// 	if (buffer == NULL) {
// 		hanlde_error("create_and_init_buffer", "Malloc buffer failed");
// 	} else {
// 		for (int i = 0; i < buffer_size; i ++) {
// 			char c = fgetc(file);
//
// 			buffer[i] = c;
//
// 			if (c == EOF) {
// 				break;
// 			}
// 		}
// 		buffer[buffer_size] = '\0';
// 	}
//
// 	return buffer;
// }

// void expect_next_char(char c, char_mode_t prev_mode, FILE *file) {
// 	if (current_mode == PREFIX_COMMENT_MODE) {
// 		switch (c) {
// 			case '/':{
// 				comment_mode = LINE_COMMENT_MODE;
// 				current_mode = prev_mode;
// 				buffer_i ++;
// 				break;
// 			}
// 			case '*': {
// 				comment_mode = BLOCK_COMMENT_MODE;
// 				current_mode = prev_mode;
// 				buffer_i ++;
// 				break;
// 			}
// 			case '\0':
// 			case EOF: {
// 				enable_mode_conn = TRUE;
// 				break;
// 			}
// 			default: {
// 				fputc('/', file);
// 				current_mode = prev_mode;
// 			}
// 		}
// 	} else if (current_mode == ESCAPE_MODE) {
// 		switch (c) {
// 			case '\0':
// 			case EOF: {
// 				enable_mode_conn = TRUE;
// 				break;
// 			}
// 			default: {
// 				fputc(c, file);
// 				current_mode = prev_mode;
// 				buffer_i ++;
// 			}
// 		}
// 	}else {
// 		hanlde_error("expect_next_char", "current_mode's value is error");
// 	}
//
// 	// if (current_mode == ESCAPE_MODE) {
// 	// 	switch (c) {
// 	// 		case '\0':
// 	// 		case EOF: {
// 	// 			enable_mode_conn = 1;
// 	// 			break;
// 	// 		}
// 	// 		default: {
// 	// 			fputc(c, file);
// 	// 			current_mode = prev_mode;
// 	// 			new_index ++;
// 	// 		}
// 	// 	}
// 	// } else 
// 	//
// 	//
// }

void init_file (FILE *src, FILE *target) {
	freopen(NULL, "r", src);
	freopen(NULL, "w", target);
}
