
#define SLJIT_CONFIG_AUTO 1
#include "../sljit/sljitLir.h"

#if !defined(SLJIT_64BIT_ARCHITECTURE)
#error Architecture shoule be 64bit.
#endif

static inline struct sljit_compiler *new_compiler(void)
{
    return sljit_create_compiler(NULL);
}

static inline void *finalize_code(struct sljit_compiler *C)
{
    void *code = sljit_generate_code(C);
    sljit_free_compiler(C);
    return code;
}

static inline void free_code(void *code)
{
    sljit_free_code(code);
}

static inline void jit_run(struct sljit_compiler *C)
{
    void *code = finalize_code(C);
    sljit_free_code(code);
}
