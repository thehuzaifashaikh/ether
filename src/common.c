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
