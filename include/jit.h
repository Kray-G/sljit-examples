
#define SLJIT_CONFIG_AUTO 1
#include "../sljit/sljitLir.h"
#include "../udis86/udis86.h"

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

static inline int get_code_code(struct sljit_compiler *C)
{
    return sljit_get_generated_code_size(C);
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

static inline int disasm_hex(struct ud* u) 
{
    int count = 0;
    if (!u->error) {
        const unsigned char *src_ptr = ud_insn_ptr(u);
        for (int i = 0; i < ud_insn_len(u) && i < sizeof(u->insn_hexcode) / 2; ++i, ++src_ptr) {
            printf(" %02x", *src_ptr & 0xFF);
            ++count;
        }
        for (int i = 0, s = 12 - count; i < s; ++i) {
            printf("   ");
        }
    }
    return count;
}

static inline void disasm_code(void *code, int size)
{
    ud_t ud_obj;

    ud_init(&ud_obj);
    ud_set_input_buffer(&ud_obj, code, size);
    ud_set_mode(&ud_obj, 64);
    ud_set_syntax(&ud_obj, UD_SYN_INTEL);

    uint8_t *adr = code;
    while (ud_disassemble(&ud_obj)) {
        printf("%p", adr);
        adr += disasm_hex(&ud_obj);
        printf("\t%s\n", ud_insn_asm(&ud_obj));
    }
}
