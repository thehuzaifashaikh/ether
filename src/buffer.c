#include "buffer.h"

void*
buf__grow(const void* p_buf, size_t p_new_len, size_t p_elem_size) {
    assert(buf_cap(p_buf) <= (__SIZE_MAX__ - 1) / 2);
    size_t new_cap = CLAMP_MIN(2 * buf_cap(p_buf), MAX(p_new_len, 16));
    assert(p_new_len <= new_cap);
    assert(new_cap <= (__SIZE_MAX__ - offsetof(BufHdr, buf)) / p_elem_size);
    size_t new_size = offsetof(BufHdr, buf) + (new_cap * p_elem_size);
    BufHdr* new_hdr;

    if (p_buf) {
        new_hdr = xrealloc(buf__hdr(p_buf), new_size);
    } else {
        new_hdr = xmalloc(new_size);
        new_hdr->len = 0;
    }

    new_hdr->cap = new_cap;
    return new_hdr->buf;
}
