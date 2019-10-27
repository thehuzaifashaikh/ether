#include "common.h"

void* 
xmalloc(size_t p_bytes) {
	void* memory = malloc(p_bytes);
	if (!memory) {
		printf("Error: not enough memory.\n");
		exit(3);
	}
	return memory;
}  

void*
xrealloc(void* p_ptr, size_t p_bytes) {
    p_ptr = realloc(p_ptr, p_bytes);
    if (!p_ptr) {
        printf("Error: not enough memory.\n");
        exit(2);
    }
    return p_ptr;
}

char*
read_file(const char* p_path) {
	FILE* file;
	file = fopen(p_path, "rb");

	if (!file) {
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	size_t file_bytes = ftell(file);
	rewind(file);
	char* file_contents = (char*)xmalloc(sizeof(char) * file_bytes + 1);
	size_t bytes_read = fread((void*)file_contents, 1, file_bytes, file);

	if (bytes_read != file_bytes) {
		free((void*)file_contents);
		fclose(file);
		return NULL;
	}

	file_contents[file_bytes] = '\0';
	fclose(file);
	return file_contents;
}
