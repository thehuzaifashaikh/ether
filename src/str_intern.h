#ifndef STR_INTERN_H
#define STR_INTERN_H

typedef struct InternStr {
    size_t len;
    const char* str;
} InternStr;

static InternStr* g_interns;

const char* str_intern_range(const char* p_start, const char* p_end);
const char* str_intern(const char* p_str);
void destroy_str_intern(void);

#endif // STR_INTERN_H
