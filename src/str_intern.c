#include "buffer.h"
#include "common.h"
#include "str_intern.h"

const char* 
str_intern_range(const char* p_start, const char* p_end) {
    size_t len = p_end - p_start;
    for (size_t i = 0; i < buf_len(g_interns); i++) {
        if (g_interns[i].len == len && strncmp(g_interns[i].str, p_start, len) == 0) {
            return g_interns[i].str;
        }
    }

    char* str = xmalloc(len + 1);
    memcpy(str, p_start, len);
    str[len] = 0;
    buf_push(g_interns, ((InternStr){len, str}));
    return str;
}

const char* 
str_intern(const char* p_str) {
    return str_intern_range(p_str, p_str + strlen(p_str));
}

void
destroy_str_intern(void) {
	buf_free(g_interns);
}
