#include "../include/jit.h"

/* cl /I ..\sljit /DSLJIT_CONFIG_AUTO=1 add3.c ..\sljit\sljitLir.c */

typedef void (*func_t)(); 

static inline void print_reg(int type, int n, int value)
{
    printf("%c%d = %d\n", type, n, value);
}

void gen_print_code(struct sljit_compiler *C, int type, int n, int reg)
{
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_R0, 0, SLJIT_IMM, type);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_R1, 0, SLJIT_IMM, n);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_R2, 0, reg, 0);
    sljit_emit_icall(C, SLJIT_CALL,
                        SLJIT_RET(SW) | SLJIT_ARG1(SW) | SLJIT_ARG2(SW) | SLJIT_ARG3(SW),
                        SLJIT_IMM, SLJIT_FUNC_OFFSET(print_reg));
}

func_t generate_code(struct sljit_compiler *C)
{
    /* To support almost all architechtures */
    sljit_emit_enter(C, 0, 0,
        6,  /* scratch  : temporary R0-R5   */
        6,  /* saved    : safety    S0-S5   */
        6,  /* fscratch : temporary FR0-FR5 */
        0,  /* fsaved   : safety    -       */
        0   /* local    :                   */
    );

    /* Registers check */
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_R3, 0, SLJIT_IMM, 13);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_R4, 0, SLJIT_IMM, 14);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_R5, 0, SLJIT_IMM, 15);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_S0, 0, SLJIT_IMM, 20);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_S1, 0, SLJIT_IMM, 21);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_S2, 0, SLJIT_IMM, 22);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_S3, 0, SLJIT_IMM, 23);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_S4, 0, SLJIT_IMM, 24);
    sljit_emit_op1(C, SLJIT_MOV, SLJIT_S5, 0, SLJIT_IMM, 25);

    gen_print_code(C, 'r', 3, SLJIT_R3);
    gen_print_code(C, 'r', 4, SLJIT_R4);
    gen_print_code(C, 'r', 5, SLJIT_R5);
    gen_print_code(C, 's', 1, SLJIT_S1);
    gen_print_code(C, 's', 2, SLJIT_S2);
    gen_print_code(C, 's', 3, SLJIT_S3);
    gen_print_code(C, 's', 3, SLJIT_S3);
    gen_print_code(C, 's', 4, SLJIT_S4);
    gen_print_code(C, 's', 5, SLJIT_S5);

    /* end of code */
    sljit_emit_return(C, SLJIT_MOV, SLJIT_R0, 0);
    return (func_t)finalize_code(C);
}

int main(void)
{
    /* set up */
    struct sljit_compiler *C = new_compiler();

    /* generate code */
    func_t code = generate_code(C);
    code();

    /* clean up */
    free_code(code);
    return 0;
}
