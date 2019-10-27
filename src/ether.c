#include "buffer.h"
#include "common.h"
#include "str_intern.h"

int 
main() {
	char* file = read_file("res/hello_world.eth");
	if (file) {
		printf("%s\n", file);
	}
	free((void*)file);

	destroy_str_intern();
}
